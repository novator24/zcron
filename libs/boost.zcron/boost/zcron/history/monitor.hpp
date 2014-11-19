
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_MONITOR_H_
#define BOOST_ZCRON_HISTORY_MONITOR_H_
#include <boost/zcron/clock.hpp> 
#include <boost/zcron/history/service_id.hpp> 
#include <boost/zcron/history/history.hpp> 
#include <boost/zcron/history/detail/history_base.hpp> 
#include <boost/zcron/history/detail/monitor_base.hpp> 
#include <boost/shared_ptr.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      using boost::zcron::duration_type;
      using boost::zcron::timepoint_type;
      using boost::zcron::history::detail::history_iface;
      using boost::zcron::history::detail::history_base;
      using boost::zcron::history::detail::monitor_iface;
      using boost::zcron::history::detail::monitor_base;

      class monitor : public monitor_base {
       public:
        monitor()
          : monitor_base(),
            m_history_ptr(new history()) {}

        virtual ~monitor() {}

        monitor(const monitor& obj) 
          : monitor_base(obj),
            m_history_ptr(obj.m_history_ptr) {
        }

        monitor& operator=(const monitor& obj) {
          if (this != &obj) {
            monitor_base::operator=(obj);
            m_history_ptr = obj.m_history_ptr;
          }
          return *this;
        }

        monitor_iface* clone() const {
          return new monitor(*this);
        }

        history_iface* _get_history_iface() const {
          return m_history_ptr.get();
        }

        void wait_registration() {
          m_history_ptr->wait_registration();
        }

        void wait_registration_for(duration_type const& timeout_duration) {
          m_history_ptr->wait_registration_for(timeout_duration);
        }

        void wait_registration_until(timepoint_type const& timeout_time) {
          m_history_ptr->wait_registration_until(timeout_time);
        }

        service_id get_service_id() const {
          return m_history_ptr->get_service_id();
        }

        service_mark get_service_mark() const {
          return m_history_ptr->get_service_mark();
        }

        void deactivate() {
          m_history_ptr->atomic_deactivate();
        }

        bool is_deactivated() const {
          return m_history_ptr->atomic_is_deactivated();
        }

        bool is_registered() const {
          return m_history_ptr->atomic_is_registered();
        }

        bool has_registration_exception() const {
          return m_history_ptr->has_registration_exception();
        }

        boost::exception_ptr get_registration_exception() const {
          return m_history_ptr->get_registration_exception();
        }

       private:
        boost::shared_ptr<history_iface> m_history_ptr;
      };
    }  // namespace history 
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_MONITOR_H_

