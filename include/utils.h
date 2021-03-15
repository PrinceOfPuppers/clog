#pragma once

char *arrStr_float_0(float* arr, int len);
char *arrStr_float_1(float** arr, int len);
char *arrStr_int_0(int* arr, int len);
char *arrStr_int_1(int** arr, int len);
char *arrStr_long_0(long* arr, int len);
char *arrStr_long_1(long** arr, int len);
char *arrStr_char_0(char* arr, int len);
char *arrStr_char_1(char** arr, int len);
char *arrStr_double_0(double* arr, int len);
char *arrStr_double_1(double** arr, int len);
char *arrStr_u_int_0(unsigned int* arr, int len);
char *arrStr_u_int_1(unsigned int** arr, int len);
char *arrStr_u_long_0(unsigned long* arr, int len);
char *arrStr_u_long_1(unsigned long** arr, int len);

                              

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
