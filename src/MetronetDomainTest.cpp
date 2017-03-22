//
// Created by jonathan on 16.03.17.
//

#include "MetronetDomainTest.h"

#include <limits>

const unsigned int TESTS_CONSISTENT = 2;
const unsigned int TESTS_INCONSISTENT = 3;

TEST_F(MetronetDomainTest, ProperlyInitialised){
    std::ostream dummy(0);
    metronet.setup("testInput/HappyDayInput.xml", dummy);

    ASSERT_TRUE(metronet.properlyInitialised());
    for(auto p : metronet.getTrams()){
        Tram* t = p.second;
        ASSERT_TRUE(t->properlyInitialised());
    }
    for(auto p : metronet.getStations()){
        Station* s = p.second;
        ASSERT_TRUE(s->properlyInitialised());
    }
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
        importResult = metronet.setup(filename, dummy);
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
        importResult = metronet.setup(filename, dummy);
        ASSERT_EQ(importResult, Success);
        ASSERT_FALSE(metronet.checkConsistent(dummy));
        metronet.reset();
    }
}

TEST_F(MetronetDomainTest, VerplaatsTram){
    Tram tram(10, 60, 2, "goodBegin");

    ASSERT_EQ(tram.getHuidigStation(), tram.getBeginStation());

    std::ostream dummy(0);
    tram.verplaatsTram("TestStation1", exp, dummy);
    ASSERT_EQ(tram.getHuidigStation(), "TestStation1");
    tram.verplaatsTram("TestStation2", exp, dummy);
    ASSERT_EQ(tram.getHuidigStation(), "TestStation2");
    tram.verplaatsTram("goodBegin", exp, dummy);
    ASSERT_EQ(tram.getHuidigStation(), "goodBegin");
    ASSERT_EQ(tram.getHuidigStation(), tram.getBeginStation());
}

TEST_F(MetronetDomainTest, OpstappenAfstappenNormaal){
    Tram smallTram(10, 50, 1, "A");
    Tram bigTram(100, 30, 2, "B");

    smallTram.opstappen(3);
    ASSERT_EQ(smallTram.getPassagiers(), 3);
    smallTram.opstappen(6);
    ASSERT_EQ(smallTram.getPassagiers(), 9);
    smallTram.afstappen(9);
    ASSERT_EQ(smallTram.getPassagiers(), 0);
    smallTram.opstappen(0);
    ASSERT_EQ(smallTram.getPassagiers(), 0);
    smallTram.afstappen(0);
    ASSERT_EQ(smallTram.getPassagiers(), 0);

    bigTram.opstappen(0);
    ASSERT_EQ(bigTram.getPassagiers(), 0);
    bigTram.opstappen(99);
    ASSERT_EQ(bigTram.getPassagiers(), 99);
    bigTram.afstappen(21);
    ASSERT_EQ(bigTram.getPassagiers(), 78);
    bigTram.opstappen(2);
    ASSERT_EQ(bigTram.getPassagiers(), 80);
    bigTram.afstappen(60);
    ASSERT_EQ(bigTram.getPassagiers(), 20);
    bigTram.afstappen(20);
    ASSERT_EQ(bigTram.getPassagiers(), 0);

}

TEST_F(MetronetDomainTest, OpstappenAfstappenOverflow){
    Tram tram(20, 50, 1, "A");
    int max = std::numeric_limits<int>::max();

    tram.opstappen(30);
    ASSERT_EQ(tram.getPassagiers(), tram.getZitplaatsen());
    tram.afstappen(30);
    ASSERT_EQ(tram.getPassagiers(), 0);

    tram.opstappen(max);
    ASSERT_EQ(tram.getPassagiers(), tram.getZitplaatsen());
    tram.afstappen(max);
    ASSERT_EQ(tram.getPassagiers(), 0);

}

TEST_F(MetronetDomainTest, OpstappenAfstappenNegative){
    Tram tram(20, 50, 1, "A");

    EXPECT_DEATH(tram.opstappen(-1), "");
    EXPECT_DEATH(tram.afstappen(-1), "");
}

TEST_F(MetronetDomainTest, addTram){
    std::ostream dummy(0);
    metronet.setup("testInput/HappyDayInput.xml", dummy);

    Tram* tram = new Tram(10, 60, 1, "A");
    metronet.addTram(tram);
    ASSERT_EQ(metronet.getTrams().at(1), tram);
}

TEST_F(MetronetDomainTest, addStation){
    std::ostream dummy(0);
    metronet.setup("testInput/HappyDayInput.xml", dummy);

    Station* station = new Station("A", "B", "C", 1, 0, 0);
    metronet.addStation(station);
    ASSERT_EQ(metronet.getStations().at("A"), station);
}

TEST_F(MetronetDomainTest, rondrijden){
    std::ostream dummy(0);
    metronet.setup("testInput/RondrijdenInput.xml", dummy);

    metronet.rondrijden(dummy);

    std::map<int, Tram*>& trams = metronet.getTrams();
    for(auto p : trams){
        Tram* tram = p.second;
        ASSERT_EQ(tram->getHuidigStation(), tram->getBeginStation());
        ASSERT_EQ(tram->getPassagiers(), 5); // Scenario zo geschreven
    }
}