/*
 * Station.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Station.h"

Station::Station() {
    initCheck = this;
}

Station::Station(std::string n, std::string vor, std::string volg, int sp, int o, int a) {
    naam = n;
    vorige = vor;
    volgende = volg;
    spoor = sp;
    opstappen = o;
    afstappen = a;
}

bool Station::properlyInitialised() const {
    return initCheck == this;
}

std::string Station::getNaam() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getNaam.");

    return naam;
}

std::string Station::getVorige() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getVorige.");

    return vorige;
}

std::string Station::getVolgende() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
    return volgende;

}

int Station::getSpoor() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getSpoor.");
    return spoor;
}
