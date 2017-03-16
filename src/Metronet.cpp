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

std::map<std::string, Station*> Metronet::getStations() {
    return stations;
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
                    + " heeft geen volgende station.\n";
            exp->write(out, os);
            consistent = false;
        } else if (station->getVorige() == "") {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " heeft geen vorig station.\n";
            exp->write(out, os);
            consistent = false;
        } else if (stations[vorige->getVolgende()] != station) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " is niet gelinkt met het volgende station "
                    + volgende->getNaam() + ".\n";
            exp->write(out, os);
            consistent = false;
        } else if (stations[volgende->getVorige()] != station) {
            std::string out = "ERROR: Station " + station->getNaam()
                    + " is niet gelinkt met het vorig station "
                    + vorige->getNaam() + ".\n";
            exp->write(out, os);
            consistent = false;
        }
    }

    // Er bestaan geen trams met een lijnnummer dat niet overeenkomt met een spoor in een station
    // Het beginstation van een tram is een geldig station in het metronet
    for (auto t : trams) {
        Tram* tram = t.second;
        tramSporen.push_back(tram->getSpoor());
        if (stations.find(tram->getBeginStation()) == stations.end()) {
            std::string out = "ERROR: Tram "
                    + std::to_string(tram->getSpoor())
                    + " heeft een ongeldig beginstation.\n";
            exp->write(out, os);
            consistent = false;
        }
        if (find(stationSporen.begin(), stationSporen.end(), tram->getSpoor())
                == stationSporen.end()) {
            std::string out = "ERROR: Spoor "
                    + std::to_string(tram->getSpoor())
                    + " komt niet door een station.\n";
            exp->write(out, os);
            consistent = false;
        }
    }

    // Er zijn geen sporen waarvoor geen tram bestaat
    for (int spoor : sporen) {
        if (find(tramSporen.begin(), tramSporen.end(), spoor)
                == tramSporen.end()) {
            std::string out = "ERROR: Spoor "
                    + std::to_string(spoor) + " heeft geen tram.\n";
            exp->write(out, os);
            consistent = false;
        }
    }
    // Elk spoor maximaal een keer door elk station komt
    // Per woensdag 8 maart: dit is niet mogelijk
    return consistent;
}

void Metronet::printMetronet(Exporter* exp, std::ostream& os) {
    std::string header = "\t ---METRONET---\n";
    exp->write(header, os);
    // Print station, vorig en volgend, en het nummer en de capaciteit van het spoor
    for(auto s : stations){
        Station* station = s.second;
        std::string out = "Station " + station->getNaam() + "\n";
        out += "<- Station " + station->getVorige() + "\n";
        out += "-> Station " + station->getVolgende() + "\n";
        out += "Spoor " + std::to_string(station->getSpoor()) + ", ";
        out += std::to_string(trams[station->getSpoor()]->getZitplaatsen()) + " zitplaatsen. \n";
        exp->write(out, os);
    }
}

bool Metronet::opstappenAfstappen(std::string station, Exporter* exp, std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij aanroep van opstappenAfstappen.");
    REQUIRE((stations.find(station) != stations.end()),
            "Station bestaat niet in het metronet.");
    REQUIRE(stations[station]->properlyInitialised(),
            "Station was niet geinitialiseerd bij aanroep van opstappenAfstappen.");

    Station* st = stations[station];
    int spoor = st->getSpoor();
    Tram* tram = trams[spoor];

    int opstappen = st->getOpstappen();
    int afstappen = st->getAfstappen();

    bool consistent = true;

    if (tram->getHuidigStation() != station) {
        std::string out = "Tram " + std::to_string(spoor) +" bevindt zich niet in station " + station +
                          " en er kan niemand op- of afstappen.\n";
        return false;
    }

    if (tram->afstappen(afstappen)) {
        std::string out = "In station " + station + " stapten " + std::to_string(afstappen) +
                          " mensen af tram " + std::to_string(spoor) + ".\n";
        exp->write(out, os);
    } else {
        std::string out = "ERROR: Er stapten te veel mensen af tram " + std::to_string(spoor) + ".\n";
        exp->write(out, os);
        consistent = false;
    }
    if (tram->opstappen(opstappen)) {
        std::string out = "In station " + station + " stapten " + std::to_string(opstappen) +
                          " mensen op tram " + std::to_string(spoor) + ".\n";
        exp->write(out, os);
    } else {
        std::string out = "ERROR: Er stapten te veel mensen op tram " + std::to_string(spoor) + ".\n";
        exp->write(out, os);
        consistent = false;
    }
    return consistent;
}