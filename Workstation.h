
#ifndef OOP_WORKSTATION_H
#define OOP_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <iostream>
#include <deque>

namespace sdds {

    extern std::deque<CustomerOrder> g_pending;

    extern std::deque<CustomerOrder> g_completed;
    
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station 
    {
        std::deque<CustomerOrder> m_orders{};

        Workstation* m_pNextStation{};
    public:

        
        void fill(std::ostream& os);
        
        bool attemptToMoveOrder();

        Workstation(const std::string& str);

        void setNextStation(Workstation* station = nullptr);
        
        Workstation* getNextStation() const;
        
        void display(std::ostream& os) const;
        
        Workstation& operator+=(CustomerOrder&& newOrder);
    };

} 

#endif
