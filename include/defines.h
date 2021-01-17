#pragma once


//ansi colors
#define grey "\e[0;90m"
#define magenta  "\e[35m"
#define blue "\e[34m"
#define cyan "\e[96m"
#define green "\e[0;92m"
#define yellow "\e[0;93m"
#define red "\e[0;91m"
#define redBg "\e[0;30m\e[41m"
#define end "\e[0m"

// log level numbers, runtime means log level is not known at compile time
// and can be dynamically set
#define ignored -1
#define debug 0
#define info 1
#define warning 2
#define error 3
#define fatal 4