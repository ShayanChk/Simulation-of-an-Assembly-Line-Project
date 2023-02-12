
#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <algorithm>

namespace sdds
{

    void LineManager::display(std::ostream& os) const
    {
        if (!m_activeLine.empty())
        {
            for (auto& var : m_activeLine)
            {
                var->display(os);
            }
        }
    }

    void LineManager::reorderStations()
    {
        const Workstation* m_ws = m_firstStation;

        size_t i{ 0 };

        do
        {
            m_activeLine[i++] = const_cast<Workstation*>(m_ws);

            m_ws = m_ws->getNextStation();

        } while (m_ws != nullptr);
    }

    bool LineManager::run(std::ostream& os)
    {
        static size_t iterate = 0;

        os << "Line Manager Iteration: " << iterate + 1 << std::endl;

        if (!g_pending.empty())
        {
            (*m_firstStation).operator+=(std::move(g_pending.front()));

            g_pending.pop_front();
        }

        for (auto i = m_activeLine.begin(); i != m_activeLine.end(); i++)
        {
            (*i)->fill(os);
        }

        for (auto i = m_activeLine.begin(); i != m_activeLine.end(); i++)
        {
            (*i)->attemptToMoveOrder();
        }

        iterate++;

        if (g_pending.empty() && g_completed.size() + g_incomplete.size() == m_cntCustomerOrder)
        {
            return true;
        }

        return false;
    }


    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        std::ifstream mainFile(file);

        if (!mainFile)
        {
            std::cerr << "Failed to open file";

            exit(EXIT_FAILURE);
        }

        Utilities uts;

        size_t pos = 0;

        std::string theLine;

        std::string nameOfStation;

        std::string nWsName;

        Workstation* nextWorkstation = nullptr;

        Workstation* currentWs = nullptr;

        Workstation* theFirstWs = nullptr;

        while (std::getline(mainFile, theLine))
        {
            bool flag = true;

            nameOfStation = uts.extractToken(theLine, pos, flag);

            currentWs = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws)
                {
                    return ws->getItemName() == nameOfStation;
                });

            m_activeLine.push_back(currentWs);

            if (flag)
            {
                nWsName = uts.extractToken(theLine, pos, flag);
                nextWorkstation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                    return ws->getItemName() == nWsName;
                    });
                currentWs->setNextStation(nextWorkstation);
            }
        }

        std::for_each(stations.begin(), stations.end(), [&](Workstation* ws)
            {
                theFirstWs = *std::find_if(stations.begin(), stations.end(), [&](Workstation* tmp) {
                    return tmp->getNextStation() == theFirstWs;
                    });
            });

        m_firstStation = theFirstWs;

        mainFile.close();

        m_cntCustomerOrder = g_pending.size();
    }
   
}