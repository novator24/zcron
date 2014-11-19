
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_FUTURE_ASYNC_H_
#define BOOST_ZTASK_FUTURE_ASYNC_H_
#include <boost/ztask/workers_pool.hpp>
#include <boost/ztask/future/handle.hpp>
#include <boost/ztask/future/task.hpp>
#include <boost/ztask/future/promise_mark.hpp>
namespace boost {
  namespace ztask {
    namespace future {
      using boost::ztask::workers_pool;

      template<typename ReturnType, typename Queue>
      handle<ReturnType> async(task<ReturnType>& t,
          workers_pool<Queue> &p,
          const promise_mark& mark = promise_mark()) {
        return p.submit_as_producer(t, 0, mark);
      }

      template<typename ReturnType, typename Queue>
      handle<ReturnType> async(task<ReturnType>& t,
          unsigned int priority,
          workers_pool<Queue> &p,
          const promise_mark& mark = promise_mark()) {
        return p.submit_as_producer(t, priority, mark);
      }
    }  // namespace future
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_FUTURE_ASYNC_H_

