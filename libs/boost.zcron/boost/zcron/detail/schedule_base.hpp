
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_DETAIL_SCHEDULE_BASE_H_
#define BOOST_ZCRON_DETAIL_SCHEDULE_BASE_H_
#include <boost/zcron/clock.hpp>
#include <boost/exception_ptr.hpp>  // boost 1.54
using boost::zcron::clock_type;
using boost::zcron::duration_type;
namespace boost {
  namespace zcron {
    namespace detail {
      class schedule_base {
       public:
        virtual ~schedule_base() {}

        virtual schedule_base* clone() const = 0;

        virtual duration_type next_call_duration( \
          timepoint_type const& utc_since) const = 0;

        virtual int get_calls_limit() const = 0;
      };
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_SCHEDULE_BASE_H_

