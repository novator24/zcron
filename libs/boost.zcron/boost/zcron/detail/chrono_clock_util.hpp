
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_DETAIL_CHRONO_CLOCK_UTIL_H_
#define BOOST_ZCRON_DETAIL_CHRONO_CLOCK_UTIL_H_
#include <boost/zcron/detail/config.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/static_assert.hpp>  // boost 1.54
#include <boost/tuple/tuple.hpp>  // boost 1.54
#include "boost/date_time/posix_time/ptime.hpp"  // boost 1.54
#include "boost/date_time/posix_time/posix_time.hpp"  // boost 1.54
#include "boost/date_time/local_time_adjustor.hpp"  // boost 1.54
#include "boost/date_time/c_local_time_adjustor.hpp"  // boost 1.54
using boost::date_time::local_adjustor;
using boost::date_time::c_local_adjustor;
namespace boost {
  namespace zcron {
    namespace detail {
      class chrono_clock_util {
       public:
        static chrono_timepoint_type now() {
          chrono_clock_type::time_point x = chrono_clock_type::now();
          return chrono_timepoint_type() + chrono_duration_type( \
              std::chrono::duration_cast<chrono_duration_type>( \
              x.time_since_epoch()).count());
        }

        static std::tm thrsafe_gmtime(std::time_t t) {
// MSVCRT (2005+): std::gmtime is threadsafe
#if (_MSC_VER >= 1400)
          return *std::gmtime(&t);
#else  // POSIX
          std::tm temp;
          return *::gmtime_r(&t, &temp);
#endif  // _MSC_VER
        }

        static std::time_t thrsafe_timegm(std::tm* tm) {
          return timegm(tm);
        }

        static chrono_duration_type calc_duration( \
            chrono_timepoint_type const& since,
            chrono_timepoint_type const& till) {
          return std::chrono::duration_cast<chrono_duration_type>(till - since);
        }

        template<typename time_type, short utc_offset, typename dst_rule>
        static std::time_t utc_to_local( \
            const local_adjustor<time_type, utc_offset, dst_rule>& adj,
            const std::time_t & t) {
          std::tm tm_result = boost::posix_time::to_tm( \
            adj.utc_to_local(boost::posix_time::from_time_t(t)));
          return thrsafe_timegm(&tm_result);
        }

        template<typename time_type, short utc_offset, typename dst_rule>
        static std::tm utc_tm_to_local( \
            const local_adjustor<time_type, utc_offset, dst_rule>& adj,
            const std::tm & tm) {
          std::tm temp = tm;
          std::time_t utc = thrsafe_timegm(&temp);
          return thrsafe_gmtime(utc_to_local(adj, utc));
        }

        template<typename time_type, short utc_offset, typename dst_rule>
        static std::time_t local_to_utc( \
            const local_adjustor<time_type, utc_offset, dst_rule>& adj,
            const std::time_t & t) {
          std::tm tm_result = boost::posix_time::to_tm( \
            adj.local_to_utc(boost::posix_time::from_time_t(t)));
          return thrsafe_timegm(&tm_result);
        }

        template<typename time_type, short utc_offset, typename dst_rule>
        static std::tm local_tm_to_utc( \
            const local_adjustor<time_type, utc_offset, dst_rule>& adj,
            const std::tm & tm) {
          std::tm temp = tm;
          std::time_t utc = thrsafe_timegm(&temp);
          return thrsafe_gmtime(local_to_utc(adj, utc));
        }

        template<typename time_type>
        static std::time_t utc_to_local( \
            const c_local_adjustor<time_type>& adj,
            const std::time_t & t) {
          std::tm tm_result = boost::posix_time::to_tm( \
            adj.utc_to_local(boost::posix_time::from_time_t(t)));
          return thrsafe_timegm(&tm_result);
        }

        template<typename time_type>
        static std::tm utc_tm_to_local( \
            const c_local_adjustor<time_type>& adj,
            const std::tm & tm) {
          std::tm temp = tm;
          std::time_t utc = thrsafe_timegm(&temp);
          return thrsafe_gmtime(utc_to_local(adj, utc));
        }

        static chrono_timepoint_type utc_tm_to_time_point(std::tm const& utc_tm) {
          std::tm utc_tm_copy = utc_tm;
          std::time_t ts_utc = thrsafe_timegm(&utc_tm_copy);
          return chrono_clock_type::from_time_t(ts_utc);
        }

        template <class Int>
        static Int days_from_civil(Int y, unsigned m, unsigned d) { 
          // BOOST_STATIC_ASSERT_MSG(std::numeric_limits<unsigned>::digits >= 18,
          //    "This algorithm has not been ported to a 16 bit unsigned integer");
          // BOOST_STATIC_ASSERT_MSG(std::numeric_limits<Int>::digits >= 20,
          //     "This algorithm has not been ported to a 16 bit signed integer");
          y -= m <= 2;
          const Int era = (y >= 0 ? y : y-399) / 400;
          const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
          const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;  // [0, 365]
          const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
          return era * 146097 + static_cast<Int>(doe) - 719468;
        }

        // Returns year/month/day triple in civil calendar
        // Preconditions:  z is number of days since 1970-01-01 and is in the range:
        //                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
        template <class Int>
        static boost::tuple<Int, unsigned, unsigned> civil_from_days(Int z) {
          // BOOST_STATIC_ASSERT_MSG(std::numeric_limits<unsigned>::digits >= 18,
          //    "This algorithm has not been ported to a 16 bit unsigned integer");
          // BOOST_STATIC_ASSERT_MSG(std::numeric_limits<Int>::digits >= 20,
          //    "This algorithm has not been ported to a 16 bit signed integer");
          z += 719468;
          const Int era = (z >= 0 ? z : z - 146096) / 146097;
          const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
          const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
          const Int y = static_cast<Int>(yoe) + era * 400;
          const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
          const unsigned mp = (5*doy + 2)/153;                                   // [0, 11]
          const unsigned d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
          const unsigned m = mp + (mp < 10 ? 3 : -9);                            // [1, 12]
          return boost::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
        }

        template <class Int>
        static unsigned weekday_from_days(Int z) {
          return static_cast<unsigned>(z >= -4 ? (z+4) % 7 : (z+5) % 7 + 6);
        }

        template <class To>
        static To round_down(const chrono_duration_type& d) {
          To t = std::chrono::duration_cast<To>(d);
          if (t > d) {
            --t;
          }
          return t;
        }

        static std::tm make_utc_tm(chrono_timepoint_type tp) {
          typedef std::ratio<86400> multi;
          typedef std::chrono::duration<int, multi> days;
          // t is time duration since 1970-01-01
          chrono_duration_type t = tp.time_since_epoch();
          // d is days since 1970-01-01
          days d = round_down<days>(t);
          // t is now time duration since midnight of day d
          t -= d;
          // break d down into year/month/day
          int year;
          unsigned month;
          unsigned day;
          boost::tuples::tie(year, month, day) = civil_from_days(d.count());
          // start filling in the tm with calendar info
          std::tm tm = {0};
          tm.tm_year = year - 1900;
          tm.tm_mon = month - 1;
          tm.tm_mday = day;
          tm.tm_wday = weekday_from_days(d.count());
          tm.tm_yday = d.count() - days_from_civil(year, 1, 1);
          // Fill in the time
          tm.tm_hour = std::chrono::duration_cast<std::chrono::hours>(t).count();
          t -= std::chrono::hours(tm.tm_hour);
          tm.tm_min = std::chrono::duration_cast<std::chrono::minutes>(t).count();
          t -= std::chrono::minutes(tm.tm_min);
          tm.tm_sec = std::chrono::duration_cast<std::chrono::seconds>(t).count();
          return tm;
        }

        static std::tm time_point_to_utc_tm(chrono_timepoint_type const& tp) {
          return make_utc_tm(tp);
        }
      };
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_CHRONO_CLOCK_UTIL_H_

