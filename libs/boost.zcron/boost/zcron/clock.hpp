
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_CLOCK_H_
#define BOOST_ZCRON_CLOCK_H_
#include <boost/zcron/detail/config.hpp>
#include <boost/zcron/detail/chrono_clock_bits.hpp>
#include <boost/zcron/detail/chrono_clock_cond.hpp>
#include <boost/zcron/detail/chrono_clock_util.hpp>
#include <boost/config.hpp>
namespace boost {
  namespace zcron {
    using boost::zcron::detail::chrono_clock_type;
    using boost::zcron::detail::chrono_duration_type;
    using boost::zcron::detail::chrono_timepoint_type;
    using boost::zcron::detail::chrono_clock_bits;
    using boost::zcron::detail::chrono_clock_cond;
    using boost::zcron::detail::chrono_clock_util;
    using boost::zcron::detail::lock_mutex_type;
    using boost::zcron::detail::lock_condition_type;
    using boost::zcron::detail::lock_guard_type;
    using boost::zcron::detail::lock_status_type;
    using boost::zcron::detail::lock_status_type_no_timeout;
    using boost::zcron::detail::lock_status_type_timeout;

    typedef chrono_clock_type clock_type;
    typedef chrono_duration_type duration_type;
    typedef chrono_timepoint_type timepoint_type;
    typedef chrono_clock_bits clock_bits_type;
    typedef chrono_clock_cond clock_cond_type;
    typedef chrono_clock_util clock_util_type;
    typedef lock_mutex_type mutex_type;
    typedef lock_condition_type condition_type;
    typedef lock_guard_type guard_type;
    typedef lock_status_type status_type;
    static const status_type status_type_timeout = lock_status_type_timeout;
    static const status_type status_type_no_timeout = lock_status_type_no_timeout;
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_CLOCK_H_

