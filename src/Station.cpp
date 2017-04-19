/*
 * Station.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Station.h"

Station::Station() {
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Station::Station(std::string n, std::map<int, std::string> vorigeStations,
                 std::map<int, std::string> volgendeStations) {
    naam = n;
    for(auto& p : vorigeStations){
        int spoor = p.first;
        std::string vorige = p.second;
        std::string volgende = volgendeStations[spoor];
        stationVerbinding verb = {vorige, volgende};
        verbindingen[spoor] = verb;

    }
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

bool Station::properlyInitialised() const {
    return initCheck == this;
}

bool Station::bevatSpoor(int spoor) const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij aanroep van bevatSpoor.");
    return (verbindingen.count(spoor) != 0);
}

std::string Station::getNaam() const {
    REQUIRE(this->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getNaam.");

    return naam;
}

std::string Station::getVolgende(int spoor) const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
    REQUIRE(bevatSpoor(spoor), "Station bevat spoor niet bij aanroep van getVolgende.");
    return verbindingen.at(spoor).volgende;
}

std::string Station::getVorige(int spoor) const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVorige.");
    REQUIRE(bevatSpoor(spoor), "Station bevat spoor niet bij aanroep van getVorige.");
    return verbindingen.at(spoor).vorige;
}

std::vector<int> Station::getSporen() const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSporen.");
    std::vector<int> sporen;
    for(auto& p : verbindingen){
        sporen.push_back(p.first);
    }
    return sporen;
}