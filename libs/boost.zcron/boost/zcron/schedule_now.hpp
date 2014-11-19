
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_SCHEDULE_NOW_H_
#define BOOST_ZCRON_SCHEDULE_NOW_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/detail/schedule_base.hpp>
namespace boost {
  namespace zcron {
    using boost::zcron::detail::schedule_base;

    class schedule_now : public schedule_base {
     public:
      schedule_now()
        : schedule_base() {}

      virtual ~schedule_now() {}

      schedule_base* clone() const {
        return new schedule_now();
      }

      duration_type next_call_duration( \
          timepoint_type const& utc_since) const {
        (void)utc_since;
        return duration_type(0.0);
      }

      int get_calls_limit() const {
        return 1;
      }

     private:
      // noncopyable
      schedule_now(const schedule_now&);
      void operator=(const schedule_now&);
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_SCHEDULE_NOW_H_

