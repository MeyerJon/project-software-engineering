/*
 * Tram.h
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#ifndef SRC_TRAM_H_
#define SRC_TRAM_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include "DesignByContract.h"
#include "Exporter.h"
#include "Passagier.h"

// double ticketPrijs = 2.0;

class Spoor;
class Station;

enum TramType {
    Albatros,
    PCC
};

/**
 * \brief Tram klasse die een TRAM element uit een XML-bestand representeert
 */
class Tram {
private:
    double omzet;
    int zitplaatsen;
    int bezettePlaatsen;
    int snelheid;
    int spoor;
    int voertuignummer;
    std::string beginStation;
    std::string huidigStation;
    TramType type;
    std::vector<Passagier*> passagiers;
    Tram* initCheck;
public:
    /**
     * \brief De lege constructor van de klasse Tram
     * \post ENSURE(this->properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
     */
    Tram();

    /**
     * \brief De default constructor van de klasse Tram
     * \param zit Het totaal aantal zitplaatsen
     * \param snel De snelheid
     * \param sp Het spoornummer
     * \param beginS Het begin station
     * \post ENSURE(this->properlyInitialised(), "Tram is niet in de juiste staat geëindigd na aanroep van de constuctor.");
     */
    Tram(int zit, int snel, int sp, int nr, std::string typeNaam, std::string beginS);

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Geef de zitplaatsen van de tram.
     * \return De zitplaatsen.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getZitplaatsen.");
     */
    int getZitplaatsen() const;

    /**
     * \brief Geef de bezette zitplaatsen van de tram.
     * \return De bezette zitplaatsen.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getBezettePlaatsen.");
    */
    int getBezettePlaatsen() const;

    /**
     * \brief Geef de passagiers terug van de tram.
     * \return De passagiers.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getPassagiers.");
     */
    std::vector<Passagier*> getPassagiers() const;

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
     * \brief Geef het type van de tram.
     * \return Het type van de tram als string.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getType.");
     */
    std::string getType() const;

    /**
     * \brief Geef het voertuignummer van de tram.
     * \return Het voertuignummer van de tram.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getVoertuignummer.");
     */
    int getVoertuignummer() const;

    /**
     * \brief Checkt of de gegeven Passagier op de tram zit.
     * \param pas De passagier die al dan niet op de tram zit.
     * \return Bool die aangeeft of de Passagier op de tram zit.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     * \pre REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van bevatPassagier.");
     */
    bool bevatPassagier(Passagier* pas) const;

    /**
     * \brief Past het huidige station aan
     * \param station Nieuw huidig station
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
     * \post ENSURE((getHuidigStation() == station), "huidigStation is niet aangepast door setHuidigStation.");
     */
    void setHuidigStation(std::string station);

    /**
     * \brief Past het aantal bezette plaatsen aan
     * \param aantalBezettePlaatsen Het nieuwe aantal bezette plaatsen
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanrooep van setBezettePlaatsen.");
     * \post ENSURE((this->getBezettePlaatsen == aantalBezettePlaatsen), "bezettePlaatsen is niet aangepast door setBezettePlaatsen.");
     */
    void setBezettePlaatsen(int aantalBezettePlaatsen);

    /**
     * \brief Voegt een passagier toe en update de status van de passagier
     * \param pas Nieuwe groep passagiers
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \pre REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \post ENSURE(bevatPassagier(pas), "Passagiers niet aangepast bij aanroep van addPassagiers.");
     */
    void addPassagier(Passagier* pas);

    /**
     * \brief Verwijdert een passagier en update de status van de passagier
     * \param pas Te verwijderen Passagier
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \pre REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van addPassagier.");
     * \pre REQUIRE(bevatPassagier(pas), "Passagier zat niet in tram bij de aanroep van removePassagier")
     * \post ENSURE(!bevatPassagier(pas), "Passagiers niet aangepast bij aanroep van addPassagiers.");
    */
    void removePassagier(Passagier* pas);

    /**
     * \brief Geeft aan of de tram een Albatros is
     * \return Boolean die aangeeft of de tram een Albatros is
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isAlbatros.");
     */
    bool isAlbatros() const;

    /**
     * \brief Geeft aan of de tram een PCC is
     * \return Boolean die aangeeft of de tram een PCC is
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van isPCC.");
     */
    bool isPCC() const;

    /**
     * \brief Past het voertuignummer aan.
     * \param n Nieuw voertuignummer
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van setVoertuignummer.");
     * \post ENSURE((getVoertuignummer() == n), "Voertuignummer niet aangepast bij aanroep van setVoertuignummer.");
     */
    void setVoertuignummer(int n);

    /**
     * \brief Verplaatst een tram naar het opgegeven station.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van verplaatsTram.");
     * \post ENSURE((getHuidigStation() == station), "huidigStation is niet correct aangepast.");
     */
    void verplaatsTram(std::string station, Exporter* exp, std::ostream& os);

    /**
     * \brief Emuleert afstappen van passagiers.
     * \param pas Passagier die afstapt.
     * \return boolean Of er meer passagiers afstapten dan mogelijk.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van afstappen.");
     * \pre REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van afstappen.");
     */
    bool afstappen(Passagier* pas);

    /**
     * \brief Emuleert opstappen van passagiers.
     * \param pas Passagier die opstapt.
     * \return boolean Of er meer passagiers opstapten dan mogelijk.
     * \pre REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van opstappen.");
     * \pre REQUIRE(pas->properlyInitialised(), "Passagier was niet geinitialiseerd bij de aanroep van opstappen.");
     */
    bool opstappen(Passagier* pas);
};

#endif /* SRC_TRAM_H_ */
