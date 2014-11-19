
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_DETAIL_FUTURE_BASE_H_
#define BOOST_ZTASK_FUTURE_DETAIL_FUTURE_BASE_H_
#include <boost/ztask/future/promise_id.hpp>
#include <boost/ztask/future/promise_mark.hpp>
#include <boost/ztask/clock.hpp>
#include <boost/function.hpp>  // boost 1.54
#include <boost/exception_ptr.hpp>  // boost 1.54
#include <boost/atomic.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    namespace future {
      namespace detail {
        using boost::ztask::timepoint_type;
        using boost::ztask::duration_type;
        using boost::ztask::mutex_type;
        using boost::ztask::condition_type;
        using boost::ztask::guard_type;
        using boost::ztask::status_type;

        class future_iface {
         public:
          typedef boost::function<void (void)> void_function_t;

          virtual ~future_iface() {}

          virtual void wait() = 0;

          virtual void wait_for(duration_type const& timeout_duration) = 0;

          virtual void wait_until(timepoint_type const& timeout_time) = 0;

          virtual void process_void_fn(const void_function_t& void_fn) = 0;

          virtual void atomic_deactivate() = 0;

          virtual bool atomic_is_deactivated() const = 0;

          virtual bool atomic_is_ready() const = 0;

          virtual void atomic_set_ready(const bool ready) = 0;

          virtual promise_id get_promise_id() const = 0;

          virtual void set_promise_id(const promise_id& value) = 0;

          virtual promise_mark get_promise_mark() const = 0;

          virtual void set_promise_mark(const promise_mark& value) = 0;

          virtual bool has_exception() = 0;

          virtual boost::exception_ptr get_exception() = 0;

          virtual void set_exception(const boost::exception_ptr& value) = 0;
        };

        class future_base : public future_iface {
         public:
          future_base()
            : m_mutex(),
              m_waiter(),
              m_ready(),
              m_deactivated(),
              m_promise_id(),
              m_promise_mark(),
              m_has_exception(false),
              m_exception_ptr() {}

          virtual ~future_base() {}

          virtual void wait() {
            guard_type lock(m_mutex);
            while (!m_ready && !m_deactivated) {
              m_waiter.wait(lock);
            }
          } 

          virtual void wait_for(duration_type const& timeout_duration) {
            guard_type lock(m_mutex);
            while (!m_ready && !m_deactivated) {
              status_type st( m_waiter.wait_for(lock, timeout_duration) );
              if ( status_type_timeout == st && !m_ready) {
                return;
              }
            }
          }

          virtual void wait_until(timepoint_type const& timeout_time) {
            guard_type lock(m_mutex);
            while (!m_ready && !m_deactivated) {
              status_type st( m_waiter.wait_until(lock, timeout_time) );
              if ( status_type_timeout == st && !m_ready) {
                return;
              }
            }
          }

          virtual void process_void_fn(const void_function_t& void_fn) {
            try {
              void_fn();
            } catch ( boost::exception const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::ios_base::failure const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::domain_error const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::invalid_argument const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::length_error const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::out_of_range const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::logic_error const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::overflow_error const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::range_error const& e) {
              set_exception( boost::copy_exception( e) ); 
            } catch ( std::underflow_error const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::runtime_error const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::bad_alloc const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::bad_cast const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::bad_typeid const& e) {
              set_exception( boost::copy_exception( e) );
            } catch ( std::bad_exception const& e) {
              set_exception( boost::copy_exception( e) );
            } catch (...) {
              set_exception( boost::current_exception() );
            }
            if (!m_deactivated) {
              m_ready = true;
            }
            m_waiter.notify_all();
          }

          void atomic_deactivate() {
            m_deactivated = true;
          }

          bool atomic_is_deactivated() const {
            return m_deactivated;
          }

          bool atomic_is_ready() const {
            return m_ready;
          }

          void atomic_set_ready(const bool ready) {
            m_ready = ready;
          }

          promise_id get_promise_id() const {
            return m_promise_id;
          }

          void set_promise_id(const promise_id& value) {
            m_promise_id = value;
          }

          promise_mark get_promise_mark() const {
            return m_promise_mark;
          }

          void set_promise_mark(const promise_mark& value) {
            m_promise_mark = value;
          }

          bool has_exception() {
            guard_type lock(m_mutex);
            return m_has_exception;
          }

          boost::exception_ptr get_exception() {
            guard_type lock(m_mutex);
            return m_exception_ptr;
          }

          void set_exception(const boost::exception_ptr& value) {
            guard_type lock(m_mutex);
            m_exception_ptr = value;
            m_has_exception = true;
          }

         protected:
          // multi-thread controllers [always first]
          mutex_type m_mutex;
          condition_type m_waiter;

          boost::atomic<bool> m_ready;
          boost::atomic<bool> m_deactivated;
          promise_id m_promise_id;
          promise_mark m_promise_mark;
          bool m_has_exception;
          boost::exception_ptr m_exception_ptr;
        };
      }  // namespace detail
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_DETAIL_FUTURE_BASE_H_

