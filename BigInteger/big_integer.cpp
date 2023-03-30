#include "big_integer.h"

void big_integer::testNumber(std::wstring& str)
{
	if (str.empty()) return; // строка пустая

	bool numIsNegative(false);
	if (str[0] == L'-')	// проверяю наличие '-' отрицательного числа
	{
		str = str.substr(1);
		numIsNegative = true;
	}
	if (str.find_first_not_of(L"0123456789") != std::string::npos)
		throw std::runtime_error("В конструктор big_integer, переданы не числовые литералы");
	// убираю не значащие нули
	auto pos = str.find_first_not_of('0');
	if (pos == std::string::npos)
	{
		str = '0';
		return;
	}
	str = str.substr(pos);
	// если число отрицательное возвращаю '-'
	if (numIsNegative) str.insert(0, L"-", 1);
}

void big_integer::strToVect(std::wstring_view str)
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

big_integer::big_integer(std::wstring& _str)
{
	auto str(std::move(_str));
	testNumber(str);
	strToVect(str);
}

big_integer::big_integer(std::wstring&& str)
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
		return *this -= rhs;
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
	
	//big_integer lhs(*this);
	big_integer rhs(right);

	if (number.front() < 0 && rhs.number.front() < 0)
	{
		// -2 - -3 = 3 - 2 = 1
		// -3 - -2 = 2 - 3 = -1
		number.front() *= -1;
		rhs.number.front() *= -1;
		std::swap(*this, rhs);
	}
	else if (number.front() < 0)
	{
		// -2 - 3 = 2 + 3 = (-)5
		number.front() *= -1;
		*this += rhs;
		this->number.front() *= -1;
		return *this;
	}
	else if (rhs.number.front() < 0)
	{
		// 2 - -3 = 2 + 3 = 5
		rhs.number.front() *= -1;
		return *this += rhs;
	}

	int sign(1);
	if (*this < rhs)	// вычитаем всегда из большего меньшее
	{
		std::swap(*this, rhs);
		sign = -1;
	}


	auto l_it = number.end();
	auto r_it = rhs.number.end();

	while (l_it > number.begin())	// пока не переберу левое (>=) число
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
	if (number.front() == 0) number.erase(number.begin());
	number.front() *= sign;
	return *this;
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
	big_integer muxDig(L"0"); // содержит левое х правое

	// правое умножаю на левое
	for (auto r_it = rhs.number.crbegin(); r_it < rhs.number.crend(); ++r_it)
	{
		std::vector<int> invbuf;	// промежуточный буфер хранения
		int whole{0}; // целая часть для переноса в следующий разряд

		for (auto l_it = number.crbegin(); l_it < number.crend(); ++l_it)
		{
			// произведение 1го разряда + целая часть
			// от предыдущего произведения пары цифр
			int mult = (*l_it) * (*r_it) + whole;	
			invbuf.push_back(mult % 10);	// остаток в буфер
			// целую часть сохраняю для следующей итерации
			whole = mult / 10;
		}
		// в случае переполнения, докидываю к нонец
		if (whole) invbuf.push_back(whole);
		
		// содержит левое число перемноженное на 1 разряд правого
		big_integer buf(L""); 
		buf.number.clear();
		// заполняю буфер задом на перед
		buf.number.assign(invbuf.crbegin(), invbuf.crend());
		//for (auto it=invbuf.rbegin(); it<invbuf.rend(); ++it) buf.number.push_back(*it);
		
		// докидываю нулей в буфер
		// при переможении:
		// 1 - 
		// 10 - 0
		// 100 - 00 и т.д.
		for (int i = count; i > 0; --i) buf.number.push_back(0);
		
		muxDig += buf;	// суммирую следующий разряд
		++count;		// счетчик разрядов (нулей)
	}

	muxDig.number.front() *= sign;		// вернул знак
	return *this = std::move(muxDig);	// готово!
}

big_integer& big_integer::operator/=(big_integer const& _denom)
{
	big_integer numer(*this);
	big_integer denom(_denom);
	int sign(1);

	// знаки
	if (numer.number.front() < 0)			// числитель
	{
		numer.number.front() *= -1;
		sign *= -1;	// меняю знак +- -+
	}
	if (denom.number.front() < 0)	// знаменатель
	{
		denom.number.front() *= -1;
		sign *= -1;	// меняю знак +- -+
	}

	if (numer == denom)	// объекты равны (5 / 5 = (+-)1)
	{
		numer.number.assign(1, 1);	// теперь содержит одну единицу
		numer.number.front() *= sign;
		return *this = numer;
	}
	else if (*this < denom)	// делитель больше (1 / 5 = 0)
	{
		numer.number.assign(1, 0);	// теперь содержит один ноль
		return *this = numer;
	}

	big_integer remain(L"");		// остаток от деления
	remain.number.clear();

	//const big_integer one("1");	// цифра "1"
	//this->number.assign(1, 0);	// теперь содержит один ноль

	auto it = numer.number.front();
	while (remain.number.size() < denom.number.size() && it != numer.number.back())
	{
		remain.number.push_back(it);
		++it;
	}
	if (remain < denom) remain.number.push_back(it++);

	std::wcout << L"remain: " << remain.getNum() << "\n";





	/*
	while (numer >= denom)
	{
		numer -= denom;
		*this += one;
	}
	*/

	if (*this != big_integer(L"0")) this->number.front() *= sign;// вернул знак
	return *this;				// готово!
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

std::wstring big_integer::getNum() const
{
	std::wstring str{L""};
	for (const auto& elem : number) str += std::to_wstring(elem);

	return str;
}

size_t big_integer::length() const
{
	return number.size();
}

std::wostream& operator<<(std::wostream& out, big_integer b_num)
{
	out << b_num.getNum();
	//for (const auto& elem : b_num.number) out << elem;

	return out;
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

big_integer operator/(big_integer const numer, big_integer const denom)
{
	big_integer tmp(numer);
	tmp /= denom;
	return tmp;
}
