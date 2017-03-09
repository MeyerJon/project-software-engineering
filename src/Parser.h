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
     * @param file De naam van het XML-bestand.
     *
     * REQUIRE(this->properlyInitialised, "De parser was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * REQUIRE(metro.properlyInitialised, "Het metronet was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * ENSURE(stationsCheck, "Stations niet correct ingelezen.");\n
     */
    void setupStations(Metronet& metro, std::string file);

    /** \brief
     *
     * @param metro
     * @param file
     */
    void setupTrams(Metronet& metro, std::string file);

    /** \brief
     *
     * @param metro
     * @param file
     */
    void setup(Metronet& metro, std::string file);

};

#endif /* SRC_PARSER_H_ */
