#pragma once
#include <stdio.h>
#include <log_utils.h>

extern FILE *logIO;


// log level numbers, ignored means log level is not known at compile time
// and can be dynamically set
#define ignored -1
#define debug 0
#define info 1
#define warning 2
#define error 3
#define fatal 4


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


#define _logArr(level,arr,len) do { \
    char* aStr = arrStr(arr,len); \
    log##level(aStr); \
    free(aStr); \
} while (0)

#define logDebugArr(arr,len) _logArr(Debug,arr,len)
#define logInfoArr(arr,len) _logArr(Info,arr,len)
#define logWarnArr(arr,len) _logArr(Warn,arr,len)
#define logErrArr(arr,len) _logArr(Err,arr,len)
#define logFatalArr(arr,len) _logArr(Fatal,arr,len)