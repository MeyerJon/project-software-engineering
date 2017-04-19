//
// Created by jonathan on 19.04.17.
//

#include "Passagier.h"


Passagier::Passagier(std::string n, std::string begin, std::string eind, int h) {
    naam = n;
    beginStation = begin;
    eindStation = eind;
    hoeveelheid = h;
    status = Wachten;
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Default constructor van Passagier is niet in de juiste staat geeindigd.");
}

bool Passagier::properlyInitialised() const {
    return (initCheck == this);
}

std::string Passagier::getNaam() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getNaam.");
    return naam;
}

std::string Passagier::getBeginStation() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getBeginStation.");
    return beginStation;
}

std::string Passagier::getEindStation() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getEindStation.");
    return eindStation;
}

int Passagier::getHoeveelheid() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getHoeveelheid.");
    return hoeveelheid;
}

PassagierStatus Passagier::getStatus() const {
    REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getHoeveelheid.");
    return status;
}

void Passagier::updateStatus() {
    REQUIRE(this->properlyInitialised(), "Passagier was niet geinitialiseerd bij aanroep van setStatus.");
    switch(status){
        case Wachten:
            status = Onderweg;
            break;
        case Onderweg:
            status = Aangekomen;
            break;
        case Aangekomen:
            break;
    }
}