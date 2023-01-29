#pragma once

#include <iostream>

#if __GNUC__ >= 4	// Linux
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
	inline const char* cancel("\033[0m");

	inline const char* black("\033[30m");
	inline const char* red("\033[31m");
	inline const char* green("\033[32m");
	inline const char* yellow("\033[33m");
	inline const char* blue("\033[34m");
	inline const char* magenta("\033[35m");
	inline const char* cyan("\033[36m");
	inline const char* white("\033[37m");
	inline const char* br_black("\033[90m");
	inline const char* br_red("\033[91m");
	inline const char* br_green("\033[92m");
	inline const char* br_yellow("\033[93m");
	inline const char* br_blue("\033[94m");
	inline const char* br_magenta("\033[95m");
	inline const char* br_cyan("\033[96m");
	inline const char* br_white("\033[97m");
}
void consoleCol(const char* color);

#elif _WIN32		// Windows
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

const int errorsetmodeout = _setmode(_fileno(stdout), _O_U16TEXT);
const int errorsetmodeinp = _setmode(_fileno(stdin), _O_U16TEXT);
const int errorsetmodeerr = _setmode(_fileno(stderr), _O_U16TEXT);

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
#error "-= Unknow OS =-"
#endif


void printHeader(std::wstring_view str);	// заголовок (std::string_view - std17)
