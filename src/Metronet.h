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

#include "Station.h"
#include "Tram.h"
#include "Exporter.h"

#include "DesignByContract.h"

class Metronet {
private:
    std::map<std::string, Station*> stations;
    std::map<int, Tram*> trams;
    std::vector<int> sporen;
    Metronet* initCheck;
public:
    Metronet();
    virtual ~Metronet();

    /** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     *  \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised();

    /** \brief Voegt station toe aan metronet.
     *  \param station Het station dat toegevoegd zal worden.
     *
     * REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addStation.");\n
     * REQUIRE(station->properlyInitialised(), "Station was niet geinitialiseerd bij de aanroep van addStation.");\n
     * ENSURE((stations.find(station->getNaam()) != stations.end()), "Station was niet toegevoegd bij de aanroep van addStation.");\n
     */
    void addStation(Station* station);

    /** \brief Voegt tram toe aan metronet.
     *  \param tram De tram die toegevoegd zal worden.
     *
     * REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addTram.");\n
     * REQUIRE(tram->properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van addTram.");\n
     * ENSURE(trams.find(tram->getSpoor()) != trams.end()), "Tram was niet toegevoegd bij de aanroep van addTram.");\n
     */
    void addTram(Tram* tram);

    /** \brief Voegt spoor toe aan metronet.
     *  \param spoor Het spoor dat toegevoegd zal worden.
     *
     * REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van addSpoor.");\n
     * ENSURE(sporen[sporen.size() - 1] == spoor), "Spoor was niet toegevoegd bij de aanroep van addSpoor.");\n
     */
    void addSpoor(int spoor);

    /** \brief Kijkt na of het metronet consistent is.
     *  \param exp De exporter die de output zal behandelen.
     *  \param os De stream waar de output naar gestuurd zal worden.
     *  \return Boolean die aangeeft of het Metronet consistent is.
     *
     * REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij de aanroep van checkConsistent.");\n
     */
    bool checkConsistent(Exporter* exp, std::ostream& os);

    /** \brief Print het hele metronet.
     *
     * @param exp De exporter die gebruikt moet worden
     * @param os De stream waarnaar de output moet gestuurd worden
     *
     * REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij aanroep van printMetronet.");\n
     */
    void printMetronet(Exporter* exp, std::ostream& os);

    /** \brief Behandelt het opstappen en afstappen van passagiers.
     *  \param station Het station waar mensen opstappen en afstappen.
     *
     * REQUIRE(this->properlyInitialised(), "Metronet was niet geinitialiseerd bij aanroep van opStappenAfstappen.");\n
     * REQUIRE((stations.find(station) != stations.end()), "Station bestaat niet in het metronet.");\n
     * REQUIRE(stations[station]->properlyInitialised(), "Station was niet geinitialiseerd bij aanroep van opStappenAfstappen.");\n
     */
     bool opStappenAfStappen(std::string station, Exporter* exp, std::ostream& os);
};

#endif /* SRC_METRONET_H_ */
