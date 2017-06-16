/*
 * main.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include "Parser.h"

int main(int argc, const char* argv[]) {
    Exporter* exp = new Exporter();
    if (argc == 3) {
        if (argv[1] == std::string("--txt")) {
            // Generate txt output
            std::string::size_type posSlash = std::string(argv[2]).rfind('/');
            std::string::size_type posPoint = std::string(argv[2]).rfind('.');
            std::string output = "testOutput" + std::string(argv[2]).substr(posSlash, posPoint - posSlash) + "ExpectedOutput.txt";
            Parser parser(exp);
            Metronet metronet(exp);
            std::ofstream of;
            of.open(output, std::ofstream::trunc);
            SuccessEnum importResult = parser.setup(metronet, argv[2], of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(of)) {
                    metronet.printMetronet(of);
                    metronet.rondrijden(of);
                }
            }
        } else if (argv[1] == std::string("-v")) {
            // Verbose output
            Parser parser(exp);
            Metronet metronet(exp);
            SuccessEnum importResult = parser.setup(metronet, argv[2], std::cout);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(std::cout)) {
                    metronet.printMetronet(std::cout);
                    metronet.rondrijden(std::cout, true);
                    metronet.printStatistics(std::cout);
                    metronet.printMetronetGrafisch(std::cout);
                }
            }
        }
    } else if (argc == 2) {
        if (argv[1] == std::string("--demo")) {
            // Demo output
            Parser parser(exp);
            Metronet metronet(exp);
            SuccessEnum importResult = parser.setup(metronet, "testInput/Demo.xml", std::cout);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(std::cout)) {
                    metronet.printMetronet(std::cout);
                    metronet.rondrijden(std::cout, true);
                    metronet.printStatistics(std::cout);
                    metronet.printMetronetGrafisch(std::cout);
                }
            }
        } else {
            // Non-verbose output
            Parser parser(exp);
            Metronet metronet(exp);
            SuccessEnum importResult = parser.setup(metronet, argv[1], std::cout);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(std::cout)) {
                    metronet.rondrijden(std::cout);
                    metronet.printMetronetGrafisch(std::cout);
                }
            }
        }
    } else {
        // Hardcoded example
        Parser parser(exp);
        Metronet metronet(exp);
        SuccessEnum importResult = parser.setup(metronet, "testInput/HappyDayInput.xml", std::cout);
        if (importResult != BadImport) {
            if (metronet.checkConsistent(std::cout)) {
                metronet.printMetronet(std::cout);
                metronet.rondrijden(std::cout, true);
                metronet.printStatistics(std::cout);
                metronet.printMetronetGrafisch(std::cout);
            }
        }
    }
    delete exp;
    return 0;
}
