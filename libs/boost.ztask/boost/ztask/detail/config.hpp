
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZTASK_DETAIL_CONFIG_H_
#define BOOST_ZTASK_DETAIL_CONFIG_H_
#include <boost/config.hpp>  // boost 1.54
#include <chrono>
#include <condition_variable>
namespace boost {
  namespace ztask {
    namespace detail {
      typedef ::std::chrono::system_clock chrono_clock_type;
      typedef ::std::chrono::duration<double, std::ratio<1> > chrono_duration_type;
      typedef ::std::chrono::time_point< chrono_clock_type,
          chrono_duration_type > chrono_timepoint_type;
      typedef std::mutex lock_mutex_type;
      typedef std::condition_variable lock_condition_type;
      typedef std::unique_lock<lock_mutex_type> lock_guard_type;
      typedef bool lock_status_type;
      static const bool lock_status_type_timeout = false;
      static const bool lock_status_type_no_timeout = true;
    }  // namespace detail
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_DETAIL_CONFIG_H_

