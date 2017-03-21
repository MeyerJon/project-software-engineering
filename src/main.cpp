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
    if (argc != 1) {
        std::string expType = argv[1];
        std::string input = argv[2];
        std::string output;
        if (argc == 4) output = argv[3];
        Exporter* exp;
        Metronet metronet;
        if (expType == "cli") {
            exp = new ExporterCLI;
            Parser parser(exp);
            SuccessEnum importResult = parser.setup(metronet, input, std::cout);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(exp, std::cout)) {
                    metronet.printMetronet(exp, std::cout);
                    metronet.rondrijden(exp, std::cout);
                }
            }
        }
        else if (expType == "html") {
            exp = new ExporterHTML;
            std::ofstream of;
            of.open(output + ".html", std::ofstream::trunc);
            Parser parser(exp);
            SuccessEnum importResult = parser.setup(metronet, input, of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(exp, of)) {
                    metronet.printMetronet(exp, of);
                    metronet.rondrijden(exp, of);
                }
            }
        }
        else if (expType == "txt") {
            exp = new ExporterTXT;
            std::ofstream of;
            of.open(output + ".txt", std::ofstream::trunc);
            Parser parser(exp);
            SuccessEnum importResult = parser.setup(metronet, input, of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(exp, of)) {
                    metronet.printMetronet(exp, of);
                    metronet.rondrijden(exp, of);
                }
            }
        }
        delete exp;
    } else {
        Exporter* expCLI = new ExporterCLI;
        Parser parsCLI(expCLI);
        Metronet metronetCLI;
        parsCLI.setup(metronetCLI, "testInput/HappyDayInput.xml", std::cout);
        if (metronetCLI.checkConsistent(expCLI, std::cout)) {
            metronetCLI.printMetronet(expCLI, std::cout);
            metronetCLI.rondrijden(expCLI, std::cout);
        }
        delete expCLI;
    }
    return 0;
}
