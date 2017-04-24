/*
 * Metronet.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Metronet.h"

Metronet::Metronet() {
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Metronet::Metronet(Exporter* exp) {
    Metronet::exp = exp;
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Metronet::~Metronet() {
    for (auto s : stations) {
        delete s.second;
    }
    for (auto t : trams) {
        delete t.second;
    }
}

Metronet& Metronet::operator=(const Metronet& rhs) {
    if (this != &rhs) {
        this->exp = rhs.exp;
        this->initCheck = this;
    }
    return *this;
}

bool Metronet::properlyInitialised() {
    return initCheck == this;
}

std::map<std::string, Station*> Metronet::getStations() {
    return stations;
}

std::map<int, Tram*>& Metronet::getTrams() {
    return trams;
}

std::map<std::string, Passagier*>& Metronet::getPassagiers() {
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getPassagiers.");
    return passagiers;
}

bool Metronet::bevatTram(Tram *tram) {
    REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij aanroep van bevatTram.");
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatTram.");
    bool out = true;
    if(trams.count(tram->getVoertuignummer()) == 0){
        out = false;
    }
    return out;
}

bool Metronet::bevatStation(Station *station) {
    REQUIRE(station->properlyInitialised(), "Station was niet geinitialiseerd bij aanroep van bevatStation.");
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatStation.");
    bool out = true;
    if(stations.count(station->getNaam()) == 0){
        out = false;
    }
    return out;
}

bool Metronet::bevatSpoor(int spoor) {
    bool out = true;
    if(find(sporen.begin(), sporen.end(), spoor) == sporen.end()){
        out = false;
    }
    return out;
}

bool Metronet::bevatPassagier(Passagier *pas) {
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatPassagier.");
    REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van bevatPassagier.");
    return(passagiers.count(pas->getNaam()) != 0);

}

void Metronet::addStation(Station* station) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addStation.");
    REQUIRE(station->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van addStation.");

    stations[station->getNaam()] = station;

    ENSURE(this->bevatStation(station),
            "Station was niet toegevoegd bij de aanroep van addStation.");
}

void Metronet::addTram(Tram* tram) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addTram.");
    REQUIRE(tram->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van addTram.");

    trams[tram->getVoertuignummer()] = tram;

    ENSURE(this->bevatTram(tram),
            "Tram was niet toegevoegd bij de aanroep van addTram.");
}

void Metronet::addSpoor(int spoor) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addSpoor.");

    sporen.push_back(spoor);

    ENSURE(this->bevatSpoor(spoor),
            "Spoor was niet toegevoegd bij de aanroep van addSpoor.");
}

void Metronet::addPassagier(Passagier *pas) {
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addPassagier.");
    REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van addPassagier.");
    passagiers.at(pas->getNaam()) = pas;
    ENSURE(bevatPassagier(pas), "Passagier was niet toegevoegd bij aanroep van addPassagier.");
}

bool Metronet::checkConsistent(std::ostream &os) {
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");
    bool consistent = true;
    // Nuttig om aanwezigheid van sporen na te gaan
    std::vector<int> gevondenStationSporen;
    std::vector<int> gevondenTramSporen;

    // Stationchecks
    for(auto& p : stations){
        Station* station = p.second;
        // Voor elk spoor: check voorgaand/volgend station
        for(int sp : station->getSporen()){
            gevondenStationSporen.push_back(sp);
            std::string vor = station->getVorige(sp);
            std::string vol = station->getVolgende(sp);
            Station* vorig; Station* volgend;
            try{
                vorig = stations.at(vor);
                volgend = stations.at(vol);
            }
            catch(std::out_of_range& ex){
                std::string out = "Station " + station->getNaam() + " heeft geen vorig of volgend station.";
                exp->write(out, os);
                consistent = false;
            }
            if(volgend->getVorige(sp) != station->getNaam() or vorig->getVolgende(sp) != station->getNaam()){
                std::string out = "Station " + station->getNaam() + " is niet verbonden met het vorig of volgend station.";
                exp->write(out, os);
                consistent = false;
            }
        }
    }

    // Tramchecks
    for(auto& p : trams){
        Tram* tram = p.second;
        gevondenTramSporen.push_back(tram->getSpoor());
        if(find(gevondenStationSporen.begin(), gevondenStationSporen.end(), tram->getSpoor()) == gevondenStationSporen.end()){
            std::string out = "Spoor " + std::to_string(tram->getSpoor()) + " van tram " + std::to_string(tram->getVoertuignummer())
                              + " behoort tot geen enkel station.";
            exp->write(out, os);
            consistent = false;
        }
        if(stations.count(tram->getBeginStation()) == 0){
            std::string out = "Tram " + std::to_string(tram->getVoertuignummer()) + " heeft een ongeldig beginstation.";
            exp->write(out, os);
            consistent = false;
        }
    }

    // Spoorchecks
    for(int spoor : sporen){
        if(find(gevondenTramSporen.begin(), gevondenTramSporen.end(), spoor) == gevondenTramSporen.end()){
            std::string out = "Spoor " + std::to_string(spoor) + " heeft geen tram.";
            exp->write(out, os);
            consistent = false;
        }
    }

    // Passagierchecks
    for(auto& p : passagiers){
        Passagier* pas = p.second;
        Station* begin;
        Station* eind;
        try{
            begin = stations.at(pas->getBeginStation());
            eind = stations.at(pas->getEindStation());
        }catch(std::out_of_range& ex){
            std::string out = "Passagier " + pas->getNaam() + " heeft een ongeldig begin- of eindstation.";
            exp->write(out, os);
            consistent = false;
        }
        if(pas->getBeginStation() == pas->getEindStation()){
            std::string out = "Passagier " + pas->getNaam() + " heeft hetzelfde begin- en eindpunt.";
            exp->write(out, os);
            consistent = false;
        }

        // Bestemming nakijken
        std::vector<int> beginSporen = begin->getSporen();
        std::vector<int> eindSporen = eind->getSporen();
        bool foundConnection = false;
        for(int sp : eindSporen){
            if(find(beginSporen.begin(), beginSporen.end(), sp) != beginSporen.end()){
                foundConnection = true;
                break;
            }
        }
        if(!foundConnection){
            std::string out = "Passagier " + pas->getNaam() + " heeft geen verbinding tot zijn bestemming.";
            exp->write(out, os);
            consistent = false;
        }
    }

    return consistent;
}

void Metronet::printMetronet(std::ostream& os) {
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

bool Metronet::opstappenAfstappen(std::string station, std::ostream& os) {
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

void Metronet::rondrijden(std::ostream& os) {
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij aanroep van rondrijden.");
    for(auto& p : trams){
        Tram* t = p.second;
        do{
            opstappenAfstappen(t->getHuidigStation(), os);
            t->verplaatsTram(stations[t->getHuidigStation()]->getVolgende(), exp, os);
        }while(t->getHuidigStation() != t->getBeginStation());
        ENSURE(t->getHuidigStation() == t->getBeginStation(), "Tram niet geëindigd in beginstation na rondrijden.");
    }
}

void Metronet::reset() {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij aanroep van reset.");

    for (auto s : stations)
        delete s.second;
    for (auto t : trams)
        delete t.second;
    stations.clear();
    trams.clear();
    sporen.clear();
}
