//
// Created by jonathan on 16.03.17.
//

#include "MetronetDomainTest.h"

#include <limits>

TEST_F(MetronetDomainTest, ProperlyInitialised){
    std::ostream dummy(0);
    parser.setup(metronet, "testInput/HappyDayInput.xml", dummy);

    ASSERT_TRUE(metronet.properlyInitialised());
    for(auto p : metronet.getTrams()){
        Tram* t = p.second;
        ASSERT_TRUE(t->properlyInitialised());
    }
    for(auto p : metronet.getStations()){
        Station* s = p.second;
        ASSERT_TRUE(s->properlyInitialised());
    }
    metronet.reset();
}

TEST_F(MetronetDomainTest, CheckConsistent){
    std::string filename;
    SuccessEnum importResult;
    // Check if the consistent nets are evaluated correctly
    for(int i = 1; i <= TESTS_LEGAL; i++){
        filename = "testInput/LegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        importResult = parser.setup(metronet, filename, dummy);
        ASSERT_EQ(importResult, Success);
        ASSERT_TRUE(metronet.checkConsistent(dummy));
        metronet.reset();
    }

    // Check if the inconsistent nets are evaluated correctly
    for(int i = 1; i <= TESTS_ILLEGAL; i++){
        filename = "testInput/IllegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        importResult = parser.setup(metronet, filename, dummy);
        ASSERT_EQ(importResult, Success);
        ASSERT_FALSE(metronet.checkConsistent(dummy));
        metronet.reset();
    }
}

TEST_F(MetronetDomainTest, addTram){
    std::ostream dummy(0);

    Tram* tram = new Tram(10, 60, 1, "A");
    metronet.addTram(tram);
    ASSERT_EQ(metronet.getTrams().at(1), tram);
    metronet.reset();
}

TEST_F(MetronetDomainTest, addStation){
    std::ostream dummy(0);

    Station* station = new Station("A", "B", "C", 1, 0, 0);
    metronet.addStation(station);
    ASSERT_EQ(metronet.getStations().at("A"), station);
    metronet.reset();
}

TEST_F(MetronetDomainTest, rondrijden){
    std::ostream dummy(0);
    parser.setup(metronet, "testInput/RondrijdenInput.xml", dummy);

    metronet.rondrijden(dummy);

    std::map<int, Tram*>& trams = metronet.getTrams();
    for(auto p : trams){
        Tram* tram = p.second;
        ASSERT_EQ(tram->getHuidigStation(), tram->getBeginStation());
        ASSERT_EQ(tram->getPassagiers(), 5); // Scenario zo geschreven
    }
    metronet.reset();
}