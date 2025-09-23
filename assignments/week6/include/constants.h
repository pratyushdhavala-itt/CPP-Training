#ifndef CONSTANTS_H
#define CONSTANTS_H


inline const char* PRINT_CSV_PARSE_ERROR = "Error parsing CSV file: ";
inline const char* PRINT_JSON_PARSE_ERROR = "JSON parse error: ";
inline const char* PRINT_JSON_EXTENSION = "json";
inline const char* PRINT_XML_EXTENSION = "xml";
inline const char* PRINT_CSV_EXTENSION = "csv";
inline const char* PRINT_FILE_ERROR = "Cannot open file: ";
inline const char* PRINT_XML_PARSE_ERROR = "XML parse error: ";
inline const char* PRINT_NEXT_LINE = "\n";
inline const char* PRINT_ENTER_FILE = "Please enter the file name with extension: ";
inline const char* PRINT_ERROR = "Error: ";
inline const char* PRINT_CSV_INDENT = " ";
inline const char* PRINT_XML_INDENT = "  ";
inline const char* JSON_OUTPUT_FILE_PATH = "./output_files/output.json";
inline const char* XML_OUTPUT_FILE_PATH = "./output_files/output.xml";
inline const char* CSV_OUTPUT_FILE_PATH = "./output_files/output.csv";
inline const char* PRINT_INVALID_OPTION = "Invalid input. Please enter a valid option number.\n";
inline const char* PRINT_CHOOSE_JSON_OPERATION = "Select from the below operations you want to perform on your JSON objects:-\n   1. Get books by Genre\n   2. Filter by minimum rating\nEnter your option: ";
inline const char* PRINT_CHOOSE_XML_OPERATION = "Select the operations you want to perform:-\n   1. Get by airline\n   2. Get by origin\n   3. Get by destination\nEnter your option: ";
inline const char* PRINT_CHOOSE_CSV_OPERATION = "Select the operations you want to perform:-\n   1. Get Person by ID\n   2. Get by City\n   3. Get by Department\nEnter your option: ";
inline const char* RELATIVE_FILE_PATH = "./input_files/";

namespace CSV {
    inline const char* ID = "ID";
    inline const char* NAME = "Name";
    inline const char* AGE = "Age";
    inline const char* CITY = "City";
    inline const char* DEPARTMENT = "Department";

    inline const char* PRINT_ONE = ". ";
    inline const char* PRINT_TWO = " (";
    inline const char* PRINT_THREE = ") from ";
    inline const char* PRINT_FOUR = " works in ";
    inline const char* PRINT_NO_ID_FOUND = "No person found with ID ";
    inline const char* PRINT_NO_PERSON_FOUND = "No persons found in city ";
    inline const char* PRINT_NO_DEPARTMENT_FOUND = "No persons found in department ";
};

namespace JSON {

    inline const char* ID = "id";
    inline const char* TITLE = "title";
    inline const char* AUTHOR = "author";
    inline const char* GENRE = "genre";
    inline const char* YEAR = "year";
    inline const char* RATING = "rating";
    inline const char* PRINT_ONE = "Title: ";
    inline const char* PRINT_TWO = "Author: ";
    inline const char* PRINT_THREE = "Genre: ";
    inline const char* PRINT_FOUR = "Published in: ";
    inline const char* PRINT_FIVE = "Rating: ";
    inline const char* PRINT_NO_RATINGS_FOUND = "No books found with rating >= ";
    inline const char* PRINT_NO_GENRE_FOUND = "No books found for genre: ";
};

namespace XML {

    inline const char* FLIGHT = "Flight";
    inline const char* ID = "id";
    inline const char* AIRLINE = "Airline";
    inline const char* ORIGIN = "Origin";
    inline const char* DESTINATION = "Destination";
    inline const char* DEPARTURE = "Departure";
    inline const char* ARRIVAL = "Arrival";
    inline const char* DURATION = "Duration";
    inline const char* STATUS = "Status";
    inline const char* PRINT_ONE = "Flight ID   : ";
    inline const char* PRINT_TWO = "Airline     : ";
    inline const char* PRINT_THREE = "Route       : ";
    inline const char* PRINT_FOUR = "Departure   : ";
    inline const char* PRINT_FIVE = "Arrival     : ";
    inline const char* PRINT_SIX = "Duration    : ";
    inline const char* PRINT_SEVEN = "Status      : ";
    inline const char* PRINT_EIGHT = "-----------------------------\n";
    inline const char* PRINT_NINE = " -> ";
    inline const char* PRINT_TEN = "-----------------------------\n   Flight Schedule Report    \n-----------------------------\n";
    inline const char* PRINT_ELEVEN = ":\n-----------------------------\n";
    inline const char* PRINT_FLIGHT_ONE = "Flights to ";
    inline const char* PRINT_FLIGHT_TWO = "Flights from ";
    inline const char* PRINT_FLIGHT_THREE = "Flights by ";

};

#endif