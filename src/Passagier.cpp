//
// Created by jonathan on 19.04.17.
//

#include "Passagier.h"


Passagier::Passagier(std::string n, std::string begin, std::string eind, int h) {
    naam = n;
    beginStation = begin;
    eindStation = eind;
    hoeveelheid = h;
    vertrokken = false;
    tram = -1;
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Default constructor van Passagier is niet in de juiste staat geeindigd.");
}

bool Passagier::properlyInitialised() const {
    return (initCheck == this);
}

std::string Passagier::getNaam() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getNaam.");
    return naam;
}

std::string Passagier::getBeginStation() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getBeginStation.");
    return beginStation;
}

std::string Passagier::getEindStation() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getEindStation.");
    return eindStation;
}

int Passagier::getHoeveelheid() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van getHoeveelheid.");
    return hoeveelheid;
}

int Passagier::huidigeTram() const {
    REQUIRE(this->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van huidigeTram.");
    return tram;
}

bool Passagier::isVertrokken() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij de aanroep van isVertrokken.");
    return vertrokken;
}

void Passagier::updateVertrokken(){
    REQUIRE(this->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van updateVertrokken.");
    vertrokken = true;
}