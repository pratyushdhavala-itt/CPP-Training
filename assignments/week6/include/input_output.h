#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "parser.h"
#include "json_parser.h"
#include "csv_parser.h"
#include "xml_parser.h"

bool exitParser();
void performOperations(Parser* parser);
int getValidOption(int minOption, int maxOption);
double getValidDouble();
void performJsonOperations(JSONParser* jsonParser);
void performXmlOperations(XMLParser* xmlParser);
void performCsvOperations(CSVParser* csvParser);
int getValidInt();
#endif