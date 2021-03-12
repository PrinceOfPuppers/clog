#include <logging.h>
int main(){
    setLogFile("testing/build/testing.log");
    setLogLevel(debug);
    logDebug("message from %s","debug");
    logInfo("message from %s","info");
    logWarn("message from %s","warning");
    logErr("message from %s","error");


    setLogOutput(stdout);
    setLogLevel(debug);
    logDebug("message from %s","debug");
    logInfo("message from %s","info");
    logWarn("message from %s","warning");
    logErr("message from %s","error");
    logFatal("message from %s","fatal");
}