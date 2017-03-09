/*
 * Metronet.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Metronet.h"

Metronet::Metronet() {
    initCheck = this;
}

Metronet::~Metronet() {
    for (auto s : stations) {
        delete s.second;
    }
    for (auto t : trams) {
        delete t.second;
    }
}

bool Metronet::properlyInitialised() {
    return initCheck == this;
}

void Metronet::addStation(Station* station) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addStation.");
    REQUIRE(station->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van addStation.");

    stations[station->getNaam()] = station;

    ENSURE((stations.find(station->getNaam()) != stations.end()),
            "Station was niet toegevoegd bij de aanroep van addStation.");
}

void Metronet::addTram(Tram* tram) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addTram.");
    REQUIRE(tram->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van addTram.");

    trams[tram->getSpoor()] = tram;

    ENSURE((trams.find(tram->getSpoor()) != trams.end()),
            "Tram was niet toegevoegd bij de aanroep van addTram.");
}

void Metronet::addSpoor(int spoor) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addSpoor.");

    sporen.push_back(spoor);

    ENSURE((sporen[sporen.size() - 1] == spoor),
            "Spoor was niet toegevoegd bij de aanroep van addSpoor.");
}

bool Metronet::checkConsistent(Exporter* exp, std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");
    std::vector<int> stationSporen; // Dit is handig om de consistentie van trams en sporen te checken
    std::vector<int> tramSporen; // Dit is handig om de consistentie van de trams en sporen te checken
    bool consistent = true;
    // Elk station is verbonden met een voorgaand en volgend station voor elk spoor
    for (auto s : stations) {
        Station* station = s.second;
        Station* volgende = stations[station->getVolgende()];
        Station* vorige = stations[station->getVorige()];
        stationSporen.push_back(station->getSpoor());
        if (station->getVolgende() == "") {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " heeft geen volgende station.";
            exp->write(out, os);
            consistent = false;
        } else if (station->getVorige() == "") {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " heeft geen vorig station.";
            exp->write(out, os);
            consistent = false;
        } else if (stations[vorige->getVolgende()] != station) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " is niet gelinkt met het volgende station "
                    + volgende->getNaam() + ".";
            exp->write(out, os);
            consistent = false;
        } else if (stations[volgende->getVorige()] != station) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " is niet gelinkt met het vorig station "
                    + vorige->getNaam() + ".";
            exp->write(out, os);
            consistent = false;
        }
    }

    // Er bestaan geen trams met een lijnnummer dat niet overeenkomt met een spoor in een station
    // Het beginstation van een tram is een geldig station in het metronet
    for (auto t : trams) {
        Tram* tram = t.second;
        if (stations.find(tram->getBeginStation()) == stations.end()) {
            std::string out = "ERROR: Tram "
                    + std::to_string(tram->getSpoor())
                    + " heeft een ongeldig beginstation.";
            exp->write(out, os);
            consistent = false;
        }
        if (find(stationSporen.begin(), stationSporen.end(), tram->getSpoor())
                == stationSporen.end()) {
            std::string out = "ERROR: Spoor "
                    + std::to_string(tram->getSpoor())
                    + " komt niet door een station.";
            exp->write(out, os);
            consistent = false;
        }
    }

    // Er zijn geen sporen waarvoor geen tram bestaat
    for (int spoor : sporen) {
        if (find(tramSporen.begin(), tramSporen.end(), spoor)
                == tramSporen.end()) {
            std::string out = "ERROR: Spoor "
                    + std::to_string(spoor) + " heeft geen tram.";
            exp->write(out, os);
            consistent = false;
        }
    }
    // Elk spoor maximaal een keer door elk station komt
    // Per woensdag 8 maart: dit is niet mogelijk
    return consistent;
}
