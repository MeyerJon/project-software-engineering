/*
 * MetronetInputTests.cpp
 *
 *  Created on: 10 Mar 2017
 *      Author: Dawid
 */

#include "MetronetInputTest.h"

TEST_F(MetronetInputTest, InputHappyDay) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    ASSERT_TRUE(FileExists("testInput/HappyDayInput.xml"));
    ASSERT_TRUE(metronet.properlyInitialised());

    std::ostream dummy(0);
    SuccessEnum importResult = parser.setup(metronet, "testInput/HappyDayInput.xml", dummy);
    ASSERT_EQ(importResult, Success);

    SuccessEnum endResult = Success;

    Station* A = metronet.getStations()["A"];
    if (A->getNaam() != "A") endResult = BadImport;
    if (A->getType() != "Metrostation") endResult = BadImport;
    if (A->getSporen()[0] != 1) endResult = BadImport;
    if (A->getVolgende(1) != "B") endResult = BadImport;
    if (A->getVorige(1) != "C") endResult = BadImport;
    if (A->getSporen()[1] != 2) endResult = BadImport;
    if (A->getVolgende(2) != "C") endResult = BadImport;
    if (A->getVorige(2) != "B") endResult = BadImport;

    Station* B = metronet.getStations()["B"];
    if (B->getNaam() != "B") endResult = BadImport;
    if (B->getType() != "Halte") endResult = BadImport;
    if (B->getSporen()[0] != 1) endResult = BadImport;
    if (B->getVolgende(1) != "C") endResult = BadImport;
    if (B->getVorige(1) != "A") endResult = BadImport;
    if (B->getSporen()[1] != 2) endResult = BadImport;
    if (B->getVolgende(2) != "A") endResult = BadImport;
    if (B->getVorige(2) != "C") endResult = BadImport;

    Station* C = metronet.getStations()["C"];
    if (C->getNaam() != "C") endResult = BadImport;
    if (C->getType() != "Metrostation") endResult = BadImport;
    if (C->getSporen()[0] != 1) endResult = BadImport;
    if (C->getVolgende(1) != "A") endResult = BadImport;
    if (C->getVorige(1) != "B") endResult = BadImport;
    if (C->getSporen()[1] != 2) endResult = BadImport;
    if (C->getVolgende(2) != "B") endResult = BadImport;
    if (C->getVorige(2) != "A") endResult = BadImport;

    Tram* t1 = metronet.getTrams()[1];
    if (t1->getSpoor() != 1) endResult = BadImport;
    if (t1->getVoertuignummer() != 1) endResult = BadImport;
    if (t1->getType() != "PCC") endResult = BadImport;
    if (t1->getZitplaatsen() != 16) endResult = BadImport;
    if (t1->getSnelheid() != 40) endResult = BadImport;
    if (t1->getBeginStation() != "A") endResult = BadImport;

    Tram* t2 = metronet.getTrams()[2];
    if (t2->getSpoor() != 1) endResult = BadImport;
    if (t2->getVoertuignummer() != 2) endResult = BadImport;
    if (t2->getType() != "Albatros") endResult = BadImport;
    if (t2->getZitplaatsen() != 72) endResult = BadImport;
    if (t2->getSnelheid() != 70) endResult = BadImport;
    if (t2->getBeginStation() != "C") endResult = BadImport;

    Tram* t3 = metronet.getTrams()[3];
    if (t3->getSpoor() != 2) endResult = BadImport;
    if (t3->getVoertuignummer() != 3) endResult = BadImport;
    if (t3->getType() != "Albatros") endResult = BadImport;
    if (t3->getZitplaatsen() != 72) endResult = BadImport;
    if (t3->getSnelheid() != 70) endResult = BadImport;
    if (t3->getBeginStation() != "A") endResult = BadImport;

    Passagier* p1 = metronet.getPassagiers()["Groep1"];
    if (p1->getNaam() != "Groep1") endResult = BadImport;
    if (p1->getBeginStation() != "A") endResult = BadImport;
    if (p1->getEindStation() != "C") endResult = BadImport;
    if (p1->getHoeveelheid() != 2) endResult = BadImport;
    if (p1->isVertrokken()) endResult = BadImport;

    ASSERT_EQ(endResult, Success);
}

TEST_F(MetronetInputTest, InputLegalSystems) {
    // setup Success

    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_LEGAL; i++) {
        filename = "testInput/LegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(parser.setup(metronet, filename, dummy), Success);
        ASSERT_FALSE(FileIsEmpty(filename));
        metronet.reset();
    }
}

TEST_F(MetronetInputTest, InputIllegalSystems) {
    // setup Success

    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_ILLEGAL; i++) {
        filename = "testInput/IllegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(parser.setup(metronet, filename, dummy), Success);
        ASSERT_FALSE(FileIsEmpty(filename));
        metronet.reset();
    }
}

TEST_F(MetronetInputTest, InputIncorrectSystems) {
    // setup PartialImport (ontbrekende, foute waarden)
    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_INCORRECT; i++) {
        filename = "testInput/IncorrectSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(parser.setup(metronet, filename, dummy), PartialImport);
        ASSERT_FALSE(FileIsEmpty(filename));
        metronet.reset();
    }
}

TEST_F(MetronetInputTest, InputSyntaxErrorSystems) {
    // setup BadImport (fouten tegen XML)
    ASSERT_TRUE(DirectoryExists("testInput"));

    std::string filename;
    for (int i = 1; i <= TESTS_SYNTAX; i++) {
        filename = "testInput/SyntaxErrorInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ostream dummy(0);
        ASSERT_EQ(parser.setup(metronet, filename, dummy), BadImport);
        metronet.reset();
    }
}
