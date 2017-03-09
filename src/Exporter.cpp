/*
 * Exporter.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: sergio
 */

#include "Exporter.h"

Exporter::Exporter() {
    documentStarted = false;
    initCheck = this;
}

bool Exporter::properlyInitialised() const {
    return initCheck == this;
}

void Exporter::write(std::string& output, std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Exporter was niet geinitialiseerd bij de aanroep van write.");
    this->validate(os);
    os << output;
}

void Exporter::validate(std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Exporter was niet geinitialiseerd bij de aanroep van validate.");
    if (!documentStarted) documentStarted = true;
}

void ExporterHTML::write(std::string& output, std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Exporter was niet geinitialiseerd bij de aanroep van write.");
    this->validate(os);
    os << "<p>\n" << output << "\n</p>\n";
    this->validate(os);
}

void ExporterHTML::validate(std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Exporter was niet geinitialiseerd bij de aanroep van validate.");
    if (!documentStarted) this->validateHead(os);
    else this->validateTail(os);

    ENSURE((documentStarted == true),
            "Het document werd niet gevalideerd bij de aanroep van validate.");
}

void ExporterHTML::validateHead(std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "ExporterHTML was niet geinititaliseerd bij de aanroep van validateHead.");
    REQUIRE((documentStarted == false),
            "Document was al aangemaakt bij de aanroep van validateHead.");

    os << "<!DOCTYPE html>\n"
       << "<html>\n"
       << "<head>\n"
       << "\t<title>" << "Project Software Engineering" << "</title>\n"
       << "</head>\n"
       << "<body>\n";

    ENSURE((documentStarted == true),
            "Document werd niet aangemaakt bij de aanroep van validateHead.");
}

void ExporterHTML::validateTail(std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "ExporterHTML was niet geinititaliseerd bij de aanroep van validateTail.");
    REQUIRE((documentStarted == true),
            "Document was nog niet aangemaakt bij de aanroep van validateTail.");

    os << "</body>\n"
       << "</html>";

    ENSURE((documentStarted == true),
            "Document werd niet aangemaakt bij de aanroep van validateTail.");
}
