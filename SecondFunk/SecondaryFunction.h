#pragma once

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
/*
	00 - черный
	01 - синий
	02 - зеленый
	03 - голубой
	04 - красный
	05 - фиолетовый
	06 - желтый
	07 - белый
	----
	08 - серый
	09 - ярк. синий
	10 - ярк. зеленый
	11 - ярк. голубой
	12 - ярк. красный
	13 - ярк. фиолетовый
	14 - ярк. желтый
	15 - ярк. белый
*/
namespace col
{
	inline constexpr WORD cancel(7);

	inline constexpr WORD black(0);
	inline constexpr WORD blue(1);
	inline constexpr WORD green(2);
	inline constexpr WORD cyan(3);
	inline constexpr WORD red(4);
	inline constexpr WORD magenta(5);
	inline constexpr WORD yellow(6);
	inline constexpr WORD white(7);
	inline constexpr WORD br_black(8);
	inline constexpr WORD br_blue(9);
	inline constexpr WORD br_green(10);
	inline constexpr WORD br_cyan(11);
	inline constexpr WORD br_red(12);
	inline constexpr WORD br_magenta(13);
	inline constexpr WORD br_yellow(14);
	inline constexpr WORD br_white(15);
}
void consoleCol(WORD color);

#else
/*
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107

тут 31 это цвет, 40 фон
\033[31;40m
отменить установку цвета
\033[0m
*/
namespace col
{
	inline constexpr char* cancel("\033[0m");

	inline constexpr char* black("\033[30m");
	inline constexpr char* red("\033[31m");
	inline constexpr char* green("\033[32m");
	inline constexpr char* yellow("\033[33m");
	inline constexpr char* blue("\033[34m");
	inline constexpr char* magenta("\033[35m");
	inline constexpr char* cyan("\033[36m");
	inline constexpr char* white("\033[37m");
	inline constexpr char* br_black("\033[90m");
	inline constexpr char* br_red("\033[91m");
	inline constexpr char* br_green("\033[92m");
	inline constexpr char* br_yellow("\033[93m");
	inline constexpr char* br_blue("\033[94m");
	inline constexpr char* br_magenta("\033[95m");
	inline constexpr char* br_cyan("\033[96m");
	inline constexpr char* br_white("\033[97m");
}
void consoleCol(const char* color);
#endif


size_t utf8_strlen(std::string_view str);		// ох уж эти кодировки Русского и могучего!

void printHeader(std::string_view str);		// заголовок
