
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_SCHEDULE_INSTANT_H_
#define BOOST_ZCRON_SCHEDULE_INSTANT_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/detail/schedule_base.hpp>
namespace boost {
  namespace zcron {
    using boost::zcron::detail::schedule_base;

    class schedule_instant : public schedule_base {
     public:
      schedule_instant(timepoint_type const& start_time)
        : schedule_base(),
          m_start_time(start_time) {}

      virtual ~schedule_instant() {}

      schedule_base* clone() const {
        return new schedule_instant(m_start_time);
      }

      duration_type next_call_duration( \
          timepoint_type const& utc_since) const {
        return clock_util_type::calc_duration(utc_since, m_start_time);
      }

      int get_calls_limit() const {
        return 1;
      }

     private:
      timepoint_type m_start_time;

      // noncopyable
      schedule_instant(const schedule_instant&);
      void operator=(const schedule_instant&);
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_SCHEDULE_INSTANT_H_

