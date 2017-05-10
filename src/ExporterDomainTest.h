//
// Created by sergio on 03/05/17.
//

#ifndef SOFTENG_EXPORTERDOMAINTEST_H
#define SOFTENG_EXPORTERDOMAINTEST_H

#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <sys/stat.h>

#include "MetronetUtils.h"
#include "Exporter.h"

/**
 * \brief ExporterDomainTest klasse die domein tests behandelt.
 */
class ExporterDomainTest : public ::testing::Test {
protected:
    friend class Exporter;

    virtual void SetUp() {
        exp = new Exporter();
    }

    virtual void TearDown() {
        delete exp;
    }
    Exporter* exp;
    std::string dummy_str = "dummy";
};


#endif //SOFTENG_EXPORTERDOMAINTEST_H
