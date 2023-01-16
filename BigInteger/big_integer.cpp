#include "big_integer.h"


void big_integer::testNumber(std::string& str)
{
	if (str.empty()) return; // строка пустая

	bool numIsNegative(false);
	if (str[0] == '-')	// проверяю наличие '-' отрицательного числа
	{
		str = str.substr(1);
		numIsNegative = true;
	}
	if (str.find_first_not_of("0123456789") != std::string::npos)
		throw std::runtime_error("В конструктор big_integer, переданы не числовые литералы");
	// убираю не значащие нули
	auto pos = str.find_first_not_of('0');
	if (pos == std::string::npos)
	{
		str = "0";
		return;
	}
	str = str.substr(pos);
	// если число отрицательное возвращаю '-'
	if (numIsNegative) str.insert(0, "-", 1);
}

void big_integer::strToVect(std::string_view str)
{
	number.clear();
	if (str.empty())
	{
		number.push_back(0);	// если строка пустая => содержит 0
		return;
	}

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

big_integer::big_integer(std::string& _str)
{
	auto str(std::move(_str));
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
	int sign(1);

	if (number.front() < 0 && rhs.number.front() < 0)
	{
		// -283 + -309 = -592
		// -326 + -290 = -616
		
		number.front() *= -1;
		rhs.number.front() *= -1;
		sign = -1;
	}
	else if (number.front() < 0)
	{
		// -247 + 308 = 61

		number.front() *= -1;
		return *this = (rhs - *this);
	}
	else if (rhs.number.front() < 0)
	{
		// 221 + -399 = -178

		rhs.number.front() *= -1;
		return *this = (*this - rhs);
	}


	auto l_it = number.end();
	auto r_it = rhs.number.end();

	while (l_it > number.begin())
	{
		--l_it;
		if (r_it > rhs.number.begin())
		{
			--r_it;
			*l_it += *r_it;
		}

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

	if (r_it != rhs.number.begin())	// если правый итератор не в начале
	{
		number.insert(number.begin(), rhs.number.begin(), r_it);
	}

	number.front() *= sign;
	return *this;
}

big_integer& big_integer::operator-=(big_integer const& right)
{
	if (*this == right)	// объекты равны (5 - 5 = 0)
	{
		this->number.clear();
		this->number.push_back(0);
		return *this;
	}
	
	big_integer lhs(*this);
	big_integer rhs(right);

	if (lhs.number.front() < 0 && rhs.number.front() < 0)
	{
		// -2 - -3 = 3 - 2 = 1
		// -3 - -2 = 2 - 3 = -1
		lhs.number.front() *= -1;
		rhs.number.front() *= -1;
		std::swap(lhs, rhs);
	}
	else if (lhs.number.front() < 0)
	{
		// -2 - 3 = 2 + 3 = (-)5
		lhs.number.front() *= -1;
		*this = (lhs + rhs);
		this->number.front() *= -1;
		return *this;
	}
	else if (rhs.number.front() < 0)
	{
		// 2 - -3 = 2 + 3 = 5
		rhs.number.front() *= -1;
		return *this = (lhs + rhs);
	}

	int sign(1);
	if (lhs < rhs)	// вычитаем всегда из большего меньшее
	{
		std::swap(lhs, rhs);
		sign = -1;
	}


	auto l_it = lhs.number.end();
	auto r_it = rhs.number.end();

	while (l_it > lhs.number.begin())	// пока не переберу левое (>=) число
	{
		--l_it;

		if (r_it > rhs.number.begin())	// правое еще не закончилось
		{
			--r_it;
			
			if (*l_it < *r_it)
			{
				*(l_it - 1) -= 1;
				*l_it += 10;
			}
			*l_it -= *r_it;
		}
		else							// правое число закончилось
		{
			if (*l_it == -1)
			{
				*(l_it - 1) -= 1;
				*l_it = 9;
			}
		}
	}
	
	// убираю не значащий 0
	if (lhs.number.front() == 0) lhs.number.erase(lhs.number.begin());
	lhs.number.front() *= sign;
	return *this = std::move(lhs);
}

big_integer& big_integer::operator*=(big_integer const& right)
{
	big_integer rhs(right);
	int sign(1);

	// знаки
	if (number.front() < 0)
	{
		number.front() *= -1;
		sign *= -1;	// меняю знак +- -+
	}
	if (rhs.number.front() < 0)
	{
		rhs.number.front() *= -1;
		sign *= -1;	// меняю знак +- -+
	}

	int count(0);
	big_integer muxDig("0");

	for (auto r_it = rhs.number.rbegin(); r_it < rhs.number.rend(); ++r_it)
	{
		std::vector<int> invbuf;
		int whole{0};

		for (auto l_it = number.rbegin(); l_it < number.rend(); ++l_it)
		{
			int mult = *l_it * *r_it;
			invbuf.push_back((mult + whole) % 10);
			whole = (mult + whole) / 10;
		}
		if (whole) invbuf.push_back(whole);

		big_integer buf("");
		buf.number.clear();
		// заполняю буфер задом на перед
		buf.number.assign(invbuf.rbegin(), invbuf.rend());
		//for (auto it=invbuf.rbegin(); it<invbuf.rend(); ++it) buf.number.push_back(*it);
		for (int i = count; i > 0; --i) buf.number.push_back(0);	// докидываю 0 в буфер
		muxDig += buf;
		
		++count;
	}

	muxDig.number.front() *= sign;
	return *this = std::move(muxDig);
}

bool big_integer::operator==(const big_integer& rhs)
{
	if (number.size() != rhs.number.size()) return false;

	auto l_it = number.begin();
	auto r_it = rhs.number.begin();

	while (l_it < number.end())
	{
		if (*l_it != *r_it) return false;
		++l_it;
		++r_it;
	}

	return true;
}

bool big_integer::operator!=(const big_integer& rhs)
{
	return !(*this == rhs);
}

bool big_integer::operator<(const big_integer& rhs)
{
	if (number.size() < rhs.number.size()) return true;
	else if (number.size() == rhs.number.size())
	{
		auto l_it = number.begin();
		auto r_it = rhs.number.begin();

		while (l_it < number.end())
		{
			if (*l_it < *r_it) return true;
			else if (*l_it > *r_it) return false;
			++l_it;
			++r_it;
		}
	}

	return false;
}

bool big_integer::operator>(const big_integer& rhs)
{
	return (big_integer&)rhs < *this;
}

bool big_integer::operator<=(const big_integer& rhs)
{
	return !(*this > rhs);
}

bool big_integer::operator>=(const big_integer& rhs)
{
	return !(*this < rhs);
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

big_integer operator-(big_integer const lhs, big_integer const rhs)
{
	big_integer tmp(lhs);
	tmp -= rhs;
	return tmp;
}

big_integer operator*(big_integer const lhs, big_integer const rhs)
{
	big_integer tmp(lhs);
	tmp *= rhs;
	return tmp;
}


/*
bool operator<(big_integer const& lhs, big_integer const& rhs)
{
	if (lhs.number.size() < rhs.number.size()) return true;
	else if (lhs.number.size() == rhs.number.size())
	{
		auto l_it = lhs.number.begin();
		auto r_it = rhs.number.begin();

		while (l_it < lhs.number.end())
		{
			if (*l_it < *r_it) return true;
			++l_it;
			++r_it;
		}
	}
	
	return false;
}

bool operator>(big_integer const& lhs, big_integer const& rhs)
{
	return rhs < lhs;
}

bool operator==(big_integer const& lhs, big_integer const& rhs)
{
	if (lhs.number.size() != rhs.number.size()) return false;
	
	auto l_it = lhs.number.begin();
	auto r_it = rhs.number.begin();

	while (l_it < lhs.number.end())
	{
		if (*l_it != *r_it) return false;
		++l_it;
		++r_it;
	}

	return true;
}

bool operator!=(big_integer const& lhs, big_integer const& rhs)
{
	return !(lhs==rhs);
}
*/
