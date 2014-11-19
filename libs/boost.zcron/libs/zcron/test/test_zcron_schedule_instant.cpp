
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
  // start == test
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

  xc::schedule_instant instant(x_start);
  xc::duration_type duration = instant.next_call_duration(x_test);
  BOOST_CHECK( duration == expected );
}

void test_case_2()
{
  // start < test
  xc::duration_type expected(-121.0);

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

  xc::schedule_instant instant(x_start);
  xc::duration_type duration = instant.next_call_duration(x_test);
  BOOST_CHECK( duration == expected );
}

void test_case_3()
{
  // start > test
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

  xc::schedule_instant instant(x_start);
  xc::duration_type duration = instant.next_call_duration(x_test);
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

    return 0;
}

