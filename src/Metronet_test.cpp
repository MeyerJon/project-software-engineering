/*
 * Metronet_test.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: sergio
 */

#include <gtest/gtest.h>
#include "MetronetInputTest.h"
#include "MetronetDomainTest.h"
#include "MetronetOutputTest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}