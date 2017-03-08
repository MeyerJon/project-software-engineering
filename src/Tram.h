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

class Spoor;
class Station;

class Tram {
private:
    int zitplaatsen;
    int passagiers;
    int snelheid;
    Spoor* spoor;
    Station* beginStation;
    Station* huidigStation;
    Tram* initCheck;
public:
    Tram();
    virtual ~Tram();

    /** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     */
    bool properlyInitialised() const;

    /** \brief Geef de zitplaatsen terug van de tram.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getZitplaatsen.");\n
     */
    int getZitplaatsen() const;

    /** \brief Geef de passagiers terug van de tram.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getPassagiers.");\n
     */
    int getPassagiers() const;

    /** \brief Geef de snelheid terug van de tram.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSnelheid.");\n
     */
    int getSnelheid() const;

    /** \brief Geef het spoor terug.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSpoor.");\n
     */
    Spoor* getSpoor() const;

    /** \brief Geef het beginstation terug.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getBeginStation.");\n
     */
    Station* getBeginStation() const;

    /** \brief Geef het huidig station.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");\n
     */
    Station* getHuidigStation() const;
};

#endif /* SRC_TRAM_H_ */
