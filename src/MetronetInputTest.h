//
// Created by jonathan on 16.03.17.
//

#ifndef PSE_METRONETINPUTTESTS_H
#define PSE_METRONETINPUTTESTS_H

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <sys/stat.h>

#include "MetronetUtils.h"
#include "Metronet.h"
#include "Parser.h"
#include "Station.h"
#include "Tram.h"
#include "Passagier.h"

/**
 * \brief MetronetInputTest klasse die input tests behandelt
 */
class MetronetInputTest: public ::testing::Test {
protected:
    friend class Metronet;

    virtual void SetUp() {
        exp = new Exporter();
        parser = Parser(exp);
        metronet = Metronet(exp);
    }

    virtual void TearDown() {
        delete exp;
    }
    Parser parser;
    Metronet metronet;
    Exporter* exp;
};

#endif //PSE_METRONETINPUTTESTS_H
