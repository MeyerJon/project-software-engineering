/*
 * Tram.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Tram.h"

// Global consts
double Tram::ticketPrijs = 2.0;


Tram::Tram() {
    initCheck = this;
    ENSURE(properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
}

Tram::Tram(int zit, int snel, int sp, int nr, std::string beginS, StatisticsTram* statistics) {
    stats = statistics;
    bezettePlaatsen = 0;
    zitplaatsen = zit;
    voertuignummer = nr;
    snelheid = snel;
    spoor = sp;
    beginStation = beginS;
    huidigStation = beginS;
    initCheck = this;
    ENSURE(properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
}

bool Tram::properlyInitialised() const {
    return initCheck == this;
}

int Tram::getZitplaatsen() const {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getZitplaatsen.");
    return zitplaatsen;
}

int Tram::getBezettePlaatsen() const {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getBezetteZitplaatsen.");
    return bezettePlaatsen;
}

std::vector<Passagier*> Tram::getPassagiers() const {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getPassagiers.");
    return passagiers;
}

int Tram::getSnelheid() const {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getSnelheid.");
    return snelheid;
}

int Tram::getSpoor() const {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getSpoor.");
    return spoor;
}

std::string Tram::getBeginStation() const {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getBeginStation.");
    return beginStation;
}

std::string Tram::getHuidigStation() const {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
    return huidigStation;
}

std::string Tram::getType() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getType.");
    return "Tram";
}

int Tram::getVoertuignummer() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getVoertuignummer.");
    return voertuignummer;
}

double Tram::getOmzet() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getOmzet.");
    return stats->getOmzet();
}

double Tram::getTicketPrijs() const {
    ENSURE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getTicketPrijs.");
    return ticketPrijs;
}

bool Tram::bevatPassagier(Passagier *pas) const {
    return (find(passagiers.begin(), passagiers.end(), pas) != passagiers.end());
}

void Tram::setHuidigStation(std::string station) {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
    huidigStation = station;
    ENSURE((getHuidigStation() == station), "huidigStation is niet aangepast door setHuidigStation.");
}

void Tram::setBezettePlaatsen(int aantalBezettePlaatsen) {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanrooep van setBezettePlaatsen.");
    bezettePlaatsen = aantalBezettePlaatsen;
    ENSURE((this->getBezettePlaatsen() == aantalBezettePlaatsen), "bezettePlaatsen is niet aangepast door setBezettePlaatsen.");
}

void Tram::setOmzet(double o) {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van setOmzet.");
    stats->setOmzet(o);
}

void Tram::addPassagier(Passagier* pas){
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van addPassagiers.");
    REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van addPassagier.");
    passagiers.push_back(pas);
    ENSURE(bevatPassagier(pas), "Passagiers niet aangepast bij aanroep van addPassagiers.");
}

void Tram::removePassagier(Passagier *pas) {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van removePassagiers.");
    REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van removePassagier.");
    REQUIRE(bevatPassagier(pas), "Passagier zat niet in tram bij de aanroep van removePassagier");
    passagiers.erase(std::remove(passagiers.begin(), passagiers.end(), pas));
    ENSURE(!bevatPassagier(pas), "Passagiers niet aangepast bij aanroep van addPassagiers.");
}

bool Tram::isAlbatros() const {
    REQUIRE(this-properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isAlbatros.");
    return false;
}

bool Tram::isPCC() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isPCC.");
    return false;
}

void Tram::setVoertuignummer(int n) {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van setVoertuignummer.");
    voertuignummer = n;
    ENSURE((getVoertuignummer() == n), "Voertuignummer niet aangepast bij aanroep van setVoertuignummer.");
}

void Tram::verplaatsTram(std::string station, Exporter* exp, std::ostream& os) {
    REQUIRE(properlyInitialised(),
            "Tram was niet geinitialiseerd bij de aanroep van verplaatsTram.");

    std::string output = "Tram " + std::to_string(spoor) + " reed van station " +
                         huidigStation + " naar station " + station + ".\n";
    this->setHuidigStation(station);

    ENSURE((getHuidigStation() == station),
           "huidigStation is niet correct aangepast.");
}

bool Tram::afstappen(Passagier* pas){
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van afstappen.");
    REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van afstappen.");
    removePassagier(pas);
    pas->updateVertrokken();
    setBezettePlaatsen(getBezettePlaatsen() - pas->getHoeveelheid());
    return true;
}

bool Tram::opstappen(Passagier* pas) {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van afstappen.");
    REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van afstappen.");
    if(getBezettePlaatsen() + pas->getHoeveelheid() > getZitplaatsen()
        or getBezettePlaatsen() + pas->getHoeveelheid() < 0){
        return false;
    }
    else{
        // Passagier stapt op
        addPassagier(pas);
        pas->updateVertrokken();
        setBezettePlaatsen(getBezettePlaatsen() + pas->getHoeveelheid());
        setOmzet(getOmzet() + (pas->getHoeveelheid() * ticketPrijs));
        return true;
    }
}

StatisticsTram* Tram::getStatistics() {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getStatistics.");
    return stats;
}

bool Tram::isLeeg() {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isLeeg.");
    return passagiers.size() == 0;
}

Tram::~Tram() {
    delete stats;
}

PCC::PCC(int zit, int snel, int sp, int nr, std::string beginS, StatisticsTram* statistics) {
    stats = statistics;
    bezettePlaatsen = 0;
    zitplaatsen = zit;
    voertuignummer = nr;
    snelheid = snel;
    spoor = sp;
    beginStation = beginS;
    huidigStation = beginS;
    initCheck = this;
    ENSURE(properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
}

bool PCC::isAlbatros() const {
    REQUIRE(this-properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isAlbatros.");
    return false;
}

bool PCC::isPCC() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isPCC.");
    return true;
}

std::string PCC::getType() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getType.");
    return "PCC";
}

Albatros::Albatros(int zit, int snel, int sp, int nr, std::string beginS, StatisticsTram* statistics) {
    stats = statistics;
    bezettePlaatsen = 0;
    zitplaatsen = zit;
    voertuignummer = nr;
    snelheid = snel;
    spoor = sp;
    beginStation = beginS;
    huidigStation = beginS;
    initCheck = this;
    ENSURE(properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
}

bool Albatros::isAlbatros() const {
    REQUIRE(this-properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isAlbatros.");
    return true;
}

bool Albatros::isPCC() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isPCC.");
    return false;
}

std::string Albatros::getType() const {
    REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getType.");
    return "Albatros";
}
