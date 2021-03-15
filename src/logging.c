#define _GNU_SOURCE

#include <logging.h>
#include <config.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>


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


int runtimeLogLevel = 0;

FILE *logIO ;

// initalizes logIO to stdout, must be wrapped in constructor because stdout is not constant
static void initLogIO(void) __attribute__((constructor)); 
static void initLogIO(void){
    logIO = stdout;
}

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

// reads fileinto buffer upto next delimiter and returns it
char *getToDelim(FILE *fp,char delim){
    char c;

    int reallocInc = 10; // determines size increase each realloc
    char * result = malloc((reallocInc+1)*sizeof(char));
    int i = 0;
    
    while(1){
        c = getc(fp);
        if (c == EOF || c == delim){
            break;
        }
        if (i%reallocInc == 0){
            result = (char *) realloc(result,(i*reallocInc+1)*sizeof(char));
        }
        result[i] = c;
        i++;
    }

    result[i] = '\0';
    return result;
}

//void print1(){
//    printf("1\n");
//}
//void print2(){
//    printf("2\n");
//}
//#define print(num) 
//    print##num(); 
//
//
//
//char *arrToStr(void *arr, int len, size_t dsize,char *typeStr){
//    int typeStrLen = strlen(typeStr);
//
//    // lenth of type string + 2 where 2 is for the comma and space after each element 
//    // + 1 at the end is for the start brackets, the end bracket and null terminator are written
//    // over the unnessisary , and space of the last element
//
//    int resLen = len*( typeStrLen + 2 ) + 3;
//
//    char * result = malloc(resLen*sizeof(char));
//
//    result[0] = '[';
//
//    int i;
//    int j;
//    for(i = 1; i < len; i+= typeStrLen + 2){
//
//        //write typeStr to result
//        for(j = 0; j < typeStrLen; j++){
//            result[i+j] = typeStr[j];
//        }
//
//        //add comma and space
//        result[i+typeStrLen] = ',';
//        result[i+typeStrLen+1] = ' ';
//    }
//    // overwrite last 2 elements (final unnessisary comma and space) with ]\0
//    result[resLen-1] = ']';
//    result[resLen] = '\0';
//
//    char **test;
//    for(i = 0; i < len; i++){
//        asprintf(test,result,(arr+i*dsize));
//    }
//    return result;
//}