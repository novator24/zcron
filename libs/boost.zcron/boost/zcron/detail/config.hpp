
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_DETAIL_CONFIG_H_
#define BOOST_ZCRON_DETAIL_CONFIG_H_
#include <boost/ztask/detail/config.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/static_assert.hpp>  // boost 1.54
#include <boost/tuple/tuple.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace detail {
      typedef boost::ztask::detail::chrono_clock_type chrono_clock_type;
      typedef boost::ztask::detail::chrono_duration_type chrono_duration_type;
      typedef boost::ztask::detail::chrono_timepoint_type chrono_timepoint_type;

      typedef boost::ztask::detail::lock_mutex_type lock_mutex_type;
      typedef boost::ztask::detail::lock_condition_type lock_condition_type;
      typedef boost::ztask::detail::lock_guard_type lock_guard_type;
      typedef boost::ztask::detail::lock_status_type lock_status_type;
      static const lock_status_type lock_status_type_timeout = \
          boost::ztask::detail::lock_status_type_timeout;
      static const lock_status_type lock_status_type_no_timeout = \
          boost::ztask::detail::lock_status_type_no_timeout;
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_CONFIG_H_

