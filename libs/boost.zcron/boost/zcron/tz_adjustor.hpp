
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_TZ_ADJUSTOR_H_
#define BOOST_ZCRON_TZ_ADJUSTOR_H_
#include <boost/zcron/exceptions.hpp>
#include <boost/zcron/clock.hpp>
#include <boost/zcron/detail/tz_adjustor_base.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/date_time/local_time_adjustor.hpp>  // boost 1.54
using boost::zcron::clock_util_type;
using boost::zcron::detail::tz_adjustor_base;
using boost::date_time::local_adjustor;
namespace boost {
  namespace zcron {
    template<typename time_type, short utc_offset, typename dst_rule>
    class tz_adjustor : public tz_adjustor_base {
     public:
      tz_adjustor(local_adjustor<time_type, utc_offset, dst_rule>const& adj)
        : tz_adjustor_base(),
          m_adj(adj) {}

      virtual ~tz_adjustor() {}

      virtual tz_adjustor_base* clone() const {
        tz_adjustor<time_type, utc_offset, dst_rule>* result;
        result = new tz_adjustor<time_type, utc_offset, dst_rule>(m_adj);
        return result;
      }

      virtual std::time_t utc_to_local(const std::time_t & t) const {
        return clock_util_type::utc_to_local(m_adj, t);
      }

      virtual std::tm utc_tm_to_local(const std::tm & utc_tm) const {
        return clock_util_type::utc_tm_to_local(m_adj, utc_tm);
      }

      virtual bool is_dst_on(unsigned days_since_1900,
          duration_type const& from_day_start) const {
        // TODO(novator24@gmail.com): implement as soon as possible
        return false;
      }

     private:
      local_adjustor<time_type, utc_offset, dst_rule> m_adj;

      // noncopyable
      tz_adjustor(const tz_adjustor&);
      void operator=(const tz_adjustor&);
    };
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_TZ_ADJUSTOR_H_

