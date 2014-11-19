
//          Copyright RBCHolding 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ZTASK_DETAIL_UNBOUNDED_QUEUE_H_
#define BOOST_ZTASK_DETAIL_UNBOUNDED_QUEUE_H_
#include <boost/ztask/exceptions.hpp>
#include <boost/ztask/clock.hpp>
#include <boost/config.hpp>  // boost 1.54
#include <boost/scoped_ptr.hpp>  // boost 1.54
#include <queue>
namespace boost {
  namespace ztask {
    namespace detail {
      using boost::ztask::packaged_task_rejected;
      using boost::ztask::mutex_type;
      using boost::ztask::condition_type;
      using boost::ztask::guard_type;

      template<typename ObjectType>
      class unbounded_queue {
       public:
        unbounded_queue()
          : m_mutex(),
            m_waiter(),
            m_queue(),
            m_num_blocked(0),
            m_deactivated(false),
            m_deactivated_now(false) {}

        virtual ~unbounded_queue() { shutdown(); }

        bool put(const ObjectType& item) {
          guard_type lock(m_mutex);
          if (m_deactivated) {
            m_waiter.notify_all();
            boost::throw_exception(packaged_task_rejected());
          }
          try {
            m_queue.push(item);
          } catch (std::exception) {
            return false;
          }
          m_waiter.notify_one();
          return true;
        }

        bool empty() const {
          guard_type lock(m_mutex);
          return m_queue.empty();
        }

        bool try_take(ObjectType& res) {
          guard_type lock(m_mutex);
          if (m_queue.empty()) {
            return false;
          }
          res = m_queue.front();
          m_queue.pop();
          return true;
        }

        bool take(ObjectType& res) {
          guard_type lock(m_mutex);
          ++m_num_blocked;
          while (!m_deactivated && m_queue.empty()) {
            m_waiter.wait(lock);
          }
          m_num_blocked--;
          if (m_deactivated || m_queue.empty()) {
            return false;
          }
          res = m_queue.front();
          m_queue.pop();
          return true;
        }

        void shutdown_now(std::vector<ObjectType>& trash) {
          guard_type lock(m_mutex);
          m_deactivated = true;
          m_deactivated_now = true;
          while (!m_queue.empty()) {
            trash.push_back(m_queue.front());
            m_queue.pop();
          }
          m_waiter.notify_all();
        }

        void shutdown() {
          guard_type lock(m_mutex);
          m_deactivated = true;
          m_waiter.notify_all();
          while (m_num_blocked) {
            m_waiter.wait(lock);
          }
        }

       private:
        // multi-thread controllers [always first]
        mutable mutex_type m_mutex;
        condition_type m_waiter;

        std::queue<ObjectType> m_queue;
        unsigned int m_num_blocked;
        bool m_deactivated;
        bool m_deactivated_now;

        // noncopyable
        unbounded_queue(const unbounded_queue&);
        void operator=(const unbounded_queue&);
      };
    }  // namespace detail
  }  // namespace ztask
}  // namespace boost
#endif  // BOOST_ZTASK_DETAIL_UNBOUNDED_QUEUE_H_

