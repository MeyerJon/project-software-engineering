/*
 * main.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include <iostream>
#include "Metronet.h"
#include "Parser.h"
#include "Exporter.h"

int main() {
    Exporter* exporter = new ExporterCLI;
    Parser parser(exporter);
    Metronet metronet;
    parser.setup(metronet, "xmls/DummyStations.xml", std::cout);
    return 0;
}
