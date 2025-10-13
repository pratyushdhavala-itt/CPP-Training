#ifndef I_WRITER_H
#define I_WRITER_H

#include <string>
#include <fstream>

class IWriter {
public:
    virtual void operator()(const std::string& content, std::ios_base::openmode mode) = 0;
    virtual ~IWriter() = default;
};

#endif

