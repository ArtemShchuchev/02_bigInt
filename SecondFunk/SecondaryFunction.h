#pragma once

#include <iostream>

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

size_t utf8_strlen(const std::string& str);		// ох уж эти кодировки Русского и могучего!

void printHeader(const std::string& str);		// заголовок
