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
#include "Exporter.h"


class Parser {
private:
    bool stationsCheck;
    bool tramsCheck;
    Exporter* exp;
    Parser* initCheck;
public:
    Parser();
    Parser(Exporter* exp);

    /** \brief Verwerkt het XML-bestand en zet het metronet op
     *
     * @param metro Het metronet (referentie) dat aangepast moet worden.
     * @param filename De naam van het XML-bestand.
     *
     * REQUIRE(this->properlyInitialised, "De parser was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     * REQUIRE(metro.properlyInitialised, "Het metronet was niet geinitialiseerd bij het aanroepen van setupStations.");\n
     */
    bool setup(Metronet& metro, std::string filename, std::ostream& os);

};

#endif /* SRC_PARSER_H_ */
