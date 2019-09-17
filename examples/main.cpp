#include <iostream>
#include <fstream>

#include "dlog.h"
#include "kaitai/kaitaistream.h"

#ifndef DOUBLE_PRECISION 
    #define DOUBLE_PRECISION 5 // Made into a preprocessing directive to be set from compiler flags
#endif

int main(int argc, char**argv) {
    if (argc != 3)
        return 1;

    std::string dlogPath = argv[1], outputName = argv[2], outputFileName = outputName + ".csv";
    std::ifstream infile(dlogPath);
    kaitai::kstream kstream(&infile);
    dlog_t log(&kstream);
    std::ofstream outfile(outputFileName);

    auto header = log.header();
    auto data = log.data();
    auto dt = 1.0 / header->sample_rate();

    std::string stopReason;
    switch(header->stop_reason()) {
        case dlog_t::stop_reasons_t::STOP_REASONS_NORMAL:
            stopReason = "Log Completed Normally\n";
            break;
        case dlog_t::stop_reasons_t::STOP_REASONS_FORCED:
            stopReason = "Log Forced\n";
            break;
        case dlog_t::stop_reasons_t::STOP_REASONS_ERROR:
            stopReason = "Log Error\n";
            break;
        case dlog_t::stop_reasons_t::STOP_REASONS_OVERFLOW:
            stopReason = "Log Overflow\n";
            break;
        case dlog_t::stop_reasons_t::STOP_REASONS_UNKNOWN:
        default:
            stopReason = "Log Unknown Error\n";
            break;
    }
    
    outfile << stopReason;
    outfile.precision(DOUBLE_PRECISION);

    int cnt = 0;
    auto initialIndex = header->start_index();
    for (auto& sample : *data->samples()) {
        outfile << std::fixed << dt * (initialIndex + cnt) << ", ";
        
        cnt++;
        
        for (auto& channel : *sample->channel()) {
            outfile << channel;

            if (&channel != &sample->channel()->back())
                outfile << ", ";
        }

        outfile << "\n";
    }

    outfile.close();

    return 0;
}