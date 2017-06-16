//
// Created by sergio on 03/05/17.
//

#ifndef SOFTENG_STATIONDOMAINTEST_H
#define SOFTENG_STATIONDOMAINTEST_H


#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <sys/stat.h>

#include "MetronetUtils.h"
#include "Station.h"

class StationDomainTest : public ::testing::Test {
protected:
    friend class Station;

    virtual void SetUp() {}

    virtual void TearDown() {}

    std::map<int, std::string> dummyMap = {{10, "dummy"}};
    StatisticsStation* statsA = new StatisticsStation();
    StatisticsStation* statsB = new StatisticsStation();
    Station halte = Station("A", "Halte", dummyMap, dummyMap, statsA);
    Station metrostation = Station("B", "Metrostation", dummyMap, dummyMap, statsB);
    const int spoor = 10;
};


#endif //SOFTENG_STATIONDOMAINTEST_H
