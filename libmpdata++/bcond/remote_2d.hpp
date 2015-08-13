// 2D MPI ``remote'' boundary conditions for libmpdata++
//
// licensing: GPU GPL v3
// copyright: University of Warsaw

#pragma once

#include <libmpdata++/bcond/detail/remote_common.hpp>

namespace libmpdataxx
{
  namespace bcond
  {
    template <typename real_t, int halo, bcond_e knd, drctn_e dir, int n_dims, int d>    
    class bcond<       real_t,     halo,         knd,         dir,     n_dims,     d,
      typename std::enable_if<
        knd == remote && 
        dir == left   && 
        n_dims == 2
      >::type
    > : public detail::remote_common<real_t, halo, dir>
    {
      using parent_t = detail::remote_common<real_t, halo, dir>;
      using arr_t = blitz::Array<real_t, 1>;
      using parent_t::parent_t; // inheriting ctor

      const int off = this->is_cyclic ? 0 : -1;

      public:

      void fill_halos_sclr(const arr_t &a, const rng_t &j, const bool deriv = false)
      {
        using namespace idxperm;
        this->xchng(a, pi<d>(this->left_intr_sclr + off, j), pi<d>(this->left_halo_sclr, j));
      }

      void fill_halos_vctr_alng(const arrvec_t<arr_t> &av, const rng_t &j)
      {
        using namespace idxperm;
        this->xchng(av[0], pi<d>(this->left_intr_vctr + off, j), pi<d>(this->left_halo_vctr, j));
      }
    };

    template <typename real_t, int halo, bcond_e knd, drctn_e dir, int n_dims, int d>
    class bcond<       real_t,     halo,         knd,         dir,     n_dims,     d,
      typename std::enable_if<
        knd == remote &&
        dir == rght   &&
        n_dims == 2
      >::type
    > : public detail::remote_common<real_t, halo, dir>
    {
      using parent_t = detail::remote_common<real_t, halo, dir>;
      using arr_t = blitz::Array<real_t, 1>;
      using parent_t::parent_t; // inheriting ctor

      const int off = this->is_cyclic ? 0 : 1;

      public:

      void fill_halos_sclr(const arr_t &a, const rng_t &j, const bool deriv = false)
      {
        using namespace idxperm;
        this->xchng(a, pi<d>(this->rght_intr_sclr + off, j), pi<d>(this->rght_halo_sclr, j));
      }

      void fill_halos_vctr_alng(const arrvec_t<arr_t> &av, const rng_t &j)
      {
        using namespace idxperm;
        this->xchng(av[0], pi<d>(this->rght_intr_vctr + off, j), pi<d>(this->rght_halo_vctr, j));
      }
    };
  } // namespace bcond
} // namespace libmpdataxx