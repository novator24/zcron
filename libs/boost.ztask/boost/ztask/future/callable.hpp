
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_CALLABLE_H_
#define BOOST_ZTASK_FUTURE_CALLABLE_H_
#include <assert.h>
#include <boost/ztask/future/task.hpp>
#include <boost/ztask/future/detail/task_base.hpp>
#include <boost/shared_ptr.hpp>
namespace boost {
  namespace ztask {
    namespace future {
      using boost::ztask::future::detail::task_iface;
      using boost::ztask::future::detail::task_base;

      // NOTICE: task instance is renamed to promise after registration in pool
      class callable {
       public:
        template<typename ReturnType>
        callable(const task<ReturnType>& task, unsigned int priority)
          : m_promise_ptr(task.clone()),
            m_priority(priority) {
          assert(NULL != m_promise_ptr);
          assert(NULL != m_promise_ptr->get_future_ptr());
        }

        virtual ~callable() {
          delete m_promise_ptr;
        }

        callable(const callable& obj)
          : m_promise_ptr(obj.m_promise_ptr),
            m_priority(obj.m_priority) {}

        callable& operator=(const callable& obj) {
          if (this != &obj) {
            m_promise_ptr = obj.m_promise_ptr;
            m_priority = obj.m_priority;
          }
          return *this;
        }

        bool operator<(const callable& obj) const {
          return m_priority < obj.m_priority;
        }

        bool operator>(const callable& obj) const {
          return m_priority > obj.m_priority;
        }

        bool operator!=(const callable& obj) const {
          return (this->operator<(obj) || this->operator>(obj));
        }

        bool operator==(const callable& obj) const {
          return !(this->operator!=(obj));
        }

        void call_task_func() {
          assert(NULL != m_promise_ptr);
          m_promise_ptr->run();
        }

       private:
        task_iface* m_promise_ptr;
        unsigned int m_priority;
      };
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_CALLABLE_H_

