/*
 * Tram.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Tram.h"
#include "Spoor.h"
#include "Station.h"

Tram::Tram() {
    initCheck = this;
}

Tram::Tram(int zit, int snel, Spoor* sp, Station* beginS) {
    zitplaatsen = zit;
    passagiers = 0;
    snelheid = snel;
    spoor = sp;
    beginStation = beginS;
    huidigStation = beginS;
    initCheck = this;
}

Tram::~Tram() {
    // TODO Auto-generated destructor stub
}

bool Tram::properlyInitialised() const {
    return initCheck == this;
}

int Tram::getZitplaatsen() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getZitplaatsen.");
    return zitplaatsen;
}

int Tram::getPassagiers() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getPassagiers.");
    return passagiers;
}

int Tram::getSnelheid() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getSnelheid.");
    return snelheid;
}

Spoor* Tram::getSpoor() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getSpoor.");
    return spoor;
}

Station* Tram::getBeginStation() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getBeginStation.");
    return beginStation;
}

Station* Tram::getHuidigStation() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
    return huidigStation;
}

void Tram::verplaatsTram(Station *station, Exporter* exp) {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van verplaatsTram.");

    huidigStation = station;
    // TODO: Uitvoer
    std::string output = "Tram " + std::to_string(spoor->getLijnNr()) + " reed van station " +
                         station->getNaam() + " naar station " + station->getNaam() + ".\n";

    ENSURE((huidigStation == station),
           "huidigStation is niet correct aangepast.");\
}