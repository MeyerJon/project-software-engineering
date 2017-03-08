/*
 * Tram.h
 *
 *  Created on: 8 Mar 2017
 *      Author: sergio
 */

#ifndef SRC_TRAM_H_
#define SRC_TRAM_H_

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
public:
	Tram();
	virtual ~Tram();

	/** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     */
    bool properlyInitialised();

    /** \brief Geef de zitplaatsen terug van de tram.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getZitplaatsen.");
     */
    int getZitplaatsen() const;

    /** \brief Geef de passagiers terug van de tram.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getPassagiers.");
     */
    int getPassagiers() const;

    /** \brief Geef de snelheid terug van de tram.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSnelheid.");
     */
    int getSnelheid() const;

    /** \brief Geef het spoor terug.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getSpoor.");
     */
    Spoor* getSpoor() const;


    /** \brief Geef het beginstation terug.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getBeginStation.");
     */
    Station* getBeginStation() const;

    /** \brief Geef het huidig station.
     *
     * REQUIRE(this->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van getHuidigStation.");
     */
    Station* getHuidigStation() const;
};

#endif /* SRC_TRAM_H_ */
