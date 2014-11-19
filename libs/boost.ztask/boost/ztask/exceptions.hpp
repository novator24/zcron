
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZTASK_EXCEPTIONS_H_
#define BOOST_ZTASK_EXCEPTIONS_H_
#include <boost/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
using boost::system::error_code;
using boost::system::system_category;
using boost::system::system_error;
using boost::system::errc::interrupted;
namespace boost {
  namespace ztask {
    static const int code_broken_service = 1;
    static const int code_future_already_retrieved = 2;
    static const int code_service_already_satisfied = 3;
    static const int code_no_state = 4;

    class future_error : public std::logic_error {
     public:
      future_error( int ec)
        : logic_error( "future error" ),
          ec_( ec) {}

      int const& code() const {
        return ec_;
      }

      const char* what() const throw() {
        return "future error";
      }

     private:
      int  ec_;
    };

    class packaged_task_rejected : public future_error {
     public:
      packaged_task_rejected()
        : future_error(code_broken_service) {}
    };
  }
}
#endif  // BOOST_ZTASK_EXCEPTIONS_H_

