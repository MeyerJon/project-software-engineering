//
// Created by jonathan on 16.03.17.
//

#ifndef PSE_METRONETOUTPUTTESTS_H
#define PSE_METRONETOUTPUTTESTS_H

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <sys/stat.h>

#include "MetronetUtils.h"
#include "Metronet.h"

const unsigned int TESTS_LEGAL = 3;
const unsigned int TESTS_ILLEGAL = 4;
const unsigned int TESTS_INCONSISTENT = 5;
const unsigned int TESTS_INCORRECT = 4;
const unsigned int TESTS_SYNTAX = 3;

class MetronetOutputTest: public ::testing::Test {
protected:
    friend class Metronet;

    virtual void SetUp() {
        exp = new ExporterTXT;
        metronet = Metronet(exp);
    }

    virtual void TearDown() {
        delete exp;
    }

    Metronet metronet;
    Exporter* exp;
};

#endif //PSE_METRONETOUTPUTTESTS_H
