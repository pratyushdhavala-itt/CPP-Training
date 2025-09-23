#include <iostream>
#include <fstream>
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include "xml_parser.h"
#include "constants.h"

using namespace std;

XMLParser::XMLParser(const std::string& filename) : Parser(filename) {}

void XMLParser::parse() {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file(filename.c_str());

    if (!result) {
        std::cerr << "XML parsed with errors: " << result.description() << std::endl;
    }

    pugi::xml_node flightsNode = document.child("Flights");

    flightCount = 0;
    for (pugi::xml_node flight : flightsNode.children("Flight")) {
        flightCount++;
    }

    flights = new Flight[flightCount];

    int i = 0;
    for (pugi::xml_node flight : flightsNode.children(XML::FLIGHT)) {
        flights[i].id          = flight.attribute(XML::ID).as_string();
        flights[i].airline     = flight.child(XML::AIRLINE).text().as_string();
        flights[i].origin      = flight.child(XML::ORIGIN).text().as_string();
        flights[i].destination = flight.child(XML::DESTINATION).text().as_string();
        flights[i].departure   = flight.child(XML::DEPARTURE).text().as_string();
        flights[i].arrival     = flight.child(XML::ARRIVAL).text().as_string();
        flights[i].duration    = flight.child(XML::DURATION).text().as_string();
        flights[i].status      = flight.child(XML::STATUS).text().as_string();
        i++;
    }

}


std::string XMLParser::print(const Flight& f) {
    std::string out;
    out += XML::PRINT_ONE + f.id + PRINT_NEXT_LINE;
    out += XML::PRINT_TWO + f.airline + PRINT_NEXT_LINE;
    out += XML::PRINT_THREE + f.origin + XML::PRINT_NINE + f.destination + PRINT_NEXT_LINE;
    out += XML::PRINT_FOUR + f.departure + PRINT_NEXT_LINE;
    out += XML::PRINT_FIVE + f.arrival + PRINT_NEXT_LINE;
    out += XML::PRINT_SIX + f.duration + PRINT_NEXT_LINE;
    out += XML::PRINT_SEVEN + f.status + PRINT_NEXT_LINE;
    out += XML::PRINT_EIGHT;
    return out;
}

std::string XMLParser::getParsedData() {
    std::string report;
    report += XML::PRINT_TEN;

    for (int i = 0; i < flightCount; i++) {
        report += print(flights[i]);
    }
    return report;
}

std::string XMLParser::getByDestination(const std::string& destination) {
    std::string result = XML::PRINT_FLIGHT_ONE + destination + XML::PRINT_ELEVEN;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].destination == destination) {
            result += print(flights[i]);
        }
    }
    return result;
}

std::string XMLParser::getByOrigin(const std::string& origin) {
    std::string result = XML::PRINT_FLIGHT_TWO + origin + XML::PRINT_ELEVEN;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].origin == origin) {
            result += print(flights[i]);
        }
    }
    return result;
}

std::string XMLParser::getByAirline(const std::string& airline) {
    std::string result = XML::PRINT_FLIGHT_THREE + airline + XML::PRINT_ELEVEN;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].airline == airline) {
            result += print(flights[i]);
        }
    }
    return result;
}

XMLParser::~XMLParser() {
    delete[] flights;
}