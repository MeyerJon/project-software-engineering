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
    Metronet metronetHTML;
    Metronet metronetTXT;
    Metronet metronetCLI;
    parsHTML.setup(metronetHTML, "xmls/DummyStations.xml", html);
    parsTXT.setup(metronetTXT, "xmls/DummyStations.xml", txt);
    parsCLI.setup(metronetCLI, "xmls/DummyStations.xml", std::cout);
    delete expHTML;
    delete expTXT;
    delete expCLI;
    return 0;
}
