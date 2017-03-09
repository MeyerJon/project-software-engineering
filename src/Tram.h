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
    Tram();
    Tram(int zit, int snel, int sp, std::string beginS);

    /** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     *  \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /** \brief Geef de zitplaatsen terug van de tram.
     *  \return De zitplaatsen.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getZitplaatsen.");\n
     */
    int getZitplaatsen() const;

    /** \brief Geef de passagiers terug van de tram.
     *  \return De passagiers.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getPassagiers.");\n
     */
    int getPassagiers() const;

    /** \brief Geef de snelheid terug van de tram.
     *  \return De snelheid.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSnelheid.");\n
     */
    int getSnelheid() const;

    /** \brief Geef het spoor terug.
     *  \return Het spoor.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSpoor.");\n
     */
    int getSpoor() const;

    /** \brief Geef het beginstation terug.
     *  \return Het beginstation.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getBeginStation.");\n
     */
    std::string getBeginStation() const;

    /** \brief Geef het huidig station.
     *  \return Het huidig station.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");\n
     */
    std::string getHuidigStation() const;

    /** \brief Verplaatst een tram naar het opgegeven station.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van verplaatsTram.");\n
     * ENSURE((huidigStation == station), "huidigStation is niet correct aangepast.");\n
     */
    void verplaatsTram(std::string station, Exporter* exp, std::ostream& os);
};

#endif /* SRC_TRAM_H_ */
