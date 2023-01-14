#include "big_integer.h"


exeptNoDigit exeptionNoDigit;

void big_integer::testNumber(std::string& str)
{
	bool numIsNegative(false);
	if (str[0] == '-')	// проверяю наличие '-' отрицательного числа
	{
		str = str.substr(1);
		numIsNegative = true;
	}
	if (str.find_first_not_of("0123456789") != std::string::npos)
		throw exeptionNoDigit;	// это не число
	// убираю не значащие нули
	str = str.substr(str.find_first_not_of('0'));
	// если число отрицательное возвращаю '-'
	if (numIsNegative) str.insert(0, "-", 1);
}

void big_integer::strToVect(std::string_view str)
{
	bool numIsNegative(false);
	if (str[0] == '-')	// проверяю наличие '-' отрицательного числа
	{
		str = str.substr(1);
		numIsNegative = true;
	}
	for (const auto& elem : str)
	{
		auto ch = elem;
		number.push_back(std::stoi(&ch));
	}
	if (numIsNegative) number.front() *= -1;
}

big_integer::big_integer(std::string& str)
{
	testNumber(str);
	strToVect(str);
}

big_integer::big_integer(std::string&& str)
{
	testNumber(str);
	strToVect(str);
}

big_integer::big_integer(big_integer const& other) : number(other.number)
{
}

big_integer::big_integer(big_integer&& other) noexcept
	: number(std::exchange(other.number, number))
{
}

big_integer& big_integer::operator=(big_integer&& rhs) noexcept
{
	std::swap(number, rhs.number);
	return *this;
}

big_integer& big_integer::operator=(big_integer const & rhs)
{
	if (this != &rhs)
	{
		number = rhs.number;
	}
	return *this;
}

big_integer& big_integer::operator+=(big_integer const& right)
{
	big_integer rhs(right);
	if (number.front() < 0) number[0] *= -1;
	if (rhs.number.front() < 0) rhs.number[0] *= -1;


	auto l_it = number.end();
	auto r_it = rhs.number.end();

	while (l_it > number.begin() && r_it > rhs.number.begin())
	{
		--l_it;
		--r_it;

		*l_it += *r_it;
		if (*l_it / 10)
		{
			*l_it %= 10;
			if (l_it != number.begin()) *(l_it - 1) += 1;
			else // прав. строка больше или равна
			{
				number.insert(number.begin(), 1);
				l_it = number.begin() + 1;
			}
		}
	}

	if (l_it != number.begin())	// если левый итератор не в начале
	{
		--l_it;
		if (*l_it / 10)
		{
			*l_it %= 10;
			if (l_it != number.begin()) *(l_it - 1) += 1;
			else number.insert(number.begin(), 1);
		}
	}
	else if (r_it != rhs.number.begin())	// если правый итератор не в начале
	{
		number.insert(number.begin(), rhs.number.begin(), r_it);
	}

	return *this;
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
	// TODO: вставьте здесь оператор return
	return *this;
}

std::string big_integer::getNum()
{
	std::string str{""};
	for (const auto& elem : number) str += std::to_string(elem);

	return str;
}

size_t big_integer::getLen()
{
	return number.size();
}

big_integer operator+(big_integer const lhs, big_integer const rhs)
{
	big_integer tmp(lhs);
	tmp += rhs;
	return tmp;
}
