// test file for quaternion
#include "../vepp.hpp"
#include <ctest.h>

/*! @{
 */

typedef float real;
using namespace vepp;
/*! @{ testing constructors for the vector
 */

CTEST(suite, test_empty_constructor) {
  VecN<real> v;
  unsigned int vsize = 5;
  v.size(vsize);
  ASSERT_EQUAL(vsize, static_cast<unsigned int>(0));
}

CTEST(suite, test_vector_constructor) {
  std::vector<real> tvec;
  tvec.resize(5);
  real v1 = static_cast<real>(-21);
  real v2 = static_cast<real>(1);
  real v3 = static_cast<real>(2);
  real v4 = static_cast<real>(1.53);
  real v5 = static_cast<real>(3);
  tvec[0] = v1;
  tvec[1] = v2;
  tvec[2] = v3;
  tvec[3] = v4;
  tvec[4] = v5;
  VecN<real> v(tvec);
  real t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;
  // test size
  unsigned int vsize = 6156;
  v.size(vsize);
  ASSERT_EQUAL(vsize, 5);

  // test values
  // first value
  ASSERT_EQUAL(v.get(0, t1), true);
  ASSERT_EQUAL(t1, v1);

  // second value
  ASSERT_EQUAL(v.get(1, t2), true);
  ASSERT_EQUAL(t2, v2);
  // third value

  ASSERT_EQUAL(v.get(2, t3), true);
  ASSERT_EQUAL(t3, v3);

  // fourth value
  ASSERT_EQUAL(v.get(3, t4), true);
  ASSERT_EQUAL(t4, v4);

  // fifth value
  ASSERT_EQUAL(v.get(4, t5), true);
  ASSERT_EQUAL(t5, v5);

  // sixth value
  ASSERT_EQUAL(v.get(5, t6), false);
}

CTEST(suite, test_dimension_constructor) {
  VecN<real> v(5);
  real v1 = static_cast<real>(0);
  real v2 = static_cast<real>(0);
  real v3 = static_cast<real>(0);
  real v4 = static_cast<real>(0);
  real v5 = static_cast<real>(5);
  // test values
  real t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = v5, t6 = 0;
  // first value
  ASSERT_EQUAL(v.get(0, t1), true);
  ASSERT_EQUAL(t1, v1);

  // second value
  ASSERT_EQUAL(v.get(1, t2), true);
  ASSERT_EQUAL(t2, v2);
  // third value

  ASSERT_EQUAL(v.get(2, t3), true);
  ASSERT_EQUAL(t3, v3);

  // fourth value
  ASSERT_EQUAL(v.get(3, t4), true);
  ASSERT_EQUAL(t4, v4);

  // fifth value

  ASSERT_EQUAL(v.set(4, v5), true);
  ASSERT_EQUAL(t5, v5);

  // sixth value
  ASSERT_EQUAL(v.get(5, t6), false);
  ASSERT_EQUAL(v.set(5, t6), false);
}

/*! @} */

/*! @{ testing base dimensions for the vector
 */
CTEST(suite, test_to_base_dimensions_vector) {
  //
  std::vector<real> out;
  VecN<real>::base(6, 1, out);
  ASSERT_EQUAL(out[1], static_cast<real>(1));
}
CTEST(suite, test_to_base_dimensions_vecn) {
  //
  VecN<real> vout;
  VecN<real>::base(6, 1, vout);
  real tout = 0;
  ASSERT_EQUAL(vout.get(1, tout), true);
  ASSERT_EQUAL(tout, static_cast<real>(1));
}

/*! @} */

/*! @{ testing summation for the vector
 */
CTEST(suite, test_add_scalar_vector) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  bool result = v.add(1, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], 2);
  ASSERT_EQUAL(out[1], 3);
  ASSERT_EQUAL(out[2], 4);
  ASSERT_EQUAL(out[3], 3);
  ASSERT_EQUAL(out[4], 2);
}
CTEST(suite, test_add_scalar_vecn) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  VecN<real> out;
  bool result = v.add(1, out);
  ASSERT_EQUAL(result, true);
  real t = static_cast<real>(0);
  out.get(0, t);
  ASSERT_EQUAL(t, 2);
  out.get(1, t);
  ASSERT_EQUAL(t, 3);
  out.get(2, t);
  ASSERT_EQUAL(t, 4);
  out.get(3, t);
  ASSERT_EQUAL(t, 3);
  out.get(4, t);
  ASSERT_EQUAL(t, 2);
}
CTEST(suite, test_add_vector_to_vector_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  bool result = v.add(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_add_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  bool result = v.add(avec, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], static_cast<real>(2));
  ASSERT_EQUAL(out[1], static_cast<real>(4));
  ASSERT_EQUAL(out[2], static_cast<real>(5));
  ASSERT_EQUAL(out[3], static_cast<real>(4));
  ASSERT_EQUAL(out[4], static_cast<real>(2));
}
CTEST(suite, test_add_vecn_to_vecn_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  VecN<real> out;
  VecN<real> avec(3);
  bool result = v.add(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_add_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);

  // output vector
  VecN<real> out;

  std::vector<real> avec;
  // prepare vector to add
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real> avecn(avec);
  bool result = v.add(avecn, out);

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(t, static_cast<real>(2));

  out.get(1, t);
  ASSERT_EQUAL(t, static_cast<real>(4));

  out.get(2, t);
  ASSERT_EQUAL(t, static_cast<real>(5));

  out.get(3, t);
  ASSERT_EQUAL(t, static_cast<real>(4));

  out.get(4, t);
  ASSERT_EQUAL(t, static_cast<real>(2));
}
/*! @} */

/*! @{ testing subtraction for the vector
 */
CTEST(suite, test_subtract_scalar_vector) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  bool result = v.subtract(1, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], 0);
  ASSERT_EQUAL(out[1], 1);
  ASSERT_EQUAL(out[2], 2);
  ASSERT_EQUAL(out[3], 1);
  ASSERT_EQUAL(out[4], 0);
}
CTEST(suite, test_subtract_scalar_vecn) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  VecN<real> out;
  bool result = v.subtract(1, out);
  ASSERT_EQUAL(result, true);
  real t = static_cast<real>(0);
  out.get(0, t);
  ASSERT_EQUAL(t, 0);
  out.get(1, t);
  ASSERT_EQUAL(t, 1);
  out.get(2, t);
  ASSERT_EQUAL(t, 2);
  out.get(3, t);
  ASSERT_EQUAL(t, 1);
  out.get(4, t);
  ASSERT_EQUAL(t, 0);
}
CTEST(suite, test_subtract_vector_to_vector_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  bool result = v.subtract(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_subtract_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  bool result = v.subtract(avec, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], static_cast<real>(0));
  ASSERT_EQUAL(out[1], static_cast<real>(0));
  ASSERT_EQUAL(out[2], static_cast<real>(1));
  ASSERT_EQUAL(out[3], static_cast<real>(0));
  ASSERT_EQUAL(out[4], static_cast<real>(0));
}
CTEST(suite, test_subtract_vecn_to_vecn_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  VecN<real> out;
  VecN<real> avec(3);
  bool result = v.subtract(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_subtract_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);

  // output vector
  VecN<real> out;

  std::vector<real> avec;
  // prepare vector to subtract
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real> avecn(avec);
  bool result = v.subtract(avecn, out);

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(t, static_cast<real>(0));

  out.get(1, t);
  ASSERT_EQUAL(t, static_cast<real>(0));

  out.get(2, t);
  ASSERT_EQUAL(t, static_cast<real>(1));

  out.get(3, t);
  ASSERT_EQUAL(t, static_cast<real>(0));

  out.get(4, t);
  ASSERT_EQUAL(t, static_cast<real>(0));
}

/*! @} */

/*! @{ testing element-wise multiplication for the vector
 */
CTEST(suite, test_multiply_scalar_vector) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  bool result = v.multiply(2, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], 2);
  ASSERT_EQUAL(out[1], 4);
  ASSERT_EQUAL(out[2], 6);
  ASSERT_EQUAL(out[3], 4);
  ASSERT_EQUAL(out[4], 2);
}
CTEST(suite, test_multiply_scalar_vecn) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  VecN<real> out;
  bool result = v.multiply(2, out);
  ASSERT_EQUAL(result, true);
  real t = static_cast<real>(0);
  out.get(0, t);
  ASSERT_EQUAL(t, 2);
  out.get(1, t);
  ASSERT_EQUAL(t, 4);
  out.get(2, t);
  ASSERT_EQUAL(t, 6);
  out.get(3, t);
  ASSERT_EQUAL(t, 4);
  out.get(4, t);
  ASSERT_EQUAL(t, 2);
}
CTEST(suite, test_multiply_vector_to_vector_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  bool result = v.multiply(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_multiply_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  bool result = v.multiply(avec, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], static_cast<real>(1));
  ASSERT_EQUAL(out[1], static_cast<real>(4));
  ASSERT_EQUAL(out[2], static_cast<real>(6));
  ASSERT_EQUAL(out[3], static_cast<real>(4));
  ASSERT_EQUAL(out[4], static_cast<real>(1));
}
CTEST(suite, test_multiply_vecn_to_vecn_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  VecN<real> out;
  VecN<real> avec(3);
  bool result = v.multiply(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_multiply_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);

  // output vector
  VecN<real> out;

  std::vector<real> avec;
  // prepare vector to multiply
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real> avecn(avec);
  bool result = v.multiply(avecn, out);

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(t, static_cast<real>(1));

  out.get(1, t);
  ASSERT_EQUAL(t, static_cast<real>(4));

  out.get(2, t);
  ASSERT_EQUAL(t, static_cast<real>(6));

  out.get(3, t);
  ASSERT_EQUAL(t, static_cast<real>(4));

  out.get(4, t);
  ASSERT_EQUAL(t, static_cast<real>(1));
}

/*! @} */
/*! @{ testing element-wise division for the vector
 */
CTEST(suite, test_divide_scalar_vector) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 2;
  inv[1] = 4;
  inv[2] = 6;
  inv[3] = 2;
  inv[4] = 0;
  VecN<real> v(inv);
  std::vector<real> out;
  bool result = v.divide(2, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], 1);
  ASSERT_EQUAL(out[1], 2);
  ASSERT_EQUAL(out[2], 3);
  ASSERT_EQUAL(out[3], 1);
  ASSERT_EQUAL(out[4], 0);
}
CTEST(suite, test_divide_scalar_vector_zero) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 2;
  inv[1] = 4;
  inv[2] = 6;
  inv[3] = 2;
  inv[4] = 0;
  VecN<real> v(inv);
  std::vector<real> out;
  bool result = v.divide(0, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_divide_scalar_vecn) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 2;
  inv[1] = 4;
  inv[2] = 6;
  inv[3] = 2;
  inv[4] = 0;
  VecN<real> v(inv);
  VecN<real> out;
  bool result = v.divide(2, out);
  ASSERT_EQUAL(result, true);
  real t = static_cast<real>(0);
  out.get(0, t);
  ASSERT_EQUAL(t, 1);
  out.get(1, t);
  ASSERT_EQUAL(t, 2);
  out.get(2, t);
  ASSERT_EQUAL(t, 3);
  out.get(3, t);
  ASSERT_EQUAL(t, 1);
  out.get(4, t);
  ASSERT_EQUAL(t, 0);
}
CTEST(suite, test_divide_scalar_vecn_zero) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 2;
  inv[1] = 4;
  inv[2] = 6;
  inv[3] = 2;
  inv[4] = 0;
  VecN<real> v(inv);
  VecN<real> out;
  bool result = v.divide(0, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_divide_vector_to_vector_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  bool result = v.divide(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_divide_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 4;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  bool result = v.divide(avec, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out[0], static_cast<real>(1));
  ASSERT_EQUAL(out[1], static_cast<real>(1));
  ASSERT_EQUAL(out[2], static_cast<real>(2));
  ASSERT_EQUAL(out[3], static_cast<real>(1));
  ASSERT_EQUAL(out[4], static_cast<real>(1));
}
CTEST(suite, test_divide_vector_to_vector_zero) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 4;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 0;
  avec[3] = 2;
  avec[4] = 1;
  bool result = v.divide(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_divide_vecn_to_vecn_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);
  VecN<real> out;
  VecN<real> avec(3);
  bool result = v.divide(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_divide_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 4;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);

  // output vector
  VecN<real> out;

  std::vector<real> avec;
  // prepare vector to divide
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real> avecn(avec);
  bool result = v.divide(avecn, out);

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(t, static_cast<real>(1));

  out.get(1, t);
  ASSERT_EQUAL(t, static_cast<real>(1));

  out.get(2, t);
  ASSERT_EQUAL(t, static_cast<real>(2));

  out.get(3, t);
  ASSERT_EQUAL(t, static_cast<real>(1));

  out.get(4, t);
  ASSERT_EQUAL(t, static_cast<real>(1));
}
CTEST(suite, test_divide_vecn_to_vecn_zero) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 4;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real> v(inv);

  // output vector
  VecN<real> out;

  std::vector<real> avec;
  // prepare vector to divide
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = -10;
  avec[3] = 2;
  avec[4] = 0;

  VecN<real> avecn(avec);
  bool result = v.divide(avecn, out);

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, false);
}

/*! @} */

/*! @{ testing element-wise division for the vector
 */

CTEST(suite, test_dot_scalar_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1; // 2
  inv[1] = 2; // 4
  inv[2] = 3; // 6
  inv[3] = 2; // 4
  inv[4] = 1; // 2
  // sum == 18
  VecN<real> v(inv);
  real out;
  bool result = v.dot(static_cast<real>(2), out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out, static_cast<real>(18));
}
CTEST(suite, test_dot_scalar_zero) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1; // 2
  inv[1] = 2; // 4
  inv[2] = 3; // 6
  inv[3] = 2; // 4
  inv[4] = 1; // 2
  // sum == 18
  VecN<real> v(inv);
  real out;
  bool result = v.dot(static_cast<real>(0), out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out, static_cast<real>(0));
}
CTEST(suite, test_dot_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1; // 1
  inv[1] = 2; // 4
  inv[2] = 3; // 3
  inv[3] = 2; // 0
  inv[4] = 1; // 0
  // sum == 8
  std::vector<real> avec;
  VecN<real> v(inv);
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 1;
  avec[3] = 0;
  avec[4] = 0;
  real out = static_cast<real>(0);
  bool result = v.dot(avec, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out, static_cast<real>(8));
}
CTEST(suite, test_dot_vector_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1; // 1
  inv[1] = 2; // 4
  inv[2] = 3; // 3
  inv[3] = 2; // 0
  inv[4] = 1; // 0
  // sum == 8
  std::vector<real> avec;
  VecN<real> v(inv);
  avec.resize(3);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 1;
  real out;
  bool result = v.dot(avec, out);
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_dot_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1; // 1
  inv[1] = 2; // 4
  inv[2] = 3; // 3
  inv[3] = 2; // 0
  inv[4] = 1; // 0
  // sum == 8
  std::vector<real> avec;
  VecN<real> v(inv);
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 1;
  avec[3] = 0;
  avec[4] = 0;
  VecN<real> av(avec);
  real out = static_cast<real>(0);
  bool result = v.dot(av, out);
  ASSERT_EQUAL(result, true);
  ASSERT_EQUAL(out, static_cast<real>(8));
}
CTEST(suite, test_dot_vecn_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1; // 1
  inv[1] = 2; // 4
  inv[2] = 3; // 3
  inv[3] = 2; // 0
  inv[4] = 1; // 0
  // sum == 8
  std::vector<real> avec;
  VecN<real> v(inv);
  avec.resize(3);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 1;
  VecN<real> av(avec);
  real out;
  bool result = v.dot(av, out);
  ASSERT_EQUAL(result, false);
}

/*! @} */
