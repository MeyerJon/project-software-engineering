//
// Created by jonathan on 24.04.17.
//

#ifndef PSE_STATISTICS_H
#define PSE_STATISTICS_H

#include <vector>
#include <string>


class StatisticsTram {
private:
    double omzet;
    double bezettingsgraad;
    int aantalGroepen;
    int aantalPersonen;
    int aantalFails;
    StatisticsTram* initCheck;
public:
    /**
     * \brief De lege constructor voor StatisticsTram
     * \post ENSURE(this->properlyInitialised(), "StatisticsTram is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
     StatisticsTram();

    /**
     * \brief Geeft de totale omzet van de tram op dit moment.
     * \pre REQUIRE(this->properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getOmzet.");
     */
    double getOmzet() const;

    /**
     * \brief Geeft de totale bezettingsgraad van de tram op dit moment.
     * \pre REQUIRE(this->properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getBezettingsgraad.");
     */
    double getBezettingsgraad() const;

    /**
     * \brief Geeft het aantal groepen dat deze tram gebruikt hebben.
     * \pre REQUIRE(this->properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getAantalGroepen.");
     */
    int getAantalGroepen() const;

    /**
     * \brief Geeft het aantal personen dat deze tram gebruikt hebben.
     * \pre REQUIRE(this->properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getAantalPersonen.");
     */

    int getAantalPersonen() const;

    /**
     * \brief Geeft het aantal keren dat een groep niet kon opstappen.
     * \pre REQUIRE(this->properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getAantalFails.");
     */

    int getAantalFails() const;

};


class StatisticsStation {
    int aantalGroepen;
    int aantalPersonen;
};


class StatisticsMetronet {
    double totaleOmzet;
    double totaleBezettingsgraad;
    int popLijn;
    int nrAlba;
    int nrPCC;
};



#endif //PSE_STATISTICS_H
