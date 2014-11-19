
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_HISTORY_ACRON_H_
#define BOOST_ZCRON_HISTORY_ACRON_H_
#include <boost/zcron/schedulers_pool.hpp>
#include <boost/zcron/history/monitor.hpp>
#include <boost/zcron/history/job.hpp>
#include <boost/zcron/history/service_mark.hpp>
namespace boost {
  namespace zcron {
    namespace history {
      using boost::zcron::schedulers_pool;

      template<typename ReturnType, typename ContextType, typename Queue, typename Set>
      monitor acron(job<ReturnType, ContextType>& t,
          schedulers_pool<Queue, Set> &p,
          const service_mark& mark = service_mark()) {
        return p.submit_as_producer(t, 0, mark);
      }

      template<typename ReturnType, typename ContextType, typename Queue, typename Set>
      monitor acron(job<ReturnType, ContextType>& t,
          unsigned priority, schedulers_pool<Queue, Set> &p,
          const service_mark& mark = service_mark()) {
        return p.submit_as_producer(t, priority, mark);
      }
    }  // namespace history
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_HISTORY_ACRON_H_

