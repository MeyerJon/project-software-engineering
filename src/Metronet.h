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
 * \brief Enum gebruikt om te bepalen of bestand correct, partieel of fout is ingelezen
 */
enum SuccessEnum {
    Success,
    PartialImport,
    BadImport
};

/**
 * \brief Metronet klasse het metronet representeert. Houdt alle trams, stations & passagiers bij
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
     * \brief De lege constructor van de klasse Metronet
     * \post ENSURE(this->properlyInitialised(), "Metronet is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Metronet();

    /**
     * \brief De default constructor van de klasse Metronet
     * \param exp De exporter die gebruikt zal worden door Metronet om output te genereren
     * \post ENSURE(this->properlyInitialised(), "Metronet is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Metronet(Exporter* exp);

    /**
     * \brief De destructor van de klasse Metronet
     */
    virtual ~Metronet();

    /**
     * \brief De overload van de = operator van de klasse Metronet
     * \param rhs Het metronet waaran this gelijk gezet zal worden
     * \return Het huidig metronet dat gelijk wordt gezet aan rhs
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
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getStations.");
     */
     std::map<std::string, Station*> getStations();

    /**
     * \brief Geeft alle trams in het metronet terug.
     * \return Map met trams in het metronet.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getTrams.");
     */
    std::map<int, Tram*>& getTrams();

    /**
     * \brief Geeft alle passagiers in het metronet terug.
     * \return Map met alle passagiers in het metronet.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van getPassagiers.");
     */
    std::map<std::string, Passagier*>& getPassagiers();

    /**
     * \brief Kijkt na of het metronet de opgegeven tram bevat.
     * \param tram De tram die moet gezocht worden.
     * \return Boolean die aangeeft of het metronet de tram bevat.
     * \pre REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij aanroep van bevatTram.");
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatTram.");
     */
    bool bevatTram(Tram* tram);

    /**
     * \brief Kijkt na of het metronet de opgegeven station bevat.
     * \param tram De tram die moet gezocht worden.
     * \return Boolean die aangeeft of het metronet de tram bevat.
     * \pre REQUIRE(station->properlyInitialised(), "Station was niet geinitialiseerd bij aanroep van bevatStation.");
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatStation.");
     * \pre REQUIRE(station->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van bevatStation.");
     */
    bool bevatStation(Station* station);

    /**
     * \brief Kijkt na of het metronet de opgegeven spoor bevat.
     * \param tram Het spoor dat moet gezocht worden.
     * \return Boolean die aangeeft of het metronet de tram bevat.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatSpoor.");
     */
    bool bevatSpoor(int spoor);

    /**
     * \brief Kijkt na of het metronet de opgegeven passagier bevat.
     * \param pas De passagier die gezocht moet worden.
     * \return Boolean die aangeeft of het metronet de passagier bevat.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     * \pre REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     */
    bool bevatPassagier(Passagier* pas);

    /**
     * \brief Voegt station toe aan metronet.
     * \param station Het station dat toegevoegd zal worden.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addStation.");
     * \pre REQUIRE(station->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van addStation.");
     * \post ENSURE(bevatStation(station), "Station was niet toegevoegd bij de aanroep van addStation.");
     */
    void addStation(
            std::string naam,
            std::string type,
            std::map<int, std::string> vorigeStations,
            std::map<int, std::string> volgendeStations);

    /**
     * \brief Voegt tram toe aan metronet.
     * \param tram De tram die toegevoegd zal worden.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addTram.");
     * \pre REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van addTram.");
     * \post ENSURE(bevatTram(tram), "Tram was niet toegevoegd bij de aanroep van addTram.");
     */
    void addTram(int zitplaatsen, int snelheid, int spoor, int voertuigNr, std::string type, std::string beginStation);

    /**
     * \brief Voegt spoor toe aan metronet.
     * \param spoor Het spoor dat toegevoegd zal worden.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addSpoor.");
     * \post ENSURE(bevatSpoor(spoor), "Spoor was niet toegevoegd bij de aanroep van addSpoor.");
     */
    void addSpoor(int spoor);

    /**
     * \brief Voegt een passagier toe aan het metronet
     * \param pas De passagier die toegevoegd zal worden
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \pre REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \post ENSURE(bevatPassagier(pas), "Passagier was niet toegevoegd bij aanroep van addPassagier.");
     */
    void addPassagier(std::string naam, std::string beginStation, std::string eindStation, int hoeveelheid);

    /**
     * \brief Kijkt na of het metronet consistent is.
     * \param os De stream waar de output naar gestuurd zal worden.
     * \return Boolean die aangeeft of het Metronet consistent is.
     * \pre REQUIRE(this->properlyInitialised(),
     *              "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");
     */
    bool checkConsistent(std::ostream& os);

    /**
     * \brief Print het hele metronet.
     * \param os De stream waar de output naar gestuurd moet worden
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij aanroep van printMetronet.");
     */
    void printMetronet(std::ostream& os);

    /**
     * \brief Geeft een grafische impressie van het hele metronet.
     * \param os De stream waar de output naar gestuurd moet worden
     * \pre REQUIRE(this->properlyInitialised(),
     *              "Metronet was niet geinitialiseerd bij aanroep van printMetronetGrafisch.");
     */
    void printMetronetGrafisch(std::ostream& os);

    /**
     * \brief Behandelt het opstappen en afstappen van passagiers.
     * \param tram De tram waar mensen opstappen en afstappen.
     * \param os De stream waar de output naar gestuurd zal worden.
     * \pre REQUIRE(this->properlyInitialised(),
     *              "Metronet was niet geinitialiseerd bij aanroep van opstappenAfstappen.");
     * \pre REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij aanroep van opstappenAfstappen.");
     * \pre REQUIRE(trams.find(tram->getVoertuignummer()) != trams.end(), "Tram bestaat niet in het metronet.");
     */
    int opstappenAfstappen(Tram* tram, std::ostream& os);

    /**
     * \brief Emuleert het rondrijden van trams
     * \param os De stream waar de output naar gestuurd moet worden
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij aanroep van rondrijden.");
     * \post (voor elke tram) ENSURE(t->getHuidigStation() == t->getBeginStation(),
     *                               "Tram niet geëindigd in beginstation na rondrijden.");
     */
    void rondrijden(std::ostream& os);

    /**
     * \brief Kijkt of de gegeven tram verder mag rijden
     * \return Boolean die aangeeft of een tram mag vertrekken
     * \pre REQUIRE(this->properlyInitialised(),
     *              "Metronet was niet geinitialiseerd bij aanroep van tramMagVertrekken.");
     * \pre REQUIRE(tram->properlyInitialised(),
     *              "Tram was niet geinitialiseerd bij het aanroepen van tramMagVertrekken.");
     */
    bool tramMagVertrekken(Tram* tram);

    /**
     * \brief (Al dan niet tijdelijk) Print de verzamelde gegevens van het metronet
     */
    void printStatistics(std::ostream& os);

    /**
     * \brief Reset heel het systeem.
     * \param tram De tram waarvoor gekeken wordt of vertrokken mag worden.
     * \pre REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij aanroep van reset.");
     */
     void reset();
};

#endif /* SRC_METRONET_H_ */
