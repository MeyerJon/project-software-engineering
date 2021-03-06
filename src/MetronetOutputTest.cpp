//
// Created by jonathan on 16.03.17.
//

#include "MetronetOutputTest.h"

TEST_F(MetronetOutputTest, OutputLegalSystemsTxt) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    std::string filename;
    for (int i = 1; i <= TESTS_LEGAL; i++) {
        exp = new Exporter();
        parser = Parser(exp);
        metronet = Metronet(exp);
        filename = "testInput/LegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::string outputName = "testOutput/LegalSystemInput" + std::to_string(i) + "Output.txt";
        std::string expectedOutput = "testOutput/LegalSystemInput" + std::to_string(i) + "ExpectedOutput.txt";
        std::ofstream output;
        output.open(outputName, std::ofstream::trunc);
        parser.setup(metronet, filename, output);
        if (metronet.checkConsistent(output)){
            metronet.printMetronet(output);
            metronet.rondrijden(output);
        }
        output.close();
        ASSERT_TRUE(FileCompare(outputName, expectedOutput));
        metronet.reset();
        delete exp;
    }
}

TEST_F(MetronetOutputTest, OutputIllegalSystemsTxt) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    std::string filename;
    for (int i = 1; i <= TESTS_ILLEGAL; i++) {
        exp = new Exporter();
        parser = Parser(exp);
        metronet = Metronet(exp);
        filename = "testInput/IllegalSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::string outputName = "testOutput/IllegalSystemInput" + std::to_string(i) + "Output.txt";
        std::string expectedOutput = "testOutput/IllegalSystemInput" + std::to_string(i) + "ExpectedOutput.txt";
        std::ofstream output;
        output.open(outputName, std::ofstream::trunc);
        parser.setup(metronet, filename, output);
        if (metronet.checkConsistent(output)) {
            metronet.printMetronet(output);
            metronet.rondrijden(output);
        }
        output.close();
        ASSERT_TRUE(FileCompare(outputName, expectedOutput));
        metronet.reset();
        delete exp;
    }
}

TEST_F(MetronetOutputTest, OutputIncorrectSystemsTxt) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    std::string filename;
    for (int i = 1; i <= TESTS_INCORRECT; i++) {
        exp = new Exporter();
        parser = Parser(exp);
        metronet = Metronet(exp);
        filename = "testInput/IncorrectSystemInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::string outputName = "testOutput/IncorrectSystemInput" + std::to_string(i) + "Output.txt";
        std::string expectedOutput = "testOutput/IncorrectSystemInput" + std::to_string(i) + "ExpectedOutput.txt";
        std::ofstream output;
        output.open(outputName, std::ofstream::trunc);
        parser.setup(metronet, filename, output);
        if (metronet.checkConsistent(output)) {
            metronet.printMetronet(output);
            metronet.rondrijden(output);
        }
        output.close();
        ASSERT_TRUE(FileCompare(outputName, expectedOutput));
        metronet.reset();
        delete exp;
    }
}

TEST_F(MetronetOutputTest, OutputSyntaxErrorSystemsTxt) {
    ASSERT_TRUE(DirectoryExists("testInput"));
    std::string filename;
    for (int i = 1; i <= TESTS_SYNTAX; i++) {
        exp = new Exporter();
        parser = Parser(exp);
        metronet = Metronet(exp);
        filename = "testInput/SyntaxErrorInput" + std::to_string(i) + ".xml";
        ASSERT_TRUE(FileExists(filename));
        ASSERT_TRUE(metronet.properlyInitialised());

        std::string outputName = "testOutput/SyntaxErrorInput" + std::to_string(i) + "Output.txt";
        std::string expectedOutput = "testOutput/SyntaxErrorInput" + std::to_string(i) + "ExpectedOutput.txt";
        std::ofstream output;
        output.open(outputName, std::ofstream::trunc);
        if (parser.setup(metronet, filename, output) != BadImport) {
            if (metronet.checkConsistent(output)) {
                metronet.printMetronet(output);
                metronet.rondrijden(output);
            }
        }
        output.close();
        ASSERT_TRUE(FileCompare(outputName, expectedOutput));
        metronet.reset();
        delete exp;
    }
}
