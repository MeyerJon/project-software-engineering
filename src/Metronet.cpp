/*
 * Metronet.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Metronet.h"

Metronet::Metronet() {
    // TODO Auto-generated constructor stub
    initCheck = this;
}

Metronet::~Metronet() {
    // TODO Auto-generated destructor stub
}

bool Metronet::properlyInitialised() {
    return initCheck == this;
}

void Metronet::addStation(Station* station) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addStation.");
    REQUIRE(station->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van addStation.");

    stations.push_back(station);

    ENSURE((stations[stations.size() - 1] == station),
            "Station was niet toegevoegd bij de aanroep van addStation.");
}

void Metronet::addTram(Tram* tram) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addTram.");
    REQUIRE(tram->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van addTram.");

    trams.push_back(tram);

    ENSURE((trams[trams.size() - 1] == tram),
            "Tram was niet toegevoegd bij de aanroep van addTram.");
}

void Metronet::addSpoor(Spoor* spoor) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addSpoor.");
    REQUIRE(spoor->properlyInitialised(),
            "Spoor was niet geinitialiseerd bij de aanroep van addSpoor.");

    sporen.push_back(spoor);

    ENSURE((sporen[sporen.size() - 1] == spoor),
            "Spoor was niet toegevoegd bij de aanroep van addSpoor.");
}

bool Metronet::checkConsistent(Exporter* exp) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");

    std::vector<Spoor*> stationSporen; // Dit is handig om de consistentie van trams en sporen te checken
    std::vector<Spoor*> tramSporen; // Dit is handig om de consistentie van de trams en sporen te checken
    bool consistent = true;
    // TODO: Maak output
    // Elk station is verbonden met een voorgaand en volgend station voor elk spoor
    for (Station* station : stations) {
        stationSporen.push_back(station->getSpoor());
        if (station->getVolgende() == nullptr) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " heeft geen volgende station.";
            consistent = false;
        } else if (station->getVorige() == nullptr) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " heeft geen vorig station.";
            consistent = false;
        } else if (station->getVolgende()->getVorige() != station) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " is niet gelinkt met het volgende station "
                    + station->getVolgende()->getNaam() + ".";
            consistent = false;
        } else if (station->getVorige()->getVolgende() != station) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " is niet gelinkt met het vorig station "
                    + station->getVorige()->getNaam() + ".";
            consistent = false;
        }
    }

    // Er bestaan geen trams met een lijnnummer dat niet overeenkomt met een spoor in een station
    // Het beginstation van een tram is een geldig station in het metronet
    for (Tram* tram : trams) {
        if (find(stations.begin(), stations.end(), tram->getBeginStation())
                == stations.end()) {
            std::string out = "ERROR: Tram "
                    + std::to_string(tram->getSpoor()->getLijnNr())
                    + " heeft een ongeldig beginstation.";
            consistent = false;
        }
        tramSporen.push_back(tram->getSpoor());
        if (find(stationSporen.begin(), stationSporen.end(), tram->getSpoor())
                == stationSporen.end()) {
            std::string out = "ERROR: Spoor "
                    + std::to_string(tram->getSpoor()->getLijnNr())
                    + " komt niet door een station.";
            consistent = false;
        }
    }

    // Er zijn geen sporen waarvoor geen tram bestaat
    for (Spoor* spoor : sporen) {
        if (find(tramSporen.begin(), tramSporen.end(), spoor)
                == tramSporen.end()) {
            std::string out = "ERROR: Spoor "
                    + std::to_string(spoor->getLijnNr()) + " heeft geen tram.";
            consistent = false;
        }
    }
    // Elk spoor maximaal een keer door elk station komt
    // Per woensdag 8 maart: dit is niet mogelijk
    return consistent;
}
