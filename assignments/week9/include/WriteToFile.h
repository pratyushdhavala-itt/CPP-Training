#ifndef WRITE_TO_FILE
#define WRITE_TO_FILE

#include <string>
#include <fstream>
#include "Writer.h"

class WriteToFile : public IWriter { 

private:
    const std::string filePath = "text.txt";

public:
    void operator()(const std::string& content, std::ios_base::openmode writeMode) {

        std::fstream file;
        file.open(filePath, writeMode);
        file << content << std::endl;
        file.close();
    }
};

#endif