
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <vector>
#include <string>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities utl;
		size_t index = 0, counter = 0;
		string itemName;
		bool value = true;

		m_name = utl.extractToken(str, index, value);
		m_product = utl.extractToken(str, index, value);


		string str2 = str;
		size_t index2 = index;
		bool value2 = value;

		do
		{
			itemName = utl.extractToken(str2, index2, value2);
			if (itemName != "")
				counter += 1;

		} while (itemName != "");

		m_lstItem = new Item * [counter];

		for (size_t i = 0; i < counter; i++)
		{

			m_lstItem[i] = new Item(utl.extractToken(str, index, value));
		}


		m_cntItem = counter;
		if (m_widthField < utl.getFieldWidth())
			m_widthField = utl.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(CustomerOrder& cOrder)
	{
		throw string("ERROR: Cannot make copies.");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& cOrder) noexcept
	{
		if (this != &cOrder)
		{
			this->m_name = cOrder.m_name;
			cOrder.m_name = "";

			this->m_product = cOrder.m_product;
			cOrder.m_product = "";

			this->m_cntItem = cOrder.m_cntItem;
			cOrder.m_cntItem = 0;

			this->m_lstItem = cOrder.m_lstItem;
			cOrder.m_lstItem = nullptr;
		}
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cOrder) noexcept
	{
		if (this != &cOrder)
		{
			this->~CustomerOrder();
			this->m_name = cOrder.m_name;
			cOrder.m_name = "";

			this->m_product = cOrder.m_product;
			cOrder.m_product = "";

			this->m_cntItem = cOrder.m_cntItem;
			cOrder.m_cntItem = 0;

			this->m_lstItem = cOrder.m_lstItem;
			cOrder.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[](m_lstItem);
	}

	bool CustomerOrder::isOrderFilled() const
	{
		size_t flag = 0;

		for (size_t i = 0; i < m_cntItem; i++)
			if (m_lstItem[i]->m_isFilled)
				flag++;

		if (flag == m_cntItem)
			return true;
		return false;
	}

	
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool check = false, flag = false;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				flag = true;
			}
		}

		if (!flag)
		{
			check = true;
		}
		else
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_lstItem[i]->m_itemName == itemName)
				{
					check = m_lstItem[i]->m_isFilled;
				}
			}
		}

		return check;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!(m_lstItem[i]->m_isFilled))
			{
				if (station.getItemName() == m_lstItem[i]->m_itemName)
				{
					if (station.getQuantity() > 0)
					{
						station.updateQuantity();

						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();

						m_lstItem[i]->m_isFilled = true;

						os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					}
					else
					{
						os << "    Unable to fill "
							<< m_name << ", " << m_product
							<< " [" << m_lstItem[i]->m_itemName
							<< "]" << std::endl;
					}

					if (m_lstItem[i]->m_isFilled)
						break;
				}

			}
		}
	}

	

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << setfill(' ') << left << "] ";
			os << setw(m_widthField) << left << m_lstItem[i]->m_itemName;
			os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << "\n";
		}
	}

	std::string CustomerOrder::returnProduct()
	{
		return m_product;
	}

}