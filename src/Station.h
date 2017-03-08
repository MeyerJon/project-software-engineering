/*
 * Station.h
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#ifndef SRC_STATION_H_
#define SRC_STATION_H_

#include <iostream>
#include "DesignByContract.h"

class Spoor;

class Station {
private:
    std::string naam;
    Station* vorige;
    Station* volgende;
    Spoor* spoor;
    Station* initCheck;
public:
    Station();
    virtual ~Station();

    /** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     */
    bool properlyInitialised() const;

    /** \brief Geef de naam terug van het station.
     *
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getNaam.");\n
     */
    std::string getNaam() const;

    /** \brief Geef het vorig station terug.
     *
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVorige.");\n
     */
    Station* getVorige() const;

    /** \brief Geef het volgende station.
     *
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");\n
     */
    Station* getVolgende() const;

    /** \brief Geef het Spoor terug.
     *
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSpoor.");\n
     */
    Spoor* getSpoor() const;

    // TODO: opstappen() && afstappen
};

#endif /* SRC_STATION_H_ */
