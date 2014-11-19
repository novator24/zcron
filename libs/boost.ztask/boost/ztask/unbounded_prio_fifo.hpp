
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZTASK_UNBOUNDED_PRIO_FIFO_H_
#define BOOST_ZTASK_UNBOUNDED_PRIO_FIFO_H_
#include <boost/ztask/future/callable.hpp>
#include <boost/ztask/detail/unbounded_prio_queue.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <functional>
#include <vector>
namespace boost {
  namespace ztask {
    using boost::ztask::future::callable;
    using boost::ztask::detail::unbounded_prio_queue;

    class unbounded_prio_fifo_compare
      : public std::binary_function<callable*, callable*, bool> {
     public:
      bool operator()(const callable* lhs, const callable* rhs) const {
        return (NULL == lhs) || (NULL != rhs && *lhs < *rhs);
      }
    };

    class unbounded_prio_fifo
      : public unbounded_prio_queue<callable*,
        std::vector<callable*>,
        unbounded_prio_fifo_compare> {
    };
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_UNBOUNDED_PRIO_FIFO_H_

