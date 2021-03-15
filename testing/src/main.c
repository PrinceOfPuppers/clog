#include <logging.h>
#include <stdlib.h>

#define formatter_float_0 "%f"
#define formatter_float_1 "&%f"

#define formatter_int_0 "%i"
#define formatter_int_1 "&%i"

#define formatter_char_0 "%c"
#define formatter_char_1 "%s"

#define formatter(type,indirection) formatter_##type##_##indirection

// char * must be derefrenced 1 less than other arrays
#define derefOffset(type) (type==char)

#define star_0
#define star_1 * star_0
#define star_2 * star_1
#define star(n) star_##n




#define DECLARE_PRINT_ARR_FUNC(type,indirection)                                \
    char *arrStr_##type##_##indirection(type * star(indirection) arr, int len)  \
{                                                                               \
    int buffReallocSize = len;                                                  \
    int buffSize = buffReallocSize;                                             \
    char *buffer = malloc(buffSize*sizeof(char));                               \
    buffer[0] = '[';                                                            \
    int i;                                                                      \
    int writeIndex = 1;                                                         \
    int sizeNeeded;                                                             \
    int reallocDiff = buffReallocSize;                                          \
    int headRoom;                                                               \
    for(i = 0; i < len; i++){                                                   \
        logDebug("Looping");                                                    \
        logDebug("%s\n",arr[0]);                                                \
        while(1){                                                               \
            sizeNeeded = snprintf(buffer+writeIndex, buffSize-writeIndex, formatter(type,indirection), arr[i]); \
            logDebug("%f",arr[i]);                                              \
            logDebug(formatter(type,indirection),arr[i]);                       \
            logDebug(buffer);                                                   \
            headRoom = buffSize - writeIndex - sizeNeeded + 1;                  \
            logDebug("writeIndex: %i buffSize: %i sizeNeeded: %i headRoom: %i", writeIndex,buffSize,sizeNeeded, headRoom); \
            if (headRoom < reallocDiff) {                                       \
                logDebug("Reallocing") ;                                        \
                buffer = realloc(buffer,buffSize+buffReallocSize + sizeNeeded); \
                buffSize+=buffReallocSize + sizeNeeded;                         \
                continue;                                                       \
            };                                                                  \
            if (headRoom < 0){                                                  \
                continue;                                                       \
            };                                                                  \
            break;                                                              \
        }                                                                       \
        writeIndex += sizeNeeded;                                               \
        buffer[writeIndex] = ',';                                               \
        buffer[writeIndex+1] = ' ';                                             \
        writeIndex += 2;                                                        \
    }                                                                           \
    buffer[writeIndex - 2] = ']';                                               \
    buffer[writeIndex - 1] = '\0';                                              \
    return buffer;                                                              \
}

DECLARE_PRINT_ARR_FUNC(int,0);
DECLARE_PRINT_ARR_FUNC(float,0);
DECLARE_PRINT_ARR_FUNC(float,1);

DECLARE_PRINT_ARR_FUNC(char,0);

DECLARE_PRINT_ARR_FUNC(char,1);

#define arrStr(arr, len) _Generic((arr), \
            float*: arrStr_float_0, \
            float**: arrStr_float_1, \
            int*: arrStr_int_0,  \
            char*: arrStr_char_0, \
            char**: arrStr_char_1 \
)(arr, len)

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

    int q = 4;
    float arr[4] =  {100000000.0, 1.0, 2.0, 3.0};
    float **ref = malloc(4*sizeof(float*));
    ref[0] = &arr[0];
    ref[1] = &arr[1];
    ref[2] = &arr[2];
    ref[3] = &arr[3];

    #include <string.h>

    char *hello = malloc(6*sizeof(char));
    strcpy(hello,"hello");

    char *how = malloc(4*sizeof(char));
    strcpy(how,"how");
    
    char *are =  malloc(4*sizeof(char));
    strcpy(are,"are");
    
    char *you =  malloc(4*sizeof(char));
    strcpy(you,"you");

    char **strArr = {&hello,&how,&are,&you};
    
    printf("%f\n",*ref[3]);
    return;
    printf("%s\n",arrStr(arr,q));
    //printf("%s\n",arrStr(strArr,3));
    logFatal("message from %s","fatal");
}
