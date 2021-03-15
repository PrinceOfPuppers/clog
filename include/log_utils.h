#pragma once

char *_arrStr_float_0(float* arr, int len);
char *_arrStr_float_1(float** arr, int len);
char *_arrStr_int_0(int* arr, int len);
char *_arrStr_int_1(int** arr, int len);
char *_arrStr_long_0(long* arr, int len);
char *_arrStr_long_1(long** arr, int len);
char *_arrStr_char_0(char* arr, int len);
char *_arrStr_char_1(char** arr, int len);
char *_arrStr_double_0(double* arr, int len);
char *_arrStr_double_1(double** arr, int len);
char *_arrStr_u_int_0(unsigned int* arr, int len);
char *_arrStr_u_int_1(unsigned int** arr, int len);
char *_arrStr_u_long_0(unsigned long* arr, int len);
char *_arrStr_u_long_1(unsigned long** arr, int len);

                              

#define arrStr(arr, len) _Generic((arr),                            \
    float*:  _arrStr_float_0, double*:           _arrStr_double_0,  \
    float**: _arrStr_float_1, double**:          _arrStr_double_1,  \
    int*:    _arrStr_int_0,   unsigned int*:     _arrStr_u_int_0,   \
    int**:   _arrStr_int_1,   unsigned int**:    _arrStr_u_int_1,   \
    long*:   _arrStr_long_0,  unsigned long*:    _arrStr_u_long_0,  \
    long**:  _arrStr_long_1,  unsigned long**:   _arrStr_u_long_0,  \
    char*:   _arrStr_char_0,                                        \
    char**:  _arrStr_char_1                                         \
)(arr, len)

