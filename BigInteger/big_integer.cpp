#include "big_integer.h"


exeptNoDigit exeptionNoDigit;

void big_integer::testNumber()
{
	if (number[0] == '-')	// �������� ������� '-' �������������� �����
	{
		number = number.substr(1);
		numIsNegative = true;
	}
	if (number.find_first_not_of("0123456789") != std::string::npos)
		throw exeptionNoDigit;	// ��� �� �����
	// ������ �� �������� ����
	number = number.substr(number.find_first_not_of('0'));
}

big_integer::big_integer(std::string& str)
	: number(std::move(str)), numIsNegative(false)
{
	testNumber();
}

big_integer::big_integer(std::string&& str)
	: number(str), numIsNegative(false)
{
	testNumber();
}

big_integer::big_integer(big_integer const& other)
	: number(other.number), numIsNegative(other.numIsNegative)
{
}

big_integer::big_integer(big_integer&& other) noexcept
	: number(std::exchange(other.number, nullptr)),
	numIsNegative(std::exchange(other.numIsNegative, false))
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

big_integer& big_integer::operator+=(big_integer const& rhs)
{
	static int carry(0);				// ������ ������� �� ��������
	auto size{ number.size() };			// ������ ����� ������
	auto sizerhs{ rhs.number.size() };	// ������ ������ ������

	while (size && sizerhs)
	{
		--size;
		--sizerhs;

		int l_num{};	// ����� �����
		if (std::from_chars(number.data()+size, number.data()+size+1, l_num).ec != std::errc())
			throw std::runtime_error("(from_chars) ������ ��������������.");
		int r_num{};	// ������ �����
		if (std::from_chars(rhs.number.data() + sizerhs, rhs.number.data() + sizerhs + 1, r_num).ec != std::errc())
			throw std::runtime_error("(from_chars) ������ ��������������.");

		l_num += r_num;			// ��������� 2 int 
		if (carry) ++l_num;		// ���� ���� ������������ �������� 1 (9 + 9 = 18)

		if (l_num / 10) carry = 1;
		else carry = 0;

		// ������� � ������, ��������� ����� (������� �� %10)
		number.replace(size, 1, std::to_string(l_num % 10));
	}

	if (size)	// ���� ����� ����� ��� �� �����������
	{
		--size;
		if (carry)		// �������� �������
		{
			carry = 0;
			int l_num{};	// ����� �����
			if (std::from_chars(number.data() + size, number.data() + size + 1, l_num).ec != std::errc())
				throw std::runtime_error("(from_chars) ������ ��������������.");
			++l_num;
			number.replace(size, 1, std::to_string(l_num % 10));
		}
	}
	else if (sizerhs)	// ���� ������ ����� ��� �� �����������
	{
		number.insert(0, rhs.number, 0, sizerhs);
	}
	else				// ������ ���� ������
	{
		if (carry)		// �������� �������
		{
			carry = 0;
			number.insert(0, "1", 1);
		}
	}

	return *this;
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
	// TODO: �������� ����� �������� return
	return *this;
}

std::string big_integer::getNum()
{
	if (numIsNegative) return "-" + number;
	return number;
}

size_t big_integer::getLen()
{
	return number.length();
}

big_integer operator+(big_integer const lhs, big_integer const rhs)
{
	big_integer tmp(lhs);
	tmp += rhs;
	return tmp.number;
}
