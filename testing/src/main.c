#include <logging.h>
#include <stdlib.h>

#define testArr(type,d1,d2,d3,d4) do{ \
    type arr[4] =  {d1, d2, d3, d4}; \
    logInfoArr(arr,4); \
    type **ref = malloc(4*sizeof(type*)); \
    ref[0] = &arr[0]; \
    ref[1] = &arr[1]; \
    ref[2] = &arr[2]; \
    ref[3] = &arr[3]; \
    logInfoArr(ref,4); \
    free(ref); \
}while(0)

int main(){
    //setLogOutput(stdout); Not needed, output defaults to stdout
    setLogLevel(debug);
    logDebug("message from %s","debug");
    logInfo("message from %s","info");
    logWarn("message from %s","warning");
    logErr("message from %s","error");
    //logFatal("message from %s","fatal");


    setLogFile("testing/build/testing.log");
    setLogLevel(debug);
    logDebug("message from %s","debug");
    logInfo("message from %s","info");
    logWarn("message from %s","warning");
    logErr("message from %s","error");


    // test stdout fatal log
    setLogOutput(stdout);

    testArr(float,0.1f, 1.1f, 2.1f, 3.1f);
    testArr(double,0.1, 1.1, 2.1, 3.1);

    testArr(int,5,6,7,8);
    testArr(long,(long)1,(long)2,(long)3,(long)4);

    #include <string.h>

    char *hello = malloc(6*sizeof(char));
    strcpy(hello,"hello");

    char *how = malloc(4*sizeof(char));
    strcpy(how,"how");
    
    char *are =  malloc(4*sizeof(char));
    strcpy(are,"are");
    
    char *you =  malloc(4*sizeof(char));
    strcpy(you,"you");

    char *strArr[4];

    strArr[0] = hello;
    strArr[1] = how;
    strArr[2] = are;
    strArr[3] = you;

    logWarnArr(hello,5);
    logErrArr(strArr,4);

    free(hello);
    free(how);
    free(are);
    free(you);
    
    logFatal("message from %s","fatal");

}
