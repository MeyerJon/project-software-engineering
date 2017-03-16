/*
 * MetronetInputTests.cpp
 *
 *  Created on: 10 Mar 2017
 *      Author: Dawid
 */

#include "MetronetInputTest.h"

TEST_F(MetronetInputTest, InputHappyDay) {
    ASSERT_TRUE(DirectoryExists("testInput"));

    std::ofstream myfile;
    bool importResult;

    myfile.open("testInput/zzzInput.xml");
    myfile << "";
}

TEST_F(MetronetInputTest, InputLegalSystems) {
    ASSERT_TRUE(DirectoryExists("testInput"));
}

TEST_F(MetronetInputTest, InputIllegalSystems) {
    ASSERT_TRUE(DirectoryExists("testInput"));

}
