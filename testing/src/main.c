#include <logging.h>
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
    logFatal("message from %s","fatal");
}