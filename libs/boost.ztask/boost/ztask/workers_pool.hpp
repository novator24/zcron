
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_WORKERS_POOL_H_
#define BOOST_ZTASK_WORKERS_POOL_H_
#include <boost/ztask/exceptions.hpp>
#include <boost/ztask/future/promise_id.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/ztask/future/handle.hpp>
#include <boost/ztask/future/task.hpp>
#include <boost/ztask/future/callable.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/thread.hpp>  // boost 1.54
#include <boost/shared_ptr.hpp>  // boost 1.54
#include <boost/bind.hpp>  // boost 1.54
#include <boost/mem_fn.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    using boost::ztask::future::promise_id;
    using boost::ztask::future::promise_mark;
    using boost::ztask::future::handle;
    using boost::ztask::future::task;
    using boost::ztask::future::callable;

    template <typename Queue>
    class workers_pool {
     public:
      workers_pool(size_t pool_size) 
        : m_queue(),
          m_last_promise_id(),
          m_thread_group(),
          m_shutdown(false) {
        for (size_t i = 0; i < pool_size; ++i) {
          m_thread_group.add_thread(new boost::thread(
              boost::bind(boost::mem_fn(&workers_pool<Queue>::loop_as_consumer),
              this)));
        }
      }

      virtual ~workers_pool() { shutdown(); }

      template <typename ReturnType>
      handle<ReturnType> submit_as_producer(task<ReturnType>& task,
          unsigned priority, const promise_mark& mark) {
        if (m_shutdown) {
          boost::throw_exception( packaged_task_rejected() );
        }
        // FIXME(novator24@gmail.com): need a check on id duplication
        // if (task.get_promise_id() != promise_id()) {
         // boost::throw_exception( packaged_task_rejected() );
        // }
        handle<ReturnType> handle;
        task.register_handle(handle);
        assert(NULL != task._get_future_iface());
        if (!task.try_set_promise_id(++m_last_promise_id)) {
          boost::throw_exception( packaged_task_rejected() );
        }
        if (!task.try_set_promise_mark(mark)) {
          boost::throw_exception( packaged_task_rejected() );
        }
        callable* obj_ptr = new callable(task, priority);
        while (!m_queue.put(obj_ptr)) {}
        return handle;
      }

      void loop_as_consumer() {
        callable* obj_ptr = 0;
        while (true) {
          if (m_shutdown) {
            return;
          }
          if (m_queue.take(obj_ptr)) {
            obj_ptr->call_task_func();
            delete obj_ptr;
          }
        }
      }

      void shutdown() {
        m_shutdown = true;
        m_queue.shutdown();
        m_thread_group.join_all();
      }

      void shutdown_now() {
        m_shutdown = true;
        std::vector<callable*> trash;
        m_queue.shutdown_now(trash);
        for(size_t i = 0; i < trash.size(); ++i) {
          delete trash[i];
        }
        m_thread_group.join_all();
      }

     private:
      Queue m_queue;
      promise_id m_last_promise_id;
      boost::thread_group m_thread_group;
      boost::atomic<bool> m_shutdown;

      // noncopyable
      workers_pool(const workers_pool&);
      void operator=(const workers_pool&);
    };
  }  // namespace ztask
}  // namespace boost

#endif  // BOOST_ZTASK_WORKERS_POOL_H_

