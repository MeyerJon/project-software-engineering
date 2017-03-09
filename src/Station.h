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
    int opstappen;
    int afstappen;
    Station* initCheck;

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

    /** \brief Geef het spoor terug.
     *  \return Het spoor.
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSpoor.");\n
     */
    int getSpoor() const;

    /** \brief Geef het aantal opstappende mensen terug.
     *  \return Een aantal opstappende mensen.
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getOpstappen.");\n
     */
    int getOpstappen() const;

    /** \brief Geef het afstappende mensen terug.
     *  \return Een aantal afstappende mensen.
     * REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getAfstappen.");\n
     */
    int getAfstappen() const;
};

#endif /* SRC_STATION_H_ */
