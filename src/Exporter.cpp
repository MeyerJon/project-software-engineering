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
    REQUIRE(this->properlyInitialised(),
            "Exporter was niet geinitialiseerd bij de aanroep van isDocumentStarted.");
    return documentStarted;
}
