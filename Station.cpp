
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>

#include "Station.h"
#include "Utilities.h"
using namespace std; 
namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& str)
	{
		Utilities utls;
		size_t index = 0;
		bool value = true;
		string sNumber, qInStock;

		item = utls.extractToken(str, index, value);
		sNumber = utls.extractToken(str, index, value);
		qInStock = utls.extractToken(str, index, value);

		if (m_widthField < utls.getFieldWidth())
		{
			m_widthField = utls.getFieldWidth();
		}

		description = utls.extractToken(str, index, value);

		serialNumber = stoi(sNumber);
		numberInStock = stoi(qInStock);

		id = ++id_generator;

	}

	const std::string& Station::getItemName() const
	{
		return item;
	}

	size_t Station::getNextSerialNumber()
	{
		return serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return numberInStock;
	}

	void Station::updateQuantity()
	{
		numberInStock > 0 ? numberInStock-- : numberInStock;
	}

	void Station::display(std::ostream& os, bool full) const
	{

		os << right << setfill('0') << setw(3) << id << " | ";
		os << left << setfill(' ') << setw(m_widthField) << item << " | ";
		os << right << setfill('0') << setw(6) << serialNumber << " | ";
		
		if(full)
		{
			
			os << setfill(' ') << right << setw(4) << numberInStock << " | ";
			os << description;
		}

		cout << endl;
	}

	size_t Station::getSerialNumber()
	{
		return serialNumber;
	}
}
