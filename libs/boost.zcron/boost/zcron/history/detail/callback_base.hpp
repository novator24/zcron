
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_DETAIL_CALLBACK_BASE_H_
#define BOOST_ZCRON_HISTORY_DETAIL_CALLBACK_BASE_H_
#include <boost/exception_ptr.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    namespace history {
      namespace detail {
        class callback_iface {
         public:
          static boost::exception_ptr no_exceptions;

          callback_iface() {}

          virtual ~callback_iface() {}

          virtual callback_iface* clone() const = 0;

        };

        boost::exception_ptr callback_iface::no_exceptions;

        class callback_base : public callback_iface {
         public:
          virtual ~callback_base() {}
        };
      }  // namespace detail
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_DETAIL_CALLBACK_BASE_H_

