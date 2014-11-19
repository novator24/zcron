
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_DETAIL_MONITOR_BASE_H_
#define BOOST_ZCRON_HISTORY_DETAIL_MONITOR_BASE_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/history/service_id.hpp>
#include <boost/zcron/history/service_mark.hpp>
#include <boost/zcron/history/detail/history_base.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/function.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      namespace detail {
        using boost::zcron::clock_type;
        using boost::zcron::history::service_id;

        class monitor_iface {
         public:
          virtual ~monitor_iface() {}

          virtual monitor_iface* clone() const = 0;

          virtual history_iface* _get_history_iface() const = 0;

          virtual void wait_registration() = 0;

          virtual void wait_registration_for(duration_type const& timeout_duration) = 0;

          virtual void wait_registration_until(timepoint_type const& timeout_time) = 0;

          virtual service_id get_service_id() const = 0;

          virtual service_mark get_service_mark() const = 0;

          virtual void deactivate() = 0;

          virtual bool is_deactivated() const = 0;

          virtual bool is_registered() const = 0;

          virtual bool has_registration_exception() const = 0;

          virtual boost::exception_ptr get_registration_exception() const = 0;
        };

        class monitor_base : public monitor_iface {
         public:
          virtual ~monitor_base() {}
        };
      }  // namespace detail
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_DETAIL_MONITOR_BASE_H_

