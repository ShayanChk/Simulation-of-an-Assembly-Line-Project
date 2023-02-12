
#ifndef OOP_UTILITIES_H
#define OOP_UTILITIES_H
#include <string>
#include <iostream>
namespace sdds
{
	class Utilities
	{
		size_t m_widthField{ 1 };
		static char m_delimiter;

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		std::string cleanField(std::string field);
		static void setDelimiter(const char newDelimiter);
		static char getDelimiter();
	};
}
#endif