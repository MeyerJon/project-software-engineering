/*
 * Station.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Station.h"

Station::Station() {
    // TODO Auto-generated constructor stub
    initCheck = this;
}

Station::Station(std::string n, Station* vor, Station* volg, Spoor* sp, int o, int a) {
    naam = n;
    vorige = vor;
    volgende = volg;
    spoor = sp;
    opstappen = o;
    afstappen = a;
}

Station::~Station() {
    // TODO Auto-generated destructor stub
}

bool Station::properlyInitialised() const {
    return initCheck == this;
}

std::string Station::getNaam() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getNaam.");

    return naam;
}

Station* Station::getVorige() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getVorige.");

    return vorige;
}

Station* Station::getVolgende() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
    return volgende;

}

Spoor* Station::getSpoor() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getSpoor.");
    return spoor;
}
