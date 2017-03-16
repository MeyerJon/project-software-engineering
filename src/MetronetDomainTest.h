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

class MetronetDomainTest: public ::testing::Test {
protected:
    friend class Metronet;

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    Metronet metronet;
};


#endif //PSE_METRONETDOMAINTESTS_H
