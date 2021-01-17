#pragma once
#include <stdio.h>
#include <defines.h>
#include <config.h>

#if enableAnsiColors
#define debugLabel debugColor debugText end
#define infoLabel infoColor infoText end
#define warningLabel warningColor warningText end
#define errorLabel errorColor errorText end
#define fatalLabel fatalColor fatalText end

#else
#define debugLabel debugText
#define infoLabel infoText
#define warningLabel warningText
#define errorLabel errorText
#define fatalLabel fatalText

#endif

extern FILE *logIO;

void setLogOutput(FILE *logOutput);
void setLogFile(char *path);
void setLogLevel(int logLevel);

void logDebug(const char* msg,...);
void logInfo(const char* msg,...);
void logWarn(const char* msg,...);
void logErr(const char* msg,...);
void logFatal(const char* msg,...);