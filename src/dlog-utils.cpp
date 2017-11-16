#include "dlog-utils.h"
#include <iostream>
#include <fstream>

namespace DlogUtil
{
uint32_t DlogConvert::ConvertFile(const std::string& pathToDlog, const std::string& outputName)
{
    ConvertStatus status = ConvertStatus::OK;
    std::string outputFileName = outputName + ".csv";
    std::ifstream inputFS (pathToDlog.c_str(), std::ifstream::binary);
    if (!inputFS) { return ConvertStatus::FILEOPENERR; }

    inputFS.read((char*)(&this->fileBuffer[0]), 512);
    if (inputFS.gcount() != 512) {
        DEBUGLN("Error reading file header");
        return ConvertStatus::INVALIDHEADER; 
    }

    //this->printBuffer();

    status = this->parseFileHeader();
    if (status != ConvertStatus::OK) { return status; }
    
    //File header parsed successfully. Time to open output file and stream out data

    std::ofstream outputFS (outputFileName.c_str(), std::ios::binary);
    if (!outputFS) {
        DEBUGLN("Error opening output file");
        return ConvertStatus::FILEOPENERR; 
    }

    this->convertToCsv(inputFS, outputFS);

    inputFS.close();
    outputFS.close();
    return status;
}

DlogConvert::DlogConvert() { }

DlogConvert::~DlogConvert()
{
    delete[] this->fileBuffer;
    delete[] this->outputBuffer;
}

ConvertStatus DlogConvert::parseFileHeader()
{
    //this->fileBuffer must contain the header of the file at this step
    this->headerInfo.endian = this->fileBuffer[0];
    this->headerInfo.cbSampleEntry = this->fileBuffer[1];
    this->headerInfo.cbHeader = this->fileBuffer[2] | (this->fileBuffer[3] << 8);
    this->headerInfo.cbHeaderInFile = this->fileBuffer[4] | (this->fileBuffer[5] << 8);
    this->headerInfo.format = this->fileBuffer[6] | (this->fileBuffer[7] << 8);
    this->headerInfo.revision = this->fileBuffer[8] | (this->fileBuffer[9] << 8) | (this->fileBuffer[10] << 16) | (this->fileBuffer[11] << 24);
    this->headerInfo.stopReason = this->fileBuffer[20] | (this->fileBuffer[21] << 8) | (this->fileBuffer[22] << 16) | (this->fileBuffer[23] << 24);
    this->headerInfo.uSPS = (uint64_t)this->fileBuffer[48] | ((uint64_t)this->fileBuffer[49] << 8) | ((uint64_t)this->fileBuffer[50] << 16) | ((uint64_t)this->fileBuffer[51] << 24) | 
        ((uint64_t)this->fileBuffer[52] << 32) | ((uint64_t)this->fileBuffer[53] << 40) | ((uint64_t)this->fileBuffer[54] << 48) | ((uint64_t)this->fileBuffer[55] << 56);

    if (this->headerInfo.format != 1 || this->headerInfo.revision != 1 || this->headerInfo.cbHeaderInFile != 512 || this->headerInfo.uSPS > 50000000000 || this->headerInfo.uSPS == 0) { return ConvertStatus::INVALIDHEADER; }
    return ConvertStatus::OK;
}

ConvertStatus DlogConvert::convertToCsv(std::istream& inputFS, std::ostream& outputFS)
{
    std::string stopReason;
    //Place stopreason first
    switch(this->headerInfo.stopReason)
    {
        case 0:
            stopReason = "Log Completed Normally\n";
            break;
        case 1:
            stopReason = "Log Forced\n";
            break;
        case 2:
            stopReason = "Log Error\n";
            break;
        case 3:
            stopReason = "Log Overflow\n";
            break;
        default:
            stopReason = "Log Unknown Error\n";
    }
        
    outputFS.write(stopReason.c_str(), stopReason.length());

    uint64_t count = 0;
    uint64_t bytesFilled = 0;
    double dt = 1.0 / ((double)(this->headerInfo.uSPS / 1000000.0));
    double prevX = -1;
    
    while (!inputFS.eof()) 
    {
        inputFS.read((char*)(&this->fileBuffer[0]), this->BUFFERSIZE);
        uint64_t numBytes = inputFS.gcount();
        uint64_t outfileCount = 0;
        
        DEBUGLN("Parsing input buffer");
        for (uint64_t i = 0; i < numBytes; i = i + 2) 
        {
            double x = (double)(dt * (count + i));
            if (x < prevX)
            {
                std::cerr << "ERR! X: " << x << " PREV X: " << prevX << std::endl;
            }
            prevX = x;
            int16_t voltage = this->fileBuffer[i] | (int16_t)(this->fileBuffer[i + 1] << 8);
            double y = (double)voltage / 1000.0;
            this->doubleToString(x, &(this->outputBuffer[outfileCount]), 5, &bytesFilled);
            outfileCount += bytesFilled;
            this->outputBuffer[outfileCount++] = ',';
            this->doubleToString(y, &(this->outputBuffer[outfileCount]), 3, &bytesFilled);
            outfileCount += bytesFilled;
            this->outputBuffer[outfileCount++] = '\n';
        }
        DEBUGLN("Done parsing input buffer");
        count += numBytes;
        DEBUG("dlog bytes read: ");
        DEBUGLN(count);
        outputFS.write(&(this->outputBuffer[0]), outfileCount);
    }
    return ConvertStatus::OK;
}

void DlogConvert::doubleToString(double num, char* str, uint8_t precision, uint64_t* numBytesFilled)
{
    if (precision < 0)
    {
        precision = 0;
    }
    else if (precision > 9)
    {
        precision = 9;
    }
    int index = 0;
    if (num < 0)
    {
        num *= -1;
        str[0] = '-';
        ++index;
    }
    int whole = num;
    double frac = num - whole;
    int place = 0;

    while (whole > 0)
    {
        place++;
        whole /= 10;
    }
    whole = num;
    for (int i = 0; i < place; i++)
    {
        str[index + (place - i - 1)] = (whole % 10) + 48;
        whole /= 10;
    }
    
    index += place;
    str[index++] = '.';

    uint64_t mult = 10;
    
    for (int i = 0; i < precision; i++)
    {
        str[index + i] = ((uint64_t)(frac * mult) % 10) + 48;
        mult *= 10;
    }

    index += precision;

    *numBytesFilled = index;
}
} //namespace DlogUtil