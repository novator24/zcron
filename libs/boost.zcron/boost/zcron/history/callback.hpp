
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_HISTORY_CALLBACK_H_
#define BOOST_ZCRON_HISTORY_CALLBACK_H_
#include <boost/ztask/future/handle.hpp>
#include <boost/ztask/future/future.hpp>
#include <boost/zcron/history/detail/callback_base.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/exception_ptr.hpp>  // boost 1.54
#include <boost/shared_ptr.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      using boost::ztask::future::handle;
      using boost::ztask::future::future;
      using boost::zcron::history::detail::callback_base;

      // Functions classification. Type #1 of 4: R f();
      template <typename ReturnType>
      class callback : public callback_base {
       public:
        typedef boost::function<void(handle<ReturnType>,
            boost::exception_ptr)> cb_t;

        typedef boost::function<ReturnType(void)> fn_t;

        static void default_callback(handle<ReturnType> h,
            boost::exception_ptr e) {
        }

        callback(const cb_t& cb_fn = default_callback)
          : callback_base(),
            m_cb_fn(cb_fn) {}

        virtual ~callback() {}

        callback(const callback& obj)
          : callback_base(*this),
            m_cb_fn(obj.m_cb_fn) {}

        callback& operator=(const callback& obj) {
          if (this != &obj) {
            m_cb_fn = obj.m_cb_fn;
          }
          return *this;
        }

        virtual callback_iface* clone() const {
          return new callback<ReturnType>(m_cb_fn);
        }

        void run_callback_on_error(boost::exception_ptr e) {
          handle<ReturnType> h;
          m_cb_fn(h, e);
        }

        void run_fn_and_callback_if_ok(const fn_t& fn) {
          handle<ReturnType> h;
          assert(NULL != h.cast_of_future_ptr());
          h.cast_of_future_ptr()->set(fn());
          m_cb_fn(h, no_exceptions);
        }

       private:
        cb_t m_cb_fn;
      };

      // Functions classification. Type #2 of 4: void f();
      template <>
      class callback<void> : public callback_base {
       public:
        typedef boost::function<void(handle<void>,
            boost::exception_ptr)> cb_t;

        typedef boost::function<void(void)> fn_t;

        static void default_callback(handle<void> h,
            boost::exception_ptr e) {
        }

        callback(const cb_t& cb_fn = default_callback)
          : callback_base(),
            m_cb_fn(cb_fn) {}

        virtual ~callback() {}

        callback(const callback& obj)
          : callback_base(*this),
            m_cb_fn(obj.m_cb_fn) {}

        callback& operator=(const callback& obj) {
          if (this != &obj) {
            m_cb_fn = obj.m_cb_fn;
          }
          return *this;
        }

        virtual callback_iface* clone() const {
          return new callback<void>(m_cb_fn);
        }

        void run_callback_on_error(boost::exception_ptr e) {
          handle<void> h;
          m_cb_fn(h, e);
        }

        void run_fn_and_callback_if_ok(const fn_t& fn) {
          handle<void> h;
          assert(NULL != h.cast_of_future_ptr());
          fn();
          m_cb_fn(h, no_exceptions);
        }

       private:
        cb_t m_cb_fn;
      };

      // Functions classification. Type #3 of 4: R& f();
      template <typename ReturnType>
      class callback<ReturnType&> : public callback_base {
       public:
        typedef boost::function<void(handle<ReturnType&>,
            boost::exception_ptr)> cb_t;

        typedef boost::function<ReturnType&(void)> fn_t;

        static void default_callback(handle<ReturnType&> h,
            boost::exception_ptr e) {
        }

        callback(const cb_t& cb_fn = default_callback)
          : callback_base(),
            m_cb_fn(cb_fn) {}

        virtual ~callback() {}

        callback(const callback& obj)
          : callback_base(*this),
            m_cb_fn(obj.m_cb_fn) {}

        callback& operator=(const callback& obj) {
          if (this != &obj) {
            m_cb_fn = obj.m_cb_fn;
          }
          return *this;
        }

        virtual callback_iface* clone() const {
          return new callback<ReturnType&>(m_cb_fn);
        }

        void run_callback_on_error(boost::exception_ptr e) {
          handle<ReturnType&> h;
          m_cb_fn(h, e);
        }

        void run_fn_and_callback_if_ok(const fn_t& fn) {
          handle<ReturnType&> h;
          assert(NULL != h.cast_of_future_ptr());
          h.cast_of_future_ptr()->set(fn());
          m_cb_fn(h, no_exceptions);
        }

       private:
        cb_t m_cb_fn;
      };

      // Functions classification. Type #4 of 4: const R& f();
      template <typename ReturnType>
      class callback<const ReturnType&> : public callback_base {
       public:
        typedef boost::function<void(handle<const ReturnType&>,
            boost::exception_ptr)> cb_t;

        typedef boost::function<const ReturnType&(void)> fn_t;

        static void default_callback(handle<const ReturnType&> h,
            boost::exception_ptr e) {
        }

        callback(const cb_t& cb_fn = default_callback)
          : callback_base(),
            m_cb_fn(cb_fn) {}

        virtual ~callback() {}

        callback(const callback& obj)
          : callback_base(*this),
            m_cb_fn(obj.m_cb_fn) {}

        callback& operator=(const callback& obj) {
          if (this != &obj) {
            m_cb_fn = obj.m_cb_fn;
          }
          return *this;
        }

        virtual callback_iface* clone() const {
          return new callback<const ReturnType&>(m_cb_fn);
        }

        void run_callback_on_error(boost::exception_ptr e) {
          handle<const ReturnType&> h;
          m_cb_fn(h, e);
        }

        void run_fn_and_callback_if_ok(const fn_t& fn) {
          handle<const ReturnType&> h;
          assert(NULL != h.cast_of_future_ptr());
          h.cast_of_future_ptr()->set(fn());
          m_cb_fn(h, no_exceptions);
        }

       private:
        cb_t m_cb_fn;
      };

    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_CALLBACK_H_

