
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_SERVICES_UNBOUNDED_PRIO_SET_H_
#define BOOST_ZCRON_SERVICES_UNBOUNDED_PRIO_SET_H_
#include <boost/zcron/history/runnable.hpp>
#include <boost/zcron/detail/services_unbounded_prio_vec.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <functional>
#include <vector>
namespace boost {
  namespace zcron {
    using boost::zcron::history::runnable;
    using boost::zcron::detail::services_unbounded_prio_vec;

    class services_unbounded_prio_set_compare
      : public std::binary_function<runnable*, runnable*, bool> {
     public:
      bool operator()(const runnable* lhs, const runnable* rhs) const {
        return (NULL == lhs) || (NULL != rhs && *lhs < *rhs);
      }
    };

    class services_unbounded_prio_set
      : public services_unbounded_prio_vec<runnable*,
         std::vector<runnable*>, services_unbounded_prio_set_compare> {
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_SERVICES_UNBOUNDED_PRIO_SET_H_

