
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/zcron/all.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/dst_rules.hpp>

using namespace boost::unit_test;
namespace xc = boost::zcron;

// eastern timezone is utc-5
// swatchover at the night after NY 3:00 -> 2:00
typedef boost::date_time::local_adjustor<boost::posix_time::ptime, -5,
     boost::posix_time::us_dst> us_eastern;

void test_case_1()
{
  // test (20131231235958) is sync with regular (58 59 * * * *)
  // [the year in pattern is not fixed]
  xc::duration_type expected(0.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test1: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_2()
{
  // test (20131231235957) is not sync with regular (58 59 * * * *)
  // 1 sec earlier [the year in pattern is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 57;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test2: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_3()
{
  // test (20131231235959) is not sync with regular (58 59 * * * *)
  // 1 sec later [the year in pattern is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 59;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test3: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_4()
{
  // test (20131231235858) is not sync with regular (58 59 * * * *)
  // 1 minute earlier [the year in pattern is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 58;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test4: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_5()
{
  // test (20140101000058) is not sync with regular (58 59 * * * *)
  // 1 minute later [the year in pattern is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 0;
  tm_test.tm_hour = 0;
  tm_test.tm_mday = 1;
  tm_test.tm_mon = 1 - 1;
  tm_test.tm_year = 2014 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test5: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_6()
{
  // test (20131231235858) is not sync with regular (58 59 * * * 2013)
  // 1 minute earlier [the year in pattern is fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 58;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 2013 - 1900;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test6: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_7()
{
  // test (20140101000058) is not sync with regular (58 59 * * * 2013)
  // 1 minute later [the year in pattern is fixed]
  xc::duration_type expected(-1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 0;
  tm_test.tm_hour = 0;
  tm_test.tm_mday = 1;
  tm_test.tm_mon = 1 - 1;
  tm_test.tm_year = 2014 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 2013 - 1900;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test7: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_8()
{
  // test (20131231235858) is not sync with regular (58 59 * * 12 *)
  // 1 minute earlier [the month in pattern is fixed, the year is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 58;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits;
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits.set(12 - 1), x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test8: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_9()
{
  // test (20140101000058) is not sync with regular (58 59 * * 12 *)
  // 1 minute later [the month in pattern is fixed, the year is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 0;
  tm_test.tm_hour = 0;
  tm_test.tm_mday = 1;
  tm_test.tm_mon = 1 - 1;
  tm_test.tm_year = 2014 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits;
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits.set(12 - 1), x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test9: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_10()
{
  // test (20131231235858) is not sync with regular (58 59 * 31 * *)
  // 1 minute earlier [the day in pattern is fixed, the year is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 58;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits;
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits.set(31), x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test10: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_11()
{
  // test (20140101000058) is not sync with regular (58 59 * 31 * *)
  // 1 minute later [the day in pattern is fixed, the year is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 0;
  tm_test.tm_hour = 0;
  tm_test.tm_mday = 1;
  tm_test.tm_mon = 1 - 1;
  tm_test.tm_year = 2014 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits;
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits.set(31), x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test11: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_12()
{
  // test (20131231235858) is not sync with regular (58 59 23 * * *)
  // 1 minute earlier [the hour in pattern is fixed, the year is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 58;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 31;
  tm_test.tm_mon = 12 - 1;
  tm_test.tm_year = 2013 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits;
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits.set(23),
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test12: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_13()
{
  // test (20140101000058) is not sync with regular (58 59 23 * * *)
  // 1 minute later [the hour in pattern is fixed, the year is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 58;
  tm_test.tm_min = 0;
  tm_test.tm_hour = 0;
  tm_test.tm_mday = 1;
  tm_test.tm_mon = 1 - 1;
  tm_test.tm_year = 2014 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits;
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits.set(23),
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test13: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_14()
{
  // swatchover in NY
  // test (20060101025959) is not sync with regular (58 59 02 * * *)
  // 1 second later, isdst is set [the hour in pattern is fixed, the year is not fixed]
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 59;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 2;
  tm_test.tm_mday = 1;
  tm_test.tm_mon = 1 - 1;
  tm_test.tm_year = 2006 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 1;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits;
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits.set(2),
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test14: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_15()
{
  // swatchover in NY
  // test (20060101025959) is not sync with regular (58 59 02 * * *)
  // 1 second later, isdst is not set 
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 59;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 2;
  tm_test.tm_mday = 1;
  tm_test.tm_mon = 1 - 1;
  tm_test.tm_year = 2006 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 0;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits;
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits.set(2),
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test15: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_16()
{
  // extra leap second, registered on the 30th of June, 2012
  // test (20120630235959) is not sync with regular (58 59 * * * *)
  // 1 second later, isdst is not set 
  xc::duration_type expected(1.0);
  us_eastern x_adjustor;

  struct std::tm tm_test;
  tm_test.tm_sec = 59;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 23;
  tm_test.tm_mday = 30;
  tm_test.tm_mon = 6 - 1;
  tm_test.tm_year = 2012 - 1900;
  //tm_test.tm_wday = 0;
  //tm_test.tm_yday = 0;
  tm_test.tm_isdst = 0;

  std::bitset<62> x_seconds_bits;
  std::bitset<60> x_minutes_bits;
  std::bitset<24> x_hours_bits(-1);
  std::bitset<32> x_days_bits(-1);
  std::bitset<12> x_months_bits(-1);
  unsigned int x_year_or_zero_if_any = 0;
  xc::clock_bits_type x_bits(x_months_bits, x_days_bits, x_hours_bits,
     x_minutes_bits.set(59), x_seconds_bits.set(58));
  xc::schedule_regular regular(x_bits, x_year_or_zero_if_any, x_adjustor, 0, 0);
  xc::duration_type duration = regular.next_call_duration( \
      clock_util_type::utc_tm_to_time_point(clock_util_type::local_tm_to_utc( \
      x_adjustor, tm_test)));
printf("test16: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

test_suite*
init_unit_test_suite( int argc, char* argv[] ) 
{
    if( framework::master_test_suite().argc > 1 )
        return 0;

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_1 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_2 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_3 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_4 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_5 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_6 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_7 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_8) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_9 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_10 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_11 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_12 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_13 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_14 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_15 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_16 ) );

    return 0;
}

