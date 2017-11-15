#include "../src/dlog-utils.h"
#include <iostream>
#include <chrono>

using namespace DlogUtil;

int main(int argc, const char * argv[])
{
    if (argc != 3) { return 1; }
    DlogConvert myConvert;
    std::string dlogPath = argv[1];
    std::string outputName = argv[2];
    DEBUG("\nPath to dlog: ");
    DEBUGLN(dlogPath);
    DEBUG("Output file: ");
    DEBUGLN(outputName);

    #ifdef DEBUGPRINT
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    #endif
    myConvert.ConvertFile(dlogPath, outputName);
    #ifdef DEBUGPRINT
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        DEBUG(std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count());
        DEBUGLN(" microseconds");
    #endif

    return 0;
}