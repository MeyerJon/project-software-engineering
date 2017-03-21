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

const unsigned int TESTS_LEGAL = 3;
const unsigned int TESTS_ILLEGAL = 4;
<<<<<<< HEAD
const unsigned int TESTS_INCORRECT = 3;
=======
const unsigned int TESTS_INCONSISTENT = 5;
const unsigned int TESTS_INCORRECT = 4;
>>>>>>> 8c27e13e47047703bdfeead8983cff05333012ee
const unsigned int TESTS_SYNTAX = 3;

class MetronetInputTest: public ::testing::Test {
protected:
    friend class Metronet;

    virtual void SetUp() {
        exp = new ExporterCLI;
        metronet = Metronet(exp);
    }

    virtual void TearDown() {
        delete exp;
    }

    Metronet metronet;
    Exporter* exp;
};

#endif //PSE_METRONETINPUTTESTS_H
