/*
 * main.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include <iostream>
#include <fstream>
#include "Parser.h"

int main(int argc, const char* argv[]) {
    Exporter* exp = new Exporter();
    if (argc != 1) {
        for (int i = 1; i < argc; i++) {
            std::ifstream fin(argv[i]);
            std::string filename = argv[i];
            std::string::size_type posSlash = filename.rfind('/');
            std::string::size_type posPoint = filename.rfind('.');
            std::string output = "testOutput" + filename.substr(posSlash, posPoint - posSlash) + "ExpectedOutput.txt";
            Parser parser(exp);
            Metronet metronet(exp);
            std::ofstream of;
            of.open(output, std::ofstream::trunc);
            SuccessEnum importResult = parser.setup(metronet, filename, of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(of)) {
                    metronet.printMetronet(of);
                    metronet.rondrijden(of);
                }
            }
        }
    } else {
        Parser parser(exp);
        Metronet metronet(exp);
        SuccessEnum importResult = parser.setup(metronet, "testInput/IncorrectSystemInput7.xml", std::cout);
        if (importResult != BadImport) {
            if (metronet.checkConsistent(std::cout)) {
                metronet.printMetronet(std::cout);
                metronet.rondrijden(std::cout);
                metronet.printStatistics(std::cout);
                metronet.printMetronetGrafisch(std::cout);
            }
        }
    }
    delete exp;
    return 0;
}
