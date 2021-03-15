#include <logging.h>
#include <stdlib.h>


#define formatter_float_0 "%g"
#define formatter_float_1 "&%g"

#define formatter_double_0 "%g"
#define formatter_double_1 "&%g"

#define formatter_int_0 "%i"
#define formatter_int_1 "&%i"

#define formatter_long_0 "%li"
#define formatter_long_1 "&%li"

#define formatter_u_int_0 "%u"
#define formatter_u_int_1 "&%u"

#define formatter_u_long_0 "%lu"
#define formatter_u_long_1 "&%lu"

#define formatter_char_0 "%c"
#define formatter_char_1 "&%s"

#define formatter(type,indirection) formatter_##type##_##indirection

// char * must be derefrenced 1 less than other arrays


#define star_0
#define star_1 * star_0
#define star_2 * star_1
#define star(n) star_##n

#define DECLARE_PRINT_ARR_FUNC(type,indirection,derefAmount)                    \
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
                                                                                \
        while(1){                                                               \
            sizeNeeded = snprintf(buffer+writeIndex, buffSize-writeIndex, formatter(type,indirection), star(derefAmount) arr[i]); \
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

DECLARE_PRINT_ARR_FUNC(int,0,0);
DECLARE_PRINT_ARR_FUNC(int,1,1);

DECLARE_PRINT_ARR_FUNC(long,0,0);
DECLARE_PRINT_ARR_FUNC(long,1,1);

DECLARE_PRINT_ARR_FUNC(u_int,0,0);
DECLARE_PRINT_ARR_FUNC(u_int,1,1);

DECLARE_PRINT_ARR_FUNC(u_long,0,0);
DECLARE_PRINT_ARR_FUNC(u_long,1,1);

DECLARE_PRINT_ARR_FUNC(float,0,0);
DECLARE_PRINT_ARR_FUNC(float,1,1);

DECLARE_PRINT_ARR_FUNC(double,0,0);
DECLARE_PRINT_ARR_FUNC(double,1,1);

DECLARE_PRINT_ARR_FUNC(char,0,0);
DECLARE_PRINT_ARR_FUNC(char,1,0);

#define arrStr(arr, len) _Generic((arr),                            \
    float*:  arrStr_float_0, double*:           arrStr_double_0,    \
    float**: arrStr_float_1, double**:          arrStr_double_1,    \
    int*:    arrStr_int_0,   unsigned int*:     arrStr_u_int_0,     \
    int**:   arrStr_int_1,   unsigned int**:    arrStr_u_int_1,     \
    long*:   arrStr_long_0,  unsigned long*:    arrStr_u_long_0,    \
    long**:  arrStr_long_1,  unsigned long**:   arrStr_u_long_0,    \
    char*:   arrStr_char_0,                                         \
    char**:  arrStr_char_1,                                         \
    default: arrStr_long_0                                          \
)(arr, len)


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
    printf("%s\n",arrStr(strArr,4));
    printf("%s\n",arrStr(hello,5));
    printf("%s\n",arrStr(intArr,4));
    logFatal("message from %s","fatal");
}
