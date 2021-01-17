#pragma once
#include <stdio.h>
#include <defines.h>


// log level labels
#define debugLabel green "[debug]" end
#define infoLabel cyan "[info ]" end
#define warningLabel yellow "[warn ]" end
#define errorLabel red "[error]" end
#define fatalLabel redBg "[fatal]" end

// current loglevel, options are: debug, info, warning, error, fatal
#define logLevel debug

// log formatting [time] label: message
#define logFmt "[%s] %s: %s\n"

extern FILE *logIO;

void setLogOutput(FILE *logOutput);

void logDebug(const char* msg,...);
void logInfo(const char* msg,...);
void logWarn(const char* msg,...);
void logErr(const char* msg,...);
void logFatal(const char* msg,...);