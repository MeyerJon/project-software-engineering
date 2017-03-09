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
protected:
    bool documentStarted;
    Exporter* initCheck;
public:
    Exporter();

    /** \brief Kijk na of de constructor in de juiste staat geeindigd is.
     *  \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    virtual bool properlyInitialised() const;

    /** \brief Stuur de output string naar de output stream.
     *  \param output De string die naar de output gestuurd moet worden.
     *  \param os De stream waar de output naar gestuurd zal worden.
     *
     * REQUIRE(this->properlyInitialised(), "Exporter was niet geinitialiseerd bij de aanroep van write.");\n
     */
    virtual void write(std::string& output, std::ostream& os);

protected:
    /** \brief Valideer de output formaat.
     *  \param os De stream waar de output naar gestuurd zal worden.
     *
     * REQUIRE(this->properlyInitialised(), "Exporter was niet geinitialiseerd bij de aanroep van validate,");\n
     * ENSURE((documentStarted == true), "Document werd niet aangemaakt bij de aanroep van validate.");\n
     */
    virtual void validate(std::ostream& os);
};

class ExporterCLI : public Exporter {

};

class ExporterTXT : public Exporter {

};

class ExporterHTML : public Exporter {
public:
    virtual void write(std::string& output, std::ostream& os);

protected:
    virtual void validate(std::ostream& os);

    /** \brief Valideer de HTML header.
     *  \param os De stream waar de output naar gestuurd zal worden.
     *
     * REQUIRE(this->properlyInitialised(), "ExporterHTML was niet geinitialiseerd bij het aanroepen van validateHead.");\n
     * REQUIRE(documentStarted == false), "Document was al aangemaakt voor de aanroep van validateHead.");\n
     * ENSURE((documentStarted == true), "Document werd niet aangemaakt bij de aanroep van validateHead.");\n
     */
    void validateHead(std::ostream& os);

    /** \brief Valideer de HTML tail.
     *  \param os De stream waar de output naar gestuurd zal worden.
     *
     * REQUIRE(this->properlyInitialised(), "ExporterHTML was niet geinitialiseerd bij het aanroepen van validateTail.");\n
     * REQUIRE((documentStarted == true), "Document was nog niet aangemaakt bij de aanroep van validateTail.");
     * ENSURE((documentStarted == true), "Document werd niet aangemaakt bij de aanroep van validateTail.");.\n
     */
    void validateTail(std::ostream& os);
};

#endif /* SRC_EXPORTER_H_ */
