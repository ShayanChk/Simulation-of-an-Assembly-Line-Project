
#ifndef OOP_STATION_H
#define OOP_STATION_H
#include <string>
#include <iostream>
namespace sdds
{
	class Station
	{
		int id{};
		std::string item{};
		std::string description{};
		size_t serialNumber{};
		size_t numberInStock{};

		static size_t m_widthField;
		static size_t id_generator;

	public:

		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif