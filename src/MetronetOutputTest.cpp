//
// Created by jonathan on 16.03.17.
//

#include "MetronetOutputTest.h"

TEST_F(MetronetOutputTest, OutputLegalSystems) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    std::string filename;
    for (int i = 1; i <= 4; i++) {
        filename = "testInput/LegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::ofstream output;
        std::string outputName = "testOutput/LegalSystemOutput" + std::to_string(i) + ".xml";
        std::string expectedOutput = "testOutput/LegalSystemExpectedOutput" + std::to_string(i) + ".xml";
        output.open(outputName);
        Parser p(exp);
        SuccesEnum importResult = p.setup(metronet, filename, output);
        ASSERT_EQ(importResult, Success);
        ASSERT_TRUE(metronet.checkConsistent(exp, output));
        ASSERT_TRUE(FileCompare(outputName, expectedOutput));
        metronet.reset();
    }

}