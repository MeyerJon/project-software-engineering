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
        Parser parser(exp);
        Metronet metronet;
        if (expType == "cli") {
            exp = new ExporterCLI;
            parser.setup(metronet, input, std::cout);
        }
        else if (expType == "html") {
            exp = new ExporterHTML;
            std::ofstream of;
            of.open(output + ".html");
            parser.setup(metronet, input, of);
        }
        else if (expType == "txt") {
            exp  = new ExporterTXT;
            std::ofstream of;
            of.open(output + ".txt");
            parser.setup(metronet, input, of);
        }
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
