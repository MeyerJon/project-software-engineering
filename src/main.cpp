/*
 * main.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include <iostream>
#include <fstream>
#include "Parser.h"

int main() {
    Exporter* expCLI = new ExporterCLI;
    Parser parsCLI(expCLI);
    Metronet metronetCLI;
    parsCLI.setup(metronetCLI, "testInput/HappyDayInput.xml", std::cout);
    metronetCLI.rondrijden(expCLI, std::cout);
    delete expCLI;
    return 0;
}
