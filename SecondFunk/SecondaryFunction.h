#pragma once

#include <iostream>
//#define COMPILE_LIBRARY

#if __GNUC__ >= 4	// Linux
#include <codecvt>
#include <locale>

#ifdef COMPILE_LIBRARY
	#define DYNAMIC_API	__attribute__((visibility("default")))
	#define IMPORT		__attribute__((visibility("hidden")))
#else
	#define DYNAMIC_API
#endif //COMPILE_LIBRARY

using COLOR = const char*;
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
	const COLOR cancel("\033[0m");

	const COLOR black("\033[30m");
	const COLOR red("\033[31m");
	const COLOR green("\033[32m");
	const COLOR yellow("\033[33m");
	const COLOR blue("\033[34m");
	const COLOR magenta("\033[35m");
	const COLOR cyan("\033[36m");
	const COLOR white("\033[37m");
	const COLOR br_black("\033[90m");
	const COLOR br_red("\033[91m");
	const COLOR br_green("\033[92m");
	const COLOR br_yellow("\033[93m");
	const COLOR br_blue("\033[94m");
	const COLOR br_magenta("\033[95m");
	const COLOR br_cyan("\033[96m");
	const COLOR br_white("\033[97m");
}

#elif _WIN32		// Windows
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

extern const int errorsetmodeout;
extern const int errorsetmodeinp;
extern const int errorsetmodeerr;

#ifdef COMPILE_LIBRARY
	#ifdef SecFun_lib_EXPORTS
		#define DYNAMIC_API __declspec(dllexport)
	#else
		#define DYNAMIC_API __declspec(dllimport)
	#endif //SecFun_lib_EXPORTS
#else
	#define DYNAMIC_API
#endif //COMPILE_LIBRARY

using COLOR = WORD;
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
	const COLOR cancel(7);

	const COLOR black(0);
	const COLOR blue(1);
	const COLOR green(2);
	const COLOR cyan(3);
	const COLOR red(4);
	const COLOR magenta(5);
	const COLOR yellow(6);
	const COLOR white(7);
	const COLOR br_black(8);
	const COLOR br_blue(9);
	const COLOR br_green(10);
	const COLOR br_cyan(11);
	const COLOR br_red(12);
	const COLOR br_magenta(13);
	const COLOR br_yellow(14);
	const COLOR br_white(15);
}

#else
#error "-= Unknow OS =-"
#endif

// цвет в консоли
DYNAMIC_API void consoleCol(COLOR color);

// заголовок (std::string_view - std17)
DYNAMIC_API void printHeader(std::wstring_view str);

// Convert an ANSI string to a wide Unicode String
DYNAMIC_API std::wstring ansi2unicode(const std::string& str);
