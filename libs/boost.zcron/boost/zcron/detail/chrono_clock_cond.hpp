
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_DETAIL_CHRONO_CLOCK_COND_H_
#define BOOST_ZCRON_DETAIL_CHRONO_CLOCK_COND_H_
#include <boost/ztask/detail/config.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/static_assert.hpp>  // boost 1.54
#include <boost/tuple/tuple.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace detail {
      // FIXME(novator24@gmail.com): replace clock_cond_type to real type
      class chrono_not_implemented {};
      class chrono_clock_cond {
       public:
        chrono_clock_cond() : m_not_implemented() {}

        virtual ~chrono_clock_cond() {}

        chrono_clock_cond(const chrono_clock_cond&) {}

        chrono_clock_cond& operator=(const chrono_clock_cond&) {
          return *this;
        }

       private:
        chrono_not_implemented m_not_implemented;
      };
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_CHRONO_CLOCK_COND_H_

