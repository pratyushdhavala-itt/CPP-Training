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
inline const char* PRINT_CONTINUE_PROGRAM = "Do you want to continue? (y/Y). Press any key to exit: ";
inline const char* PRINT_EXIT_PROGRAM = "Exiting program ! ! ! ";
inline const char* PRINT_INVALID_INPUT = "Invalid input. Please enter a valid number.\n";
inline const char* PRINT_ENTER_BOOK_GENRE = "Please enter the book genre: ";
inline const char* PRINT_ENTER_BOOK_RATING = "Please enter the rating: ";
inline const char* PRINT_ENTER_AIRLINE = "Please enter the airline: ";
inline const char* PRINT_ENTER_ORIGIN = "Please enter the origin: ";
inline const char* PRINT_ENTER_DESTINATION = "Please enter the destination: ";
inline const char* PRINT_ENTER_ID = "Please enter the ID: ";
inline const char* PRINT_ENTER_CITY = "Please enter the city: ";
inline const char* PRINT_ENTER_DEPT = "Please enter the department: ";
inline const char* PRINT_CSV_EXCEPTION = "Invalid CSV schema at row ";
inline const char* PRINT_JSON_EXCEPTION = "Error parsing JSON file";
inline const char* PRINT_JSON_EXCEPTION_TWO = "Invalid JSON: missing 'library' array";
inline const char* PRINT_XML_EXCEPTION = "XML Parse Error: ";
inline const char* PRINT_FACTORY_EXCEPTION = "Unsupported or unknown file format: ";

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

    inline const char* LIBRARY = "library";
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

    inline const char* FLIGHTS = "Flights";
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