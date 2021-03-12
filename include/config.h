#pragma once
#include <defines.h>

// good to disable when logging to file
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


// compile time loglevel, options are: debug, info, warning, error, fatal and ignored
// setting staticLogLevel ignored will allow log level to be set at runtime (however this is less efficent)
#define staticLogLevel ignored

// time formatting
#define dateFmt year"/"month"/"day
#define timeFmt hour":"min":"sec

#define dateTimeFmt dateFmt " " timeFmt



// full log formatting

// example using all data
//#define logFmt "["date_time"] ["filename":"line_number"] "log_level":"message"\n"

#define logFmt "["date_time"] ["filename":"line_number"] "log_level":"message"\n"