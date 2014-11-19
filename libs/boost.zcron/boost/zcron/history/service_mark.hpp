
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_HISTORY_SERVICE_MARK_H_
#define BOOST_ZCRON_HISTORY_SERVICE_MARK_H_
namespace boost {
  namespace zcron {
    namespace history {
      class service_mark {
       public:
        service_mark(const std::string& str = "")
          : m_size(str.size()), 
            m_buf(new char[m_size]) {
          strncpy(m_buf, str.c_str(), m_size);
        }

        virtual ~service_mark() {
          delete [] m_buf;
        }

        service_mark(const service_mark& obj)
          : m_size(obj.m_size),
            m_buf(new char[m_size]) {
          strncpy(m_buf, obj.m_buf, m_size);
        }

        service_mark& operator=(const service_mark& obj) {
          if (this != &obj) {
            delete [] m_buf;
            m_size = obj.m_size;
            m_buf = new char[m_size];
            strncpy(m_buf, obj.m_buf, m_size);
          }
          return *this;
        }

        std::string to_string() const {
          return std::string(m_buf, m_size);
        }

       private:
        size_t m_size;
        char* m_buf;
      };
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_SERVICE_MARK_H_

