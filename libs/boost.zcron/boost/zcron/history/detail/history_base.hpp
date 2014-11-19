
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_DETAIL_HISTORY_BASE_H_
#define BOOST_ZCRON_HISTORY_DETAIL_HISTORY_BASE_H_
#include <boost/zcron/history/service_id.hpp>
#include <boost/zcron/history/service_mark.hpp>
#include <boost/zcron/clock.hpp>
#include <boost/exception_ptr.hpp>  // boost 1.54
#include <boost/thread/condition.hpp>  // boost 1.54
#include <boost/thread/mutex.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      namespace detail {
        using boost::zcron::history::service_id;
        using boost::zcron::history::service_mark;
        using boost::zcron::duration_type;
        using boost::zcron::timepoint_type;

        class history_iface {
         public:
          virtual ~history_iface() {}

          virtual void wait_registration() = 0;

          virtual void wait_registration_for(duration_type const& timeout_duration) = 0;

          virtual void wait_registration_until(timepoint_type const& timeout_time) = 0;

          virtual void finish_registration() = 0;

          virtual service_id get_service_id() const = 0;

          virtual void set_service_id(const service_id& value) = 0;

          virtual service_mark get_service_mark() const = 0;

          virtual void set_service_mark(const service_mark& value) = 0;

          virtual void atomic_deactivate() = 0;

          virtual bool atomic_is_deactivated() const = 0;

          virtual bool atomic_is_registered() const = 0;

          virtual void atomic_set_registered(const bool ready) = 0;

          virtual bool has_registration_exception() = 0;

          virtual boost::exception_ptr get_registration_exception() = 0;

          virtual void set_registration_exception(const boost::exception_ptr& value) = 0;

          virtual void atomic_register_call() = 0;

          virtual int atomic_get_calls() const = 0;
        };

        class history_base : public history_iface {
        };
      }  // namespace detail
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_DETAIL_HISTORY_BASE_H_

