
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_JOB_H_
#define BOOST_ZCRON_HISTORY_JOB_H_
#include <boost/zcron/exceptions.hpp>
#include <boost/zcron/schedule_instant.hpp>
#include <boost/zcron/schedule_regular.hpp>
#include <boost/zcron/schedule_periodic.hpp>
#include <boost/zcron/detail/tasks_context_base.hpp>
#include <boost/zcron/detail/config.hpp>
#include <boost/zcron/history/callback.hpp>
#include <boost/zcron/history/service_id.hpp>
#include <boost/zcron/history/monitor.hpp>
#include <boost/zcron/history/detail/job_base.hpp>
#include <boost/ztask/future/async.hpp>
#include <boost/ztask/future/future.hpp>
#include <boost/ztask/future/handle.hpp>
#include <boost/ztask/future/task.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/ztask/future/detail/future_base.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/bind.hpp>  // boost 1.54
#include <boost/function.hpp>  // boost 1.54
#include <boost/mem_fn.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      using boost::zcron::packaged_job_rejected;
      using boost::zcron::schedule_instant;
      using boost::zcron::schedule_regular;
      using boost::zcron::schedule_periodic;
      using boost::zcron::detail::schedule_base;
      using boost::zcron::detail::tasks_context_base;
      using boost::zcron::history::detail::job_iface;
      using boost::zcron::history::detail::job_base;
      using boost::zcron::history::detail::history_iface;
      using boost::zcron::history::detail::history_base;
      using boost::ztask::future::async;
      using boost::ztask::future::future;
      using boost::ztask::future::handle;
      using boost::ztask::future::task;
      using boost::ztask::future::promise_mark;
      using boost::ztask::future::detail::future_iface;
      using boost::ztask::future::detail::future_base;

      template<typename ReturnType, typename PoolType>
      class job : public job_base {
       public:
        job(const boost::function<ReturnType(void)>& fn,
            schedule_base const& schedule,
            PoolType & pool,
            callback<ReturnType> const& cb = \
            callback<ReturnType>())
          : job_base(),
            m_fn(fn),
            m_schedule_ptr(schedule.clone()),
            m_context_ptr(new tasks_context<PoolType>(pool)),
            m_cb(cb),
            m_monitor_ptr(NULL) {}

        virtual ~job() {
          delete m_schedule_ptr;
          delete m_context_ptr;
          delete m_monitor_ptr;
        }

        virtual job_iface* clone() const {
          job<ReturnType, PoolType>* result = new job<ReturnType, PoolType>(m_fn,
              *m_schedule_ptr, *(m_context_ptr->get_pool_ptr()), m_cb);
          if (NULL != m_monitor_ptr) {
            result->register_monitor(*m_monitor_ptr);
          }
          return result;
        }

        virtual history_iface* _get_history_iface() const {
          assert(NULL != m_monitor_ptr);
          return m_monitor_ptr->_get_history_iface();
        }

        virtual duration_type get_next_call_duration( \
          timepoint_type const& utc_since) const {
          return m_schedule_ptr->next_call_duration(utc_since);
        }

        virtual void finish_registration() {
          _get_history_iface()->finish_registration();
        }

        void process_custom_fn(future_iface* status_ptr,
            unsigned priority_in_context,
            const service_mark& mark = service_mark()) {
          try {
            m_context_ptr->run_async(boost::bind(boost::mem_fn( \
                &callback<ReturnType>::run_fn_and_callback_if_ok), &m_cb, m_fn),
                priority_in_context, mark);
          } catch ( boost::exception const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::ios_base::failure const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::domain_error const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::invalid_argument const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::length_error const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::out_of_range const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::logic_error const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::overflow_error const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::range_error const& e) {
            status_ptr->set_exception( boost::copy_exception( e) ); 
          } catch ( std::underflow_error const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::runtime_error const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::bad_alloc const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::bad_cast const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::bad_typeid const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch ( std::bad_exception const& e) {
            status_ptr->set_exception( boost::copy_exception( e) );
          } catch (...) {
            status_ptr->set_exception( boost::current_exception() );
          }
        }

        virtual void run_with_callback(unsigned priority_in_context,
            const service_mark& mark) {
          future<ReturnType> status;
          process_custom_fn(&status, priority_in_context, mark);
          if (status.has_exception()) {
            m_cb.run_callback_on_error(status.get_exception());
          }
        }

        void register_monitor(monitor& h) {
          if (NULL != m_monitor_ptr) {
            boost::throw_exception(packaged_job_rejected());
          }
          m_monitor_ptr = new monitor(h);
        }

        service_id get_service_id() const {
          if (NULL == m_monitor_ptr) {
            return service_id();
          }
          return m_monitor_ptr->get_service_id();
        }

        service_mark get_service_mark() const {
          if (NULL == m_monitor_ptr) {
            return service_mark();
          }
          return m_monitor_ptr->get_service_mark();
        }

        bool is_deactivated() const {
          if (NULL == m_monitor_ptr) {
            return false;
          }
          return m_monitor_ptr->is_deactivated();
        }

        bool try_set_service_id(const service_id& id) const {
          if (NULL == m_monitor_ptr || NULL == _get_history_iface()) {
            return false;
          }
          _get_history_iface()->set_service_id(id);
          return true;
        }

        bool try_set_service_mark(const service_mark& value) const {
          if (NULL == m_monitor_ptr || NULL == _get_history_iface()) {
            return false;
          }
          _get_history_iface()->set_service_mark(value);
          return true;
        }

        bool are_calls_allowed() const {
          const int total = _get_history_iface()->atomic_get_calls();
          const int limit = m_schedule_ptr->get_calls_limit();
          return (0 > limit) || (0 <= limit && total < limit);
        }

       private:
        boost::function<ReturnType(void)> m_fn;
        schedule_base* m_schedule_ptr;
        tasks_context<PoolType>* m_context_ptr;
        callback<ReturnType> m_cb;
        monitor* m_monitor_ptr;

        // noncopyable
        job(const job&);
        void operator=(const job&);
      };
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_JOB_H_

