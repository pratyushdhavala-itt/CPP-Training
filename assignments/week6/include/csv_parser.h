#ifndef CSV_PARSER
#define CSV_PARSER

#include "parser.h"
#include "csv.hpp"
#include "person.h"
class CSVParser : public Parser {
private:

    Person* persons;
    int personCount;
    csv::CSVReader fileReader;

public:
    CSVParser(const std::string& filename);
    void parse();
    std::string print(const Person& p);
    std::string getParsedData();
    std::string getByCity(const std::string& city);
    std::string getByDepartment(const std::string& department);
    std::string getById(int id);
    ~CSVParser();

};

#endif