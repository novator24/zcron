#include <iostream>
#include <boost/ztask/all.hpp>

long fibonacci( long n, int thread) {
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
  fibonacci( n, thread );
}

long& threadsafe_fibonacci( long n, long& result, int thread ) {
  long tmp = fibonacci( n, thread );
  result = tmp;
  return result;
}

using boost::ztask::future_error;
using boost::ztask::clock_type;
using boost::ztask::duration_type;
using boost::ztask::future::async;
using boost::ztask::future::callable;
using boost::ztask::future::task;
using boost::ztask::future::handle;
using boost::ztask::unbounded_prio_fifo;
using boost::ztask::workers_pool;

int main() {
  // create pool
  workers_pool<unbounded_prio_fifo> pool(5);

  // create handlers
  handle<long> h1;
  handle<long> h2;

  clock_type::time_point start(clock_type::now());
  {
    // create task
    task<long> t1(boost::bind(fibonacci, 20, 1));
    task<long> t2(boost::bind(fibonacci, 5, 2));

    // move task ownership to executor
    try {
      h1 = async(t1, 2, pool);
      h2 = async(t2, 0, pool);
    } catch(future_error& e) {
      printf("future error: %s\n", e.what());
      return 1;
    }
  }

  std::cout << "h1 ID == " << h1.get_promise_id().to_string() << "\n";
  std::cout << "h2 ID == " << h2.get_promise_id().to_string() << "\n";

  duration_type delta = clock_type::now() - start;
  std::cout << "delta " << delta.count() << " seconds\n";
  duration_type limit(0.800000), notime(0.001000);
  if( limit > delta ) {
    std::cout << "ENOUGH TIME limit " << limit.count() << " seconds\n";
    h1.wait_for(limit - delta);
    h2.wait_for(limit - delta);
  } else {
    std::cout << "NOT ENOUGH TIME limit " << limit.count() << " seconds\n";
    h1.wait_for(notime);
    h2.wait_for(notime);
  }

  if(!h1.is_ready()) {
    h1.deactivate();
    std::cout << "DEACTIVATED1 fibonacci(20)" << "\n";
  } else {
    duration_type spent = clock_type::now() - start;
    std::cout << "RESULT1 fibonacci(20) spent " << spent.count() << " seconds\n";

    std::cout << "h1 has value == " << std::boolalpha << h1.has_value() << "\n";
    std::cout << "h1 has exception == " << std::boolalpha << h1.has_exception() << "\n";

    // return result
    std::cout << "fibonacci(20) == " << h1.get() << std::endl;
  }
  if(!h2.is_ready()) {
    h2.deactivate();
    std::cout << "DEACTIVATED2 fibonacci(5)" << "\n";
  } else {
    duration_type spent = clock_type::now() - start;
    std::cout << "RESULT2 fibonacci(5) spent " << spent.count() << " seconds\n";

    std::cout << "h2 has value == " << std::boolalpha << h2.has_value() << "\n";
    std::cout << "h2 has exception == " << std::boolalpha << h2.has_exception() << "\n";

    // return result
    std::cout << "fibonacci(5) == " << h2.get() << std::endl;
  }

  pool.shutdown_now();

  return 0;
}

