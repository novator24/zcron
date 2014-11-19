
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZCRON_DETAIL_SERVICES_UNBOUNDED_PRIO_VEC_H_
#define BOOST_ZCRON_DETAIL_SERVICES_UNBOUNDED_PRIO_VEC_H_
#include <boost/zcron/exceptions.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <algorithm>
#include <vector>
using boost::zcron::packaged_service_rejected;
namespace boost {
  namespace zcron {
  namespace detail {
      template<typename ObjectType, typename ContainerType,
          typename CompareType>
      class services_unbounded_prio_vec {
       public:
        services_unbounded_prio_vec()
          : m_vec(),
            m_deactivated(false),
            m_deactivated_now(false) {}

        virtual ~services_unbounded_prio_vec() { shutdown(); }

        bool sort_if_possible() {
          std::sort(m_vec.begin(), m_vec.end(), CompareType());
          return true;
        }

        bool push_back(ObjectType const& item) {
          if (m_deactivated) {
            boost::throw_exception(packaged_service_rejected());
          }
          m_vec.push_back(item);
          return true;
        }

        bool find_and_erase(ObjectType const& item, std::vector<ObjectType>& trash) {
          (void)trash; // FIXME: use trash container to save deleted
          m_vec.erase( std::remove( m_vec.begin(), m_vec.end(), item ), m_vec.end() );
          return true;
        }
        
        bool get(size_t index, ObjectType & res) {
          res = m_vec[index];
          return true;
        }

        bool empty() const {
          return m_vec.empty();
        }

        size_t size() const {
          return m_vec.size();
        }

        void shutdown_now(std::vector<ObjectType>& trash) {
          m_deactivated = true;
          m_deactivated_now = true;
          for (size_t i = 0; i < m_vec.size(); ++i) {
            trash.push_back(m_vec[i]);
          }
          m_vec.clear();
        }

        void shutdown() {
          m_deactivated = true;
          for (size_t i = 0; i < m_vec.size(); ++i) {
            delete m_vec[i];
          }
          m_vec.clear();
        }

       private:
        ContainerType m_vec;
        bool m_deactivated;
        bool m_deactivated_now;

        // noncopyable
        services_unbounded_prio_vec(const services_unbounded_prio_vec&);
        void operator=(const services_unbounded_prio_vec&);
      };
    }  // namespace detail
  }  // namespace zcron
}  // namespace boost
#endif  // BOOST_ZCRON_DETAIL_SERVICES_UNBOUNDED_PRIO_VEC_H_

