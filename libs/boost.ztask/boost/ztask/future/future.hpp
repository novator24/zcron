
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_FUTURE_H_
#define BOOST_ZTASK_FUTURE_FUTURE_H_
#include <boost/ztask/clock.hpp>
#include <boost/ztask/future/promise_id.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/ztask/future/detail/future_base.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/atomic.hpp>  // boost 1.54
#include <boost/exception_ptr.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    namespace future {
      using boost::ztask::mutex_type;
      using boost::ztask::guard_type;
      using boost::ztask::future::detail::future_iface;
      using boost::ztask::future::detail::future_base;

      // Functions classification. Type #1 of 4: R f();
      template<typename ReturnType>
      class future : public future_base {
       public:
        future()
          : future_base(),
            m_has_value(false),
            m_value_ptr(NULL) {}

        virtual ~future() { delete m_value_ptr; }

        bool has_value() { 
          guard_type lock(m_mutex);
          return m_has_value;
        }

        ReturnType get() {
          guard_type lock(m_mutex);
          return *m_value_ptr;
        }

        void set(const ReturnType& value) {
          guard_type lock(m_mutex);
          delete m_value_ptr;
          m_value_ptr = new ReturnType(value);
          m_has_value = true;
        }

       private:
        bool m_has_value;
        ReturnType* m_value_ptr;

        // noncopyable
        future(const future&);
        void operator=(const future&);
      };

      // Functions classification. Type #2 of 4: void f();
      template<>
      class future<void> : public future_base {
       public:
        future()
          : future_base() {}

        virtual ~future() {}

       private:
        // noncopyable
        future(const future&);
        void operator=(const future&);
      };

      // Functions classification. Type #3 of 4: R& f();
      template<typename ReturnType>
      class future<ReturnType&> : public future_base {
       public:
        future()
          : future_base(),
            m_has_value(false),
            m_value_ptr(NULL) {}

        virtual ~future() {}

        bool has_value() { 
          guard_type lock(m_mutex);
          return m_has_value;
        }

        ReturnType& get() {
          guard_type lock(m_mutex);
          return *m_value_ptr;
        }

        void set(ReturnType& value) {
          guard_type lock(m_mutex);
          m_value_ptr = &value;
          m_has_value = true;
        }

       private:
        bool m_has_value;
        ReturnType* m_value_ptr;

        // noncopyable
        future(const future&);
        void operator=(const future&);
      };

      // Functions classification. Type #4 of 4: const R& f();
      template<typename ReturnType>
      class future<const ReturnType&> : public future_base {
       public:
        future()
          : future_base(),
            m_has_value(false),
            m_value_ptr(NULL) {}

        virtual ~future() {}

        bool has_value() { 
          guard_type lock(m_mutex);
          return m_has_value;
        }

        const ReturnType& get() {
          guard_type lock(m_mutex);
          return *m_value_ptr;
        }

        void set(const ReturnType& value) {
          guard_type lock(m_mutex);
          m_value_ptr = &value;
          m_has_value = true;
        }

       private:
        bool m_has_value;
        const ReturnType* m_value_ptr;

        // noncopyable
        future(const future&);
        void operator=(const future&);
      };
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_FUTURE_H_

