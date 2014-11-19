
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_TASKS_CONTEXT_H_
#define BOOST_ZCRON_TASKS_CONTEXT_H_
#include <boost/zcron/exceptions.hpp>
#include <boost/zcron/clock.hpp>
#include <boost/zcron/exceptions.hpp>
#include <boost/zcron/detail/tasks_context_base.hpp>
#include <boost/ztask/unbounded_fifo.hpp>
#include <boost/ztask/unbounded_prio_fifo.hpp>
#include <boost/ztask/workers_pool.hpp>
#include <boost/ztask/future/async.hpp>
#include <boost/ztask/future/task.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/config.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    using boost::zcron::detail::tasks_context_iface;
    using boost::zcron::detail::tasks_context_base;
    using boost::zcron::history::service_mark;
    using boost::ztask::future::async;
    using boost::ztask::future::task;
    using boost::ztask::future::promise_mark;
    using boost::ztask::unbounded_fifo;
    using boost::ztask::unbounded_prio_fifo;
    using boost::ztask::workers_pool;

    template<typename PoolType>
    class tasks_context : public tasks_context_base {
     public:
      tasks_context(PoolType& work_pool)
        : tasks_context_base(),
          m_pool_ptr(&work_pool) {}

      virtual ~tasks_context() {}

      virtual tasks_context_iface* clone() const {
        return new tasks_context(*m_pool_ptr);
      }

      virtual void run_async(const void_function_t& fn,
        unsigned priority, const service_mark& mark) {
        boost::throw_exception(tasks_context_not_supported());
      }

      PoolType* get_pool_ptr() const {
        return m_pool_ptr;
      }

     private:
      PoolType* m_pool_ptr;

      // noncopyable
      tasks_context(const tasks_context&);
      void operator=(const tasks_context&);
    };

    template<>
    class tasks_context<workers_pool<unbounded_fifo> > : public tasks_context_base {
     public:
      tasks_context(workers_pool<unbounded_fifo>& work_pool)
        : tasks_context_base(),
          m_pool_ptr(&work_pool) {}

      virtual ~tasks_context() {}

      virtual tasks_context_iface* clone() const {
        return new tasks_context(*m_pool_ptr);
      }

      virtual void run_async(const void_function_t& fn,
        unsigned priority, const service_mark& mark) {
        task<void> t(fn);
        async(t, priority, *m_pool_ptr, promise_mark(mark.to_string()));
      }

      workers_pool<unbounded_fifo>* get_pool_ptr() const {
        return m_pool_ptr;
      }

     private:
      workers_pool<unbounded_fifo>* m_pool_ptr;

      // noncopyable
      tasks_context(const tasks_context&);
      void operator=(const tasks_context&);
    };

    template<>
    class tasks_context<workers_pool<unbounded_prio_fifo> > : public tasks_context_base {
     public:
      tasks_context(workers_pool<unbounded_prio_fifo>& work_pool)
        : tasks_context_base(),
          m_pool_ptr(&work_pool) {}

      virtual ~tasks_context() {}

      virtual tasks_context_iface* clone() const {
        return new tasks_context(*m_pool_ptr);
      }

      virtual void run_async(const void_function_t& fn,
        unsigned priority, const service_mark& mark) {
        task<void> t(fn);
        async(t, priority, *m_pool_ptr, promise_mark(mark.to_string()));
      }

      workers_pool<unbounded_prio_fifo>* get_pool_ptr() const {
        return m_pool_ptr;
      }

     private:
      workers_pool<unbounded_prio_fifo>* m_pool_ptr;

      // noncopyable
      tasks_context(const tasks_context&);
      void operator=(const tasks_context&);
    };

  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_TASKS_CONTEXT_H_

