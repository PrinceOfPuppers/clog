

# clog


> A lightweight c logging library 
- [INSTALLATION](#INSTALLATION)
- [ABOUT](#ABOUT)
- [USAGE](#USAGE)
- [LOG OUTPUT](#LOG-OUTPUT)
- [LEVEL SETTING](#LEVEL-SETTING)


# INSTALLATION
Note: Only tested using gcc, should be compatible with any compiler which supports gnu99. to use a different compiler change the CC variable in the make file

Clone repository into your lib folder of an existing c project

``` 
cd lib
git clone https://github.com/PrinceOfPuppers/clog.git
```
You can then test the library by running the following
``` 
cd clog
make test
```
This should output a log messages testing the various log types and helpers, if your terminal does not support ansi escape sequences you can disable them in clog/include/log_config.h
## Compiling
To compile clog
```
make -C /path/to/clog 
```
If you wish to use gdb on clog then compile with debug recipe
```
make -C /path/to/clog debug
```

## Linking
To link clog, you must add the following include and lib flags to gcc when compiling your main project
```
include: -Ilib/clog/include
lib:     -L ./lib -l:clog/lib/clog.a
```


# ABOUT
clog is a lightweight and very low overhead logging library, supporting both compile time and runtime log levels, by default calling a logging function below the current logging level will immediately return with no conditional checking

The formatting of the logging is completely customizable in clog/include/log_config.h, this includes:
- datetime formatting
- file and line number formatting
- log label formatting
- log label colors
- etc...

In addition to the usual type polymorphism of printf, clog logging functions allows for type polymorphic logging of arrays with arbitrary datatype.

# USAGE
For full examples see clog/testing/src/main.c
## Standard Logging Functions
```
logDebug("FmtString",...);
logInfo("FmtString",...);
logWarn("FmtString",...);
logErr("FmtString",...);
logFatal("FmtString",...);
```
The syntax of these are identical to printf, they will log to whatever output is set as shown in the [LOG OUTPUT](#LOG-OUTPUT) section, their formatting is set in clog/include/log_config.h

logFatal will also exit with status 1, to include perror info use:
```
#include <errno.h>
logFatal("Error: %s",strerror(errno));
```
## Array Logging
```
logDebugArr(arr,len);
logInfoArr(arr,len);
logWarnArr(arr,len);
logErrArr(arr,len);
logFatalArr(arr,len);
```
These will log the array arr of length len at the relevant log level, the array type is polymorphic, supported types can be seen in include/log_utils.h, pointers are prepended with an &. For example output run make test.
# LOG OUTPUT
Added the following include to any file in which you wish to use logging:
```
#include <logging.h>
```
You can set the logging output file using one of the following:
```
setLogFile("path/to/logfile.log");
setLogOutput(FilePointer);
```
clog defaults to:
```
setLogOutput(stdout);
```

# LEVEL SETTING
For logging levels there are 2 modes for setting it:

## Static Log Level
In this mode, the log level is fixed for the runtime of the application, it is set in clog/include/log_config.h
```
// options are: debug, info, warning, error, fatal and ignored
#define staticLogLevel ignored
```
Where staticLogLevel = ignored is for runtime log level (the default)

## Runtime Log Level
In this mode the log level can be changed at runtime using
```
// LEVEL = debug,info,warn,error,fatal
setLogLevel(LEVEL);
```