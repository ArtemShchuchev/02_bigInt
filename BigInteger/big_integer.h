﻿#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>	// std::exchange
#include <iostream>

class big_integer
{
private:
	std::vector<int> number;

	void testNumber(std::wstring&);
	void strToVect(std::wstring_view);

public:
	// конструктор принимает lvalue (очищает str, теперь это число типа big_integer)
	big_integer(std::wstring& str);
	big_integer(std::wstring&& str);					// конструктор принимает rvalue
	big_integer(big_integer const & other);				// конструктор копирования
	big_integer(big_integer&& other) noexcept;			// конструктор перемещения

	big_integer& operator= (big_integer&&) noexcept;	// перемещающее присваивание
	big_integer& operator= (big_integer const&);		// копирующее присваивание

	friend std::wostream& operator<< (std::wostream& out, big_integer b_num);
	
	big_integer& operator+= (big_integer const& rhs);
	big_integer& operator-= (big_integer const& rhs);
	big_integer& operator*= (big_integer const& rhs);
	big_integer& operator/= (big_integer const& _denom);
	
	friend big_integer operator+ (big_integer const lhs, big_integer const rhs);
	friend big_integer operator- (big_integer const lhs, big_integer const rhs);
	friend big_integer operator* (big_integer const lhs, big_integer const rhs);
	friend big_integer operator/ (big_integer const lhs, big_integer const rhs);

	bool operator == (const big_integer& rhs);
	bool operator != (const big_integer& rhs);
	bool operator < (const big_integer& rhs);
	bool operator > (const big_integer& rhs);
	bool operator <= (const big_integer& rhs);
	bool operator >= (const big_integer& rhs);

	std::wstring getNum() const;
	size_t length() const;
};
