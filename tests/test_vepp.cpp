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
  VecN<real, 2> v;
  unsigned int vsize = 5;
  v.size(vsize);
  ASSERT_EQUAL(vsize, static_cast<unsigned int>(2));
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
  VecN<real, 5> v(tvec);
  real t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;
  // test size
  unsigned int vsize = 6156;
  v.size(vsize);
  ASSERT_EQUAL(vsize, 5);

  // test values
  // first value
  ASSERT_EQUAL(v.get(0, t1).status, SUCCESS);
  ASSERT_EQUAL(t1, v1);

  // second value
  ASSERT_EQUAL(v.get(1, t2).status, SUCCESS);
  ASSERT_EQUAL(t2, v2);
  // third value

  ASSERT_EQUAL(v.get(2, t3).status, SUCCESS);
  ASSERT_EQUAL(t3, v3);

  // fourth value
  ASSERT_EQUAL(v.get(3, t4).status, SUCCESS);
  ASSERT_EQUAL(t4, v4);

  // fifth value
  ASSERT_EQUAL(v.get(4, t5).status, SUCCESS);
  ASSERT_EQUAL(t5, v5);

  // sixth value
  ASSERT_EQUAL(v.get(5, t6).status, INDEX_ERROR);
}

CTEST(suite, test_dimension_constructor) {
  VecN<real, 5> v(5);
  real r1 = static_cast<real>(5);
  // test values
  real t1 = 0;
  // first value
  ASSERT_EQUAL(v.get(0, t1).status, SUCCESS);
  ASSERT_EQUAL(t1, r1);

  // second value
  ASSERT_EQUAL(v.get(1, t1).status, SUCCESS);
  ASSERT_EQUAL(t1, r1);
  // third value

  ASSERT_EQUAL(v.get(2, t1).status, SUCCESS);
  ASSERT_EQUAL(t1, r1);

  // fourth value
  ASSERT_EQUAL(v.get(3, t1).status, SUCCESS);
  ASSERT_EQUAL(t1, r1);

  // fifth value

  ASSERT_EQUAL(v.set(4, t1).status, SUCCESS);
  ASSERT_EQUAL(t1, r1);

  // sixth value
  ASSERT_EQUAL(v.get(5, t1).status, INDEX_ERROR);
  ASSERT_EQUAL(v.set(5, t1).status, INDEX_ERROR);
}

CTEST(suite, test_vecn_flag_fn_name) {
  VecN<real, 2> v;
  unsigned int vsize = 5;
  auto vflag = v.size(vsize);
  const std::string fname = vflag.fn_name;
  const std::string compval = "size";
  ASSERT_EQUAL(fname == compval, true);
}
CTEST(suite, test_debug_check_true) {
  VecN<real, 2> v;
  unsigned int vsize = 5;
  bool vflag = CHECK(v.size(vsize));
  ASSERT_EQUAL(vflag, true);
}
CTEST(suite, test_add_debug_check_false) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  auto result = CHECK(v.add(avec, out));
  ASSERT_EQUAL(result, false);
}
CTEST(suite, test_debug_check_m_true) {
  VecN<real, 2> v;
  unsigned int vsize = 5;
  Result res;
  CHECK_M(v.size(vsize), res);
  ASSERT_EQUAL(res.success, true);
  std::string cname = "v.size(vsize)";
  std::string rcname = res.call_name;
  ASSERT_EQUAL(rcname == cname, true);
}

/*! @} */

/*! @{ testing base dimensions for the vector
 */
CTEST(suite, test_to_base_dimensions_vector) {
  //
  std::vector<real> out;
  VecN<real, 6>::base(6, 1, out);
  ASSERT_EQUAL(out[1], static_cast<real>(1));
}
CTEST(suite, test_to_base_dimensions_vecn) {
  //
  VecN<real, 6> vout(0);
  VecN<real, 6>::base(1, vout);
  real tout = 0;
  ASSERT_EQUAL(vout.get(1, tout).status, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  auto result = v.add(1, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  VecN<real, 5> out;
  auto result = v.add(1, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  auto result = v.add(avec, out).status;
  ASSERT_EQUAL(result, SIZE_ERROR);
}

CTEST(suite, test_add_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  auto result = v.add(avec, out).status;
  ASSERT_EQUAL(result, SUCCESS);
  ASSERT_EQUAL(out[0], static_cast<real>(2));
  ASSERT_EQUAL(out[1], static_cast<real>(4));
  ASSERT_EQUAL(out[2], static_cast<real>(5));
  ASSERT_EQUAL(out[3], static_cast<real>(4));
  ASSERT_EQUAL(out[4], static_cast<real>(2));
}
CTEST(suite, test_add_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);

  // output vector
  VecN<real, 5> out;

  std::vector<real> avec;
  // prepare vector to add
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real, 5> avecn(avec);
  auto result = v.add(avecn, out).status;

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  auto result = v.subtract(1, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  VecN<real, 5> out;
  auto result = v.subtract(1, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  auto result = v.subtract(avec, out).status;
  ASSERT_EQUAL(result, SIZE_ERROR);
}
CTEST(suite, test_subtract_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  auto result = v.subtract(avec, out).status;
  ASSERT_EQUAL(result, SUCCESS);
  ASSERT_EQUAL(out[0], static_cast<real>(0));
  ASSERT_EQUAL(out[1], static_cast<real>(0));
  ASSERT_EQUAL(out[2], static_cast<real>(1));
  ASSERT_EQUAL(out[3], static_cast<real>(0));
  ASSERT_EQUAL(out[4], static_cast<real>(0));
}
CTEST(suite, test_subtract_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);

  // output vector
  VecN<real, 5> out;

  std::vector<real> avec;
  // prepare vector to subtract
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real, 5> avecn(avec);
  auto result = v.subtract(avecn, out).status;

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  auto result = v.multiply(2, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  VecN<real, 5> out;
  auto result = v.multiply(2, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  auto result = v.multiply(avec, out).status;
  ASSERT_EQUAL(result, SIZE_ERROR);
}
CTEST(suite, test_multiply_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  auto result = v.multiply(avec, out).status;
  ASSERT_EQUAL(result, SUCCESS);
  ASSERT_EQUAL(out[0], static_cast<real>(1));
  ASSERT_EQUAL(out[1], static_cast<real>(4));
  ASSERT_EQUAL(out[2], static_cast<real>(6));
  ASSERT_EQUAL(out[3], static_cast<real>(4));
  ASSERT_EQUAL(out[4], static_cast<real>(1));
}
CTEST(suite, test_multiply_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);

  // output vector
  VecN<real, 5> out;

  std::vector<real> avec;
  // prepare vector to multiply
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real, 5> avecn(avec);
  auto result = v.multiply(avecn, out).status;

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  auto result = v.divide(2, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  auto result = v.divide(0, out).status;
  ASSERT_EQUAL(result, ARG_ERROR);
}
CTEST(suite, test_divide_scalar_vecn) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 2;
  inv[1] = 4;
  inv[2] = 6;
  inv[3] = 2;
  inv[4] = 0;
  VecN<real, 5> v(inv);
  VecN<real, 5> out;
  auto result = v.divide(2, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  VecN<real, 5> out;
  auto result = v.divide(0, out).status;
  ASSERT_EQUAL(result, ARG_ERROR);
}
CTEST(suite, test_divide_vector_to_vector_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(3);
  avec[0] = 83;
  avec[1] = 8;
  avec[2] = 3;
  auto result = v.divide(avec, out).status;
  ASSERT_EQUAL(result, SIZE_ERROR);
}
CTEST(suite, test_divide_vector_to_vector_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 4;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;
  auto result = v.divide(avec, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  std::vector<real> out;
  std::vector<real> avec;
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 0;
  avec[3] = 2;
  avec[4] = 1;
  auto result = v.divide(avec, out).status;
  ASSERT_EQUAL(result, ARG_ERROR);
}
CTEST(suite, test_divide_vecn_to_vecn_f) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 3;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);
  VecN<real, 5> out;
  VecN<real, 5> avec(0);
  auto result = v.divide(avec, out).status;
  ASSERT_EQUAL(result, ARG_ERROR);
}
CTEST(suite, test_divide_vecn_to_vecn_t) {
  std::vector<real> inv;
  inv.resize(5);
  inv[0] = 1;
  inv[1] = 2;
  inv[2] = 4;
  inv[3] = 2;
  inv[4] = 1;
  VecN<real, 5> v(inv);

  // output vector
  VecN<real, 5> out;

  std::vector<real> avec;
  // prepare vector to divide
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 2;
  avec[3] = 2;
  avec[4] = 1;

  VecN<real, 5> avecn(avec);
  auto result = v.divide(avecn, out).status;

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);

  // output vector
  VecN<real, 5> out;

  std::vector<real> avec;
  // prepare vector to divide
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = -10;
  avec[3] = 2;
  avec[4] = 0;

  VecN<real, 5> avecn(avec);
  auto result = v.divide(avecn, out).status;

  real t = static_cast<real>(0);
  out.get(0, t);
  //
  ASSERT_EQUAL(result, ARG_ERROR);
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
  VecN<real, 5> v(inv);
  real out;
  auto result = v.dot(static_cast<real>(2), out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  real out;
  auto result = v.dot(static_cast<real>(0), out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 1;
  avec[3] = 0;
  avec[4] = 0;
  real out = static_cast<real>(0);
  auto result = v.dot(avec, out).status;
  ASSERT_EQUAL(result, SUCCESS);
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
  VecN<real, 5> v(inv);
  avec.resize(3);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 1;
  real out;
  auto result = v.dot(avec, out).status;
  ASSERT_EQUAL(result, SIZE_ERROR);
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
  VecN<real, 5> v(inv);
  avec.resize(5);
  avec[0] = 1;
  avec[1] = 2;
  avec[2] = 1;
  avec[3] = 0;
  avec[4] = 0;
  VecN<real, 5> av(avec);
  real out = static_cast<real>(0);
  auto result = v.dot(av, out).status;
  ASSERT_EQUAL(result, SUCCESS);
  ASSERT_EQUAL(out, static_cast<real>(8));
}

/*! @} */
