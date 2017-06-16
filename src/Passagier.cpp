//
// Created by jonathan on 19.04.17.
//

#include "Passagier.h"


Passagier::Passagier() {
    initCheck = this;
}

Passagier::Passagier(std::string n, std::string begin, std::string eind, int h) {
    naam = n;
    beginStation = begin;
    eindStation = eind;
    hoeveelheid = h;
    vertrokken = false;
    tram = -1;
    initCheck = this;
    ENSURE(properlyInitialised(), "Default constructor van Passagier is niet in de juiste staat geeindigd.");
}

bool Passagier::properlyInitialised() const {
    return (initCheck == this);
}

std::string Passagier::getNaam() const {
    REQUIRE(properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getNaam.");
    return naam;
}

std::string Passagier::getBeginStation() const {
    REQUIRE(properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getBeginStation.");
    return beginStation;
}

std::string Passagier::getEindStation() const {
    REQUIRE(properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getEindStation.");
    return eindStation;
}

int Passagier::getHoeveelheid() const {
    REQUIRE(properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getHoeveelheid.");
    return hoeveelheid;
}

void Passagier::setHuidigeTram(int tram) {
    REQUIRE(properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van setHuidigeTram.");
    Passagier::tram = tram;
    ENSURE((huidigeTram() == tram), "Tram is niet aangepast door setHuidigeTram.");
}

int Passagier::huidigeTram() const {
    REQUIRE(properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van huidigeTram.");
    return tram;
}

bool Passagier::isVertrokken() const {
    REQUIRE(properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van isVertrokken.");
    return vertrokken;
}

void Passagier::updateVertrokken(){
    REQUIRE(properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van updateVertrokken.");
    vertrokken = true;
}

bool Passagier::isAangekomen() {
    REQUIRE(properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van isAangekomen.");
    return huidigeTram() == -2;
}