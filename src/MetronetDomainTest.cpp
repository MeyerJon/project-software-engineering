//
// Created by jonathan on 16.03.17.
//

#include "MetronetDomainTest.h"

const unsigned int TESTS_CONSISTENT = 2;
const unsigned int TESTS_INCONSISTENT = 3;

TEST_F(MetronetDomainTest, VoorbeeldTest){
    ASSERT_TRUE(metronet.properlyInitialised());
}

TEST_F(MetronetDomainTest, CheckConsistent){
    Parser p(exp);
    std::string filename;
    SuccessEnum importResult;
    // Check if the consistent nets are evaluated correctly
    for(int i = 1; i <= TESTS_CONSISTENT; i++){
        filename = "testInput/ConsistentNet" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        Parser p(exp);
        importResult = p.setup(metronet, filename, dummy);
        ASSERT_EQ(importResult, Success);
        ASSERT_TRUE(metronet.checkConsistent(exp, dummy));
        metronet.reset();
    }

    // Check if the inconsistent nets are evaluated correctly
    for(int i = 1; i <= TESTS_INCONSISTENT; i++){
        filename = "testInput/InconsistentNet" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        Parser p(exp);
        importResult = p.setup(metronet, filename, dummy);
        ASSERT_EQ(importResult, Success);
        ASSERT_FALSE(metronet.checkConsistent(exp, dummy));
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
    
}

TEST_F(MetronetDomainTest, OpstappenAfstappenOverflow){

}