#include "Workstation.h"
#include "CustomerOrder.h"
#include <deque>

namespace sdds {

    std::deque<CustomerOrder> g_pending {};
    
    std::deque<CustomerOrder> g_completed {};
    
    std::deque<CustomerOrder> g_incomplete {};

 

    Workstation::Workstation(const std::string &str) : Station(str)
    {

    }

    void Workstation::setNextStation(Workstation* station)
    {
        if (m_pNextStation != nullptr)
        {
            delete m_pNextStation;
        }

        m_pNextStation = station;
    }

   

    void Workstation::fill(std::ostream& os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    void Workstation::display(std::ostream& os) const
    {
        os << getItemName() << " --> ";

        if (m_pNextStation == nullptr)
        {
            os << "End of Line";
        }
        else
        {
            os << m_pNextStation->getItemName();
        }

        os << "\n";
    }

    bool Workstation::attemptToMoveOrder()
    {
        if (!m_orders.empty())
        {
            if (m_orders.front().isItemFilled(getItemName()))
            {
                if (!m_pNextStation)
                {
                    if (m_orders.front().isOrderFilled())
                    {
                        g_completed.push_back(std::move(m_orders.front()));
                    }
                    else
                    {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                else
                {
                    *m_pNextStation += std::move(m_orders.front());
                }

                m_orders.pop_front();

                return true;
            }
            else if (!getQuantity())
            {
                if (!m_pNextStation)
                {
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
                else
                {
                    *m_pNextStation += std::move(m_orders.front());
                }

                m_orders.pop_front();

                return true;
            }
        }

        return false;
    }

    
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));

        return *this;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

}