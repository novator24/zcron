#include <iostream>
#include <boost/ztask/all.hpp>
#include <boost/zcron/all.hpp>
#include <boost/exception_ptr.hpp>

long fibonacci( long n, int thread) {
  std::cout << "TEST FUNCTION #1" << std::endl;
  if ( n == 0) return 0;
  if ( n == 1) return 1;
  long k1( 1), k2( 0);
  for ( int i( 2); i <= n; ++i) {
    long tmp( k1);
    std::cout << "#" << thread << " TEMP: "
              << k1 << "+" << k2 << "=" << (k1+k2) << std::endl;
    usleep(100000);
    k1 = k1 + k2;
    k2 = tmp;
  }
  std::cout << "#" << thread << " FINISH: " << k1 << std::endl;
  return k1;
}

void test_fibonacci( long n, int thread ) {
  std::cout << "TEST FUNCTION #2" << std::endl;
  fibonacci( n, thread );
}

long& threadsafe_fibonacci( long n, long& result, int thread ) {
  std::cout << "TEST FUNCTION #3" << std::endl;
  long tmp = fibonacci( n, thread );
  result = tmp;
  return result;
}

const long& threadsafe_fibonacci2( long n, long& result, int thread ) {
  std::cout << "TEST FUNCTION #4" << std::endl;
  long tmp = fibonacci( n, thread );
  result = tmp;
  return result;
}

using boost::zcron::clock_type;
using boost::zcron::duration_type;
using boost::zcron::timepoint_type;
using boost::zcron::clock_bits_type;
using boost::zcron::clock_cond_type;
using boost::ztask::future::callable;
using boost::ztask::future::task;
using boost::ztask::future::handle;
using boost::ztask::unbounded_prio_fifo;
using boost::ztask::workers_pool;
using boost::zcron::schedulers_pool;
using boost::zcron::tasks_context;
using boost::zcron::schedule_now;
using boost::zcron::schedule_instant;
using boost::zcron::schedule_periodic;
using boost::zcron::schedule_regular;
using boost::zcron::jobs_unbounded_prio_fifo;
using boost::zcron::services_unbounded_prio_set;
using boost::zcron::history::callback;
using boost::zcron::history::job;
using boost::zcron::history::monitor;

static void x0_cb_fn(handle<void> h, boost::exception_ptr e) {
  static int x = 0;
  printf("CALLBACK x0_cb_fn time_%d %s\n", ++x, e == boost::exception_ptr() ? "OK" : "ERROR");
}

static void x1_cb_fn(handle<long> h, boost::exception_ptr e) {
  static int x = 0;
  printf("CALLBACK x1_cb_fn time_%d %s\n", ++x, e == boost::exception_ptr() ? "OK" : "ERROR");
}

static void x2_cb_fn(handle<long&> h, boost::exception_ptr e) {
  static int x = 0;
  printf("CALLBACK x2_cb_fn time_%d %s\n", ++x, e == boost::exception_ptr() ? "OK" : "ERROR");
}

static void x3_cb_fn(handle<const long&> h, boost::exception_ptr e) {
  static int x = 0;
  printf("CALLBACK x3_cb_fn time_%d %s\n", ++x, e == boost::exception_ptr() ? "OK" : "ERROR");
}

int main() {
  std::string answer;
  do {
    std::cout << "Want to sleep 10 seconds to test jobs? (y/n)" << "\n";
    std::cin >> answer;
  } while(answer != "y" && answer != "n");

  // create pools
  schedulers_pool<jobs_unbounded_prio_fifo,
      services_unbounded_prio_set> sched_pool(5);
  typedef workers_pool<unbounded_prio_fifo> pool_t;
  pool_t work_pool(5);

  callback<void> x0_callback(x0_cb_fn);
  callback<long> x1_callback(x1_cb_fn);
  callback<long&> x2_callback(x2_cb_fn);
  callback<const long&> x3_callback(x3_cb_fn);

  // choose time
  timepoint_type now(clock_util_type::now());
  duration_type three_seconds(3.0);
  clock_cond_type conditions[0];
  std::bitset<12> months(-1);
  std::bitset<32> days(-1);
  std::bitset<24> hours(-1);
  std::bitset<60> minutes(-1);
  std::bitset<62> seconds(-1);
  std::bitset<2> daysaves(-1);
  unsigned int year = 2013;

  // create job 
  long x;
  job<void, pool_t> j0(boost::bind(fibonacci, 2, 1), schedule_now(), work_pool, x0_callback);
  job<long, pool_t> j1(boost::bind(fibonacci, 5, 1), schedule_instant(now + duration_type(5.0)), work_pool, x1_callback);
  job<long&, pool_t> j2(boost::bind(threadsafe_fibonacci, 20, boost::ref(x), 1), schedule_regular(
      clock_bits_type(months, days, hours, minutes, seconds, daysaves),
      year, conditions, 0), work_pool, x2_callback);
  job<const long&, pool_t> j3(boost::bind(threadsafe_fibonacci2, 10, boost::ref(x), 1),
      schedule_periodic(three_seconds, now, conditions, 0), work_pool, x3_callback);
  
  // move job ownership to executor
  monitor m1(acron(j1, 2, sched_pool));
  monitor m2(acron(j2, 0, sched_pool));
  monitor m3(acron(j3, 0, sched_pool));

  // == ADVANCED ==
  m1.wait_registration();
  m2.wait_registration();
  m3.wait_registration();

  std::cout << "m1 is registered == " << std::boolalpha << m1.is_registered() << "\n";
  std::cout << "m2 is registered == " << std::boolalpha << m2.is_registered() << "\n";
  std::cout << "m3 is registered == " << std::boolalpha << m3.is_registered() << "\n";

  if (answer == "y") {
    for(int z = 0; z < 10; ++z) {
      sleep(1);
      std::cout << "passed " << (z+1) << " second(s)\n";
    }
  }

  work_pool.shutdown();
  sched_pool.shutdown();

//  sched_pool.shutdown_now();
//  work_pool.shutdown_now();

  return 0;
}

