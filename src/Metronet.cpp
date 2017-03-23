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

Metronet::Metronet(Exporter* exp) {
    Metronet::exp = exp;
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

SuccessEnum Metronet::setup(std::string filename, std::ostream& os){
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str())) {
        std::string out = "ERROR: Kan bestand " + filename + " niet openen.\n";
        exp->write(out, os);
        return BadImport;
    }
    TiXmlElement* root = doc.FirstChildElement();
    std::string rootName;
    if (root != NULL) rootName = root->Value();
    else {
        std::string out = "ERROR: Er is geen root.\n";
        exp->write(out, os);
        return BadImport;
    }
    if (!(rootName == "ROOT" || rootName == "METRONET")) {
        std::string out = "ERROR: Geen root gevonden. Gelieve een root object genaamd <ROOT> of <METRONET> aan te maken.\n";
        exp->write(out, os);
        return BadImport;
    }

    SuccessEnum endResult = Success;
    // Iterate over all elements
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        std::string elemName = elem->Value();
        if(elemName == "STATION") {
            std::string attrName;
            std::string name = "";
            std::string vor = "";
            std::string volg = "";
            int opstappen = 0;
            int afstappen = 0;
            int spoor = -1;
            try {
                for(TiXmlNode* node = elem->FirstChild(); node != NULL; node = node->NextSibling()){
                    attrName = node->Value();
                    TiXmlText* text;
                    std::string t;
                    if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                    else continue;
                    if(text != NULL) t = text->Value();
                    else continue;
                    if(attrName == "naam") name = t;
                    else if(attrName == "volgende") volg = t;
                    else if(attrName == "vorige") vor = t;
                    else if(attrName == "spoor") {
                        if (std::stoi(t) >= 0) spoor = std::stoi(t);
                    }
                    else if(attrName == "opstappen") {
                        opstappen = std::stoi(t);
                    }
                    else if(attrName == "afstappen") {
                        afstappen = std::stoi(t);
                    }
                    else{
                        std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                        exp->write(out, os);
                        endResult = PartialImport;
                    }
                }
                if(name == "" or vor == "" or volg == "" or spoor == -1){
                    std::string out = "ERROR: Station mist een attribuut.\n";
                    exp->write(out, os);
                    endResult = PartialImport;
                    continue;
                }
                Station* station = new Station(name, vor, volg, spoor, opstappen, afstappen);
                this->addStation(station);
                this->addSpoor(spoor);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Station niet toegevoegd.\n";
                exp->write(out, os);
                endResult = PartialImport;
                continue;
            }
        }
        else if(elemName == "TRAM"){
            std::string attrName;
            int zitpl = -1;
            int snelh = -1;
            int spoor = -1;
            std::string beginS = "";
            try {
                for(TiXmlNode* node = elem->FirstChild(); node != NULL; node = node->NextSibling()){
                    attrName = node->Value();
                    TiXmlText* text;
                    std::string t;
                    if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                    else continue;
                    if(text != NULL) t = text->Value();
                    else continue;
                    if(attrName == "zitplaatsen") zitpl = stoi(t);
                    else if(attrName == "snelheid") snelh = stoi(t);
                    else if(attrName == "lijnNr") spoor = std::stoi(t);
                    else if(attrName == "beginStation") beginS = t;
                    else{
                        std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                        endResult = PartialImport;
                        exp->write(out, os);
                    }
                }
                if(zitpl == -1 or snelh == -1 or spoor == -1 or beginS == ""){
                    std::string out = "ERROR: Tram mist een attribuut.\n";
                    exp->write(out, os);
                    endResult = PartialImport;
                    continue;
                }
                Tram* tram = new Tram(zitpl, snelh, spoor, beginS);
                this->addTram(tram);
                this->addSpoor(spoor);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Tram niet toegevoegd.\n";
                exp->write(out, os);
                endResult = PartialImport;
                continue;
            }

        } else {
            continue;
        }
    }

    return endResult;
}

std::map<std::string, Station*> Metronet::getStations() {
    return stations;
}

std::map<int, Tram*>& Metronet::getTrams() {
    return trams;
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

bool Metronet::checkConsistent(std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");
    std::vector<int> stationSporen; // Dit is handig om de consistentie van trams en sporen te checken
    std::vector<int> tramSporen; // Dit is handig om de consistentie van de trams en sporen te checken
    std::map<int, std::vector<Station*>> lijnen; // Dit is handig om aparte lijnen met hetzelfde lijnNr te vinden
    bool consistent = true;
    // Elk station is verbonden met een voorgaand en volgend station voor elk spoor
    for (auto s : stations) {
        Station* station = s.second;
        Station* volgende;
        Station* vorige;
        if (stations.find(station->getVolgende()) != stations.end()) volgende = stations[station->getVolgende()];
        else {
            std::string out = "ERROR: Station " + station->getNaam()
                              + " heeft geen volgende station.\n";
            exp->write(out, os);
            return false;
        }
        if (stations.find(station->getVorige()) != stations.end()) vorige = stations[station->getVorige()];
        else {
            std::string out = "ERROR: Station " + station->getNaam()
                              + " heeft geen vorig station.\n";
            exp->write(out, os);
            return false;
        }
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
        if (consistent) {
            if (lijnen.count(station->getSpoor()) == 0) {
                Station *original = station;
                Station *current = original;
                do {
                    lijnen[station->getSpoor()].push_back(current);
                    current = stations.at(current->getVolgende());
                } while (current != original);
            } else {
                std::vector<Station *> &lijn = lijnen[station->getSpoor()];
                if (find(lijn.begin(), lijn.end(), station) == lijn.end()) {
                    std::string out = "Station " + station->getNaam() + " behoort tot een gesloten circulaire lijn.\n";
                    exp->write(out, os);
                    consistent = false;
                }
            }
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
    // Elk spoor maximaal een keer voorkomen over alle circulair verbonden stations
    // Per dinsdag 21 maart: dit is niet mogelijk
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
    for(auto& p : trams){
        Tram* t = p.second;
        do{
            opstappenAfstappen(t->getHuidigStation(), os);
            t->verplaatsTram(stations[t->getHuidigStation()]->getVolgende(), exp, os);
        }while(t->getHuidigStation() != t->getBeginStation());
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
