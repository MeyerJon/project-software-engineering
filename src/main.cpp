/*
 * main.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include <iostream>
#include <fstream>
#include "Metronet.h"
#include "Parser.h"
#include "Exporter.h"

int main() {
    Exporter* exporter = new ExporterHTML;
    Parser parser(exporter);
    std::ofstream html;
    html.open("fuckMe.html");
    Metronet metronet;
    parser.setup(metronet, "xmls/DummyStations.xml", html);
    metronet.printMetronet(exporter, html);
    return 0;
}
