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
    int aantalZetels;
    double omzet;
    int aantalGroepen;
    int aantalPersonen;
    int aantalFails;
    std::vector<double> bezettingsgraden;
    double bezettingsgraad;
    StatisticsTram* initCheck;
public:
    /**
     * \brief De lege constructor voor StatisticsTram
     * \post ENSURE(properlyInitialised(), "StatisticsTram is niet in de juiste staat geëindigd na aanroep van de constructor.");
     */
     StatisticsTram(int zetels);

    bool properlyInitialised() const;

    /**
     * \brief Geeft de totale bezettingsgraad van de tram op dit moment.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getBezettingsgraad.");
     */
    double getBezettingsgraad() const;

    /**
     * \brief Geeft het aantal groepen dat deze tram gebruikt hebben.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getAantalGroepen.");
     */
    int getAantalGroepen() const;

    /**
     * \brief Geeft het aantal personen dat deze tram gebruikt hebben.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getAantalPersonen.");
     */
    int getAantalPersonen() const;

    /**
     * \brief Geeft het aantal keren dat een groep niet kon opstappen.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getAantalFails.");
     */
    int getAantalFails() const;

    /**
     * \brief Geeft de totale omzet van de tram op dit moment.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van getOmzet.");
     */
    double getOmzet() const;

    /**
     * \brief Past de huidige omzet van de tram aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van setOmzet.");
     * \post ENSURE(getOmzet() == omzet, "Omzet niet correct aangepast na aanroep van setOmzet.");
     */
    void setOmzet(double omzet);

    /**
     * \brief Past de huidige bezettingsgraad van de tram aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van setBezettingsgraad.");
     * ENSURE(getBezettingsGraad() == bezettingsgraad, "Bezettingsgraad niet correct aangepast na aanroep van setBezettingsgraad.");
     */
    void setBezettingsgraad(double bezettingsgraad);

    /**
     * \brief Past het huidige aantal groepen van de tram aan (totaal aantal dat van de tram gebruikt heeft gemaakt).
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van setAantalGroepen.");
     * ENSURE(getAantalGroepen() == aantalGroepen, "Aantal groepen niet correct aangepast na aanroep van setAantalGroepen.");
     */
    void setAantalGroepen(int aantalGroepen);

    /**
     * \brief Past het huidig aantal personen van de tram aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van setAantalPersonen.");
     * ENSURE(getAantalPersonen() == aantalPersonen, "Aantal personen niet correct aangepast na aanroep van setAantalPersonen.");
     */
    void setAantalPersonen(int aantalPersonen);

    /**
     * \brief Past huidig aantal keer dat passagiers niet konden opstappen aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsTram was niet geinitialiseerd bij aanroep van setAantalFails.");
     * \post ENSURE(getAantalFails() == aantalFails, "Aantal fails niet correct aangepast na aanroep van setAantalfails.");
     */
    void setAantalFails(int aantalFails);

    /**
     * \brief Herberekent de gemiddelde bezettingsgraad van de tram
     * \pre REQUIRE(properlyInitialised(), "Tram was niet geinitialiseerd bij de aanroep van updateGemiddeldeBezettingsgraad.");
     */
    void updateGemiddeldeBezettingsgraad(int huidigePassagiers);

};


class StatisticsStation {
private:
    int aantalGroepen;
    int aantalPersonen;
    StatisticsStation* initCheck;
public:
    /**
     * \brief De lege constructor van StatisticsStation.
     * \post ENSURE(properlyInitialised(), "Lege constructor van StatisticsStation is niet in de juiste staat geïndigd.");
     */
    StatisticsStation();

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Geeft het aantal groepen dat al gebruik heeft gemaakt van dit station.
     * \pre REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij aanroep van getAantalGroepen.");
     */
    int getAantalGroepen() const;

    /**
     * \brief Geeft het aantal personen dat al gebruik heeft gemaakt van dit station.
     * \pre REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij aanroep van getAantalPersonen.");
     */
    int getAantalPersonen() const;

    /**
     * \brief Past het aantal groepen dat al gebruik heeft gemaakt van dit station aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij aanroep van setAantalGroepen.");
     * \post ENSURE(getAantalGroepen() == aantalGroepen, "Aantal groepen niet correct aangepast bij aanroep van setAantalGroepen.");
     */
    void setAantalGroepen(int aantalGroepen);

    /**
     * \brief Past het aantal personen dat al gebruik heeft gemaakt van dit station aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsStation was niet geinitialiseerd bij aanroep van setAantalPersonen.");
     * \post ENSURE(getAantalPersonen() == aantalPersonen, "Aantal groepen niet correct aangepast bij aanroep van setAantalPersonen.");
     */
    void setAantalPersonen(int aantalPersonen);
};


class StatisticsMetronet {
private:
    double totaleOmzet;
    double totaleBezettingsgraad;
    int totaalAantalPersonen;
    int totaalAantalGroepen;
    int aantalBezettePlaatsen;
    int aantalZitplaatsen;
    int popLijn;
    int nrAlba;
    int nrPCC;
    StatisticsMetronet* initCheck;
public:
    /**
     * \brief De lege constructor van StatisticsStation.
     * \post ENSURE(properlyInitialised(), "Lege constructor van StatisticsMetronet is niet in de juiste staat geïndigd.");
     */
    StatisticsMetronet();

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    bool properlyInitialised() const;

    /**
     * \brief Geeft de totale omzet van het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getTotaleOmzet.");
     */
    double getTotaleOmzet() const;

    /**
     * \brief Geeft de (algemene) gemiddelde bezettingsgraad van het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getTotaleBezetingsgraad.");
     */
    double getTotaleBezettingsgraad() const;

    /**
     * \brief Geeft het totaal aantal bezette plaatsen in het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getTotaleBezettePlaatsen.");
     */
    int getAantalBezettePlaatsen() const;

    /**
     * \brief Geeft het totaal aantal zitplaatsen in het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getAantalZitplaatsen.");
     */
    int getAantalZitplaatsen() const;

    /**
     * \brief Geeft de meest populaire lijn van het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getPopLijn.");
     */
    int getPopLijn() const;

    /**
     * \brief Geeft het aantal albatrossen in het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getNrAlba.");
     */
    int getNrAlba() const;

    /**
     * \brief Geeft het aantal PCC's in het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getNrPCC.");
     */
    int getNrPCC() const;

    /**
     * \brief Geeft het totaal aantal personen in het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getTotaalAantalPersonen.");
     */
    int getTotaalAantalPersonen() const;

    /**
     * \brief Geeft het totaal aantal groepen in het metronet.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van getTotaalAantalGroepen.");
     */
    int getTotaalAantalGroepen() const;

    /**
     * \brief Past de totale omzet van het metronet aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van setTotaleOmzet.");
     * \post ENSURE(getTotaleOmzet() == totaleOmzet, "Totale omzet niet correct aangepast bij aanroep van setTotaleOmzet.");
     */
    void setTotaleOmzet(double totaleOmzet);

    /**
     * \brief Past de totale bezettingsgraad van het metronet aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van setTotaleBezettingsgraad.");
     * \post ENSURE(getTotaleBezettingsgraad() == totaleBezettingsgraad, "Totale omzet niet correct aangepast bij aanroep van setTotaleBezettingsgraad.");
     */
    void setTotaleBezettingsgraad(double totaleBezettingsgraad);

    /**
     * \brief Past de totale omzet van het metronet aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van setAantalBezettePlaatsen.");
     * \post ENSURE(getAantalBezettePlaatsen() == aantalBezettePlaatsen, "Totale omzet niet correct aangepast bij aanroep van setAantalBezettePlaatsen.");
     */
    void setAantalBezettePlaatsen(int aantalBezettePlaatsen);

    /**
     * \brief Past het aantal zitplaatsen in het metronet aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van setAantalZitplaatsen.");
     * \post ENSURE(getAantalZitplaatsen() == aantalZitplaatsen, "Totale omzet niet correct aangepast bij aanroep van setAantalBezettePlatsen.");
     */
    void setAantalZitplaatsen(int aantalZitplaatsen);

    /**
     * \brief Past de populairste lijn aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet niet geinitialiseerd bij aanroep van setPopLijn.");
     * \post ENSURE(getPopLijn == popLijn, "Populairste lijn niet correct aangepast bij aanroep van setPopLijn.");
     */
    void setPopLijn(int popLijn);

    /**
     * \brief Past het nummer van albatros trams aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij aanroep van setNrAlba.");
     * \post ENSURE(getNrAlba == nrAlba, "Nummer van albatros trams niet correct aangepast bij aanroep van setNrAlba.");
     */
    void setNrAlba(int nrAlba);

    /**
     * \brief Past het nummer van pcc trams aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij aanroep van setNrPCC.");
     * \post ENSURE(getNrPCC == nrPCC, "Nummer van pcc trams niet correct aangepast bij aanroep van setNrPCC.");
     */
    void setNrPCC(int nrPCC);

    /**
     * \brief Past het totaal aantal personen aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij aanroep van setTotaalAantalPersonen.");
     * \post ENSURE(getTotaalAantalPersonen == aantal, "Totaal aantal personen niet correct aangepast bij aanroep van setTotaalAantalPersonen.");
     */
    void setTotaalAantalPersonen(int aantal);

    /**
     * \brief Past het totaal aantal groepen aan.
     * \pre REQUIRE(properlyInitialised(), "StatisticsMetronet was niet geinitialiseerd bij aanroep van setTotaalAantalGroepen.");
     * \post ENSURE(getTotaalAantalGroepen == aantal, "Totaal aantal groepen niet correct aangepast bij aanroep van setTotaalAantalGroepen.");
     */
    void setTotaalAantalGroepen(int aantal);

};

#endif //PSE_STATISTICS_H
