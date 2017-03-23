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

/**
 * \brief Station klasse die een STATION element uit een XML-bestand representeert
 */
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
    /**
     * \brief De lege constructor van de klasse Station
     * \post ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Station();

    /**
     * \brief De default constructor van de klasse Station
     * \param n De naam van het station
     * \param vor Het vorig station
     * \param volg Het volgend station
     * \param sp Het spoornummer van het station
     * \param op Het aantal opstappende passagiers
     * \param af Het aantal afstappende passgiers
     * \post ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Station(std::string n, std::string vor, std::string volg, int sp, int op, int af);

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Geef de naam terug van het station.
     * \return De naam van het station.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getNaam.");
     */
    std::string getNaam() const;

    /**
     * \brief Geef het vorig station terug.
     * \return Het vorig station.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVorige.");
     */
    std::string getVorige() const;

    /**
     * \brief Geef het volgende station.
     * \return Het volgende station.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
     */
    std::string getVolgende() const;

    /**
     * \brief Geef het spoor terug.
     * \return Het spoor.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSpoor.");
     */
    int getSpoor() const;

    /**
     * \brief Geef het aantal opstappende mensen terug.
     * \return Een aantal opstappende mensen.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getOpstappen.");
     */
    int getOpstappen() const;

    /**
     * \brief Geef het afstappende mensen terug.
     * \return Een aantal afstappende mensen.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getAfstappen.");
     */
    int getAfstappen() const;
};

#endif /* SRC_STATION_H_ */
