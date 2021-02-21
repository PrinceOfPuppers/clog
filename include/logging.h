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

void _logDebug(const char* fileName,int lineNum,const char* msg,...);
void _logInfo(const char* fileName,int lineNum,const char* msg,...);
void _logWarn(const char* fileName,int lineNum,const char* msg,...);
void _logErr(const char* fileName,int lineNum,const char* msg,...);
void _logFatal(const char* fileName,int lineNum,const char* msg,...);

#define logDebug(msg,...) _logDebug(__FILE__,__LINE__,msg, ##__VA_ARGS__);
#define logInfo(msg,...) _logInfo(__FILE__,__LINE__,msg, ##__VA_ARGS__);
#define logWarn(msg,...) _logWarn(__FILE__,__LINE__,msg, ##__VA_ARGS__);
#define logErr(msg,...) _logErr(__FILE__,__LINE__,msg, ##__VA_ARGS__);
#define logFatal(msg,...) _logFatal(__FILE__,__LINE__,msg, ##__VA_ARGS__);