/*
 * Exporter.h
 *
 *  Created on: 8 Mar 2017
 *      Author: sergio
 */

#ifndef SRC_EXPORTER_H_
#define SRC_EXPORTER_H_

#include <iostream>
#include "DesignByContract.h"

class Exporter {
private:
    std::ostream os;
    bool documentStarted;
    Exporter* initCheck;
public:
    Exporter();

    Exporter(std::ostream& os);

    /** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     *  \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    virtual bool properlyInitialised() const;

    /** \brief Stuur de output string naar de output stream.
     *  \param output De string die naar de output gestuurd moet worden.
     *
     * REQUIRE(this->properlyInitialised(), "Exporter was niet geinitialiseerd bij de aanroep van write.");\n
     */
    virtual void write(std::string& output);

    /** \brief Valideer de output formaat.
     *
     * REQUIRE(this->properlyInitialised(), "Exporter was niet geinitialiseerd bij de aanroep van validate,");\n
     * ENSURE((documentStarted == true), "Document werd niet aangemaakt bij de aanroep van validate.");\n
     */
    virtual void validate();
};

class ExporterCLI : public Exporter {

};

class ExporterTXT : public Exporter {

};

class ExporterHTML : public Exporter {
public:
    virtual void write(std::string& output);

    virtual void validate();

    /** \brief Valideer de HTML header.
     *
     * REQUIRE(this->properlyInitialised(), "ExporterHTML was niet geinitialiseerd bij het aanroepen van validateHead.");\n
     * REQUIRE(documentStarted == false), "Document was al aangemaakt voor de aanroep van validateHead.");\n
     * ENSURE((documentStarted == true), "Document werd niet aangemaakt bij de aanroep van validateHead.");\n
     */
    void validateHead();

    /** \brief Valideer de HTML tail.
     *
     * REQUIRE(this->properlyInitialised(), "ExporterHTML was niet geinitialiseerd bij het aanroepen van validateTail.");\n
     * REQUIRE((documentStarted == true), "Document was nog niet aangemaakt bij de aanroep van validateTail.");
     * ENSURE((documentStarted == true), "Document werd niet aangemaakt bij de aanroep van validateTail.");.\n
     */
    void validateTail();
};

#endif /* SRC_EXPORTER_H_ */
