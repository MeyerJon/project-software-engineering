//
// Created by jonathan on 24.04.17.
//

#include "Statistics.h"

StatisticsTram::StatisticsTram() {
    initCheck = this;
    omzet = 0.0;
    aantalGroepen = 0;
    aantalPersonen = 0;
    aantalFails = 0;
    ENSURE(properlyInitialised(), "StatisticsTram is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

bool StatisticsTram::properlyInitialised() const {
    return this == initCheck;
}

double StatisticsTram::getOmzet() const {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van getOmzet.");
    return omzet;
}

double StatisticsTram::getBezettingsgraad() const {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van getBezettingsgraad.");
    return bezettingsgraad;
}

int StatisticsTram::getAantalGroepen() const {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van getAantalGroepen.");
    return aantalGroepen;
}

int StatisticsTram::getAantalPersonen() const {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van getAantalPersonen.");
    return aantalPersonen;
}

int StatisticsTram::getAantalFails() const {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van getAantalFails.");
    return aantalFails;
}

void StatisticsTram::setOmzet(double omzet) {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van setOmzet.");
    StatisticsTram::omzet = omzet;
    ENSURE((getOmzet() == omzet), "Omzet is niet aangepast door setOmzet.");
}

void StatisticsTram::setBezettingsgraad(double bezettingsgraad) {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van setBezettingsgraad.");
    StatisticsTram::bezettingsgraad = bezettingsgraad;
    ENSURE((getBezettingsgraad() == bezettingsgraad), "Bezettingsgraad is niet aangepast door setBezettingsgraad.");
}

void StatisticsTram::setAantalGroepen(int aantalGroepen) {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van setAantalGroepen.");
    StatisticsTram::aantalGroepen = aantalGroepen;
    ENSURE((getAantalGroepen() == aantalGroepen), "AantalGroepen is niet aangepast door setAantalGroepen.");
}

void StatisticsTram::setAantalPersonen(int aantalPersonen) {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van setAantalPersonen.");
    StatisticsTram::aantalPersonen = aantalPersonen;
    ENSURE((getAantalPersonen() == aantalPersonen), "AantalPersonen is niet aangepast door setAantalPersonen.");
}

void StatisticsTram::setAantalFails(int aantalFails) {
    REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij de aanroep van setAantalFails.");
    StatisticsTram::aantalFails = aantalFails;
    ENSURE((getAantalFails() == aantalFails), "AantalFail is niet aangepast door setAantalFails.");
}

StatisticsStation::StatisticsStation() {
    initCheck = this;
    ENSURE(properlyInitialised(),
           "StatisticsStation is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

bool StatisticsStation::properlyInitialised() const {
    return this == initCheck;
}

int StatisticsStation::getAantalGroepen() const {
    REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij de aanroep van getAantalGroepen.");
    return aantalGroepen;
}

int StatisticsStation::getAantalPersonen() const {
    REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij de aanroep van getAantalPersonen.");
    return aantalPersonen;
}

void StatisticsStation::setAantalGroepen(int aantalGroepen) {
    REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij de aanroep van setAantalGroepen.");
    StatisticsStation::aantalGroepen = aantalGroepen;
    ENSURE((getAantalPersonen() == aantalGroepen), "AantalPersonen is niet aangepast door setAantalGroepen.");
}

void StatisticsStation::setAantalPersonen(int aantalPersonen) {
    REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij de aanroep van setAantalPersonen.");
    StatisticsStation::aantalPersonen = aantalPersonen;
    ENSURE((getAantalPersonen() == aantalPersonen), "AantalPersonen is niet aangepast door setAantalPersonen.");
}

StatisticsMetronet::StatisticsMetronet() {
    initCheck = this;
    ENSURE(properlyInitialised(),
           "StatisticsMetronet is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

bool StatisticsMetronet::properlyInitialised() const {
    return this == initCheck;
}

double StatisticsMetronet::getTotaleOmzet() const {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van getTotaleOmzet.");
    return totaleOmzet;
}

double StatisticsMetronet::getTotaleBezettingsgraad() const {
    REQUIRE(properlyInitialised(),
            "StatisticsMetronet was niet geinitialiseerd bij de aanroep van getTotaleBezettingsgraad.");
    return totaleBezettingsgraad;
}

int StatisticsMetronet::getAantalBezettePlaatsen() const {
    return aantalBezettePlaatsen;
}

int StatisticsMetronet::getAantalZitplaatsen() const {
    return aantalZitplaatsen;
}

int StatisticsMetronet::getPopLijn() const {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van getPopLijn.");
    return popLijn;
}

int StatisticsMetronet::getNrAlba() const {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van getNrAlba.");
    return nrAlba;
}

int StatisticsMetronet::getNrPCC() const {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van getNrPCC.");
    return nrPCC;
}

void StatisticsMetronet::setTotaleOmzet(double totaleOmzet) {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van setTotaleOmzet.");
    StatisticsMetronet::totaleOmzet = totaleOmzet;
    ENSURE((getTotaleOmzet() == totaleOmzet), "TotaleOmzet is niet aangepast door setTotaleOmzet.");
}

void StatisticsMetronet::setTotaleBezettingsgraad(double totaleBezettingsgraad) {
    REQUIRE(properlyInitialised(),
            "StatisticsMetronet was niet geinitialiseerd bij de aanroep van setTotaleBezettingsgraad.");
    StatisticsMetronet::totaleBezettingsgraad = totaleBezettingsgraad;
    ENSURE((getTotaleBezettingsgraad() == totaleBezettingsgraad),
           "TotaleBezettingsgraad is niet aangepast door setTotaleBezettingsgraad.");
}

void StatisticsMetronet::setAantalBezettePlaatsen(int aantalBezettePlaatsen) {
    REQUIRE(properlyInitialised(),
            "StatisticsMetronet was niet geinitialiseerd bij de aanroep van setAantalBezettePlaatsen.");
    StatisticsMetronet::aantalBezettePlaatsen = aantalBezettePlaatsen;
    ENSURE((getAantalBezettePlaatsen() == aantalBezettePlaatsen),
           "AantalBezettePlaatsen is niet aangepast door setAantalBezettePlaatsen.");
}

void StatisticsMetronet::setAantalZitplaatsen(int aantalZitplaatsen) {
    REQUIRE(properlyInitialised(),
            "StatisticsMetronet was niet geinitialiseerd bij de aanroep van setAantalZitplaatsen.");
    StatisticsMetronet::aantalZitplaatsen = aantalZitplaatsen;
    ENSURE((getAantalZitplaatsen() == aantalZitplaatsen),
           "AantalZitplaatsen is niet aangepast door setAantalZitplaatnse.");
}

void StatisticsMetronet::setPopLijn(int popLijn) {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van setPopLijn.");
    StatisticsMetronet::popLijn = popLijn;
    ENSURE((getPopLijn() == popLijn), "PopLijn is niet aangepast door setPopLijn.");
}

void StatisticsMetronet::setNrAlba(int nrAlba) {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van setNrAlba.");
    StatisticsMetronet::nrAlba = nrAlba;
    ENSURE((getNrAlba() == nrAlba), "NrAlba is niet aangepast door setNrAlba.");
}

void StatisticsMetronet::setNrPCC(int nrPCC) {
    REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij de aanroep van setNrPCC.");
    StatisticsMetronet::nrPCC = nrPCC;
    ENSURE((getNrPCC() == nrPCC), "NrPCC is niet aangepast door setNrPCC.");
}
