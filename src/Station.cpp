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
    ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Station::Station(std::string n, std::map<int, std::string> vorigeStations,
                 std::map<int, std::string> volgendeStations, StatisticsStation* statistics) {
    naam = n;
    stats = statistics;
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
    ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

bool Station::properlyInitialised() const {
    return initCheck == this;
}

bool Station::bevatSpoor(int spoor) const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij aanroep van bevatSpoor.");
    return (verbindingen.count(spoor) != 0);
}

std::string Station::getNaam() const {
    REQUIRE(properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van getNaam.");

    return naam;
}

std::string Station::getType() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType");
    return "Station";
}

std::string Station::getVolgende(int spoor) const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
    REQUIRE(bevatSpoor(spoor), ("Station bevat spoor niet bij aanroep van getVolgende."));
    return verbindingen.at(spoor).volgende;
}

std::string Station::getVorige(int spoor) const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVorige.");
    REQUIRE(bevatSpoor(spoor), "Station bevat spoor niet bij aanroep van getVorige.");
    return verbindingen.at(spoor).vorige;
}

std::vector<int> Station::getSporen() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSporen.");
    std::vector<int> sporen;
    for(auto& p : verbindingen){
        sporen.push_back(p.first);
    }
    return sporen;
}

StatisticsStation* Station::getStatistics() {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getStatistics.");
    return stats;
}

bool Station::isHalte() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte");
    return false;
}

bool Station::isMetrostation() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
    return false;
}

bool Station::spoorBezet(int spoor) const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van spoorBezet.");
    REQUIRE(bevatSpoor(spoor), "Station bevat het gegeven spoor niet bij aanroep van spoorBezet.");
    return trams.at(spoor);
}

void Station::bezetSpoor(int spoor, bool isTramHier) {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van bezetSpoor.");
    REQUIRE(bevatSpoor(spoor), "Station bevat het gegeven spoor niet bij aanroep van bezetSpoor.");
    trams.at(spoor) = isTramHier;
    ENSURE(spoorBezet(spoor) == isTramHier, "Spoor was niet correct bezet na aanroep van bezetSpoor");
}

Station::~Station() {
    delete (*this).stats;
}

Metrostation::Metrostation(std::string n, std::map<int, std::string> vorigeStations,
                 std::map<int, std::string> volgendeStations, StatisticsStation* statistics) {
    naam = n;
    stats = statistics;
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
    ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

bool Metrostation::isHalte() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte");
    return false;
}

bool Metrostation::isMetrostation() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
    return true;
}

std::string Metrostation::getType() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType");
    return "Metrostation";
}

Halte::Halte(std::string n, std::map<int, std::string> vorigeStations,
                 std::map<int, std::string> volgendeStations, StatisticsStation* statistics) {
    naam = n;
    stats = statistics;
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
    ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

bool Halte::isHalte() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte");
    return true;
}

bool Halte::isMetrostation() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
    return false;
}

std::string Halte::getType() const {
    REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType");
    return "Halte";
}