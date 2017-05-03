/*
 * Station.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Station.h"
#include "Tram.h"

Station::Station() {
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Station::Station(std::string n, std::string typeNaam, std::map<int, std::string> vorigeStations,
                 std::map<int, std::string> volgendeStations) {
    naam = n;
    if (typeNaam == "Metrostation") type = Metrostation;
    else if (typeNaam == "Halte") type = Halte;
    for(auto& p : vorigeStations){
        int spoor = p.first;
        std::string vorige = p.second;
        std::string volgende = volgendeStations[spoor];
        stationVerbinding verb = {vorige, volgende};
        verbindingen[spoor] = verb;
        // Init trams
        trams[spoor] = false;
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

std::string Station::getType() const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType");
    switch (type) {
        case Metrostation :
            return "Metrostation";
        case Halte :
            return "Halte";
    }
}

std::string Station::getVolgende(int spoor) const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
    REQUIRE(bevatSpoor(spoor), ("Station bevat spoor niet bij aanroep van getVolgende."));
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

bool Station::isHalte() const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte");
    return type == Halte;
}

bool Station::isMetrostation() const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
    return type == Metrostation;
}

bool Station::spoorBezet(int spoor) const {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van spoorBezet.");
    REQUIRE(bevatSpoor(spoor), "Station bevat het gegeven spoor niet bij aanroep van spoorBezet.");
    return trams.at(spoor);
}

void Station::bezetSpoor(int spoor, bool isTramHier) {
    REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van bezetSpoor.");
    REQUIRE(bevatSpoor(spoor), "Station bevat het gegeven spoor niet bij aanroep van bezetSpoor.");
    trams.at(spoor) = isTramHier;
    ENSURE(spoorBezet(spoor) == isTramHier, "Spoor was niet correct bezet na aanroep van bezetSpoor");
}