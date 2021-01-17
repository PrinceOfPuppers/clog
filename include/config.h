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

// time formatting
#define dateFmt year"/"month"/"day
#define timeFmt hour":"min":"sec

#define dateTimeFmt dateFmt " " timeFmt


// full log formatting
#define logFmt "["date_time"] ["file_name":"line_number"] "log_level":"message"\n"