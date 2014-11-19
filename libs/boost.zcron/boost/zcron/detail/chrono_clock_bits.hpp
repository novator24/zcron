
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZCRON_DETAIL_CHRONO_CLOCK_BITS_H_
#define BOOST_ZCRON_DETAIL_CHRONO_CLOCK_BITS_H_
#include <boost/config.hpp>  // boost 1.54
#include <boost/static_assert.hpp>  // boost 1.54
#include <boost/tuple/tuple.hpp>  // boost 1.54
#include <strings.h>
#include <bitset>
namespace boost {
  namespace zcron {
    namespace detail {
      class chrono_clock_bits {
       public:
        chrono_clock_bits(std::bitset<12> const& tm_mon_bits,
            std::bitset<32> const& tm_mday_bits,
            std::bitset<24> const& tm_hour_bits,
            std::bitset<60> const& tm_min_bits,
            std::bitset<62> const& tm_sec_bits,
            std::bitset<2> const& tm_isdst_bits = -1)
          : m_tm_mon_bits(tm_mon_bits),
            m_tm_mday_bits(tm_mday_bits),
            m_tm_hour_bits(tm_hour_bits),
            m_tm_min_bits(tm_min_bits),
            m_tm_sec_bits(tm_sec_bits),
            m_tm_isdst_bits(tm_isdst_bits) {}

        ~chrono_clock_bits() {}

        chrono_clock_bits(const chrono_clock_bits& obj)
          : m_tm_mon_bits(obj.m_tm_mon_bits),
            m_tm_mday_bits(obj.m_tm_mday_bits),
            m_tm_hour_bits(obj.m_tm_hour_bits),
            m_tm_min_bits(obj.m_tm_min_bits),
            m_tm_sec_bits(obj.m_tm_sec_bits),
            m_tm_isdst_bits(obj.m_tm_isdst_bits) {}

        chrono_clock_bits& operator=(const chrono_clock_bits& obj) {
          if (this != &obj) {
            m_tm_mon_bits = obj.m_tm_mon_bits;
            m_tm_mday_bits = obj.m_tm_mday_bits;
            m_tm_hour_bits = obj.m_tm_hour_bits;
            m_tm_min_bits = obj.m_tm_min_bits;
            m_tm_sec_bits = obj.m_tm_sec_bits;
            m_tm_isdst_bits = obj.m_tm_isdst_bits;
          }
          return *this;
        }

        std::bitset<12> tm_mon_bits() const {
          return m_tm_mon_bits;
        }

        std::bitset<32> tm_mday_bits() const {
          return m_tm_mday_bits;
        }

        std::bitset<24> tm_hour_bits() const {
          return m_tm_hour_bits;
        }

        std::bitset<60> tm_min_bits() const {
          return m_tm_min_bits;
        }

        std::bitset<62> tm_sec_bits() const {
          return m_tm_sec_bits;
        }

        std::bitset<2> tm_isdst_bits() const {
          return m_tm_isdst_bits;
        }

       private:
        std::bitset<12> m_tm_mon_bits;
        std::bitset<32> m_tm_mday_bits;
        std::bitset<24> m_tm_hour_bits;
        std::bitset<60> m_tm_min_bits;
        std::bitset<62> m_tm_sec_bits;
        std::bitset<2>  m_tm_isdst_bits;
      };
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_CHRONO_CLOCK_BITS_H_

