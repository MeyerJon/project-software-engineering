/*
 * Tram.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Tram.h"

Tram::Tram() {
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
}

Tram::Tram(int zit, int snel, int sp, std::string beginS) {
    zitplaatsen = zit;
    passagiers = 0;
    snelheid = snel;
    spoor = sp;
    beginStation = beginS;
    huidigStation = beginS;
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
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

int Tram::getSpoor() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getSpoor.");
    return spoor;
}

std::string Tram::getBeginStation() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getBeginStation.");
    return beginStation;
}

std::string Tram::getHuidigStation() const {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
    return huidigStation;
}

void Tram::setHuidigStation(std::string station) {
    REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
    huidigStation = station;
    ENSURE((getHuidigStation() == station), "huidigStation is niet aangepast door setHuidigStation.");
}

void Tram::setPassagiers(int pas){
    REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van setPassagiers.");
    REQUIRE(pas >= 0, "Aantal passagiers moet positief zijn.");
    passagiers = pas;
    ENSURE((getPassagiers() == pas), "Aantal passagiers niet aangepast bij aanroep van setPassagiers.");
}

void Tram::verplaatsTram(std::string station, Exporter* exp, std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van verplaatsTram.");

    std::string output = "Tram " + std::to_string(spoor) + " reed van station " +
                         huidigStation + " naar station " + station + ".\n";
    this->setHuidigStation(station);

    ENSURE((getHuidigStation() == station),
           "huidigStation is niet correct aangepast.");
}

bool Tram::afstappen(int afstappen){
    REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van afstappen.");
    REQUIRE(afstappen >= 0, "Afstappen kan geen negatieve waarde hebben bij aanroep van afstappen.");
    if (afstappen <= passagiers) {
        setPassagiers((passagiers-afstappen));
        return true;
    } else {
        setPassagiers(0);
        return false;
    }
}

bool Tram::opstappen(int opstappen) {
    REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van afstappen.");
    REQUIRE(opstappen >= 0, "Opstappen kan geen negatieve waarde hebben bij aanroep van opstappen.");
    if (opstappen <= zitplaatsen - passagiers) {
        setPassagiers((passagiers+opstappen));
        return true;
    } else {
        setPassagiers(zitplaatsen);
        return false;
    }
}
