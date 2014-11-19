
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_TASK_H_
#define BOOST_ZTASK_FUTURE_TASK_H_
#include <boost/ztask/exceptions.hpp>
#include <boost/ztask/detail/config.hpp>
#include <boost/ztask/future/promise_id.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/ztask/future/handle.hpp>
#include <boost/ztask/future/detail/future_base.hpp>
#include <boost/ztask/future/detail/task_base.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/bind.hpp>  // boost 1.54
#include <boost/function.hpp>  // boost 1.54
#include <boost/mem_fn.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    namespace future {
      using boost::ztask::packaged_task_rejected;
      using boost::ztask::future::detail::future_iface;
      using boost::ztask::future::detail::task_iface;
      using boost::ztask::future::detail::future_base;
      using boost::ztask::future::detail::task_base;

      // Functions classification. Type #1 of 4: R f();
      template<class ReturnType>
      class task : public task_base {
       public:
        task(const boost::function<ReturnType(void)>& fn)
          : task_base(),
            m_fn(fn) {}

        virtual ~task() {}

        virtual task_iface* clone() const {
          task<ReturnType>* result = new task<ReturnType>(m_fn);
          if (NULL != m_handle_ptr) {
            result->register_handle(*m_handle_ptr);
          }
          return result;
        }

        handle<ReturnType>* cast_of_handle_ptr() const {
          return dynamic_cast<handle<ReturnType>*>(_get_handle_iface());
        }

        void custom_fn() {
          assert(NULL != cast_of_handle_ptr()
              && NULL != cast_of_handle_ptr()->cast_of_future_ptr());
          cast_of_handle_ptr()->cast_of_future_ptr()->set( m_fn() );
        }

        void run() {
          assert(NULL != _get_handle_iface() && NULL != _get_handle_iface()->_get_future_iface());
          if (_get_handle_iface()->_get_future_iface()->atomic_is_deactivated()) {
            return;
          }
          _get_handle_iface()->_get_future_iface()->process_void_fn( \
              boost::bind(boost::mem_fn(&task<ReturnType>::custom_fn), this));
        }

       private:
        boost::function<ReturnType(void)> m_fn;

        // noncopyable
        task(const task&);
        void operator=(const task&);
      };

      // Functions classification. Type #2 of 4: void f();
      template<>
      class task<void> : public task_base {
       public:
        task(const boost::function<void(void)>& fn)
          : task_base(),
            m_fn(fn) {}

        virtual ~task() {}

        virtual task_iface* clone() const {
          task<void>* result = new task<void>(m_fn);
          if (NULL != m_handle_ptr) {
            result->register_handle(*m_handle_ptr);
          }
          return result;
        }

        handle<void>* cast_of_handle_ptr() const {
          return dynamic_cast<handle<void>*>(_get_handle_iface());
        }

        void custom_fn() {
          assert(NULL != cast_of_handle_ptr()
              && NULL != cast_of_handle_ptr()->cast_of_future_ptr());
          m_fn();
        }

        void run() {
          assert(NULL != _get_handle_iface() && NULL != _get_handle_iface()->_get_future_iface());
          if (_get_handle_iface()->_get_future_iface()->atomic_is_deactivated()) {
            return;
          }
          _get_handle_iface()->_get_future_iface()->process_void_fn( \
              boost::bind(boost::mem_fn(&task<void>::custom_fn), this));
        }

       private:
        boost::function<void(void)> m_fn;

        // noncopyable
        task(const task&);
        void operator=(const task&);
      };

      // Functions classification. Type #3 of 4: R& f();
      template<class ReturnType>
      class task<ReturnType&> : public task_base {
       public:
        task(const boost::function<ReturnType&(void)>& fn)
          : task_base(),
            m_fn(fn) {}

        virtual ~task() {}

        virtual task_iface* clone() const {
          task<ReturnType&>* result = new task<ReturnType&>(m_fn);
          if (NULL != m_handle_ptr) {
            result->register_handle(*m_handle_ptr);
          }
          return result;
        }

        handle<ReturnType&>* cast_of_handle_ptr() const {
          return dynamic_cast<handle<ReturnType&>*>(_get_handle_iface());
        }

        void custom_fn() {
          assert(NULL != cast_of_handle_ptr()
              && NULL != cast_of_handle_ptr()->cast_of_future_ptr());
          cast_of_handle_ptr()->cast_of_future_ptr()->set( m_fn() );
        }

        void run() {
          assert(NULL != _get_handle_iface() && NULL != _get_handle_iface()->_get_future_iface());
          if (_get_handle_iface()->_get_future_iface()->atomic_is_deactivated()) {
            return;
          }
          _get_handle_iface()->_get_future_iface()->process_void_fn( \
              boost::bind(boost::mem_fn(&task<ReturnType&>::custom_fn), this));
        }

       private:
        boost::function<ReturnType&(void)> m_fn;
        handle<ReturnType&>* m_handle_ptr;

        // noncopyable
        task(const task&);
        void operator=(const task&);
      };

      // Functions classification. Type #4 of 4: const R& f();
      template<class ReturnType>
      class task<const ReturnType&> : public task_base {
       public:
        task(const boost::function<const ReturnType&(void)>& fn)
          : task_base(),
            m_fn(fn) {}

        virtual ~task() {}

        virtual task_iface* clone() const {
          task<const ReturnType&>* result = new task<const ReturnType&>(m_fn);
          if (NULL != m_handle_ptr) {
            result->register_handle(*m_handle_ptr);
          }
          return result;
        }

        handle<const ReturnType&>* cast_of_handle_ptr() const {
          return dynamic_cast<handle<const ReturnType&>*>(_get_handle_iface());
        }

        void custom_fn() {
          assert(NULL != cast_of_handle_ptr()
              && NULL != cast_of_handle_ptr()->cast_of_future_ptr());
          cast_of_handle_ptr()->cast_of_future_ptr()->set( m_fn() );
        }

        void run() {
          assert(NULL != _get_handle_iface() && NULL != _get_handle_iface()->_get_future_iface());
          if (_get_handle_iface()->_get_future_iface()->atomic_is_deactivated()) {
            return;
          }
          _get_handle_iface()->_get_future_iface()->process_void_fn( \
              boost::bind(boost::mem_fn(&task<const ReturnType&>::custom_fn), this));
        }

       private:
        boost::function<const ReturnType&(void)> m_fn;

        // noncopyable
        task(const task&);
        void operator=(const task&);
      };
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_TASK_H_

