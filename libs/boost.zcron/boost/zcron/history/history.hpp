
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_HISTORY_H_
#define BOOST_ZCRON_HISTORY_HISTORY_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/history/service_id.hpp>
#include <boost/zcron/history/service_mark.hpp>
#include <boost/zcron/history/detail/history_base.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/atomic.hpp>  // boost 1.54
#include <boost/exception_ptr.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      using boost::zcron::mutex_type;
      using boost::zcron::condition_type;
      using boost::zcron::guard_type;
      using boost::zcron::status_type;
      using boost::zcron::status_type_timeout;
      using boost::zcron::history::detail::history_base;

      class history : public history_base {
       public:
        history()
          : history_base(),
            m_mutex(),
            m_waiter(),
            m_registered(false),
            m_service_id(),
            m_service_mark(),
            m_deactivated(false),
            m_has_exception(false),
            m_exception_ptr(),
            m_total_calls(0) {}

        virtual ~history() {}

        void wait_registration() {
          guard_type lock(m_mutex);
          while (!m_registered && !m_deactivated) {
            m_waiter.wait(lock);
          }
        }

        void wait_registration_for(duration_type const& timeout_duration) {
          guard_type lock(m_mutex);
          while (!m_registered && !m_deactivated) {
            status_type st( m_waiter.wait_for(lock, timeout_duration) );
            if ( status_type_timeout == st && !m_registered) {
              return;
            }
          }
        }

        void wait_registration_until(timepoint_type const& timeout_time) {
          guard_type lock(m_mutex);
          while (!m_registered && !m_deactivated) {
            status_type st( m_waiter.wait_until(lock, timeout_time) );
            if ( status_type_timeout == st && !m_registered) {
              return;
            }
          }
        }

        void finish_registration() {
          if (m_deactivated) {
            return;
          }
          m_registered = true;
          m_waiter.notify_all();
        }

        service_id get_service_id() const {
          return m_service_id;
        }

        void set_service_id(const service_id& value) {
          m_service_id = value;
        }

        service_mark get_service_mark() const {
          return m_service_mark;
        }

        void set_service_mark(const service_mark& value) {
          m_service_mark = value;
        }

        void atomic_deactivate() {
          m_deactivated = true;
        }

        bool atomic_is_deactivated() const {
          return m_deactivated;
        }

        bool atomic_is_registered() const {
          return m_registered;
        }

        void atomic_set_registered(const bool registered) {
          m_registered = registered;
        }

        bool has_registration_exception() {
          guard_type lock(m_mutex);
          return m_has_exception;
        }

        boost::exception_ptr get_registration_exception() {
          guard_type lock(m_mutex);
          return m_exception_ptr;
        }

        void set_registration_exception(const boost::exception_ptr& value) {
          guard_type lock(m_mutex);
          m_exception_ptr = value;
          m_has_exception = true;
        }

        void atomic_register_call() {
          ++m_total_calls;
        }

        int atomic_get_calls() const {
          return m_total_calls;
        }

       private:
        // multi-thread controllers [always first]
        mutex_type m_mutex;
        condition_type m_waiter;

        boost::atomic<bool> m_registered;
        service_id m_service_id;
        service_mark m_service_mark;
        boost::atomic<bool> m_deactivated;
        bool m_has_exception;
        boost::exception_ptr m_exception_ptr;
        boost::atomic<int> m_total_calls;

        // noncopyable
        history(const history&);
        void operator=(const history&);
      };
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_HISTORY_H_

