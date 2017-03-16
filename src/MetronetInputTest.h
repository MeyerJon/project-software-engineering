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

class MetronetInputTest: public ::testing::Test {
protected:
    friend class Metronet;

    virtual void SetUp() {
        exp = new ExporterCLI;
    }

    virtual void TearDown() {
        delete exp;
    }

    Metronet metronet;
    Exporter* exp;
    SuccesEnum endResult;
};

#endif //PSE_METRONETINPUTTESTS_H