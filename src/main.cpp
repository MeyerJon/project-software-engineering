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
    Exporter* expHTML = new ExporterHTML;
    Exporter* expTXT = new ExporterTXT;
    Exporter* expCLI = new ExporterCLI;
    Parser parsHTML(expHTML);
    Parser parsTXT(expTXT);
    Parser parsCLI(expCLI);
    std::ofstream html;
    std::ofstream txt;
    html.open("fuckMe.html");
    txt.open("kek.txt");
    Metronet metronet;
    parsHTML.setup(metronet, "xmls/DummyStations.xml", html);
    parsTXT.setup(metronet, "xmls/DummyStations.xml", txt);
    parsCLI.setup(metronet, "xmls/DummyStations.xml", std::cout);
    return 0;
}
