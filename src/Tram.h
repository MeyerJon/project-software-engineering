/*
 * Tram.h
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#ifndef SRC_TRAM_H_
#define SRC_TRAM_H_

#include <iostream>
#include "DesignByContract.h"
#include "Exporter.h"

class Spoor;
class Station;

/**
 * \brief Tram klasse die een TRAM element uit een XML-bestand representeert
 */
class Tram {
private:
    int zitplaatsen;
    int passagiers;
    int snelheid;
    int spoor;
    std::string beginStation;
    std::string huidigStation;
    Tram* initCheck;
public:
    /**
     * \brief De lege constructor van de klasse Tram
     */
    Tram();

    /**
     * \brief De default constructor van de klasse Tram
     * \param zit Het totaal aantal zitplaatsen
     * \param snel De snelheid
     * \param sp Het spoornummer
     * \param beginS Het begin station
     */
    Tram(int zit, int snel, int sp, std::string beginS);

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Geef de zitplaatsen terug van de tram.
     * \return De zitplaatsen.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getZitplaatsen.");
     */
    int getZitplaatsen() const;

    /**
     * \brief Geef de passagiers terug van de tram.
     * \return De passagiers.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getPassagiers.");
     */
    int getPassagiers() const;

    /**
     * \brief Geef de snelheid terug van de tram.
     * \return De snelheid.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSnelheid.");
     */
    int getSnelheid() const;

    /**
     * \brief Geef het spoor terug.
     * \return Het spoor.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSpoor.");
     */
    int getSpoor() const;

    /**
     * \brief Geef het beginstation terug.
     * \return Het beginstation.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getBeginStation.");
     */
    std::string getBeginStation() const;

    /**
     * \brief Geef het huidig station.
     * \return Het huidig station.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
     */
    std::string getHuidigStation() const;

    /**
     * \brief Past het huidige station aan
     * \param station Nieuw huidig station
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
     * \post ENSURE((huidigStation == station), "huidigStation is niet aangepast door setHuidigStation.");
     */
    void setHuidigStation(std::string station);

    /**
     * \brief Past het aantal passagiers aan
     * \param pas Positief nieuw aantal passagiers
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van setPassagiers.");
     * \pre REQUIRE(passagiers >= 0, "Aantal passagiers moet positief zijn.");
     * \post ENSURE((passagiers == pas), "Aantal passagiers niet aangepast bij aanroep van setPassagiers.");
     */
    void setPassagiers(int pas);


    /**
     * \brief Verplaatst een tram naar het opgegeven station.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van verplaatsTram.");
     * \post ENSURE((huidigStation == station), "huidigStation is niet correct aangepast.");
     */
    void verplaatsTram(std::string station, Exporter* exp, std::ostream& os);

    /**
     * \brief Emuleert afstappen van passagiers. (Nieuw huidig aantal = huidig aantal - afstappende passagiers)
     * \param afstappen Aantal passagiers dat afstapt.
     * \return boolean Of er meer passagiers afstapten dan mogelijk.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van afstappen.");
     * \pre REQUIRE(afstappen >= 0, "Afstappen kan geen negatieve waarde hebben bij aanroep van afstappen.");
     */
    bool afstappen(int afstappen);

    /**
     * \brief Emuleert opstappen van passagiers. (Nieuw huidig aantal = huidig aantal + opstappende passagiers)
     * \param opstappen Aantal passagiers dat opstapt.
     * \return boolean Of er meer passigiers opstapten dan mogelijk.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van opstappen.");
     * \pre REQUIRE(opstappen >= 0, "Opstappen kan geen negatieve waarde hebben bij aanroep van opstappen.");
     */
    bool opstappen(int opstappen);
};

#endif /* SRC_TRAM_H_ */
