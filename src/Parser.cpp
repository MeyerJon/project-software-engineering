/*
 * Parser.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Parser.h"
#include <map>

Parser::Parser() {
    initCheck = this;
}

Parser::Parser(Exporter* exp) {
    Parser::exp = exp;
    initCheck = this;
}

bool Parser::setup(Metronet& metro, std::string filename, std::ostream& os){
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str())) {
        os << "ERROR: Kan bestand " + filename + " niet openen.";
        return false;
    }
    TiXmlElement* root = doc.FirstChildElement();
    // Iterate over all elements
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        std::string elemName = elem->Value();
        if(elemName == "STATION") {
            std::string attrName;
            std::string name;
            std::string vor;
            std::string volg;
            int opstappen = 0;
            int afstappen = 0;
            int spoor;
            try {
                for(TiXmlNode* node = elem->FirstChild(); node != NULL; node = node->NextSibling()){
                    attrName = node->Value();
                    TiXmlText* text;
                    std::string t;
                    if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                    else continue;
                    if(text != NULL) t = text->Value();
                    else continue;
                    if(attrName == "naam") name = t;
                    else if(attrName == "volgende") volg = t;
                    else if(attrName == "vorige") vor = t;
                    else if(attrName == "spoor") spoor = std::stoi(t);
                    else if(attrName == "opstappen") opstappen = std::stoi(t);
                    else if(attrName == "afstappen") afstappen = std::stoi(t);
                    else{
                        std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                        exp->write(out, os);
                    }
                }
                Station* station = new Station(name, vor, volg, spoor, opstappen, afstappen);
                metro.addStation(station);
                metro.addSpoor(spoor);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Station niet toegevoegd.\n";
                exp->write(out, os);
                continue;
            }
        }
        else if(elemName == "TRAM"){
            std::string attrName;
            int zitpl;
            int snelh;
            int spoor;
            std::string beginS;
            try {
                for(TiXmlNode* node = elem->FirstChild(); node != NULL; node = node->NextSibling()){
                    attrName = node->Value();
                    TiXmlText* text;
                    std::string t;
                    if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                    else continue;
                    if(text != NULL) t = text->Value();
                    else continue;
                    if(attrName == "zitplaatsen") zitpl = stoi(t);
                    else if(attrName == "snelheid") snelh = stoi(t);
                    else if(attrName == "lijnNr") spoor = std::stoi(t);
                    else if(attrName == "beginStation") beginS = t;
                    else{
                        std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                        exp->write(out, os);
                    }
                }
                Tram* tram = new Tram(zitpl, snelh, spoor, beginS);
                metro.addTram(tram);
                metro.addSpoor(spoor);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Tram niet toegevoegd.\n";
                exp->write(out, os);
                continue;
            }

        }
    }
    bool consistency = metro.checkConsistent(exp, os);
    metro.printMetronet(exp, os);
    for (auto& s : metro.getStations()) {
        Station* station = s.second;
        metro.opstappenAfStappen(station->getNaam(), exp, os);
    }
}