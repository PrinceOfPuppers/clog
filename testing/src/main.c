#include <logging.h>
#include <utils.h>
#include <stdlib.h>

int main(){
    //setLogOutput(stdout); Not needed, output defaults to stdout
    setLogLevel(info);
    logDebug("message from %s","debug");
    logInfo("message from %s","info");
    logWarn("message from %s","warning");
    logErr("message from %s","error");
    //logFatal("message from %s","fatal");


    setLogFile("testing/build/testing.log");
    setLogLevel(info);
    logDebug("message from %s","debug");
    logInfo("message from %s","info");
    logWarn("message from %s","warning");
    logErr("message from %s","error");


    // test stdout fatal log
    setLogOutput(stdout);

    int q = 4;
    float arr[4] =  {0.1, 1.1, 2.1, 3.1};
    float **ref = malloc(4*sizeof(float*));
    ref[0] = &arr[0];
    ref[1] = &arr[1];
    ref[2] = &arr[2];
    ref[3] = &arr[3];

    #include <string.h>

    int intArr[4] = {0,1,2,3};

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


    printf("%f\n",*ref[3]);

    printf("%s\n",arrStr(arr,q));
    printf("%s\n",arrStr(ref,q));
    printf("%s\n",arrStr(strArr,4));
    printf("%s\n",arrStr(hello,5));
    printf("%s\n",arrStr(intArr,4));

    logFatal("message from %s","fatal");
}
