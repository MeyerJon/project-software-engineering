/*
 * Metronet.h
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#ifndef SRC_METRONET_H_
#define SRC_METRONET_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "tinyxml.h"
#include "tinystr.h"
#include "Station.h"
#include "Tram.h"
#include "Passagier.h"
#include "Exporter.h"
#include "Statistics.h"
#include "DesignByContract.h"

/**
 * \brief Enum gebruikt om te bepalen of bestand correct, partieel of fout is ingelezen.
 */
enum SuccessEnum {
    Success,
    PartialImport,
    BadImport
};

/**
 * \brief Metronet klasse het metronet representeert. Houdt alle trams, stations en passagiers bij.
 */
class Metronet {
private:
    Exporter* exp;
    StatisticsMetronet* stats;
    std::map<std::string, Station*> stations;
    std::map<int, Tram*> trams;
    std::vector<int> sporen;
    std::map<std::string, Passagier*> passagiers;
    Metronet* initCheck;
public:
    /**
     * \brief De lege constructor van de klasse Metronet.
     * \post ENSURE(properlyInitialised(),
     *              "Metronet is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Metronet();

    /**
     * \brief De default constructor van de klasse Metronet.
     * \param exp De exporter die gebruikt zal worden door Metronet om output te genereren.
     * \post ENSURE(properlyInitialised(),
     *              "Metronet is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Metronet(Exporter* exp);

    /**
     * \brief De destructor van de klasse Metronet.
     */
    virtual ~Metronet();

    /**
     * \brief De overload van de = operator van de klasse Metronet.
     * \param rhs Het metronet waaran this gelijk gezet zal worden.
     * \return Het huidig metronet dat gelijk wordt gezet aan rhs.
     */
    Metronet& operator=(const Metronet& rhs);

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised();

    /**
     * \brief Geeft alle stations in het metronet terug.
     * \return Map met stations in het metronet.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getStations.");
     */
     std::map<std::string, Station*> getStations();

    /**
     * \brief Geeft het station met de opgegeven naam.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getStation.");
     */
     Station* getStation(std::string name);

    /**
     * \brief Geeft alle trams in het metronet terug.
     * \return Map met trams in het metronet.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getTrams.");
     */
    std::map<int, Tram*>& getTrams();

    /**
     * \brief Geeft de tram met het opgegeven nummer.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getTram.");
     */
    Tram* getTram(int nummer);

    /**
     * \brief Geeft alle passagiers in het metronet terug.
     * \return Map met alle passagiers in het metronet.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getPassagiers.");
     */
    std::map<std::string, Passagier*>& getPassagiers();

    /**
     * \brief Kijkt na of het metronet de opgegeven tram bevat.
     * \param tram De tram die moet gezocht worden.
     * \return Boolean die aangeeft of het metronet de tram bevat.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatTram.");
     * \pre REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van bevatTram.");
     */
    bool bevatTram(Tram* tram);

    /**
     * \brief Kijkt na of het metronet de opgegeven station bevat.
     * \param tram Het station (pointer) die gezocht moet worden.
     * \return Boolean die aangeeft of het metronet het station bevat.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatStation.");
     * \pre REQUIRE(station->properlyInitialised(),
     *              "Station was niet geinitialiseerd bij de aanroep van bevatStation.");
     */
    bool bevatStation(Station* station);

    /**
     * \brief Kijkt na of het metronet de opgegeven station bevat.
     * \param tram De station (string) die gezocht moet worden.
     * \return Boolean die aangeeft of het metronet het station bevat.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatStation.");
     * \pre REQUIRE(station->properlyInitialised(),
     *              "Station was niet geinitialiseerd bij de aanroep van bevatStation.");
     */
    bool bevatStation(std::string name);

    /**
     * \brief Kijkt na of het metronet het opgegeven spoor bevat.
     * \param tram Het spoor dat gezocht moet worden.
     * \return Boolean die aangeeft of het metronet het spoor bevat.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatSpoor.");
     */
    bool bevatSpoor(int spoor);

    /**
     * \brief Kijkt na of het metronet de opgegeven passagier bevat.
     * \param pas De passagier (pointer) die gezocht moet worden.
     * \return Boolean die aangeeft of het metronet de passagier bevat.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     * \pre REQUIRE(pas->properlyInitialised(),
     *              "Passagier was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     */
    bool bevatPassagier(Passagier* pas);

    /**
     * \brief Kijkt na of het metronet de opgegeven passagier bevat.
     * \param pas De passagier (string) die gezocht moet worden.
     * \return Boolean die aangeeft of het metronet de passagier bevat.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     * \pre REQUIRE(pas->properlyInitialised(),
     *              "Passagier was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     */
    bool bevatPassagier(std::string name);

    /**
     * \brief Voegt station toe aan het metronet.
     * \param station Het station dat toegevoegd zal worden.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addStation.");
     * \post ENSURE(station->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van addStation.");
     * \post ENSURE(bevatStation(station), "Station was niet toegevoegd bij de aanroep van addStation.");
     */
    void addStation(
            std::string naam,
            std::string type,
            std::map<int, std::string> vorigeStations,
            std::map<int, std::string> volgendeStations);

    /**
     * \brief Voegt tram toe aan het metronet.
     * \param tram De tram die toegevoegd zal worden.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addTram.");
     * \pre REQUIRE(bevatStation(beginStation), "Metronet bevat beginstation niet bij de aanroep van addTram");
     * \post ENSURE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van addTram.");
     * \post ENSURE(bevatTram(tram), "Tram was niet toegevoegd bij de aanroep van addTram.");
     */
    void addTram(int zitplaatsen, int snelheid, int spoor, int voertuigNr, std::string type, std::string beginStation);

    /**
     * \brief Voegt spoor toe aan metronet.
     * \param spoor Het spoor dat toegevoegd zal worden.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addSpoor.");
     * \post ENSURE(bevatSpoor(spoor), "Spoor was niet toegevoegd bij de aanroep van addSpoor.");
     */
    void addSpoor(int spoor);

    /**
     * \brief Voegt een passagier toe aan het metronet
     * \param pas De passagier die toegevoegd zal worden
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \post ENSURE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \post ENSURE(bevatPassagier(pas), "Passagier was niet toegevoegd bij de aanroep van addPassagier.");
     */
    void addPassagier(std::string naam, std::string beginStation, std::string eindStation, int hoeveelheid);

    /**
     * \brief Kijkt na of het metronet consistent is. Een metronet is consistent als:
     *  • elk  station  is  verbonden  met  een  voorgaand  en  een  volgend  station  voor  elk spoor
     *  • er bestaan geen trams met een lijn nummer dat niet overeenkomt met een spoor in een station
     *  • er geen sporen zijn waarvoor geen tram bestaat
     *  • het beginstation van een tram een geldig station in het metronet is
     *  • elk spoor maximaal  ́e ́en keer door elk station komt
     *  • een passagier in een ander station afstapt dan het station waar hij/zij opstapt
     *  • elke passagier zijn bestemming kan bereiken
     * \param os De stream waar de output naar gestuurd zal worden.
     * \return Boolean die aangeeft of het Metronet consistent is.
     * \pre REQUIRE(properlyInitialised(),
     *              "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");
     */
    bool checkConsistent(std::ostream& os);

    /**
     * \brief Print het hele metronet.
     * \param os De stream waar de output naar gestuurd moet worden
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van printMetronet.");
     */
    void printMetronet(std::ostream& os);

    /**
     * \brief Geeft een grafische impressie van het hele metronet.
     * \param os De stream waar de output naar gestuurd moet worden
     * \pre REQUIRE(properlyInitialised(),
     *              "Metronet was niet geinitialiseerd bij de aanroep van printMetronetGrafisch.");
     */
    void printMetronetGrafisch(std::ostream& os);

    /**
     * \brief Behandelt het opstappen en afstappen van passagiers.
     *  Gaat eerst na of passagiers op de gegeven tram moeten afstappen en laat ze afstappen indien dit het geval is.
     *  Daarna gaat het na of er passagiers moeten opstappen, zo ja doen ze dat.
     * \param tram De tram waar mensen opstappen en afstappen.
     * \param os De stream waar de output naar gestuurd zal worden.
     * \return Het aantal groepen dat afgestapt is.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van opstappenAfstappen.");
     * \pre REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van opstappenAfstappen.");
     * \pre REQUIRE(bevatTram(tram), "Tram bestaat niet in het metronet.");
     */
    int opstappenAfstappen(Tram* tram, std::ostream& os);

    /**
     * \brief Simuleert het rondrijden van trams.
     *  Overloopt alle trams een per een en laat ze naar het volgende station gaan indien mogelijk
     *  en laat de passagiers op- en afstappen.
     * \param os De stream waar de output naar gestuurd moet worden.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van rondrijden.");
     * \post ENSURE(allePassagiersAangekomen(),
     *              "Niet alle passagiers zijn op hun bestemming aangekomen na rondrijden.");
     */
    void rondrijden(std::ostream& os, bool step=false);

    /**
     * \brief Gaat na of alle passagiers op hun bestemming zijn aangekomen.
     * \return Boolean die aangeeft of alle passagiers zijn aangekomen.
     * \pre REQUIRE(properlyInitialised(),
     *              "Metronet was niet geinitialiseerd bij de aanroep van allePassagiersAangekomen.");
     */
    bool allePassagiersAangekomen();

    /**
     * \brief Kijkt of de gegeven tram verder mag rijden.
     * \return Boolean die aangeeft of een tram mag vertrekken.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van tramMagVertrekken.");
     * \pre REQUIRE(tram->properlyInitialised(),
     *              "Tram was niet geinitialiseerd bij de aanroep van tramMagVertrekken.");
     */
    bool tramMagVertrekken(Tram* tram);

    /**
     * \brief Print de verzamelde gegevens van het metronet.
     * \param os De stream waar de output naar gestuurd moet worden.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van printStatistics.");
     */
    void printStatistics(std::ostream& os);

    /**
     * \brief Reset heel het systeem.
     * \pre REQUIRE(properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van reset.");
     */
     void reset();
};

#endif /* SRC_METRONET_H_ */
