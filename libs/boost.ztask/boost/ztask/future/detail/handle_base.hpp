
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_DETAIL_HANDLE_BASE_H_
#define BOOST_ZTASK_FUTURE_DETAIL_HANDLE_BASE_H_
#include <boost/ztask/clock.hpp>
#include <boost/ztask/future/promise_id.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/ztask/future/detail/future_base.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/function.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    namespace future {
      namespace detail {
        using boost::ztask::clock_type;
        using boost::ztask::future::promise_id;
        using boost::ztask::future::promise_mark;

        class handle_iface {
         public:
          virtual ~handle_iface() {}

          virtual handle_iface* clone() const = 0;

          virtual future_iface* _get_future_iface() const = 0;

          virtual void wait() = 0;

          virtual void wait_for(duration_type const& timeout_duration) = 0;

          virtual void wait_until(timepoint_type const& timeout_time) = 0;

          virtual promise_id get_promise_id() const = 0;

          virtual promise_mark get_promise_mark() const = 0;

          virtual void deactivate() = 0;

          virtual bool is_deactivated() const = 0;

          virtual bool is_ready() const = 0;

          virtual bool has_exception() const = 0;

          virtual boost::exception_ptr get_exception() const = 0;
        };

        class handle_base : public handle_iface {
         public:
          handle_base(future_base* future_ptr)
            : m_future_ptr(future_ptr) {}

          virtual ~handle_base() {}

          handle_base(const handle_base& obj) 
            : m_future_ptr(obj.m_future_ptr) {
          }

          handle_base& operator=(const handle_base& obj) {
            if (this != &obj) {
              m_future_ptr = obj.m_future_ptr;
            }
            return *this;
          }

          future_iface* _get_future_iface() const {
            return m_future_ptr.get();
          }

          void wait() {
            m_future_ptr->wait();
          }

          void wait_for(duration_type const& timeout_duration) {
            m_future_ptr->wait_for(timeout_duration);
          }

          void wait_until(timepoint_type const& timeout_time) {
            m_future_ptr->wait_until(timeout_time);
          }

          promise_id get_promise_id() const {
            return m_future_ptr->get_promise_id();
          }

          promise_mark get_promise_mark() const {
            return m_future_ptr->get_promise_mark();
          }

          void deactivate() {
            m_future_ptr->atomic_deactivate();
          }

          bool is_deactivated() const {
            return m_future_ptr->atomic_is_deactivated();
          }

          bool is_ready() const {
            return m_future_ptr->atomic_is_ready();
          }

          bool has_exception() const {
            return m_future_ptr->has_exception();
          }

          boost::exception_ptr get_exception() const {
            return m_future_ptr->get_exception();
          }

         protected:
          boost::shared_ptr<future_iface> m_future_ptr;
        };
      }  // namespace detail
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_DETAIL_HANDLE_BASE_H_

