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
// staticLogLevel: runtime will allow log level to be set at runtime (however is less efficent)
#define staticLogLevel ignored

// log formatting [time] label: message 
// (can be changed but requres 3 %s)
#define logFmt "[%s] %s: %s\n"