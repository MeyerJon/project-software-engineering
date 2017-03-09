/*
 * Parser.h
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <iostream>
#include "DesignByContract.h"
#include "Metronet.h"
#include "tinyxml.h"
#include "tinystr.h"


class Parser {
private:
    bool stationsCheck;
    bool tramsCheck;
    Parser* initCheck;
public:
    Parser();
    virtual ~Parser();

    /** \brief Leest alle stations uit een XML-bestand en voegt ze toe aan het metronet.
     *
     * @param metro Het metronet (referentie) dat aangepast moet worden.
     * @param filename De naam van het XML-bestand.
     *
     * REQUIRE(this->properlyInitialised, "De parser was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * REQUIRE(metro.properlyInitialised, "Het metronet was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * ENSURE(stationsCheck, "Stations niet correct ingelezen.");\n
     */
    void setupStations(Metronet& metro, std::string filename);

    /** \brief Leest alle trams uit een XML-bestand en voegt ze toe aan het metronet.
     *
     * @param metro Het metronet (referentie) dat aangepast moet worden.
     * @param filename De naam van het XML-bestand.
     *
     * REQUIRE(this->properlyInitialised, "De parser was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * REQUIRE(metro.properlyInitialised, "Het metronet was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * REQUIRE(stationsCheck, "Stations niet correct ingelezen bij aanroep van setupStations.");\n
     * ENSURE(tramsCheck, "Stations niet correct ingelezen.");\n
     */
    void setupTrams(Metronet& metro, std::string filename);

    /** \brief Verwerkt het XML-bestand en zet het metronet op
     *
     * @param metro Het metronet (referentie) dat aangepast moet worden.
     * @param filename De naam van het XML-bestand.
     *
     * REQUIRE(this->properlyInitialised, "De parser was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * REQUIRE(metro.properlyInitialised, "Het metronet was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * REQUIRE(stationsCheck, "Stations niet correct ingelezen bij aanroep van setup.");\n
     * REQUIRE(tramsCheck, "Trams niet correct ingelezen bij aanroep van setup");\n
     */
    void setup(Metronet& metro, std::string filename);

};

#endif /* SRC_PARSER_H_ */
