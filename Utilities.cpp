
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;
namespace sdds
{
	char Utilities::m_delimiter;

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return this->m_widthField;	
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string input, cleanedInput;
		size_t delPlace;
		delPlace = str.find(m_delimiter, next_pos);

		if (more)
		{
			if (delPlace > 1000)
				more = false;
			else
				more = true;

			input = str.substr(next_pos, delPlace - next_pos);
			cleanedInput = cleanField(input);

			next_pos = delPlace + 1;

			if (input.empty())
			{
				more = false;
				throw string("No Token");
			}
			else if (m_widthField < input.size())
			{
				setFieldWidth(input.size());
			}

		}

		return cleanedInput;

	}

	string Utilities::cleanField(string field)
	{
		field.erase(0, field.find_first_not_of(' '));
		field.erase(field.find_last_not_of(' ') + 1);
		return field;
	}

	void Utilities::setDelimiter(const char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}