/** @file
* @copyright University of Warsaw
* @section LICENSE
* GPLv3+ (see the COPYING file or http://www.gnu.org/licenses/)
*/

#pragma once

#include <libmpdata++/formulae/mpdata/formulae_mpdata_common.hpp>
#include <libmpdata++/formulae/mpdata/formulae_mpdata_psi_3d.hpp>
#include <libmpdata++/formulae/mpdata/formulae_mpdata_gc_3d.hpp>
#include <libmpdata++/formulae/mpdata/formulae_mpdata_g_3d.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>

namespace libmpdataxx
{
  namespace formulae
  {
    namespace mpdata
    {
      template<opts_t opts, int dim, class arr_3d_t>
      inline auto ndxx_psi_coeff(
        const arr_3d_t &GC,
        const arr_3d_t &G,
        const rng_t &i,
        const rng_t &j,
        const rng_t &k
      ) return_macro(,
          (
            3 * GC(pi<dim>(i+h, j, k)) * abs(GC(pi<dim>(i+h, j, k))) / G_bar_x<opts BOOST_PP_COMMA() dim>(G, i, j, k)
          - 2 * pow(GC(pi<dim>(i+h, j, k)), 3) / pow(G_bar_x<opts BOOST_PP_COMMA() dim>(G, i, j, k), 2)
          - GC(pi<dim>(i+h, j, k))
          ) / 6
      )

      template<opts_t opts, int dim, class arr_3d_t>
      inline auto ndxy_psi_coeff(
        const arrvec_t<arr_3d_t> &GC,
        const arr_3d_t &G,
        const rng_t &i,
        const rng_t &j,
        const rng_t &k
      ) return_macro(,
          (
            abs(GC[dim](pi<dim>(i+h, j, k)))
          - 2 * pow(GC[dim](pi<dim>(i+h, j, k)), 2) / G_bar_x<opts BOOST_PP_COMMA() dim>(G, i, j, k)
          ) * GC1_bar_xy<dim>(GC[dim+1], i, j, k) / (2 * G_bar_x<opts BOOST_PP_COMMA() dim>(G, i, j, k))
      )

      template<opts_t opts, int dim, class arr_3d_t>
      inline auto ndxz_psi_coeff(
        const arrvec_t<arr_3d_t> &GC,
        const arr_3d_t &G,
        const rng_t &i,
        const rng_t &j,
        const rng_t &k
      ) return_macro(,
          (
            abs(GC[dim](pi<dim>(i+h, j, k)))
          - 2 * pow(GC[dim](pi<dim>(i+h, j, k)), 2) / G_bar_x<opts BOOST_PP_COMMA() dim>(G, i, j, k)
          ) * GC2_bar_xz<dim>(GC[dim-1], i, j, k) / (2 * G_bar_x<opts BOOST_PP_COMMA() dim>(G, i, j, k))
      )

      template<opts_t opts, int dim, class arr_3d_t>
      inline auto ndyz_psi_coeff(
        const arrvec_t<arr_3d_t> &GC,
        const arr_3d_t &G,
        const rng_t &i,
        const rng_t &j,
        const rng_t &k
      ) return_macro(,
          -2 * GC[dim](pi<dim>(i+h, j, k)) * GC1_bar_xy<dim>(GC[dim+1], i, j, k) * GC2_bar_xz<dim>(GC[dim-1], i, j, k) / 3
             / pow(G_bar_x<opts BOOST_PP_COMMA() dim>(G, i, j, k), 2)
      )

      // third order terms
      template<opts_t opts, int dim, class arr_3d_t>
      inline auto TOT(
        const arr_3d_t &psi,
        const arrvec_t<arr_3d_t> &GC,
        const arr_3d_t &G,
        const rng_t &i,
        const rng_t &j,
        const rng_t &k,
        typename std::enable_if<opts::isset(opts, opts::tot)>::type* = 0
      ) return_macro(,
         ndxx_psi<opts BOOST_PP_COMMA() dim>(psi, i, j, k) * ndxx_psi_coeff<opts BOOST_PP_COMMA() dim>(GC[dim], G, i, j, k)
         + 
         ndxy_psi<opts BOOST_PP_COMMA() dim>(psi, i, j, k) * ndxy_psi_coeff<opts BOOST_PP_COMMA() dim>(GC, G, i, j, k)
         + 
         ndxz_psi<opts BOOST_PP_COMMA() dim>(psi, i, j, k) * ndxz_psi_coeff<opts BOOST_PP_COMMA() dim>(GC, G, i, j, k)
         + 
         ndyz_psi<opts BOOST_PP_COMMA() dim>(psi, i, j, k) * ndyz_psi_coeff<opts BOOST_PP_COMMA() dim>(GC, G, i, j, k)
      )

      template<opts_t opts, int dim, class arr_3d_t>
      inline typename arr_3d_t::T_numtype TOT(
        const arr_3d_t &psi,
        const arrvec_t<arr_3d_t> &GC,
        const arr_3d_t &G,
        const rng_t &i,
        const rng_t &j,
        const rng_t &k,
        typename std::enable_if<!opts::isset(opts, opts::tot)>::type* = 0
      )
      {
        return 0;
      }
    } // namespace mpdata
  } // namespace formulae
} // namespcae libmpdataxx
