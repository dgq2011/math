#ifndef STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_CDF_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_CDF_LOG_HPP

#include <stan/math/prim/scal/meta/return_type.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_lcdf.hpp>

namespace stan {
namespace math {

/**
 * @deprecated use <code>neg_binomial_lcdf</code>
 */
template <typename T_n, typename T_shape, typename T_inv_scale>
typename return_type<T_shape, T_inv_scale>::type neg_binomial_cdf_log(
    const T_n& n, const T_shape& alpha, const T_inv_scale& beta) {
  return neg_binomial_lcdf<T_n, T_shape, T_inv_scale>(n, alpha, beta);
}

}  // namespace math
}  // namespace stan
#endif
