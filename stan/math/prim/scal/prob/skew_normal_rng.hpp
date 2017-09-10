#ifndef STAN_MATH_PRIM_SCAL_PROB_SKEW_NORMAL_RNG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_SKEW_NORMAL_RNG_HPP

#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/scal/err/check_positive.hpp>
#include <stan/math/prim/scal/meta/scalar_seq_view.hpp>
#include <stan/math/prim/scal/meta/VectorBuilder.hpp>
#include <stan/math/prim/scal/prob/normal_rng.hpp>
#include <string>

namespace stan {
  namespace math {
    /**
     * Return a pseudorandom Skew-normal variate for the given location, scale,
     * and shape using the specified random number generator.
     *
     * mu, sigma, and alpha can each be either scalars or vectors. All vector
     * inputs must be the same length.
     *
     * @tparam T_loc Type of location parameter
     * @tparam T_scale Type of scale parameter
     * @tparam T_shape Type of shape parameter
     * @tparam RNG type of random number generator
     * @param mu (Sequence of) location parameter(s)
     * @param sigma (Sequence of) scale parameter(s)
     * @param alpha (Sequence of) shape parameter(s)
     * @param rng random number generator
     * @return Skew-normal random variate
     * @throw std::domain_error if mu is infinite, sigma is nonpositive, or
     * alpha is infinite
     * @throw std::invalid_argument if vector arguments are not the same length
     */
    template <typename T_loc, typename T_scale, typename T_shape, class RNG>
    inline typename VectorBuilder<true, double, T_loc, T_scale, T_shape>::type
    skew_normal_rng(const T_loc& mu,
                    const T_scale& sigma,
                    const T_shape& alpha,
                    RNG& rng) {
      static const std::string function = "skew_normal_rng";

      check_finite(function, "Location parameter", mu);
      check_positive_finite(function, "Scale parameter", sigma);
      check_finite(function, "Shape parameter", alpha);
      check_consistent_sizes(function,
                             "Location parameter", mu,
                             "Scale Parameter", sigma,
                             "Shape Parameter", alpha);

      scalar_seq_view<T_loc> mu_vec(mu);
      scalar_seq_view<T_scale> sigma_vec(sigma);
      scalar_seq_view<T_shape> alpha_vec(alpha);

      size_t N = max_size(mu, sigma, alpha);

      VectorBuilder<true, double, T_loc, T_scale, T_shape> output(N);

      for (size_t n = 0; n < N; n++) {
        double r1 = normal_rng(0.0, 1.0, rng),
          r2 = normal_rng(0.0, 1.0, rng);

        if (r2 > alpha_vec[n] * r1)
          r1 *= -1;

        output[n] = mu_vec[n] + sigma_vec[n] * r1;
      }

      return output.data();
    }
  }
}
#endif
