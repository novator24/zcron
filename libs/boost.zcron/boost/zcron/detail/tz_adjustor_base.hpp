
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_DETAIL_TZ_ADJUSTOR_BASE_H_
#define BOOST_ZCRON_DETAIL_TZ_ADJUSTOR_BASE_H_
#include <time.h>
namespace boost {
  namespace zcron {
    namespace detail {
      class tz_adjustor_base {
       public:
        tz_adjustor_base() {}

        virtual ~tz_adjustor_base() {}

        virtual tz_adjustor_base* clone() const = 0;

        virtual std::time_t utc_to_local(const std::time_t &) const = 0;

        virtual std::tm utc_tm_to_local(const std::tm &) const = 0;

        virtual bool is_dst_on(unsigned days_since_1900,
            duration_type const& from_day_start) const = 0;

       private:
        // noncopyable
        tz_adjustor_base(const tz_adjustor_base&);
        void operator=(const tz_adjustor_base&);
      };
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_TZ_ADJUSTOR_BASE_H_

