/*
 * MetronetInputTests.cpp
 *
 *  Created on: 10 Mar 2017
 *      Author: Dawid
 */

#include "MetronetInputTest.h"

//TEST_F(MetronetInputTest, InputHappyDay) {
//    ASSERT_TRUE(DirectoryExists("testInput"));
//    ASSERT_TRUE(FileExists("testInput/HappyDayInput.xml"));
//    ASSERT_TRUE(metronet.properlyInitialised());
//
//    std::ostream dummy(0);
//    SuccessEnum importResult = metronet.setup("testInput/HappyDayInput.xml", dummy);
//    ASSERT_EQ(importResult, Success);
//
//    SuccessEnum endResult;
//    if (metronet.checkConsistent(dummy)) endResult = Success;
//    else endResult = PartialImport;
//
//    Station* A = metronet.getStations()["A"];
//    if (A->getNaam() != "A") endResult = BadImport;
//    if (A->getVolgende() != "B") endResult = BadImport;
//    if (A->getVorige() != "C") endResult = BadImport;
//    if (A->getSpoor() != 12) endResult = BadImport;
//    if (A->getAfstappen() != 0) endResult = BadImport;
//    if (A->getOpstappen() != 0) endResult = BadImport;
//
//    Station* B = metronet.getStations()["B"];
//    if (B->getNaam() != "B") endResult = BadImport;
//    if (B->getVolgende() != "C") endResult = BadImport;
//    if (B->getVorige() != "A") endResult = BadImport;
//    if (B->getSpoor() != 12) endResult = BadImport;
//    if (B->getAfstappen() != 0) endResult = BadImport;
//    if (B->getOpstappen() != 0) endResult = BadImport;
//
//    Station* C = metronet.getStations()["C"];
//    if (C->getNaam() != "C") endResult = BadImport;
//    if (C->getVolgende() != "A") endResult = BadImport;
//    if (C->getVorige() != "B") endResult = BadImport;
//    if (C->getSpoor() != 12) endResult = BadImport;
//    if (C->getAfstappen() != 0) endResult = BadImport;
//    if (C->getOpstappen() != 0) endResult = BadImport;
//
//    Tram* t12 = metronet.getTrams()[12];
//    if (t12->getSpoor() != 12) endResult = BadImport;
//    if (t12->getZitplaatsen() != 32) endResult = BadImport;
//    if (t12->getSnelheid() != 60) endResult = BadImport;
//    if (t12->getBeginStation() != "A") endResult = BadImport;
//    ASSERT_EQ(endResult, Success);
//}

TEST_F(MetronetInputTest, InputLegalSystems) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_LEGAL; i++) {

        filename = "testInput/LegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(metronet.setup(filename, dummy), Success);
        ASSERT_TRUE(metronet.checkConsistent(dummy));
        ASSERT_FALSE(FileIsEmpty(filename));
        metronet.reset();
    }
}

TEST_F(MetronetInputTest, InputIllegalSystems) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_ILLEGAL; i++) {
        filename = "testInput/IllegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(metronet.setup(filename, dummy), PartialImport);
        ASSERT_FALSE(metronet.checkConsistent(dummy));
        ASSERT_FALSE(FileIsEmpty(filename));
        metronet.reset();
    }
}

TEST_F(MetronetInputTest, InputIncorrectSystems) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_INCORRECT; i++) {
        filename = "testInput/IncorrectSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(metronet.setup(filename, dummy), PartialImport);
        ASSERT_FALSE(metronet.checkConsistent(dummy));
        ASSERT_FALSE(FileIsEmpty(filename));
        metronet.reset();
    }
}

TEST_F(MetronetInputTest, InputSyntaxErrorSystems) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_SYNTAX; i++) {
        filename = "testInput/SyntaxErrorSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(metronet.setup(filename, dummy), BadImport);
        metronet.reset();
    }
}
