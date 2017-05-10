//
// Created by sergio on 24/03/17.
//

#ifndef SOFTENG_PARSER_H
#define SOFTENG_PARSER_H

#include <iostream>
#include "Metronet.h"

/**
 * \brief Parser klasse die het inlezen van XML-bestanden behandelt.
 */
class Parser {
private:
    Exporter* exp;
    Parser* initCheck;
public:
    /**
     * \brief De lege constructor van de klasse Parser.
     * \post ENSURE(properlyInitialised(),
     *              "Parser is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Parser();

    /**
     * \brief De default constructor van de klasse Parser
     * \param exp De exporter die het genereren van de output zal behandelen
     * \post ENSURE(properlyInitialised(),
     *              "Parser is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
    Parser(Exporter* exp);

    /**
     * \brief De overload van de = operator van de klasse Parser
     * \param rhs De parser waaraan this gelijk gezet zal worden
     * \return De huidige parser dat gelijk wordt gezet aan rhs
     * \post ENSURE(properlyInitialised(),
     *              "Parser is niet in de juiste staat geëindigd na aanroep van de copy assignment.");
     */
    Parser& operator=(const Parser& rhs);

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Verwerkt het XML-bestand.
     *  Leest eerst stations met hun sporen in, daarna trams en tenslotte passagiers.
     * \param filename De naam van het XML-bestand.
     * \param os De stream waarnaar de output geschreven wordt (nodig voor de exporter).
     * \pre REQUIRE(properlyInitialised,
     *              "Het metronet was niet geinitialiseerd bij het aanroepen van setupStations.");
     */
    SuccessEnum setup(Metronet& metronet, std::string filename, std::ostream& os);

};


#endif //SOFTENG_PARSER_H
