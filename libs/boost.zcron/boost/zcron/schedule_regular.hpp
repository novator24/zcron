
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_SCHEDULE_REGULAR_H_
#define BOOST_ZCRON_SCHEDULE_REGULAR_H_
#include <boost/zcron/clock.hpp>
#include <boost/zcron/tz_adjustor.hpp>
#include <boost/zcron/tz_local_adjustor.hpp>
#include <boost/zcron/detail/tz_adjustor_base.hpp>
#include <boost/zcron/detail/schedule_base.hpp>
#include <boost/date_time/local_time_adjustor.hpp>  // boost 1.54
#include <boost/date_time/posix_time/ptime.hpp>  // boost 1.54
#include <bitset>
namespace boost {
  namespace zcron {
    using boost::zcron::detail::tz_adjustor_base;
    using boost::zcron::detail::schedule_base;

     // Special considerations exist when the clock is changed by less than
     // 3 hours, for example at the beginning and end of daylight savings time.
     // If the time has moved forwards, those jobs which would have run
     // in the time that was skipped will be run soon after the change.
     // Conversely, if the time has moved backwards by less than 3 hours,
     // those jobs that fall into the repeated time will not be re-run.

     // Only  jobs  that  run at a particular time (not specified as @hourly,
     // nor with '*' in the hour or minute specifier) are affected.
     // Jobs which are specified with wildcards are run based
     // on the new time immediately.

     // Clock changes of more than 3 hours are considered to be corrections
     // to the clock, and the new time is used immediately.
    class schedule_regular : public schedule_base {
     public:
      // If some form of daylight savings or summer/winter time is in effect,
      // then jobs scheduled during the switchover period could be executed once, twice, or not at all.
      // Do not set the tasks at that time or set summer/winter switchover period correctly.

      // Public constructor #1 (default): for boost::date_time::c_local_adjustor
      schedule_regular(clock_bits_type const& tm_bits,
          int const year_or_zero_if_any,
          clock_cond_type* cond_array,
          size_t cond_array_size)
        : schedule_base(),
          m_tm_bits(tm_bits),
          m_year_or_zero_if_any(year_or_zero_if_any),
          m_adj_ptr(new tz_local_adjustor<boost::posix_time::ptime>(
              c_local_adjustor<boost::posix_time::ptime>())),
          m_cond_array(new clock_cond_type[cond_array_size]),
          m_cond_array_size(cond_array_size) {
        for (size_t i = 0; i < m_cond_array_size; ++i) {
          m_cond_array[i] = cond_array[i];
        }
      }

      // Public constructor #2: for boost::date_time::local_adjustor
      template<typename time_type, short utc_offset, typename dst_rule>
      schedule_regular(clock_bits_type const& tm_bits,
          int const year_or_zero_if_any,
          local_adjustor<time_type, utc_offset, dst_rule> const& adj,
          clock_cond_type* cond_array,
          size_t cond_array_size)
        : schedule_base(),
          m_tm_bits(tm_bits),
          m_year_or_zero_if_any(year_or_zero_if_any),
          m_adj_ptr(new tz_adjustor<time_type, utc_offset, dst_rule>(adj)),
          m_cond_array(new clock_cond_type[cond_array_size]),
          m_cond_array_size(cond_array_size) {
        for (size_t i = 0; i < m_cond_array_size; ++i) {
          m_cond_array[i] = cond_array[i];
        }
      }

     protected:
      // Protected constructor #3
      schedule_regular(clock_bits_type const& tm_bits,
          int const year_or_zero_if_any,
          tz_adjustor_base* adj_base_ptr,
          clock_cond_type* cond_array,
          size_t cond_array_size)
        : schedule_base(),
          m_tm_bits(tm_bits),
          m_year_or_zero_if_any(year_or_zero_if_any),
          m_adj_ptr(adj_base_ptr->clone()),
          m_cond_array(new clock_cond_type[cond_array_size]),
          m_cond_array_size(cond_array_size) {
        for (size_t i = 0; i < m_cond_array_size; ++i) {
          m_cond_array[i] = cond_array[i];
        }
      }

     public:
      virtual ~schedule_regular() {
        delete m_adj_ptr;
        delete[] m_cond_array;
      }

      schedule_base* clone() const {
        return new schedule_regular(m_tm_bits, m_year_or_zero_if_any, m_adj_ptr,
            m_cond_array, m_cond_array_size);
      }

      duration_type next_call_duration( \
          timepoint_type const& utc_since) const {
        std::tm utc_tm = clock_util_type::time_point_to_utc_tm(utc_since);
        std::tm loc_tm = m_adj_ptr->utc_tm_to_local(utc_tm);
        if (m_year_or_zero_if_any != 0
            && m_year_or_zero_if_any < loc_tm.tm_year) {
          return duration_type(-1.0);
        }
        if (m_tm_bits.tm_isdst_bits().test(loc_tm.tm_isdst)
            && m_tm_bits.tm_sec_bits().test(loc_tm.tm_sec)
            && m_tm_bits.tm_min_bits().test(loc_tm.tm_min)
            && m_tm_bits.tm_hour_bits().test(loc_tm.tm_hour)
            && m_tm_bits.tm_mday_bits().test(loc_tm.tm_mday)
            && m_tm_bits.tm_mon_bits().test(loc_tm.tm_mon)) {
          return duration_type(0.0);
        }
        return duration_type(1.0);
      }

      int get_calls_limit() const {
        return -1;
      }

     private:
      clock_bits_type m_tm_bits;
      int m_year_or_zero_if_any;
      tz_adjustor_base* m_adj_ptr;
      clock_cond_type* m_cond_array;
      size_t m_cond_array_size;

      // noncopyable
      schedule_regular(const schedule_regular&);
      void operator=(const schedule_regular&);
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_SCHEDULE_REGULAR_H_

