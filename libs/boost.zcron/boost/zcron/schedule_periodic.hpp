
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_SCHEDULE_PERIODIC_H_
#define BOOST_ZCRON_SCHEDULE_PERIODIC_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/detail/schedule_base.hpp>
namespace boost {
  namespace zcron {
    using boost::zcron::detail::schedule_base;

    class schedule_periodic : public schedule_base {
     public:
      schedule_periodic(duration_type const& period_time,
                       timepoint_type const& start_time,
                       clock_cond_type* cond_array,
                       const size_t cond_array_size)
        : schedule_base(),
          m_period_time(period_time), 
          m_start_time(start_time),
          m_cond_array(new clock_cond_type[cond_array_size]),
          m_cond_array_size(cond_array_size) {
        for (size_t i = 0; i < m_cond_array_size; ++i) {
          m_cond_array[i] = cond_array[i];
        }
      }

      virtual ~schedule_periodic() {
        delete[] m_cond_array;
      }

      schedule_base* clone() const {
        return new schedule_periodic(m_period_time, m_start_time,
            m_cond_array, m_cond_array_size);
      }

      duration_type next_call_duration( \
          timepoint_type const& utc_since) const {
        if (m_period_time <= duration_type(0.0) || utc_since < m_start_time) {
          return clock_util_type::calc_duration(utc_since, m_start_time);
        }
        duration_type p = m_period_time;
        duration_type l = clock_util_type::calc_duration(m_start_time, utc_since);
        double d = l / p;
        int n = static_cast<int>(d);
        duration_type delta = l - n * p;
        if (delta <= duration_type(0.0)) {
          return duration_type(0.0);
        }
        return duration_type(p - delta);
      }

      int get_calls_limit() const {
        return -1;
      }

     private:
      duration_type m_period_time;
      timepoint_type m_start_time;
      clock_cond_type* m_cond_array;
      size_t m_cond_array_size;

      // noncopyable
      schedule_periodic(const schedule_periodic&);
      void operator=(const schedule_periodic&);
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_SCHEDULE_PERIODIC_H_

