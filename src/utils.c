#include <stdlib.h>
#include <utils.h>
#include <stdio.h>
#include <logging.h>

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

#define DECLARE_ARR_STR_FUNC(type, indirection, derefAmount)                                                                \
    char *arrStr_##type##_##indirection(type * star(indirection) arr, int len)                                              \
{                                                                                                                           \
    int buffReallocSize = len;                                                                                              \
    int buffSize = buffReallocSize;                                                                                         \
    char *buffer = malloc(buffSize*sizeof(char));                                                                           \
    buffer[0] = '[';                                                                                                        \
    int i;                                                                                                                  \
    int writeIndex = 1;                                                                                                     \
    int sizeNeeded;                                                                                                         \
    int reallocDiff = buffReallocSize;                                                                                      \
    int headRoom;                                                                                                           \
    for(i = 0; i < len; i++){                                                                                               \
        while(1){                                                                                                           \
            sizeNeeded = snprintf(buffer+writeIndex, buffSize-writeIndex, formatter(type,indirection), star(derefAmount) arr[i]); \
            logDebug(formatter(type,indirection),arr[i]);                                                                   \
            logDebug(buffer);                                                                                               \
            headRoom = buffSize - writeIndex - sizeNeeded + 1;                                                              \
            logDebug("writeIndex: %i buffSize: %i sizeNeeded: %i headRoom: %i", writeIndex,buffSize,sizeNeeded, headRoom);  \
            if (headRoom < reallocDiff) {                                                                                   \
                logDebug("Reallocing") ;                                                                                    \
                buffer = realloc(buffer,buffSize+buffReallocSize + sizeNeeded);                                             \
                buffSize+=buffReallocSize + sizeNeeded;                                                                     \
                continue;                                                                                                   \
            };                                                                                                              \
            if (headRoom < 0){                                                                                              \
                continue;                                                                                                   \
            };                                                                                                              \
            break;                                                                                                          \
        }                                                                                                                   \
        writeIndex += sizeNeeded;                                                                                           \
        buffer[writeIndex] = ',';                                                                                           \
        buffer[writeIndex+1] = ' ';                                                                                         \
        writeIndex += 2;                                                                                                    \
    }                                                                                                                       \
    buffer[writeIndex - 2] = ']';                                                                                           \
    buffer[writeIndex - 1] = '\0';                                                                                          \
    return buffer;                                                                                                          \
}

DECLARE_ARR_STR_FUNC(int,0,0);
DECLARE_ARR_STR_FUNC(int,1,1);

DECLARE_ARR_STR_FUNC(long,0,0);
DECLARE_ARR_STR_FUNC(long,1,1);

DECLARE_ARR_STR_FUNC(u_int,0,0);
DECLARE_ARR_STR_FUNC(u_int,1,1);

DECLARE_ARR_STR_FUNC(u_long,0,0);
DECLARE_ARR_STR_FUNC(u_long,1,1);

DECLARE_ARR_STR_FUNC(float,0,0);
DECLARE_ARR_STR_FUNC(float,1,1);

DECLARE_ARR_STR_FUNC(double,0,0);
DECLARE_ARR_STR_FUNC(double,1,1);

DECLARE_ARR_STR_FUNC(char,0,0);
DECLARE_ARR_STR_FUNC(char,1,0);