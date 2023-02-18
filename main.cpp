#include "SecondFunk/SecondaryFunction.h"
#include "BigInteger/big_integer.h"

#include <iomanip>	// std::setw

/*
Задача 2. Большие числа
Описание
Вам нужно реализовать класс для работы с большими числами, которые не помещаются в стандартные типы данных.

Для этого класса нужно определить методы:

конструктор перемещения;
перемещающий оператор присваивания;
оператор сложения двух больших чисел;
оператор умножения на число.
Для реализации этого класса можно воспользоваться std::string или std::vector.

Пример правильной работы программы
auto number1 = big_integer("114575");
auto number2 = big_integer("78524");
auto result = number1 + number2;
std::cout << result; // 193099
*/

template<class T>
size_t maxSizeNum(const T&, const T&, const T&);
void print(std::wstring_view, size_t, big_integer, size_t, COLOR = col::cancel);

int main(int argc, char** argv)
{
	printHeader(L"Задача 2. Большие числа");
	
	try
	{
		auto number1 = big_integer(L"114575");
		auto number2 = big_integer(L"785j24");
		auto result = number1 * number2;
		auto maxLenNum = maxSizeNum(number1, number2, result);

		const std::wstring str1 = L"Число 1";
		const std::wstring str2 = L"Число 2";
		const std::wstring str3 = L"Результат";
		auto maxLenStr = maxSizeNum(str1, str2, str3);

		print(str1, maxLenStr, number1, maxLenNum);
		print(str2, maxLenStr, number2, maxLenNum);
		print(str3, maxLenStr, result, maxLenNum, col::br_yellow);
	}
	catch (const std::exception& err)
	{
		consoleCol(col::br_red);
		std::wcout << L"\nОшибка типа: " << typeid(err).name() << "\n";
		std::wcout << ansi2unicode(err.what()) << "\n";
		consoleCol(col::cancel);
	}

	std::wcout << "\n";
	//system("pause"); // Команда задержки экрана

	return 0;
}

template<class T>
size_t maxSizeNum(const T& n1, const T& n2, const T& n3)
{
	size_t max = n1.length() >= n2.length() ? n1.length() : n2.length();
	return max >= n3.length() ? max : n3.length();
}

void print(std::wstring_view str, size_t lenStr, big_integer num, size_t lenNum, COLOR color)
{
	consoleCol(color);
	std::wcout << std::left << std::setw(lenStr + 1) << str << '='
		<< std::right << std::setw(lenNum + 1) << num << "\n";
	consoleCol(col::cancel);
}