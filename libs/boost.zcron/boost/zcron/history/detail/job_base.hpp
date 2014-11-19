
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_DETAIL_JOB_BASE_H_
#define BOOST_ZCRON_HISTORY_DETAIL_JOB_BASE_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/history/service_id.hpp>
#include <boost/zcron/history/service_mark.hpp>
#include <boost/zcron/history/detail/history_base.hpp>
#include <boost/ztask/future/future.hpp>
#include <boost/ztask/future/detail/future_base.hpp>
#include <boost/function.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      namespace detail {
        using boost::zcron::clock_type;
        using boost::zcron::duration_type;
        using boost::zcron::history::service_id;
        using boost::zcron::history::service_mark;
        using boost::ztask::future::detail::future_iface;
        using boost::ztask::future::detail::future_base;

        class job_iface {
         public:
          typedef boost::function<void ()> void_function_t;

          job_iface() {}

          virtual ~job_iface() {}

          virtual job_iface* clone() const = 0;

          virtual history_iface* _get_history_iface() const = 0;

          virtual service_id get_service_id() const = 0;

          virtual service_mark get_service_mark() const = 0;

          virtual bool is_deactivated() const = 0;

          virtual bool try_set_service_id(const service_id& value) const = 0;

          virtual bool try_set_service_mark(const service_mark& value) const = 0;

          virtual duration_type get_next_call_duration( \
            timepoint_type const& utc_since) const = 0;

          virtual void finish_registration() = 0;

          virtual void run_with_callback(unsigned priority_in_context,
              const service_mark& service_mark) = 0;

          virtual bool are_calls_allowed() const = 0;
        };

        class job_base : public job_iface {
         public:
          virtual ~job_base() {}
        };
      }  // namespace detail
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_DETAIL_JOB_BASE_H_

