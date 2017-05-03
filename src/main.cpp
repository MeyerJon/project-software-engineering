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
    Exporter* exp;
    if (argc != 1) {
        std::string expType = argv[1];
        std::string input = argv[2];
        std::string output;
        if (argc == 4) output = argv[3];
        if (expType == "cli") {
            exp = new ExporterCLI;
            Parser parser(exp);
            Metronet metronet(exp);
            SuccessEnum importResult = parser.setup(metronet, input, std::cout);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(std::cout)) {
                    metronet.printMetronet(std::cout);
                    metronet.rondrijden(std::cout);
                }
            }
        }
        else if (expType == "html") {
            exp = new ExporterHTML;
            Parser parser(exp);
            Metronet metronet(exp);
            std::ofstream of;
            of.open(output + ".html", std::ofstream::trunc);
            SuccessEnum importResult = parser.setup(metronet, input, of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(of)) {
                    metronet.printMetronet(of);
                    metronet.rondrijden(of);
                }
            }
        }
        else if (expType == "txt") {
            exp = new ExporterTXT;
            Parser parser(exp);
            Metronet metronet(exp);
            std::ofstream of;
            of.open(output + ".txt", std::ofstream::trunc);
            SuccessEnum importResult = parser.setup(metronet, input, of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(of)) {
                    metronet.printMetronet(of);
                    metronet.rondrijden(of);
                }
            }
        }
    } else {
        exp = new ExporterCLI;
        Parser parser(exp);
        Metronet metronet(exp);
        SuccessEnum importResult = parser.setup(metronet, "testInput/fatMetronet.xml", std::cout);
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
