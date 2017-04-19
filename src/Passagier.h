//
// Created by jonathan on 19.04.17.
//

#ifndef PSE_PASSAGIER_H
#define PSE_PASSAGIER_H

#include <string>
#include "DesignByContract.h"

enum PassagierStatus{
    Wachten,
    Onderweg,
    Aangekomen
};



class Passagier {
    std::string naam;
    std::string beginStation;
    std::string eindStation;
    int hoeveelheid;
    PassagierStatus status;
    Passagier* initCheck;
    /// Maybe later: int curTram
public:

    /**
     * \brief Lege constructor.
     * \post ENSURE(this->properlyInitialised(), "Lege constructor van Passagier is niet in de juiste staat geeindigd.");
     */
    Passagier() {};

    /**
     * \brief Default constructor van Passagier.
     * \param n De naam van de groep passagiers.
     * \param begin Het beginstation van de groep.
     * \param eind Het eindstation van de groep.
     * \param h De hoeveelheid personen in de groep.
     * \post ENSURE(this->properlyInitialised(), "Default constructor van Passagier is niet in de juiste staat geeindigd.");
     */
    Passagier(std::string n, std::string begin, std::string eind, int h);

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
    */
    bool properlyInitialised() const;

    /**
     * \brief Geef de naam van de groep passagiers.
     * \return Naam van de groep.
     * \pre REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getNaam.");
     */
    std::string getNaam() const;

    /**
     * \brief Geef het beginstation van de groep passagiers.
     * \return Beginstation van de groep.
     * \pre REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getBeginStation.");
    */
    std::string getBeginStation() const;

    /**
     * \brief Geef het eindstation van de groep passagiers.
     * \return Eindstation van de groep.
     * \pre REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getEindStation.");
    */
    std::string getEindStation() const;

    /**
     * \brief Geef het aantal personen in de groep passagiers.
     * \return Aantal personen in de groep.
     * \pre REQUIRE(this->properlyInitialised(), "Passagiers was niet geinitialiseerd bij aanroep van getHoeveelheid.");
    */
    int getHoeveelheid() const;

    PassagierStatus getStatus() const;

    /**
     * \brief Update de status van de passagiers.
     * \pre REQUIRE(this->properlyInitialised(), "Passagier was niet geinitialiseerd bij aanroep van setStatus.");
     */
    void updateStatus();

};


#endif //PSE_PASSAGIER_H
