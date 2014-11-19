
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_RUNNABLE_H_
#define BOOST_ZCRON_HISTORY_RUNNABLE_H_
#include <assert.h>
#include <boost/zcron/clock.hpp>
#include <boost/zcron/history/job.hpp>
#include <boost/zcron/history/detail/job_base.hpp>
#include <boost/shared_ptr.hpp>
namespace boost {
  namespace zcron {
    namespace history {
      using boost::zcron::clock_type;
      using boost::zcron::duration_type;
      using boost::zcron::history::detail::job_base;

      // NOTICE: job instance is renamed to service after registration in pool
      class runnable {
       public:
        template<typename ReturnType, typename ContextType>
        runnable(const job<ReturnType, ContextType>& job, unsigned int priority)
          : m_service_ptr(job.clone()),
            m_priority(priority),
            m_last_update(),
            m_duration_next_call() {}

        virtual ~runnable() {
          delete m_service_ptr;
        }

        runnable(const runnable& obj)
          : m_service_ptr(obj.m_service_ptr),
            m_priority(obj.m_priority),
            m_last_update(obj.m_last_update),
            m_duration_next_call(obj.m_duration_next_call) {}

        runnable& operator=(const runnable& obj) {
          if (this != &obj) {
            m_service_ptr = obj.m_service_ptr;
            m_priority = obj.m_priority;
            m_last_update = obj.m_last_update;
            m_duration_next_call = obj.m_duration_next_call;
          }
          return *this;
        }

        bool operator<(const runnable& obj) const {
          return m_priority < obj.m_priority;
        }

        bool operator>(const runnable& obj) const {
          return m_priority > obj.m_priority;
        }

        bool operator!=(const runnable& obj) const {
          return (this->operator<(obj) || this->operator>(obj));
        }

        bool operator==(const runnable& obj) const {
          return !(this->operator!=(obj));
        }

        void call_finish_registration() {
          assert(NULL != m_service_ptr.get());
          m_service_ptr->finish_registration();
        }

        bool try_call_run_func(timepoint_type const& instant) {
          assert(NULL != m_service_ptr.get());

          bool errors = !m_service_ptr->are_calls_allowed();

          // step0. verify that duration is not negative
          if (m_duration_next_call < duration_type(0.0)) {
            errors = true;
          }

          // step1. verify that duration passed
          duration_type real = clock_util_type::calc_duration(m_last_update, instant);
          if (real < m_duration_next_call) {
            errors = true;
          }

          // step2. calc duration for passed point for extra test
          timepoint_type passed_point = m_last_update + m_duration_next_call;
          duration_type test =  m_service_ptr->get_next_call_duration(passed_point);
          if (test != duration_type(0.0)) {
            errors = true;
          }

          // step3. run job and do callback
          m_duration_next_call = m_service_ptr->get_next_call_duration(instant);
          m_last_update = instant;
          if (!errors) {
            m_service_ptr->run_with_callback(m_priority, m_service_ptr->get_service_mark());
            m_service_ptr->_get_history_iface()->atomic_register_call();
            return true;
          }
          return false;
        }

        timepoint_type get_last_update() const {
          return m_last_update;
        }

        duration_type get_duration_next_call() const {
          return m_duration_next_call;
        }

       private:
        job_iface*                     m_service_ptr;
        unsigned int                   m_priority;
        timepoint_type                 m_last_update;
        duration_type                  m_duration_next_call;
      };
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_RUNNABLE_H_

