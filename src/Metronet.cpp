/*
 * Metronet.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Metronet.h"

Metronet::Metronet() {
    stats = new StatisticsMetronet();
    initCheck = this;
    ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Metronet::Metronet(Exporter* exp) {
    stats = new StatisticsMetronet();
    Metronet::exp = exp;
    initCheck = this;
    ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Metronet::~Metronet() {
    for (auto s : stations) {
        delete s.second;
    }
    for (auto t : trams) {
        delete t.second;
    }
    for (auto p : passagiers) {
        delete p.second;
    }
    delete stats;
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

Station* Metronet::getStation(std::string name){
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getStation.");
    REQUIRE(bevatStation(name), "Metronet bevat opgevraagd station niet bij de aanroep van getStation.");
    return stations.at(name);
}

std::map<int, Tram*>& Metronet::getTrams() {
    return trams;
}

Tram* Metronet::getTram(int nummer) {
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getTram.");
    return trams.at(nummer);
}

std::map<std::string, Passagier*>& Metronet::getPassagiers() {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getPassagiers.");
    return passagiers;
}

bool Metronet::bevatTram(Tram *tram) {
    REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van bevatTram.");
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatTram.");
    bool out = true;
    if(trams.count(tram->getVoertuignummer()) == 0){
        out = false;
    }
    return out;
}

bool Metronet::bevatStation(Station *station) {
    REQUIRE(station->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van bevatStation.");
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatStation.");
    bool out = true;
    if(stations.count(station->getNaam()) == 0){
        out = false;
    }
    return out;
}

bool Metronet::bevatStation(std::string name) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatStation.");
    return stations.count(name) != 0;
}

bool Metronet::bevatSpoor(int spoor) {
    bool out = true;
    if(find(sporen.begin(), sporen.end(), spoor) == sporen.end()){
        out = false;
    }
    return out;
}

bool Metronet::bevatPassagier(Passagier *pas) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatPassagier.");
    REQUIRE(pas->properlyInitialised(),
            "Passagier was niet geinitialiseerd bij de aanroep van bevatPassagier.");
    return(passagiers.count(pas->getNaam()) != 0);

}

bool Metronet::bevatPassagier(std::string name){
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatPassagier.");
    return passagiers.count(name) != 0;
}

void Metronet::addStation(
        std::string naam,
        std::string type,
        std::map<int, std::string> vorigeStations,
        std::map<int, std::string> volgendeStations) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addStation.");
    StatisticsStation* stats = new StatisticsStation();
    Station* station = new Station(naam, type, vorigeStations, volgendeStations, stats);
    stations[station->getNaam()] = station;
    ENSURE(station->properlyInitialised(),
            "Station was niet geinitialiseerd bij de aanroep van addStation.");
    ENSURE(bevatStation(station), "Station was niet toegevoegd bij de aanroep van addStation.");
}

void Metronet::addTram(
        int zitplaatsen,
        int snelheid,
        int spoor,
        int voertuigNr,
        std::string type,
        std::string beginStation) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van addTram.");
    REQUIRE(bevatStation(beginStation), "Metronet bevat beginstation niet bij de aanroep van addTram");
    StatisticsTram* stats = new StatisticsTram(zitplaatsen);
    Tram* tram = new Tram(zitplaatsen, snelheid, spoor, voertuigNr, type, beginStation, stats);
    trams[tram->getVoertuignummer()] = tram;
    stations[beginStation]->bezetSpoor(spoor, true);

    // Gegevens verzamelen
    if(type == "Albatros"){
        this->stats->setNrAlba(this->stats->getNrAlba() + 1);
    }
    else if(type == "PCC"){
        this->stats->setNrPCC(this->stats->getNrPCC() + 1);
    }
    this->stats->setAantalZitplaatsen(this->stats->getAantalZitplaatsen() + zitplaatsen);

    ENSURE(tram->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van addTram.");
    ENSURE(this->bevatTram(tram),
            "Tram was niet toegevoegd bij de aanroep van addTram.");
}

void Metronet::addSpoor(int spoor) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addSpoor.");

    sporen.push_back(spoor);

    ENSURE(bevatSpoor(spoor), "Spoor was niet toegevoegd bij de aanroep van addSpoor.");
}

void Metronet::addPassagier(
        std::string naam, std::string beginStation, std::string eindStation, int hoeveelheid) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addPassagier.");
    Passagier* pas = new Passagier(naam, beginStation, eindStation, hoeveelheid);
    passagiers[pas->getNaam()] = pas;

    // Gegevens verzamelen
    this->stats->setTotaalAantalGroepen(this->stats->getTotaalAantalGroepen() + 1);
    this->stats->setTotaalAantalPersonen(this->stats->getTotaalAantalPersonen() + hoeveelheid);

    ENSURE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van addPassagier.");
    ENSURE(bevatPassagier(pas), "Passagier was niet toegevoegd bij de aanroep van addPassagier.");
}

bool Metronet::checkConsistent(std::ostream &os) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");
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
            try {
                vorig = stations.at(vor);
                volgend = stations.at(vol);
            }
            catch(std::out_of_range& ex){
                std::string out = "Station " + station->getNaam() + " heeft geen vorig of volgend station.\n";
                exp->write(out, os);
                consistent = false;
                continue;
            }
            if (!(volgend->bevatSpoor(sp) and vorig->bevatSpoor(sp))){
                std::string out = "Station " + station->getNaam() + " mist spoor " + std::to_string(sp) + ".\n";
                exp->write(out, os);
                consistent = false;
                continue;
            }
            if(volgend->getVorige(sp) != station->getNaam() or vorig->getVolgende(sp) != station->getNaam()){
                std::string out =
                        "Station " + station->getNaam()
                        + " is niet verbonden met het vorig of volgend station.\n";
                exp->write(out, os);
                consistent = false;
            }
        }
    }

    // Tramchecks
    for(auto& p : trams){
        Tram* tram = p.second;
        gevondenTramSporen.push_back(tram->getSpoor());
        if(find(gevondenStationSporen.begin(),
                gevondenStationSporen.end(),
                tram->getSpoor()) == gevondenStationSporen.end()){
            std::string out =
                    "Spoor " + std::to_string(tram->getSpoor()) + " van tram "
                    + std::to_string(tram->getVoertuignummer())
                    + " behoort tot geen enkel station.\n";
            exp->write(out, os);
            consistent = false;
        }
        if(stations.count(tram->getBeginStation()) == 0){
            std::string out =
                    "Tram " + std::to_string(tram->getVoertuignummer()) +
                    " heeft een ongeldig beginstation.\n";
            exp->write(out, os);
            consistent = false;
        }
    }

    // Spoorchecks
    for(int spoor : sporen){
        if(find(gevondenTramSporen.begin(), gevondenTramSporen.end(), spoor) == gevondenTramSporen.end()){
            std::string out = "Spoor " + std::to_string(spoor) + " heeft geen tram.\n";
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
            std::string out = "Passagier " + pas->getNaam() + " heeft een ongeldig begin- of eindstation.\n";
            exp->write(out, os);
            consistent = false;
            continue;
        }
        if(pas->getBeginStation() == pas->getEindStation()){
            std::string out = "Passagier " + pas->getNaam() + " heeft hetzelfde begin- en eindpunt.\n";
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
            std::string out = "Passagier " + pas->getNaam() + " heeft geen verbinding tot zijn bestemming.\n";
            exp->write(out, os);
            consistent = false;
        }
    }

    return consistent;
}

void Metronet::printMetronet(std::ostream& os) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van printMetronet.");
    // Print station, vorig en volgend, en het nummer en de capaciteit van het spoor
    std::string stations_head = "--== STATIONS ==--\n";
    exp->write(stations_head, os);
    for(auto s : stations){
        Station* station = s.second;
        std::string out = "-> Station " + station->getNaam() + "\n";
        out += "wachtende passagiers:\n";
        for (auto& p : passagiers) {
            Passagier* passagier = p.second;
            if (passagier->getBeginStation() == station->getNaam()) {
                out += "* " + passagier->getNaam() + ", " + std::to_string(passagier->getHoeveelheid()) +
                       " mensen, reist naar station " + passagier->getEindStation() + "\n";
            }
        }
        out += "\n";
        exp->write(out, os);
    }
    std::string trams_head = "--== TRAMS ==--\n";
    exp->write(trams_head, os);
    for (auto& t : trams) {
        Tram* tram = t.second;
        std::string out = "Tram " + std::to_string(tram->getSpoor()) +
                          " nr " + std::to_string(tram->getVoertuignummer()) + "\n";
        out += "zitplaatsen: " + std::to_string(tram->getZitplaatsen()) + "\n";
        out += "snelheid: " + std::to_string(tram->getSnelheid()) + "\n";
        out += "huidig station: " + tram->getHuidigStation() + "\n";
        out += "reizende passagiers:\n";
        for (auto& p : passagiers) {
            Passagier* passagier = p.second;
            if (passagier->huidigeTram() == tram->getVoertuignummer()) {
                out += "* " + passagier->getNaam() + ", " + std::to_string(passagier->getHoeveelheid()) +
                       " mensen, reist naar station " + passagier->getEindStation() + "\n";
            }
        }
        out += "\n";
        exp->write(out, os);
    }
}

void Metronet::printMetronetGrafisch(std::ostream& os) {
    std::map<std::string, bool> stationsBezocht;
    for (auto& p : stations) {
        Station* station = p.second;
        std::string stationNaam = station->getNaam();
        if (stationsBezocht.count(stationNaam) == 0) {
            stationsBezocht[stationNaam] = false;
        }
        else if (stationsBezocht[stationNaam] == true) {
            continue;
        }
        stationsBezocht[stationNaam] = true;
        for (auto& spoor : station->getSporen()) {
            std::string start = "Spoor " + std::to_string(spoor) + ": ";
            std::string filler = "===";
            std::string stations_out = start + stationNaam + filler;
            std::string trams_out;
            trams_out.append(start.length(), ' ');
            if (station->spoorBezet(spoor)) trams_out += "T";
            else trams_out += " ";
            trams_out.append(stationNaam.length() - 1 + filler.length(), ' ');
            std::string stationVolgende = station->getVolgende(spoor);
            while (stationVolgende != stationNaam) {
                stations_out += stationVolgende + filler;
                stationsBezocht[stationVolgende] = true;
                if (stations[stationVolgende]->spoorBezet(spoor)) trams_out += "T";
                else trams_out += " ";
                trams_out.append(stationVolgende.length() - 1 + filler.length(), ' ');
                stationVolgende = stations[stationVolgende]->getVolgende(spoor);
            }
            stations_out += "\n";
            trams_out += "\n";
            exp->write(stations_out, os);
            exp->write(trams_out, os);
        }
    }
}

int Metronet::opstappenAfstappen(Tram* tram, std::ostream& os) {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van opstappenAfstappen.");
    REQUIRE(tram->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van opstappenAfstappen.");
    REQUIRE(bevatTram(tram), "Tram bestaat niet in het metronet.");

    Station* st = stations[tram->getHuidigStation()];
    StatisticsStation* stationStats = st->getStatistics();
    int spoor = tram->getSpoor();
    std::string station = tram->getHuidigStation();

    int afgestapteGroepen = 0;

    if (!st->bevatSpoor(spoor)) {
        std::string out = "Tram " + std::to_string(spoor) +" bevindt zich niet in station " + station +
                          " en er kan niemand op- of afstappen.\n";
        return 0;
    }

    if (tram->isAlbatros() && st->isHalte()) return 0;

    // Eerst afstappende passagiers
    for (Passagier* passagier: tram->getPassagiers()) {
        if (station == passagier->getEindStation()) {
            if (tram->afstappen(passagier)) {
                std::string out = "In station " + station + " stapte " + passagier->getNaam() +
                                  " af tram " + std::to_string(tram->getVoertuignummer()) + ". (" +
                                  std::to_string(passagier->getHoeveelheid()) + " personen)\n";

                exp->write(out, os);
                afgestapteGroepen++;
                passagier->setHuidigeTram(-2);
            }
        }
    }

    // Daarna opstappende passagiers
    for (auto& passagier: getPassagiers()) {
        if (tram->isAlbatros() && stations[passagier.second->getEindStation()]->isHalte()) continue;
        if ((station == passagier.second->getBeginStation())
            && (!(passagier.second->isVertrokken()))) {
            // Statistics-objecten voor gegevensverzameling
            StatisticsTram* tramStats = tram->getStatistics();

            // Kijk of voldoende plaats is
            if (stations[passagier.second->getEindStation()]->bevatSpoor(spoor)) {
                if (tram->opstappen(passagier.second)) {
                    std::string out = "In station " + station + " stapte " + passagier.second->getNaam() +
                                      " op tram " + std::to_string(tram->getVoertuignummer()) + ". (" +
                                      std::to_string(passagier.second->getHoeveelheid()) + " personen)\n";
                    exp->write(out, os);
                    passagier.second->setHuidigeTram(tram->getVoertuignummer());

                    // Gegevens updaten/verzamelen
                    // Metronetgegevens
                    this->stats->setTotaleOmzet(this->stats->getTotaleOmzet() + (passagier.second->getHoeveelheid() * tram->getTicketPrijs()));
                    // Tramgegevens
                    tramStats->setAantalGroepen(tramStats->getAantalGroepen() + 1);
                    tramStats->setAantalPersonen(tramStats->getAantalPersonen() + passagier.second->getHoeveelheid());
                    // Stationgegevens
                    stationStats->setAantalGroepen(stationStats->getAantalGroepen() + 1);
                    stationStats->setAantalPersonen(stationStats->getAantalPersonen() + passagier.second->getHoeveelheid());


                } else {
                    std::string out = "Waarschuwing: Er was niet voldoende plaats op tram " +
                                      std::to_string(tram->getVoertuignummer())
                                      + ", Groep " + passagier.second->getNaam() + " is niet opgestapt.\n";
                    exp->write(out, os);
                    // Gegevens updaten/verzamelen
                    tramStats->setAantalFails(tramStats->getAantalFails() + 1);
                }
            }
        }
    }

    return afgestapteGroepen;
}

void Metronet::rondrijden(std::ostream& os) {
    REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van rondrijden.");

    int aantalGroepen = passagiers.size();

    while (aantalGroepen > 0) {
        for (auto& tram: trams) {
            aantalGroepen -= opstappenAfstappen(tram.second, os);
            if (tramMagVertrekken(tram.second)) {
                std::string volgendStation =
                        stations[tram.second->getHuidigStation()]->getVolgende(tram.second->getSpoor());
                stations[tram.second->getHuidigStation()]->bezetSpoor(tram.second->getSpoor(), false);
                stations[volgendStation]->bezetSpoor(tram.second->getSpoor(), true);
                tram.second->setHuidigStation(volgendStation);
            }
            tram.second->getStatistics()->updateGemiddeldeBezettingsgraad(tram.second->getBezettePlaatsen());
        }
    }
    std::string out = "Alle passagiers zijn op hun bestemming aangekomen.\n\n";
    exp->write(out, os);
    ENSURE(allePassagiersAangekomen(), "Niet alle passagiers zijn op hun bestemming aangekomen na rondrijden.");
}

bool Metronet::allePassagiersAangekomen() {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van allePassagiersAangekomen.");
    for (auto p : passagiers) {
        Passagier* passagier = p.second;
        if (!passagier->isAangekomen()) return false;
    }
    return true;
}

bool Metronet::tramMagVertrekken(Tram* tram) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van tramMagVertrekken.");
    REQUIRE(tram->properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van tramMagVertrekken.");

    std::string volgendStation = stations[tram->getHuidigStation()]->getVolgende(tram->getSpoor());

    // Als er tram is op volgend station, zelfde spoor return false
    return !stations[volgendStation]->spoorBezet(tram->getSpoor());
}

void Metronet::printStatistics(std::ostream& os) {
    REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van printStatistics.");
    std::string head = "-- METRONET GEGEVENS --\n";
    exp->write(head, os);

    // Metronetgegevens
    std::string metronetHead = "-Metronetgegevens: \n";
    exp->write(metronetHead, os);
    std::string out = "Totale omzet: €" + std::to_string(this->stats->getTotaleOmzet()) + ".\n";
    out += "Totaal aantal passagiers: " + std::to_string(this->stats->getTotaalAantalPersonen()) + ".\n";
    out += "Totaal aantal groepen: " + std::to_string(this->stats->getTotaalAantalGroepen()) + ".\n";
    out += "Totaal aantal zitplaatsen: " + std::to_string(this->stats->getAantalZitplaatsen()) + ".\n";
    double bezettingsgraad = 0.0;
    Tram* popTram = trams.begin()->second;
    for(auto& p : trams){
        bezettingsgraad += p.second->getStatistics()->getBezettingsgraad();
        if(p.second->getStatistics()->getAantalPersonen() > popTram->getStatistics()->getAantalPersonen()){
            popTram = p.second;
        }
    }
    bezettingsgraad /= (double) trams.size();
    out += "Gemiddelde bezettingsgraad: " + std::to_string(bezettingsgraad) + ".\n";
    out += "Populairste tram: " + std::to_string(popTram->getVoertuignummer()) + " (" + std::to_string(popTram->getStatistics()->getAantalPersonen()) + " personen)\n";
    exp->write(out, os);

    // Tramgegevens
    std::string tramHead = "\n-Tramgegevens: \n";
    exp->write(tramHead, os);
    for(auto& p : trams){
        Tram* tram = p.second;
        StatisticsTram* stats = tram->getStatistics();
        std::string out = "Tram " + std::to_string(tram->getVoertuignummer()) +": \n";
        out += "Totale omzet: €" + std::to_string(stats->getOmzet()) + ".\n";
        out += "Totaal aantal groepen: " + std::to_string(stats->getAantalGroepen()) + ".\n";
        out += "Totaal aantal personen: " + std::to_string(stats->getAantalPersonen()) + ".\n";
        out += "Aantal mislukte opstappen: " + std::to_string(stats->getAantalFails()) + ".\n";
        out += "Gemiddelde bezettingsgraad: " + std::to_string(stats->getBezettingsgraad()) + ".\n";
        out += "\n";
        exp->write(out, os);
    }

    // Stationgegevens
    std::string stationHead = "-Stationgegevens: \n";
    exp->write(stationHead, os);
    for(auto& p : stations){
        Station* station = p.second;
        StatisticsStation* stats = station->getStatistics();
        std::string out = "Station " + station->getNaam() + ": \n";
        out += "Totaal aantal groepen: " + std::to_string(stats->getAantalGroepen()) + ".\n";
        out += "Totaal aantal personen: " + std::to_string(stats->getAantalPersonen()) + ".\n";
        out += "\n";
        exp->write(out, os);
    }

    std::string end = "-------------------------------------------\n\n";
    exp->write(end, os);
}

void Metronet::reset() {
    REQUIRE(this->properlyInitialised(),
            "Metronet was niet geinitialiseerd bij de aanroep van reset.");

    for (auto s : stations)
        delete s.second;
    for (auto t : trams)
        delete t.second;
    for (auto p : passagiers)
        delete p.second;
    stations.clear();
    trams.clear();
    passagiers.clear();
    sporen.clear();
}
