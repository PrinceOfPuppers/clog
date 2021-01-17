#define _GNU_SOURCE

#include <logging.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>

int runtimeLogLevel = 0;

FILE *logIO;

// fills str with yy/mm/dd hh:mm:ss
void getDateTime(char (*str)[16]){
    time_t t;
    time(&t);
    struct tm * tInfo = localtime ( &t );
    
    sprintf(*str,dateTimeFmt,
        tInfo->tm_year-100,
        tInfo->tm_mon+1,
        tInfo->tm_mday,
        tInfo->tm_hour,
        tInfo->tm_min,
        tInfo->tm_sec);
}

// must be called before using logging, sets log output stream
void setLogOutput(FILE *logOutput){
    logIO = logOutput;
}
// opens the logfile in append mode, if one does not exist it will be created
void setLogFile(char *path){
    setLogOutput(fopen(path,"a"));
}
void setLogLevel(int logLevel){
    #if logLevel!=runtime
    if(logIO==NULL){
        logIO = stdout;
    }
    logFatal("Runtime Log Level Overrided by Static Log Level!\n \
              Recompile With staticLogLevel Set to runtime to Allow for Runtime changing of log level, or set staticLogLevel to Desired Level");
    return;
    #endif
    runtimeLogLevel = logLevel;
    return;
}


void _logHelper(const char* fileName, int lineNumber, const char* msgFmt, const char* logLabel, va_list *valist){

    // puts variable args into msgFmt 
    char *msg;
    
    if (vasprintf(&msg,msgFmt, *valist) == -1){
        exit(137); // unable to allocate memory
    }

    char t[16];

    getDateTime(&t);

    fprintf(logIO,logFmt,t,logLabel,msg,fileName,lineNumber);


    free(msg);
    return;
}

// external logging functions
void _logDebug(const char* fileName, int lineNumber,const char* msgFmt,...){
    #if staticLogLevel > debug
        return;
    #elif staticLogLevel == ignored
    if(runtimeLogLevel > debug){
        return;
    }
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(fileName,lineNumber,msgFmt,debugLabel,&valist);
        va_end(valist);

    return;
}

void _logInfo(const char* fileName, int lineNumber,const char* msgFmt,...){
    #if staticLogLevel > info
        return;
    #elif staticLogLevel == ignored
    if(runtimeLogLevel > info){
        return;
    }
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(fileName,lineNumber,msgFmt,infoLabel,&valist);
        va_end(valist);
    return;
}

void _logWarn(const char* fileName, int lineNumber,const char* msgFmt,...){
    #if staticLogLevel > warning
        return;
    #elif staticLogLevel == ignored
    if(runtimeLogLevel > warning){
        return;
    }
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(fileName,lineNumber,msgFmt,warningLabel,&valist);
        va_end(valist);
    return;
}

void _logErr(const char* fileName, int lineNumber,const char* msgFmt,...){
    #if staticLogLevel > error
        return;
    #elif staticLogLevel == ignored
    if(runtimeLogLevel > error){
        return;
    }
    #endif
        va_list valist;
        va_start(valist,msgFmt);
        _logHelper(fileName, lineNumber,msgFmt,errorLabel,&valist);
        va_end(valist);
    return;
}

void _logFatal(const char* fileName, int lineNumber,const char* msgFmt,...){

    va_list valist;
    va_start(valist,msgFmt);
    _logHelper(fileName,lineNumber,msgFmt,fatalLabel,&valist);
    va_end(valist);

    exit(1);

}

