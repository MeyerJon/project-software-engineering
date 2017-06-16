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
#include "Statistics.h"

class Tram;


struct stationVerbinding{
    std::string vorige;
    std::string volgende;
};

/**
 * \brief Station klasse die een STATION element uit een XML-bestand representeert
 */
class Station {
protected:
    std::string naam;
    StatisticsStation* stats;
    std::map<int, stationVerbinding> verbindingen;
    std::map<int, bool> trams;
    Station* initCheck;

public:
    /**
     * \brief De lege constructor van de klasse Station
     * \post ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Station();

    /**
     * \brief De default constructor van de klasse Station
     * \param n De naam van het station
     * \param typeNaam Het station type in string vorm, wordt omgezet naar StationType
     * \param vorigeStations Map met als key het spoor en als value de vorige station
     * \param volgendeStations Map met als key het spoor en als value de volgende station
     * \post ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Station(std::string n, std::map<int, std::string> vorigeStations, std::map<int, std::string> volgendeStations, StatisticsStation* statistics);

    /**
     * \brief Dit is de destructor van Station.
     */
    ~Station();

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Checkt of het station een spoor bevat.
     * \param spoor Het spoor dat beschouwd moet worden.
     * \return Een bool die weergeeft of het station het spoor bevat.
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij aanroep van bevatSpoor.");
     */
    bool bevatSpoor(int spoor) const;

    /**
     * \brief Geef de naam terug van het station.
     * \return De naam van het station.
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getNaam.");
     */
    std::string getNaam() const;

    /**
     * \brief Geeft het station type terug
     * \return String "Albatros" of "PCC"
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType.");
     */
    virtual std::string getType() const;

    /**
     * \brief Geef het vorig station op een spoor.
     * \param spoor Het te beschouwen spoor.
     * \return Het vorig station.
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVorige.");
     * \pre REQUIRE(bevatSpoor(spoor), "Station bevat spoor niet bij aanroep van getVorige.");
     */
    std::string getVorige(int spoor) const;

    /**
     * \brief Geef het volgende station op een spoor.
     * \return Het volgende station.
     * \param spoor Het te beschouwen spoor.
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getVolgende.");
     * \pre REQUIRE(bevatSpoor(spoor), "Station bevat spoor niet bij aanroep getVolgende.");
     */
    std::string getVolgende(int spoor) const;

    /**
     * \brief Geef de sporen.
     * \return De sporen.
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getSporen.");
     */
    std::vector<int> getSporen() const;

    /**
     * \brief Geeft de extra gegevens van het station
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getStatistics.");
     */
     StatisticsStation* getStatistics();

    /**
     * \brief Geeft aan of het station een halte is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte.");
     */
    virtual bool isHalte() const;

    /**
     * \brief Geeft aan of het station een metrostation is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
     */
    virtual bool isMetrostation() const;

    /**
     * \brief Geeft aan of er zich op het gegeven spoor een tram bevindt.
     * \param spoor Het gegeven spoor.
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van spoorBezet.");
     * \pre REQUIRE(bevatSpoor(spoor), "Station bevat het gegeven spoor niet bij aanroep van spoorBezet.");
     */
    bool spoorBezet(int spoor) const;

    /**
     * \brief Bezet het spoor met de gegeven tram.
     * \param spoor Het spoor waarop de tram gezet moet worden
     * \param isTramHier De boolean die zegt of de tram aanwezig is op het spoor.
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van bezetSpoor.");
     * \pre REQUIRE(bevatSpoor(spoor), "Station bevat het gegeven spoor niet bij aanroep van bezetSpoor.");
     * \post ENSURE(spoorBezet(spoor) == isTramHier, "Spoor was niet correct bezet na aanroep van bezetSpoor");
     */
    void bezetSpoor(int spoor, bool isTramHier);

};

class Metrostation : public Station {
public:
    /**
     * \brief De default constructor van de klasse Metrostation
     * \param n De naam van het station
     * \param typeNaam Het station type in string vorm, wordt omgezet naar StationType
     * \param vorigeStations Map met als key het spoor en als value de vorige station
     * \param volgendeStations Map met als key het spoor en als value de volgende station
     * \post ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Metrostation(std::string n, std::map<int, std::string> vorigeStations, std::map<int, std::string> volgendeStations, StatisticsStation* statistics);

    /**
     * \brief Geeft aan of het station een halte is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte.");
     */
    virtual bool isHalte() const;

    /**
     * \brief Geeft aan of het station een metrostation is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
     */
    virtual bool isMetrostation() const;

    /**
     * \brief Geeft het station type terug
     * \return String "Albatros" of "PCC"
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType.");
     */
    virtual std::string getType() const;
};

class Halte : public Station {
public:
    /**
     * \brief De default constructor van de klasse Halte
     * \param n De naam van het station
     * \param typeNaam Het station type in string vorm, wordt omgezet naar StationType
     * \param vorigeStations Map met als key het spoor en als value de vorige station
     * \param volgendeStations Map met als key het spoor en als value de volgende station
     * \post ENSURE(properlyInitialised(), "Station is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Halte(std::string n, std::map<int, std::string> vorigeStations, std::map<int, std::string> volgendeStations, StatisticsStation* statistics);

    /**
     * \brief Geeft aan of het station een halte is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isHalte.");
     */
    virtual bool isHalte() const;

    /**
     * \brief Geeft aan of het station een metrostation is
     * \return Een bool die aangeeft of het station een halte is
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van isMetrostation.");
     */
    virtual bool isMetrostation() const;

    /**
     * \brief Geeft het station type terug
     * \return String "Albatros" of "PCC"
     * \pre REQUIRE(properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van getType.");
     */
    virtual std::string getType() const;
};

#endif /* SRC_STATION_H_ */
