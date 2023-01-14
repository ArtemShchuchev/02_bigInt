#pragma once
#include <vector>
#include <string>
#include <charconv>
#include "../SecondFunk/SecondaryFunction.h"

/*

�������� ��������� �� �����.

��� ���������� ����� ������ ����� ��������������� std::string ��� std::vector.
*/

struct exeptNoDigit{};

class big_integer
{
private:
	std::string number;
	bool numIsNegative;
	//std::vector<int> number;

	void testNumber();

public:
	// ����������� ��������� lvalue (������� str, ������ ��� ����� ���� big_integer)
	big_integer(std::string& str);
	big_integer(std::string&& str);						// ����������� ��������� rvalue
	big_integer(big_integer const & other);				// ����������� �����������
	big_integer(big_integer&& other) noexcept;			// ����������� �����������

	big_integer& operator= (big_integer&&) noexcept;	// ������������ ������������
	big_integer& operator= (big_integer const&);		// ���������� ������������
	big_integer& operator+= (big_integer const& rhs);
	friend big_integer operator+ (big_integer const lhs, big_integer const rhs);
	big_integer& operator*= (big_integer const& rhs);
	std::string getNum();
	size_t getLen();
};