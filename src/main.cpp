/*
 * main.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include <iostream>
#include <fstream>
#include "Metronet.h"

int main(int argc, const char* argv[]) {
    if (argc != 1) {
        std::string expType = argv[1];
        std::string input = argv[2];
        std::string output;
        if (argc == 4) output = argv[3];
        Exporter* exp;
        if (expType == "cli") {
            exp = new ExporterCLI;
            Metronet metronet(exp);
            SuccessEnum importResult = metronet.setup(input, std::cout);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(std::cout)) {
                    metronet.printMetronet(std::cout);
                    metronet.rondrijden(std::cout);
                }
            }
        }
        else if (expType == "html") {
            exp = new ExporterHTML;
            Metronet metronet(exp);
            std::ofstream of;
            of.open(output + ".html", std::ofstream::trunc);
            SuccessEnum importResult = metronet.setup(input, of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(of)) {
                    metronet.printMetronet(of);
                    metronet.rondrijden(of);
                }
            }
        }
        else if (expType == "txt") {
            exp = new ExporterTXT;
            Metronet metronet(exp);
            std::ofstream of;
            of.open(output + ".txt", std::ofstream::trunc);
            SuccessEnum importResult = metronet.setup(input, of);
            if (importResult != BadImport) {
                if (metronet.checkConsistent(of)) {
                    metronet.printMetronet(of);
                    metronet.rondrijden(of);
                }
            }
        }
        delete exp;
    } else {
        Exporter* exp = new ExporterCLI;
        Metronet metronet(exp);
        metronet.setup("testInput/HappyDayInput.xml", std::cout);
        if (metronet.checkConsistent(std::cout)) {
            metronet.printMetronet(std::cout);
            metronet.rondrijden(std::cout);
        }
        delete exp;
    }
    return 0;
}
