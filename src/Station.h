/*
 * Station.h
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#ifndef SRC_STATION_H_
#define SRC_STATION_H_

#include <iostream>
#include <map>
#include <vector>
#include "DesignByContract.h"

enum StationType {
    Metrostation,
    Halte
};

struct stationVerbinding{
    std::string vorige;
    std::string volgende;
};

/**
 * \brief Station klasse die een STATION element uit een XML-bestand representeert
 */
class Station {
private:
    std::string naam;
    StationType type;
    std::map<int, stationVerbinding> verbindingen;
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
     * \param typeNaam Het station type in string vorm, wordt omgezet naar StationType
     * \param vorigeStations Map met als key het spoor en als value de vorige station
     * \param volgendeStations Map met als key het spoor en als value de volgende station
     * \post ENSURE(this->properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Station(std::string n, std::string typeNaam, std::map<int, std::string> vorigeStations, std::map<int, std::string> volgendeStations);

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Checkt of het station een spoor bevat.
     * \param spoor Het spoor dat beschouwd moet worden.
     * \return Een bool die weergeeft of het station het spoor bevat.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij aanroep van bevatSpoor.");
     */
    bool bevatSpoor(int spoor) const;

    /**
     * \brief Geef de naam terug van het station.
     * \return De naam van het station.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getNaam.");
     */
    std::string getNaam() const;
    /**
     * \brief Geeft het station type terug
     * \return String "Albatros" of "PCC"
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType.");
     */
    std::string getType() const;

    /**
     * \brief Geef het vorig station op een spoor.
     * \return Het vorig station.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVorige.");
     * \pre REQUIRE(bevatSpoor(spoor), "Station bevat spoor niet bij aanroep van getVorige.");
     */
    std::string getVorige(int spoor) const;

    /**
     * \brief Geef het volgende station op een spoor.
     * \return Het volgende station.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
     * \pre REQUIRE(bevatSpoor(spoor), "Station bevat spoor niet bij aanroep getVolgende.");
     */
    std::string getVolgende(int spoor) const;

    /**
     * \brief Geef de sporen.
     * \return De sporen.
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSporen.");
     */
    std::vector<int> getSporen() const;

    /**
     * \brief Geeft aan of het station een halte is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte.");
     */
    bool isHalte() const;

    /**
     * \brief Geeft aan of het station een metrostation is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(this->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
     */
    bool isMetrostation() const;
};


#endif /* SRC_STATION_H_ */
