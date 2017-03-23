/*
 * Exporter.h
 *
 *  Created on: 8 Mar 2017
 *      Author: sergio
 */

#ifndef SRC_EXPORTER_H_
#define SRC_EXPORTER_H_

#include <iostream>
#include <string>
#include <algorithm>
#include "DesignByContract.h"
/**
 * \brief Exporter base klasse die de output van gegevens behandelt
 */
class Exporter {
protected:
    bool documentStarted;
    Exporter* initCheck;
public:
    /**
     * \brief Lege constructor van Exporter
     */
    Exporter();

    /**
     * \brief Getter van member documentStarted
     * \return De waarde van documentStarted
     * \pre REQUIRE(this->properlyInitialised(), "Exporter was niet geinitialiseerd bij de aanroep van isDocumentStarted.");
     */
    bool isDocumentStarted() const;

    /**
     * \brief Kijk na of de constructor in de juiste staat geeindigd is.
     * \return Boolean die aangeeft of het object juist geinitialiseerd is.
     */
    virtual bool properlyInitialised() const;

    /**
     * \brief Stuur de output string naar de output stream.
     * \param output De string die naar de output gestuurd moet worden.
     * \param os De stream waar de output naar gestuurd zal worden.
     * \pre REQUIRE(this->properlyInitialised(), "Exporter was niet geinitialiseerd bij de aanroep van write.");
     * \post ENSURE(documentStarted, "Document was niet aangemaakt bij de aanroep van write.");
     */
    virtual void write(std::string& output, std::ostream& os);

    /**
     * \brief Stuurt de nodige informatie naar de output stream om het document correct af te sluiten.
     * \param os De stream waar de output naar gestuurd zal worden.
     * \pre REQUIRE(this->properlyInitialised(), "Exporter was niet geinitialiseerd bij de aanroep van finish.");
     * \pre REQUIRE(documentStarted, "Document was niet aangemaakt voor de aanroep van finish.");
     */
     virtual void finish(std::ostream& os);
};

/**
 * \brief ExporterCLI child klasse die de output van gegevens naar de command line behandelt
 */
class ExporterCLI : public Exporter {

};

/**
 * \brief ExporterTXT child klasse die de output van gegevens naar een txt-bestand behandelt
 */
class ExporterTXT : public Exporter {

};

/**
 * \brief ExporterHTML child klasse die de output van gegevens naar een html-bestand behandelt
 */
class ExporterHTML : public Exporter {
public:
    virtual void write(std::string& output, std::ostream& os);

    virtual void finish(std::ostream& os);

private:
    /**
     * \brief Valideer de HTML header.
     * \param os De stream waar de output naar gestuurd zal worden.
     * \pre REQUIRE(this->properlyInitialised(), "ExporterHTML was niet geinitialiseerd bij de aanroep van createHTMLHead.");
     * \pre REQUIRE(!documentStarted, "Document was aangemaakt voor de aanroep van createHTMLHead.");
     */
    void createHTMLHead(std::ostream& os);
};

#endif /* SRC_EXPORTER_H_ */
