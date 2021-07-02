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
  VecN(const std::vector<T> &vd) {
    vdata.clear();
    vdata.resize(vd.size());
    for (unsigned int i = 0; i < vd.size(); i++) {
      vdata[i] = vd[i];
    }
  }
  /*! Tested */
  VecN(unsigned int s) {

    vdata.clear();
    vdata.resize(static_cast<std::size_t>(s));
    for (unsigned int i = 0; i < s; i++) {
      vdata[i] = static_cast<T>(0);
    }
  }
  /*! Tested */
  std::size_t size() const { return vdata.size(); }
  /*! Tested */
  bool get(unsigned int index, T &out) const {
    if (index >= size()) {
      return false;
    }
    out = vdata[index];
    return true;
  }
  /*! Tested */
  bool set(unsigned int index, T el) {
    if (index >= size()) {
      return false;
    }
    vdata[index] = el;
    return true;
  }
  /*! Tested */
  static bool base(unsigned int nb_dimensions,
                   unsigned int base_order,
                   std::vector<T> &out) {
    if (base_order >= nb_dimensions)
      return false;
    //
    out.clear();
    out.resize(static_cast<std::size_t>(nb_dimensions));
    for (unsigned int i = 0; i < nb_dimensions; i++) {
      out[i] = static_cast<T>(0);
    }
    out[base_order] = static_cast<T>(1);
    return true;
  }
  /*! Tested */
  static bool base(unsigned int nb_dimensions,
                   unsigned int base_order, VecN<T> &vout) {
    std::vector<T> out;
    bool result =
        VecN<T>::base(nb_dimensions, base_order, out);
    if (result == false)
      return result;
    vout = VecN<T>(out);
    return true;
  }
  /*! Tested */
  bool add(T v, std::vector<T> &out) const {
    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] + v;
    }
    return true;
  }
  /*! Tested */
  bool add(T v, VecN<T> &vout) const {
    std::vector<T> out;
    bool result = add(v, out);
    if (result == false)
      return result;
    vout = VecN<T>(out);
    return true;
  }
  /*! Tested */
  bool add(const std::vector<T> &v,
           std::vector<T> &out) const {
    if (v.size() != vdata.size())
      return false;
    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] + v[i];
    }
    return true;
  }
  /*! Tested */
  bool add(const VecN<T> &v, VecN<T> &out) const {
    if (v.size() != vdata.size())
      return false;
    out = VecN<T>(static_cast<unsigned int>(vdata.size()));
    for (unsigned int i = 0; i < vdata.size(); i++) {
      T vout = static_cast<T>(0);
      v.get(i, vout);
      out.set(i, vdata[i] + vout);
    }
    return true;
  }

  //
  bool subtract(T v, std::vector<T> &out) const {
    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] - v;
    }
    return true;
  }
  bool subtract(const std::vector<T> &v,
                std::vector<T> &out) const {
    if (v.size() != vdata.size())
      return false;
    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] - v;
    }
    return true;
  }
  bool multiply(T v, std::vector<T> &out) const {
    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] * v;
    }
    return true;
  }
  bool multiply(std::vector<T> &v,
                std::vector<T> &out) const {
    if (v.size() != vdata.size())
      return false;

    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] * v;
    }
    return true;
  }
  bool divide(T v, std::vector<T> &out) const {
    if (v == static_cast<T>(0))
      return false;
    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] / v;
    }
    return true;
  }
  bool divide(const std::vector<T> &v,
              std::vector<T> &out) const {
    if (v.size() != vdata.size())
      return false;

    for (unsigned int j = 0; j < v.size(); j++) {
      if (v[j] == static_cast<T>(0))
        return false;
    }
    out.resize(vdata.size());
    for (unsigned int i = 0; i < vdata.size(); i++) {
      out[i] = vdata[i] / v[i];
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
};
}

#endif
