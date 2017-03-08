/*
 * Spoor.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: sergio
 */

#include "Spoor.h"

Spoor::Spoor() {
    // TODO Auto-generated constructor stub

}

Spoor::~Spoor() {
    // TODO Auto-generated destructor stub
}

bool Spoor::properlyInitialised() const {
    return initCheck == this;
}

int Spoor::getLijnNr() const {
    REQUIRE(this->properlyInitialised(),
            "Spoor was niet geinitialiseerd bij de aanroep van getLijnNr.");
    return lijnNr;
}
