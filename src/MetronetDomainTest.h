//
// Created by jonathan on 16.03.17.
//

#ifndef PSE_METRONETDOMAINTESTS_H
#define PSE_METRONETDOMAINTESTS_H


#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <sys/stat.h>

#include "MetronetUtils.h"
#include "Metronet.h"
#include "Parser.h"

class MetronetDomainTest: public ::testing::Test {
protected:
    friend class Metronet;

    virtual void SetUp() {
        Exporter* exp = new ExporterCLI;
        Parser p(exp);
        std::ostream dummy(0);
        p.setup(metronet, "xmls/DummyStations.xml", dummy);
        delete exp;
    }

    virtual void TearDown() {

    }

    Metronet metronet;
};


#endif //PSE_METRONETDOMAINTESTS_H
