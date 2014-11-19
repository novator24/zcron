
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZTASK_FUTURE_PROMISE_ID_H_
#define BOOST_ZTASK_FUTURE_PROMISE_ID_H_
#include <boost/ztask/clock.hpp>
#include <boost/scoped_ptr.hpp>  // boost 1.54
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
namespace boost {
  namespace ztask {
    namespace future {
      using boost::ztask::mutex_type;
      using boost::ztask::guard_type;

      class promise_id {
       public:
        promise_id()
          : m_mutex(),
            m_number01(0),
            m_number02(0) {}

        virtual ~promise_id() {}

        promise_id(const promise_id& obj) 
          : m_mutex(),
            m_number01(obj.m_number01),
            m_number02(obj.m_number02) {}

        promise_id& operator=(const promise_id& obj) {
          guard_type lock(m_mutex);
          if (this != &obj) {
            m_number01 = obj.m_number01;
            m_number02 = obj.m_number02;
          }
          return *this;
        }

        bool operator>(const promise_id& obj) const {
          guard_type lock(m_mutex);
          return (m_number01 > obj.m_number01)
              || (m_number01 == obj.m_number01 && m_number02 > obj.m_number02);
        }

        bool operator<(const promise_id& obj) const {
          guard_type lock(m_mutex);
          return (m_number01 < obj.m_number01)
              || (m_number01 == obj.m_number01 && m_number02 < obj.m_number02);
        }

        bool operator!=(const promise_id& obj) const {
          guard_type lock(m_mutex);
          return this->operator>(obj) || this->operator<(obj);
        }

        bool operator==(const promise_id& obj) const {
          guard_type lock(m_mutex);
          return !(this->operator!=(obj));
        }

        bool is_set() const {
          guard_type lock(m_mutex);
          return (0 == m_number01 && 0 == m_number02);
        }

        promise_id& operator++() {
          guard_type lock(m_mutex);
          if(m_number02 < m_number02 + 1) {
            m_number02++;
          } else {
            m_number02 = 0;
            m_number01++;
          }
          return *this;
        }

        std::string to_string() const {
          guard_type lock(m_mutex);
          char buffer[256];
          snprintf(buffer, 256, "<%u:%u>", m_number01, m_number02);
          return buffer;
        }

       private:
        // multi-thread controllers [always first]
        mutable mutex_type m_mutex;

        unsigned m_number01;
        unsigned m_number02;
      };
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_PROMISE_ID_H_

