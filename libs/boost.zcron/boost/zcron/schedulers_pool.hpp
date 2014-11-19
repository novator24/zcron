
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_SCHEDULERS_POOL_H_
#define BOOST_ZCRON_SCHEDULERS_POOL_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/exceptions.hpp>
#include <boost/zcron/tasks_context.hpp>
#include <boost/zcron/detail/tasks_context_base.hpp>
#include <boost/zcron/history/service_id.hpp>
#include <boost/zcron/history/service_mark.hpp>
#include <boost/zcron/history/monitor.hpp>
#include <boost/zcron/history/job.hpp>
#include <boost/zcron/history/runnable.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/thread.hpp>  // boost 1.54
#include <boost/bind.hpp>  // boost 1.54
#include <boost/mem_fn.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    using boost::zcron::status_type;
    using boost::zcron::detail::tasks_context_base;
    using boost::zcron::history::service_id;
    using boost::zcron::history::service_mark;
    using boost::zcron::history::monitor;
    using boost::zcron::history::job;
    using boost::zcron::history::runnable;
    using boost::ztask::workers_pool;

    template <typename Queue, typename Set>
    class schedulers_pool {
     public:
      schedulers_pool(size_t pool_size) 
        : m_queues_array(new Queue[pool_size]),
          m_sets_array(new Set[pool_size]),
          m_last_service_id(),
          m_counter(0),
          m_thread_group(),
          m_shutdown(false) {
        for (size_t i = 0; i < pool_size; ++i) {
          m_thread_group.add_thread(new boost::thread(
              boost::bind(boost::mem_fn(&schedulers_pool<Queue,Set>::loop_as_consumer),
              this, i)));
        }
      }

      virtual ~schedulers_pool() {
        shutdown();
        delete [] m_queues_array;
        delete [] m_sets_array;
      }

      template <typename ReturnType, typename PoolType>
      monitor submit_as_producer(job<ReturnType, PoolType>& job,
          unsigned int priority, const service_mark& service_mark) {
        if (m_shutdown) {
          boost::throw_exception( packaged_job_rejected() );
        }
        monitor mon;
        job.register_monitor(mon);
        m_counter++;
        int thread_index = m_counter % m_thread_group.size();
        // FIXME(novator24@gmail.com): need a check if service already exist
        // if(job.get_service_id() == service_id()) {
         //  boost::throw_exception( packaged_job_rejected() );
        // }
        if (!job.try_set_service_id(++m_last_service_id)) {
          boost::throw_exception(packaged_job_rejected());
        }
        if (!job.try_set_service_mark(service_mark)) {
          boost::throw_exception(packaged_job_rejected());
        }
        runnable* obj_ptr = new runnable(job, priority);
        while (!m_queues_array[thread_index].put(obj_ptr)) {}
        return mon;
      }

      void loop_as_consumer(size_t thread_index) {
        runnable* obj_ptr = NULL;
        while (true) {
          if (m_shutdown) {
            return;
          }
          // FIXME(novator24@gmail.com): remove hard-coded value (1 hour)
          timepoint_type instant = clock_util_type::now();
          duration_type duration_limit(3600.0);
          duration_type min_duration(0.0);
          min_duration = duration_limit;
          for (size_t i = 0; i < m_sets_array[thread_index].size(); ++i) {
            m_sets_array[thread_index].get(i, obj_ptr);
            obj_ptr->try_call_run_func(instant);
            duration_type duration = obj_ptr->get_duration_next_call();
            if (duration < min_duration) {
              min_duration = duration;
            }
          }
          timepoint_type timeout_time = instant + min_duration;
          status_type status;
          if (m_queues_array[thread_index].take_until(obj_ptr, timeout_time, &status)
              && status != status_type_timeout) {
            m_sets_array[thread_index].push_back(obj_ptr);
            m_sets_array[thread_index].sort_if_possible();
            obj_ptr->call_finish_registration();
          }
        }
      }

      void shutdown() {
        m_shutdown = true;
        for (size_t i = 0; i < m_thread_group.size(); ++i) {
          m_queues_array[i].shutdown();
        }
        m_thread_group.join_all();
      }

      void shutdown_now() {
        m_shutdown = true;
        for (size_t i = 0; i < m_thread_group.size(); ++i) {
          std::vector<runnable*> trash;
          m_queues_array[i].shutdown_now(trash);
          for(size_t i = 0; i < trash.size(); ++i) {
            delete trash[i];
          }
        }
        m_thread_group.join_all();
      }

     private:
      Queue* m_queues_array;
      Set* m_sets_array;
      service_id m_last_service_id;
      boost::atomic<int> m_counter;
      boost::thread_group m_thread_group;
      boost::atomic<bool> m_shutdown;

      // noncopyable
      schedulers_pool(const schedulers_pool&);
      void operator=(const schedulers_pool&);
    };
  }  // namespace zcron
}  // namespace boost

#endif  // BOOST_ZCRON_SCHEDULERS_POOL_H_

