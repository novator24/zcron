
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/zcron/history/service_mark.hpp>
#include <boost/function.hpp>
#ifndef BOOST_ZCRON_DETAIL_TASKS_CONTEXT_BASE_H_
#define BOOST_ZCRON_DETAIL_TASKS_CONTEXT_BASE_H_
namespace boost {
  namespace zcron {
    namespace detail {
      using boost::zcron::history::service_mark;

      class tasks_context_iface {
       public:
        typedef boost::function<void ()> void_function_t;

        tasks_context_iface() {}

        virtual ~tasks_context_iface() {}

        virtual tasks_context_iface* clone() const = 0;

        virtual void run_async(const void_function_t& fn,
          unsigned priority, const service_mark& mark) = 0; // throw errors
      };

      class tasks_context_base : public tasks_context_iface {
       public:
        virtual ~tasks_context_base() {}
      };
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_TASKS_CONTEXT_BASE_H_

