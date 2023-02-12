
#ifndef OOP_CUSTOMERORDER_H
#define OOP_CUSTOMERORDER_H
#include <string>
#include <iostream>
#include "Station.h"
namespace sdds
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName{};
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem = nullptr;
		static size_t m_widthField;

	public:

		CustomerOrder(const std::string& str);
		//copy constructor
		CustomerOrder(CustomerOrder& cOrder); 
		//move constructor
		CustomerOrder(CustomerOrder&& cOrder) noexcept;
		//move assignment
		CustomerOrder& operator=(CustomerOrder&& cOrder) noexcept;

		//destructor
		~CustomerOrder();

		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
		std::string returnProduct();
	};
}
#endif
