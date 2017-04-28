//
// Created by jonathan on 24.04.17.
//

#ifndef PSE_STATISTICS_H
#define PSE_STATISTICS_H

#include <vector>
#include <string>
#include "DesignByContract.h"


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

    bool properlyInitialised() const;

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

    /**
     * \brief Geeft de totale omzet van de tram op dit moment.
     * \pre REQUIRE(this->properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getOmzet.");
     */
    double getOmzet() const;

    void setOmzet(double omzet);

    void setBezettingsgraad(double bezettingsgraad);

    void setAantalGroepen(int aantalGroepen);

    void setAantalPersonen(int aantalPersonen);

    void setAantalFails(int aantalFails);

};


class StatisticsStation {
private:
    int aantalGroepen;
    int aantalPersonen;
    StatisticsStation* initCheck;
public:
    StatisticsStation();

    bool properlyInitialised() const;

    int getAantalGroepen() const;

    int getAantalPersonen() const;

    void setAantalGroepen(int aantalGroepen);

    void setAantalPersonen(int aantalPersonen);
};


class StatisticsMetronet {
private:
    double totaleOmzet;
    double totaleBezettingsgraad;
    int aantalBezettePlaatsen;
    int aantalZitplaatsen;
    int popLijn;
    int nrAlba;
    int nrPCC;
    StatisticsMetronet* initCheck;
public:
    StatisticsMetronet();

    bool properlyInitialised() const;

    double getTotaleOmzet() const;

    double getTotaleBezettingsgraad() const;

    int getAantalBezettePlaatsen() const;

    int getAantalZitplaatsen() const;

    int getPopLijn() const;

    int getNrAlba() const;

    int getNrPCC() const;

    void setTotaleOmzet(double totaleOmzet);

    void setTotaleBezettingsgraad(double totaleBezettingsgraad);

    void setAantalBezettePlaatsen(int aantalBezettePlaatsen);

    void setAantalZitplaatsen(int aantalZitplaatsen);

    void setPopLijn(int popLijn);

    void setNrAlba(int nrAlba);

    void setNrPCC(int nrPCC);

};

#endif //PSE_STATISTICS_H
