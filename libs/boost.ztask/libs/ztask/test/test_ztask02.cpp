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

using boost::ztask::future::async;
using boost::ztask::future::callable;
using boost::ztask::future::task;
using boost::ztask::future::handle;
using boost::ztask::unbounded_prio_fifo;
using boost::ztask::workers_pool;

int main() {
  // create pool
  workers_pool<unbounded_prio_fifo> pool(5);

  // create task
  task<void> t1(boost::bind(test_fibonacci, 20, 1));
  task<void> t2(boost::bind(test_fibonacci, 5, 2));

  // move task ownership to executor
  handle<void> h1(async(t1, 2, pool));
  handle<void> h2(async(t2, 0, pool));

  std::cout << "h1 ID == " << h1.get_promise_id().to_string() << "\n";
  std::cout << "h2 ID == " << h2.get_promise_id().to_string() << "\n";

  h1.wait();
  h2.wait();

  pool.shutdown_now();

  std::cout << "h1 has exception == " << std::boolalpha << h1.has_exception() << "\n";
  std::cout << "h2 has exception == " << std::boolalpha << h2.has_exception() << "\n";

  return 0;
}

