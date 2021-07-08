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
#include <functional>
#include <math.h>
#include <ostream>
#include <stdio.h>
#include <vector>

namespace vepp {

template <class T> class VecN {
  /** holds the vector data*/
  std::vector<T> vdata;

public:
  /*! Tested */
  VecN() {}
  /*! Tested */
  VecN(const std::vector<T> &vd) : vdata(vd) {}
  /*! Tested */
  VecN(unsigned int s) {

    vdata.clear();
    vdata.resize(static_cast<std::size_t>(s));
    for (unsigned int i = 0; i < s; i++) {
      vdata[i] = static_cast<T>(0);
    }
  }
  /*! Tested */
  bool size(unsigned int &out) const {
    out = static_cast<unsigned int>(vdata.size());
    return true;
  }
  /*! Tested */
  bool get(unsigned int index, T &out) const {
    if (index >= vdata.size()) {
      return false;
    }
    out = vdata[index];
    return true;
  }
  /*! Tested */
  bool set(unsigned int index, T el) {
    if (index >= vdata.size()) {
      return false;
    }
    vdata[index] = el;
    return true;
  }
  /*! Tested */
  static bool base(unsigned int nb_dimensions, unsigned int base_order,
                   std::vector<T> &out) {
    if (base_order >= nb_dimensions)
      return false;
    //
    if (out.size() != nb_dimensions) {
      out.clear();
      out.resize(static_cast<std::size_t>(nb_dimensions));
    }
    for (unsigned int i = 0; i < nb_dimensions; i++) {
      out[i] = static_cast<T>(0);
    }
    out[base_order] = static_cast<T>(1);
    return true;
  }
  /*! Tested */
  static bool base(unsigned int nb_dimensions, unsigned int base_order,
                   VecN<T> &vout) {
    std::vector<T> out;
    bool result = VecN<T>::base(nb_dimensions, base_order, out);
    if (result == false)
      return result;
    vout = VecN<T>(out);
    return true;
  }
  bool apply_el(T v, std::vector<T> &out,
                const std::function<T(T, T)> &fn) const {
    if (out.size() != vdata.size()) {
      out.resize(vdata.size());
    }
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = fn(vdata[i], v);
    }
    return true;
  }
  bool apply_el(const std::vector<T> &v, std::vector<T> &out,
                const std::function<T(T, T)> &fn) const {
    if (v.size() != vdata.size())
      return false;
    if (vdata.size() != out.size()) {
      out.resize(vdata.size());
    }
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = fn(vdata[i], v[i]);
    }
    return true;
  }
  bool apply_el(T v, VecN<T> &vout, const std::function<T(T, T)> &fn) const {
    std::vector<T> out;
    bool result = apply_el(v, out, fn);
    if (result == false)
      return result;
    vout = VecN<T>(out);
    return true;
  }
  bool apply_el(const VecN<T> &v, VecN<T> &vout,
                const std::function<T(T, T)> &fn) const {
    unsigned int vsize;
    v.size(vsize);
    if (vsize != vdata.size())
      return false;
    vout.size(vsize);
    if (vsize != vdata.size()) {
      vout = VecN<T>(static_cast<unsigned int>(vdata.size()));
    }
    for (unsigned int i = 0; i < vdata.size(); i++) {
      T tout = static_cast<T>(0);
      v.get(i, tout);
      vout.set(i, fn(vdata[i], tout));
    }
    return true;
  }
  /*! Tested */
  bool add(T v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, out, fn);
  }

  /*! Tested */
  bool add(T v, VecN<T> &vout) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  bool add(const std::vector<T> &v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  bool add(const VecN<T> &v, VecN<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel + argel; };
    return apply_el(v, out, fn);
  }
  //
  bool subtract(T v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  bool subtract(T v, VecN<T> &vout) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  bool subtract(const std::vector<T> &v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  bool subtract(const VecN<T> &v, VecN<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel - argel; };
    return apply_el(v, out, fn);
  }
  //
  bool multiply(T v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  bool multiply(T v, VecN<T> &vout) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  bool multiply(const std::vector<T> &v, std::vector<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  bool multiply(const VecN<T> &v, VecN<T> &out) const {
    auto fn = [](T thisel, T argel) { return thisel * argel; };
    return apply_el(v, out, fn);
  }

  //
  bool divide(T v, std::vector<T> &out) const {
    if (v == static_cast<T>(0))
      return false;

    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  bool divide(T v, VecN<T> &vout) const {
    // check for zero division
    if (v == static_cast<T>(0))
      return false;
    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, vout, fn);
  }
  /*! Tested */
  bool divide(const std::vector<T> &v, std::vector<T> &out) const {
    for (unsigned int j = 0; j < v.size(); j++) {
      if (v[j] == static_cast<T>(0))
        return false;
    }
    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, out, fn);
  }
  /*! Tested */
  bool divide(const VecN<T> &v, VecN<T> &out) const {
    unsigned int vsize = 0;
    v.size(vsize);
    // check zero division
    for (unsigned int j = 0; j < vsize; j++) {
      T vout = static_cast<T>(0);
      v.get(j, vout);
      if (vout == static_cast<T>(0))
        return false;
    }
    auto fn = [](T thisel, T argel) { return thisel / argel; };
    return apply_el(v, out, fn);
  }
  bool dot(const T &v, T &out) const {
    out = static_cast<T>(0);
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out += vdata[i] * v;
    }
    return true;
  }
  bool dot(const std::vector<T> &v, T &out) const {
    if (v.size() != vdata.size())
      return false;
    out = static_cast<T>(0);
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out += vdata[i] * v[i];
    }
    return true;
  }
  bool dot(const VecN<T> &v, T &out) const {

    unsigned int vsize = 0;
    v.size(vsize);
    // check size
    if (vsize != vdata.size())
      return false;

    out = static_cast<T>(0);
    for (unsigned int i = 0; i < vdata.size(); i++) {
      T tout = static_cast<T>(0);
      v.get(i, tout);
      out += vdata[i] * tout;
    }
    return true;
  }

  // bool cross(const std::vector<T> &v, std::vector<T>
  // &out) const {}

private:
  bool n_n_matrix(unsigned int n, std::vector<std::vector<T>> &out) const {
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
    return true;
  }
};
} // namespace vepp

#endif
