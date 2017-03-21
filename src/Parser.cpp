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

SuccessEnum Parser::setup(Metronet& metro, std::string filename, std::ostream& os){
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str())) {
        os << "ERROR: Kan bestand " + filename + " niet openen.\n";
        return BadImport;
    }
    TiXmlElement* root = doc.FirstChildElement();
    std::string rootName;
    if (root != NULL) rootName = root->Value();
    else {
        os << "ERROR: Er is geen root.\n";
        return BadImport;
    }
    if (!(rootName == "ROOT" || rootName == "METRONET")) {
        os << "ERROR: Geen root gevonden. Gelieve een root object genaamd "
           << "<ROOT> of <METRONET> aan te maken.\n";
        return BadImport;
    }

    SuccessEnum endResult = Success;
    // Iterate over all elements
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        std::string elemName = elem->Value();
        if(elemName == "STATION") {
            std::string attrName;
            std::string name = "";
            std::string vor = "";
            std::string volg = "";
            int opstappen = 0;
            int afstappen = 0;
            int spoor = -1;
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
                    else if(attrName == "spoor") {
                        if (std::stoi(t) >= 0) spoor = std::stoi(t);
                    }
                    else if(attrName == "opstappen") {
                        if (std::stoi(t) >= 0) opstappen = std::stoi(t);
                        else throw std::invalid_argument("");
                    }
                    else if(attrName == "afstappen") {
                        if (std::stoi(t) >= 0) afstappen = std::stoi(t);
                        else throw std::invalid_argument("");
                    }
                    else{
                        std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                        exp->write(out, os);
                        endResult = PartialImport;
                    }
                }
                if(name == "" or vor == "" or volg == "" or spoor == -1){
                    std::string out = "ERROR: Station mist een attribuut.\n";
                    exp->write(out, os);
                    endResult = PartialImport;
                    continue;
                }
                Station* station = new Station(name, vor, volg, spoor, opstappen, afstappen);
                metro.addStation(station);
                metro.addSpoor(spoor);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Station niet toegevoegd.\n";
                exp->write(out, os);
                endResult = PartialImport;
                continue;
            }
        }
        else if(elemName == "TRAM"){
            std::string attrName;
            int zitpl = -1;
            int snelh = -1;
            int spoor = -1;
            std::string beginS = "";
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
                        endResult = PartialImport;
                        exp->write(out, os);
                    }
                }
                if(zitpl == -1 or snelh == -1 or spoor == -1 or beginS == ""){
                    std::string out = "ERROR: Tram mist een attribuut.\n";
                    exp->write(out, os);
                    endResult = PartialImport;
                    continue;
                }
                Tram* tram = new Tram(zitpl, snelh, spoor, beginS);
                metro.addTram(tram);
                metro.addSpoor(spoor);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Tram niet toegevoegd.\n";
                exp->write(out, os);
                endResult = PartialImport;
                continue;
            }

        } else {
            continue;
        }
    }

    return endResult;
}