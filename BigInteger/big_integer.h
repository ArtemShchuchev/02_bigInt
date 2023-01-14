#pragma once
#include <vector>
#include <string>
#include <charconv>
#include "../SecondFunk/SecondaryFunction.h"

#include <iostream>

/*

оператор умножения на число.

Для реализации этого класса можно воспользоваться std::string или std::vector.
*/

struct exeptNoDigit{};

class big_integer
{
private:
	std::vector<int> number;

	void testNumber(std::string&);
	void strToVect(std::string_view);

public:
	// конструктор принимает lvalue (очищает str, теперь это число типа big_integer)
	big_integer(std::string& str);
	big_integer(std::string&& str);						// конструктор принимает rvalue
	big_integer(big_integer const & other);				// конструктор копирования
	big_integer(big_integer&& other) noexcept;			// конструктор перемещения

	big_integer& operator= (big_integer&&) noexcept;	// перемещающее присваивание
	big_integer& operator= (big_integer const&);		// копирующее присваивание
	big_integer& operator+= (big_integer const& rhs);
	friend big_integer operator+ (big_integer const lhs, big_integer const rhs);
	big_integer& operator*= (big_integer const& rhs);
	std::string getNum();
	size_t getLen();
};