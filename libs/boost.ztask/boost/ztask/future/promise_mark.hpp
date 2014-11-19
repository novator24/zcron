
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZTASK_FUTURE_PROMISE_MARK_H_
#define BOOST_ZTASK_FUTURE_PROMISE_MARK_H_
#include <string.h>
namespace boost {
  namespace ztask {
    namespace future {
      class promise_mark {
       public:
        promise_mark(const std::string& str = "")
          : m_size(str.size()), 
            m_buf(new char[m_size]) {
          strncpy(m_buf, str.c_str(), m_size);
        }

        virtual ~promise_mark() {
          delete [] m_buf;
        }

        promise_mark(const promise_mark& obj)
          : m_size(obj.m_size),
            m_buf(new char[m_size]) {
          strncpy(m_buf, obj.m_buf, m_size);
        }

        promise_mark& operator=(const promise_mark& obj) {
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
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_PROMISE_MARK_H_

