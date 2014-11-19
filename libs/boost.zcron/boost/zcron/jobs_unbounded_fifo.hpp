
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_JOBS_UNBOUNDED_FIFO_H_
#define BOOST_ZCRON_JOBS_UNBOUNDED_FIFO_H_
#include <boost/zcron/history/runnable.hpp>
#include <boost/zcron/detail/jobs_unbounded_queue.hpp>
#include <boost/config.hpp>  // boost 1.54
namespace boost {
  namespace zcron {
    using boost::zcron::history::runnable;
    using boost::zcron::detail::jobs_unbounded_queue;

    class jobs_unbounded_fifo : public jobs_unbounded_queue<runnable*> {
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_JOBS_UNBOUNDED_FIFO_H_

