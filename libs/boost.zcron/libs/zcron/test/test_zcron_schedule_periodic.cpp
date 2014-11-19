
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/included/unit_test.hpp>
#include <boost/zcron/all.hpp>

using namespace boost::unit_test;

namespace xc = boost::zcron;

void test_case_1()
{
  // test == start
  // period(121 sec)
  xc::duration_type expected(0.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 1;
  tm_start.tm_min = 2;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 1;
  tm_test.tm_min = 2;
  tm_test.tm_hour = 3;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(11.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test1: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_2()
{
  // start < test (121 sec)
  // test is sync with period (11 sec)
  xc::duration_type expected(0.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 0;
  tm_start.tm_min = 0;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 1;
  tm_test.tm_min = 2;
  tm_test.tm_hour = 3;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(11.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test2: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_2a()
{
  // start < test (120 sec)
  // test is not sync with period(11 sec): 1 sec earler
  xc::duration_type expected(1.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 0;
  tm_start.tm_min = 0;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 0;
  tm_test.tm_min = 2;
  tm_test.tm_hour = 3;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(11.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test2a: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_2b()
{
  // start < test (122 sec)
  // test is not sync with period (11 sec): 1 sec later

  xc::duration_type expected(10.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 0;
  tm_start.tm_min = 0;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 2;
  tm_test.tm_min = 2;
  tm_test.tm_hour = 3;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(11.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test2b: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_2c()
{
  // start < test (121 sec)
  // test is not sync with period (0 sec): 121 sec later
  xc::duration_type expected(-1.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 0;
  tm_start.tm_min = 0;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 2;
  tm_test.tm_min = 2;
  tm_test.tm_hour = 3;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(0.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test2c: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_3()
{
  // test < start (121 sec)
  // test is sync with period(11 sec)
  xc::duration_type expected(121.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 1;
  tm_start.tm_min = 2;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 0;
  tm_test.tm_min = 0;
  tm_test.tm_hour = 3;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(11.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test3: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_3a()
{
  // test < start (122 sec)
  // test is not sync with period (11 sec): 1 sec earlier
  xc::duration_type expected(122.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 1;
  tm_start.tm_min = 2;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 59;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 2;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(11.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test3a: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_3b()
{
  // test > start (120 sec)
  // test is not sync with period (11 sec): 1 sec later
  xc::duration_type expected(120.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 1;
  tm_start.tm_min = 2;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 1;
  tm_test.tm_min = 0;
  tm_test.tm_hour = 3;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(11.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test3b: %lf expected %lf\n", duration.count(), expected.count());
  BOOST_CHECK( duration == expected );
}

void test_case_3c()
{
  // test < start (121 sec)
  // test is not sync with period (0 sec): 121 sec earlier
  xc::duration_type expected(121.0);

  struct std::tm tm_start;
  tm_start.tm_sec = 1;
  tm_start.tm_min = 2;
  tm_start.tm_hour = 3;
  tm_start.tm_mday = 4;
  tm_start.tm_mon = 5 - 1;
  tm_start.tm_year = 2006 - 1970;
  //tm_start.tm_wday = 6;
  //tm_start.tm_yday = 7;
  tm_start.tm_isdst = 1;
  std::time_t ts_start = std::mktime(&tm_start);
  xc::clock_type::time_point x_start;
  x_start = xc::clock_type::from_time_t(ts_start);

  struct std::tm tm_test;
  tm_test.tm_sec = 59;
  tm_test.tm_min = 59;
  tm_test.tm_hour = 2;
  tm_test.tm_mday = 4;
  tm_test.tm_mon = 5 - 1;
  tm_test.tm_year = 2006 - 1970;
  //tm_test.tm_wday = 6;
  //tm_test.tm_yday = 7;
  tm_test.tm_isdst = 1;
  std::time_t ts_test = std::mktime(&tm_test);
  xc::clock_type::time_point x_test;
  x_test = xc::clock_type::from_time_t(ts_test);

  xc::duration_type x_period(0.0);
  xc::schedule_periodic periodic(x_period, x_start, 0, 0);
  xc::duration_type duration = periodic.next_call_duration(x_test);
//printf("test3c: %lf expected %lf\n", duration.count(), expected.count());
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
        add( BOOST_TEST_CASE( &test_case_2a ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_2b ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_3 ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_3a ) );

    framework::master_test_suite().
        add( BOOST_TEST_CASE( &test_case_3b ) );

    return 0;
}

