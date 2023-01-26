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

int main(int argc, char** argv)
{
	printHeader("Задача 2. Большие числа");
	
	try
	{
		auto number1 = big_integer("114575");
		auto number2 = big_integer("78524");
		auto result = number1 * number2;

		std::cout << std::left << std::setw(7) << "number1" << " = " << std::right
			<< std::setw(result.getLen()) << number1 << "\n";
		std::cout << std::left << std::setw(7) << "number2" << " = " << std::right
			<< std::setw(result.getLen()) << number2 << "\n";

		consoleCol(col::br_yellow);
		std::cout << std::left << std::setw(7) << "result" << " = " << std::right
			<< std::setw(result.getLen()) << result << "\n";
		consoleCol(col::cancel);
	}
	catch (const std::exception& err)
	{
		consoleCol(col::br_red);
		std::cout << "\nОшибка типа: " << typeid(err).name() << "\n";
		std::cout << err.what() << "\n";
		consoleCol(col::cancel);
	}

	std::cout << "\n";
	system("pause"); // Команда задержки экрана

	return 0;
}
