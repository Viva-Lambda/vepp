/*
MIT License

Copyright (c) 2021 Viva Lambda email
<76657254+Viva-Lambda@users.noreply.github.com>

Permission is hereby granted, free of charge, to any person
obtaining a copy
of this software and associated documentation files (the
"Software"), to deal
in the Software without restriction, including without
limitation the rights
to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall
be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef VEPP_HPP
#define VEPP_HPP
#include <array>
#include <cstdint>
#include <functional>
#include <math.h>
#include <ostream>
#include <stdio.h>
#include <vector>

namespace vepp {

/** VecN operator flags*/
enum VECN_FLAG : std::uint_least8_t {
  SUCCESS = 1,
  SIZE_ERROR = 2,
  INDEX_ERROR = 3,
  INCORRECT_ARG_ERROR = 4
};
std::ostream &operator<<(std::ostream &out, const VECN_FLAG &flag) {
  switch (flag) {
  case SUCCESS: {
    out << "SUCCESS";
    break;
  }
  case INDEX_ERROR: {
    out << "INDEX_ERROR";
    break;
  }
  case INCORRECT_ARG_ERROR: {
    out << "INCORRECT_ARG_ERROR";
    break;
  }
  case SIZE_ERROR: {
    out << "SIZE_ERROR";
    break;
  }
  }
  return out;
}

template <class T, std::size_t N> class VecN {
  /** holds the vector data*/
  std::array<T, N> data;

public:
  /*! Tested */
  VecN() {}
  /*! Tested */
  VecN(const std::vector<T> &vd) {
    unsigned int nb_s =
        vd.size() < N ? static_cast<unsigned int>(vd.size()) : N;
    for (unsigned int i = 0; i < nb_s; i++) {
      data[i] = vd[i];
    }
  } /*! Tested */
  VecN(unsigned int s) {
    unsigned int nb_s = s < N ? s : N;
    for (unsigned int i = 0; i < nb_s; i++) {
      data[i] = static_cast<T>(0);
    }
  }
  /*! Tested */
  VECN_FLAG size(unsigned int &out) const {
    out = static_cast<unsigned int>(data.size());
    return SUCCESS;
  }
  /*! Tested */
  VECN_FLAG get(unsigned int index, T &out) const {
    if (index >= data.size()) {
      return INDEX_ERROR;
    }
    out = data[index];
    return SUCCESS;
  }
  /*! Tested */
  VECN_FLAG set(unsigned int index, T el) {
    if (index >= data.size()) {
      return INDEX_ERROR;
    }
    data[index] = el;
    return SUCCESS;
  }
  /*! Tested */
  static VECN_FLAG base(unsigned int nb_dimensions, unsigned int base_order,
                        std::vector<T> &out) {
    if (base_order >= nb_dimensions)
      return INCORRECT_ARG_ERROR;
    //
    if (out.size() != nb_dimensions) {
      out.clear();
      out.resize(static_cast<std::size_t>(nb_dimensions));
    }
    for (unsigned int i = 0; i < nb_dimensions; i++) {
      out[i] = static_cast<T>(0);
    }
    out[base_order] = static_cast<T>(1);
    return SUCCESS;
  }
  /*! Tested */
  static VECN_FLAG base(unsigned int base_order, VecN<T, N> &vout) {
    std::vector<T> out;
    VECN_FLAG result =
        VecN<T, N>::base(static_cast<unsigned int>(N), base_order, out);
    if (result != SUCCESS)
      return result;
    vout = VecN<T, N>(out);
    return SUCCESS;
  }
  VECN_FLAG apply_el(T v, std::vector<T> &out,
                     const std::function<T(T, T)> &fn) const {
    if (out.size() != data.size()) {
      out.resize(data.size());
    }
    for (unsigned int i = 0; i < data.size(); i++) {
      out[i] = fn(data[i], v);
    }
    return SUCCESS;
  }
  VECN_FLAG apply_el(const std::vector<T> &v, std::vector<T> &out,
                     const std::function<T(T, T)> &fn) const {
    if (v.size() != data.size())
      return SIZE_ERROR;
    if (data.size() != out.size()) {
      out.resize(data.size());
    }
    for (unsigned int i = 0; i < data.size(); i++) {
      out[i] = fn(data[i], v[i]);
    }
    return SUCCESS;
  }
  VECN_FLAG apply_el(T v, VecN<T, N> &vout,
                     const std::function<T(T, T)> &fn) const {
    std::vector<T> out;
    VECN_FLAG result = apply_el(v, out, fn);
    if (result != SUCCESS)
      return result;
    vout = VecN<T, N>(out);
    return SUCCESS;
  }
  VECN_FLAG apply_el(const VecN<T, N> &v, VecN<T, N> &vout,
                     const std::function<T(T, T)> &fn) const {
    unsigned int vsize;
    v.size(vsize);
    if (vsize != data.size())
      return SIZE_ERROR;
    vout.size(vsize);
    if (vsize != data.size()) {
      vout = VecN<T, N>(static_cast<unsigned int>(data.size()));
    }
    for (unsigned int i = 0; i < data.size(); i++) {
      T tout = static_cast<T>(0);
      v.get(i, tout);
      vout.set(i, fn(data[i], tout));
    }
    return SUCCESS;
  }
  /*! Tested */
  VECN_FLAG add(T v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, out, fn);
  }

  /*! Tested */
  VECN_FLAG add(T v, VecN<T, N> &vout) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  VECN_FLAG add(const std::vector<T> &v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  VECN_FLAG add(const VecN<T, N> &v, VecN<T, N> &out) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, out, fn);
  }
  //
  VECN_FLAG subtract(T v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  VECN_FLAG subtract(T v, VecN<T, N> &vout) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  VECN_FLAG subtract(const std::vector<T> &v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  VECN_FLAG subtract(const VecN<T, N> &v, VecN<T, N> &out) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, out, fn);
  }
  //
  VECN_FLAG multiply(T v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  VECN_FLAG multiply(T v, VecN<T, N> &vout) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  VECN_FLAG multiply(const std::vector<T> &v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  VECN_FLAG multiply(const VecN<T, N> &v, VecN<T, N> &out) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, out, fn);
  }

  //
  VECN_FLAG divide(T v, std::vector<T> &out) const {
    if (v == static_cast<T>(0))
      return INCORRECT_ARG_ERROR;

    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  VECN_FLAG divide(T v, VecN<T, N> &vout) const {
    // check for zero division
    if (v == static_cast<T>(0))
      return INCORRECT_ARG_ERROR;
    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  VECN_FLAG divide(const std::vector<T> &v, std::vector<T> &out) const {
    for (unsigned int j = 0; j < v.size(); j++) {
      if (v[j] == static_cast<T>(0))
        return INCORRECT_ARG_ERROR;
    }
    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  VECN_FLAG divide(const VecN<T, N> &v, VecN<T, N> &out) const {
    unsigned int vsize = 0;
    v.size(vsize);
    // check zero division
    for (unsigned int j = 0; j < vsize; j++) {
      T vout = static_cast<T>(0);
      v.get(j, vout);
      if (vout == static_cast<T>(0))
        return INCORRECT_ARG_ERROR;
    }
    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, out, fn);
  }
  VECN_FLAG dot(const T &v, T &out) const {
    out = static_cast<T>(0);
    for (unsigned int i = 0; i < data.size(); i++) {
      out += data[i] * v;
    }
    return SUCCESS;
  }
  VECN_FLAG dot(const std::vector<T> &v, T &out) const {
    if (v.size() != data.size())
      return SIZE_ERROR;
    out = static_cast<T>(0);
    for (unsigned int i = 0; i < data.size(); i++) {
      out += data[i] * v[i];
    }
    return SUCCESS;
  }
  VECN_FLAG dot(const VecN<T, N> &v, T &out) const {

    unsigned int vsize = 0;
    v.size(vsize);
    // check size
    if (vsize != data.size())
      return SIZE_ERROR;

    out = static_cast<T>(0);
    for (unsigned int i = 0; i < data.size(); i++) {
      T tout = static_cast<T>(0);
      v.get(i, tout);
      out += data[i] * tout;
    }
    return SUCCESS;
  }

  // bool cross(const std::vector<T> &v, std::vector<T>
  // &out) const {}

private:
  VECN_FLAG n_n_matrix(unsigned int n, std::vector<std::vector<T>> &out) const {
    std::vector<std::vector<T>> mat;
    mat.resize(n);
    for (unsigned int i = 0; i < n; i++) {
      std::vector<T> row;
      row.resize(n);
      mat[i] = row;
      for (unsigned int j = 0; j < n; j++) {
        mat[i][j] = static_cast<T>(0);
      }
    }
    out = mat;
    return SUCCESS;
  }
};

#define CHECK(call)                                                            \
  do {                                                                         \
    VECN_FLAG res = call;                                                      \
    return res == SUCCESS;                                                     \
  } while (0)

#define INFO(call)                                                             \
  do {                                                                         \
    VECN_FLAG res = call;                                                      \
    switch (res) {                                                             \
    case SUCCESS: {                                                            \
      break;                                                                   \
    }                                                                          \
    case SIZE_ERROR: {                                                         \
      std::cout << "SIZE_ERROR "                                               \
                << " :: " << __FILE__ << " :: " << __LINE__ << std::endl;      \
    }                                                                          \
    case INDEX_ERROR: {                                                        \
      std::cout << "INDEX_ERROR at "                                           \
                << " :: " << __FILE__ << " :: " << __LINE__ << std::endl;      \
    }                                                                          \
    case INCORRECT_ARG_ERROR: {                                                \
      std::cout << "INCORRECT_ARG_ERROR at "                                   \
                << " :: " << __FILE__ << " :: " << __LINE__ << std::endl;      \
    }                                                                          \
    }                                                                          \
    return res;                                                                \
  } while (0)

#define INFO_VERBOSE(call)                                                     \
  do {                                                                         \
    VECN_FLAG res = call;                                                      \
    switch (res) {                                                             \
    case SUCCESS: {                                                            \
      std::cout << "SUCCESS" << std::endl;                                     \
      break;                                                                   \
    }                                                                          \
    case SIZE_ERROR: {                                                         \
      std::cout << "SIZE_ERROR "                                               \
                << " :: " << __FILE__ << " :: " << __LINE__ << std::endl;      \
    }                                                                          \
    case INDEX_ERROR: {                                                        \
      std::cout << "INDEX_ERROR "                                              \
                << " :: " << __FILE__ << " :: " << __LINE__ << std::endl;      \
    }                                                                          \
    case INCORRECT_ARG_ERROR: {                                                \
      std::cout << "INCORRECT_ARG_ERROR "                                      \
                << " :: " << __FILE__ << " :: " << __LINE__ << std::endl;      \
    }                                                                          \
    }                                                                          \
    return res;                                                                \
  } while (0)

} // namespace vepp

#endif
