
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_DETAIL_TASK_BASE_H_
#define BOOST_ZTASK_FUTURE_DETAIL_TASK_BASE_H_
#include <boost/ztask/future/promise_id.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/ztask/future/detail/handle_base.hpp>
#include <boost/function.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    namespace future {
      namespace detail {
        using boost::ztask::future::promise_id;
        using boost::ztask::future::promise_mark;

        class task_iface {
         public:
          typedef boost::function<void (void)> void_function_t;

          task_iface() {}

          virtual ~task_iface() {}

          virtual task_iface* clone() const = 0;

          virtual handle_iface* _get_handle_iface() const = 0;

          virtual void register_handle(const handle_iface& h) = 0;

          virtual promise_id get_promise_id() const = 0;

          virtual promise_mark get_promise_mark() const = 0;

          virtual bool is_deactivated() const = 0;

          virtual bool try_set_promise_id(const promise_id& value) const = 0;

          virtual bool try_set_promise_mark(const promise_mark& value) const = 0;

          virtual void run() = 0;
        };

        class task_base : public task_iface {
         public:
          task_base()
            : m_handle_ptr(NULL) {}

          virtual ~task_base() {
            delete m_handle_ptr;
          }

          handle_iface* _get_handle_iface() const {
            return m_handle_ptr;
          }

          void register_handle(const handle_iface& h) {
            if (NULL != m_handle_ptr) {
              boost::throw_exception(packaged_task_rejected());
            }
            m_handle_ptr = h.clone();
          }

          promise_id get_promise_id() const {
            if (NULL == m_handle_ptr) {
              return promise_id();
            }
            return m_handle_ptr->get_promise_id();
          }

          promise_mark get_promise_mark() const {
            if (NULL == m_handle_ptr) {
              return promise_mark();
            }
            return m_handle_ptr->get_promise_mark();
          }

          bool is_deactivated() const {
            if (NULL == m_handle_ptr) {
              return false;
            }
            return m_handle_ptr->is_deactivated();
          }

          bool try_set_promise_id(const promise_id& id) const {
            if (NULL == _get_handle_iface() || NULL == _get_handle_iface()->_get_future_iface()) {
              return false;
            }
            _get_handle_iface()->_get_future_iface()->set_promise_id(id);
            return true;
          }

          bool try_set_promise_mark(const promise_mark& value) const {
            if (NULL == _get_handle_iface() || NULL == _get_handle_iface()->_get_future_iface()) {
              return false;
            }
            _get_handle_iface()->_get_future_iface()->set_promise_mark(value);
            return true;
          }

         protected:
          handle_iface* m_handle_ptr;
        };
      }  // namespace detail
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_DETAIL_TASK_BASE_H_

