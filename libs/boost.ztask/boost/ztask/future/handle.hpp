
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_HANDLE_H_
#define BOOST_ZTASK_FUTURE_HANDLE_H_
#include <boost/ztask/clock.hpp> 
#include <boost/ztask/future/promise_id.hpp> 
#include <boost/ztask/future/promise_mark.hpp> 
#include <boost/ztask/future/future.hpp> 
#include <boost/ztask/future/detail/handle_base.hpp> 
#include <boost/ztask/future/detail/future_base.hpp> 
#include <boost/shared_ptr.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    namespace future {
      using boost::ztask::clock_type;
      using boost::ztask::future::detail::handle_iface;
      using boost::ztask::future::detail::future_iface;
      using boost::ztask::future::detail::handle_base;
      using boost::ztask::future::detail::future_base;

      // Functions classification. Type #1 of 4: R f();
      template<typename ReturnType>
      class handle : public handle_base {
       public:
        handle()
          : handle_base(new future<ReturnType>()) {}

        virtual ~handle() {}

        handle(const handle& obj) 
          : handle_base(obj) {}

        handle& operator=(const handle& obj) {
          if (this != &obj) {
            handle_base::operator=(obj);
          }
          return *this;
        }

        handle_iface* clone() const {
          return new handle(*this);
        }

        future<ReturnType>* cast_of_future_ptr() const {
          return dynamic_cast<future<ReturnType>*>(m_future_ptr.get());
        }

        bool has_value() const { 
          return cast_of_future_ptr()->has_value();
        }

        ReturnType get() const {
          return cast_of_future_ptr()->get();
        }
      };

      // Functions classification. Type #2 of 4: void f();
      template<>
      class handle<void> : public handle_base {
       public:
        handle()
          : handle_base(new future<void>()) {}

        virtual ~handle() {}

        handle(const handle& obj) 
          : handle_base(obj) {}

        handle& operator=(const handle& obj) {
          if (this != &obj) {
            handle_base::operator=(obj);
          }
          return *this;
        }

        handle_iface* clone() const {
          return new handle(*this);
        }

        future<void>* cast_of_future_ptr() const {
          return dynamic_cast<future<void>*>(m_future_ptr.get());
        }
      };

      // Functions classification. Type #3 of 4: R& f();
      template<typename ReturnType>
      class handle <ReturnType&> : public handle_base {
       public:
        handle()
          : handle_base(new future<ReturnType&>()) {}

        virtual ~handle() {}

        handle(const handle& obj) 
          : handle_base(obj) {}

        handle& operator=(const handle& obj) {
          if (this != &obj) {
            handle_base::operator=(obj);
          }
          return *this;
        }

        handle_iface* clone() const {
          return new handle(*this);
        }

        future<ReturnType&>* cast_of_future_ptr() const {
          return dynamic_cast<future<ReturnType&>*>(m_future_ptr.get());
        }

        bool has_value() const { 
          return cast_of_future_ptr()->has_value();
        }

        ReturnType& get() const {
          return cast_of_future_ptr()->get();
        }
      };

      // Functions classification. Type #4 of 4: const R& f();
      template<typename ReturnType>
      class handle <const ReturnType&> : public handle_base {
       public:
        handle()
          : handle_base(new future<const ReturnType&>()) {}

        virtual ~handle() {}

        handle(const handle& obj) 
          : handle_base(obj) {}

        handle& operator=(const handle& obj) {
          if (this != &obj) {
            handle_base::operator=(obj);
          }
          return *this;
        }

        handle_iface* clone() const {
          return new handle(*this);
        }

        future<const ReturnType&>* cast_of_future_ptr() const {
          return dynamic_cast<future<const ReturnType&>*>(m_future_ptr.get());
        }

        bool has_value() const { 
          return cast_of_future_ptr()->has_value();
        }

        const ReturnType& get() const {
          return cast_of_future_ptr()->get();
        }
      };
    }  // namespace future 
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_HANDLE_H_

