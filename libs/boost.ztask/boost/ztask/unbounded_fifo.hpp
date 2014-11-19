
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZTASK_UNBOUNDED_FIFO_H_
#define BOOST_ZTASK_UNBOUNDED_FIFO_H_
#include <boost/ztask/future/callable.hpp>
#include <boost/ztask/detail/unbounded_queue.hpp>
#include <boost/config.hpp>  // boost 1.54
namespace boost {
  namespace ztask {
    using boost::ztask::future::callable;
    using boost::ztask::detail::unbounded_queue;

    class unbounded_fifo : public unbounded_queue<callable*> {
    };
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_UNBOUNDED_FIFO_H_

