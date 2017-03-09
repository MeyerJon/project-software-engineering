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

class Station {
private:
    std::string naam;
    std::string vorige;
    std::string volgende;
    int spoor;
    Station* initCheck;
    int opstappen;
    int afstappen;

public:
    Station();
    Station(std::string n, std::string vor, std::string volg, int sp, int op, int af);

    /** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     *  \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /** \brief Geef de naam terug van het station.
     *  \return De naam van het station.
     *
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getNaam.");\n
     */
    std::string getNaam() const;

    /** \brief Geef het vorig station terug.
     *  \return Het vorig station.
     *
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVorige.");\n
     */
    std::string getVorige() const;

    /** \brief Geef het volgende station.
     *  \return Het volgende station.
     *
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");\n
     */
    std::string getVolgende() const;

    /** \brief Geef het Spoor terug.
     *  \return Het spoor.
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSpoor.");\n
     */
    int getSpoor() const;

    // TODO: opstappen() && afstappen
};

#endif /* SRC_STATION_H_ */
