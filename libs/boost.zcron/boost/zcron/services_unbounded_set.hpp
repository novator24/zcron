
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_SERVICES_UNBOUNDED_SET_H_
#define BOOST_ZCRON_SERVICES_UNBOUNDED_SET_H_
#include <boost/zcron/history/runnable.hpp>
#include <boost/zcron/detail/services_unbounded_vec.hpp>
#include <boost/config.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    using boost::zcron::history::runnable;
    using boost::zcron::detail::services_unbounded_vec;

    class services_unbounded_set : public services_unbounded_vec<runnable*> {
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_SERVICES_UNBOUNDED_SET_H_

