#define _GNU_SOURCE

#include <logging.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>


// fills str with yy/mm/dd hh:mm:ss
void getDateTime(char (*str)[16]){
    time_t t;
    time(&t);
    struct tm * tInfo = localtime ( &t );
    
    sprintf(*str,"%0*i/%0*i/%0*i %0*i:%0*i:%0*i",
        2,tInfo->tm_year-100,
        2,tInfo->tm_mon+1,
        2,tInfo->tm_wday,
        2,tInfo->tm_hour,
        2,tInfo->tm_min,
        2,tInfo->tm_sec);
}

// must be called before using logging
void setLogOutput(FILE *logOutput){
    logIO = logOutput;
}

void _logHelper(const char* msgFmt, const char* logLabel, va_list *valist){

    // puts variable args into msgFmt 
    char *msg;
    
    if (vasprintf(&msg,msgFmt, *valist) == -1){
        exit(137); // unable to allocate memory
    }

    char t[16];

    getDateTime(&t);
    fprintf(logIO,logFmt,t,logLabel,msg);
        
    free(msg);
    return;
}

// external logging functions
void logDebug(const char* msgFmt,...){
    #if logLevel > debug
        return;
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(msgFmt,debugLabel,&valist);
        va_end(valist);

    return;
}

void logInfo(const char* msgFmt,...){
    #if logLevel > info
        return;
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(msgFmt,infoLabel,&valist);
        va_end(valist);
    return;
}

void logWarn(const char* msgFmt,...){
    #if logLevel > warning
        return;
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(msgFmt,warningLabel,&valist);
        va_end(valist);
    return;
}

void logErr(const char* msgFmt,...){
    #if logLevel > error
        return;
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(msgFmt,errorLabel,&valist);
        va_end(valist);
    return;
}

void logFatal(const char* msgFmt,...){

    va_list valist;
    va_start(valist,msgFmt);
    _logHelper(msgFmt,fatalLabel,&valist);
    va_end(valist);

    exit(1);

}

FILE *logIO;