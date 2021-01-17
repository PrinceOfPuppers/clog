#pragma once
#include <defines.h>

#define enableAnsiColors 1

// log level colors (grey, magenta, blue, cyan, green, yellow, red, redBg)
#define debugColor green
#define infoColor cyan
#define warningColor yellow
#define errorColor red
#define fatalColor redBg

// log level labels
#define debugText "[debug]"
#define infoText "[info] "
#define warningText "[warn] "
#define errorText "[error]"
#define fatalText "[fatal]"


// compile time loglevel, options are: debug, info, warning, error, fatal
// setting staticLogLevel runtime will allow log level to be set at runtime (however this is less efficent)
#define staticLogLevel ignored


// Determines what args are present in logFmt
// 0: Message
// 1: level Message
// 2: Time Message
// 3: Time Level Message
#define fmtArgs 3


// log formats
#if fmtArgs == 0
//              message 
#define logFmt "%s\n"

#elif fmtArgs == 1
//              label: message 
#define logFmt "%s: %s\n"

#elif fmtArgs == 2
//              [time]: message 
#define logFmt "[%s]: %s\n"

#elif fmtArgs == 3
//              [time] label: message 
#define logFmt "[%s] %s: %s\n"

#endif


