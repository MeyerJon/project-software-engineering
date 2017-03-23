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
    os << output;
    documentStarted = true;

    ENSURE(documentStarted,
            "Document was niet aangemaakt bij de aanroep van write.");
}

void Exporter::finish(std::ostream &os) {
    REQUIRE(this->properlyInitialised(),
            "Exporter was niet geinitialiseerd bij de aanroep van finish.");
    REQUIRE(documentStarted,
            "Document was niet aangemaakt voor de aanroep van finish.");
}

bool Exporter::isDocumentStarted() const {
    return documentStarted;
}

void ExporterHTML::write(std::string& output, std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Exporter was niet geinitialiseerd bij de aanroep van write.");

    while (output.find("\n") != std::string::npos) {
        output.replace(output.find("\n"), std::string("\n").length(), "<br>");
    }
    if (!documentStarted) this->createHTMLHead(os);
    documentStarted = true;
    os << "\t\t<p>\n" << output << "\n</p>\n";

    ENSURE(documentStarted,
           "Document was niet aangemaakt bij de aanroep van write.");
}

void ExporterHTML::createHTMLHead(std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "ExporterHTML was niet geinititaliseerd bij de aanroep van createHTMLHead.");
    REQUIRE(!documentStarted,
            "Document was al aangemaakt voor de aanroep van createHTMLHead.");

    os << "<!DOCTYPE html>\n"
       << "<html>\n"
       << "\t<head>\n"
       << "\t\t<title>" << "Project Software Engineering" << "</title>\n"
       << "\t\t<style>\n"
       << "\t\t\tp {text-align: center;}\n"
       << "\t\t</style>\n"
       << "\t</head>\n"
       << "\t<body>\n";
    documentStarted = true;

    ENSURE(documentStarted,
           "Document was niet aangemaakt bij de aanroep van createHTMLHead.");
}

void ExporterHTML::finish(std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "ExporterHTML was niet geinititaliseerd bij de aanroep van finish.");
    REQUIRE(documentStarted,
            "Document was niet aangemaakt voor de aanroep van finish.");

    os  << "\t</body>\n"
        << "</html>";
}
