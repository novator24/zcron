
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_HISTORY_SERVICE_ID_H_
#define BOOST_ZCRON_HISTORY_SERVICE_ID_H_
#include <boost/zcron/clock.hpp>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
namespace boost {
  namespace zcron {
    namespace history {
      using boost::zcron::mutex_type;
      using boost::zcron::guard_type;

      class service_id {
       public:
        service_id()
          : m_mutex(),
            m_number01(0),
            m_number02(0) {}

        virtual ~service_id() {}

        service_id(const service_id& obj) 
          : m_mutex(),
            m_number01(obj.m_number01),
            m_number02(obj.m_number02) {}

        service_id& operator=(const service_id& obj) {
          guard_type lock(m_mutex);
          if (this != &obj) {
            m_number01 = obj.m_number01;
            m_number02 = obj.m_number02;
          }
          return *this;
        }

        bool operator>(const service_id& obj) const {
          guard_type lock(m_mutex);
          return (m_number01 > obj.m_number01)
              || (m_number01 == obj.m_number01 && m_number02 > obj.m_number02);
        }

        bool operator<(const service_id& obj) const {
          guard_type lock(m_mutex);
          return (m_number01 < obj.m_number01)
              || (m_number01 == obj.m_number01 && m_number02 < obj.m_number02);
        }

        bool operator!=(const service_id& obj) const {
          guard_type lock(m_mutex);
          return this->operator>(obj) || this->operator<(obj);
        }

        bool operator==(const service_id& obj) const {
          guard_type lock(m_mutex);
          return !(this->operator!=(obj));
        }

        bool is_set() const {
          guard_type lock(m_mutex);
          return (0 == m_number01 && 0 == m_number02);
        }

        service_id& operator++() {
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
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_SERVICE_ID_H_

