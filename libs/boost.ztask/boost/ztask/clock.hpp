
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZTASK_CLOCK_H_
#define BOOST_ZTASK_CLOCK_H_
#include <boost/ztask/detail/config.hpp>
#include <boost/config.hpp>
namespace boost {
  namespace ztask {
    using boost::ztask::detail::chrono_clock_type;
    using boost::ztask::detail::chrono_duration_type;
    using boost::ztask::detail::chrono_timepoint_type;
    using boost::ztask::detail::lock_mutex_type;
    using boost::ztask::detail::lock_condition_type;
    using boost::ztask::detail::lock_guard_type;
    using boost::ztask::detail::lock_status_type;
    using boost::ztask::detail::lock_status_type_no_timeout;
    using boost::ztask::detail::lock_status_type_timeout;

    typedef chrono_clock_type clock_type;
    typedef chrono_duration_type duration_type;
    typedef chrono_timepoint_type timepoint_type;
    typedef lock_mutex_type mutex_type;
    typedef lock_condition_type condition_type;
    typedef lock_guard_type guard_type;
    typedef lock_status_type status_type;
    static const status_type status_type_timeout = lock_status_type_timeout;
    static const status_type status_type_no_timeout = lock_status_type_no_timeout;
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_CLOCK_H_

