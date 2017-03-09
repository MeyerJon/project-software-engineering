/*
 * Parser.cpp
 *
 *  Created on: 8 Mar 2017
 *      Author: Sergio Fenoll
 */

#include "Parser.h"
#include <map>

Parser::Parser() {
    // TODO Auto-generated constructor stub

}

Parser::~Parser() {
    // TODO Auto-generated destructor stub
}

void Parser::setupStations(Metronet& metro, std::string filename){
    TiXmlDocument doc;
    doc.LoadFile(filename);
    TiXmlElement* root = doc.FirstChildElement();
    // Iterate over all elements
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        if(elem->Value() == "STATION") {
            std::string attrName;
            std::string name;
            std::string vor;
            std::string volg;
            int opstappen;
            int afstappen;
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
                        // TODO: Naar exporter schrijven
                    }
                }
                // TODO: Station* station = new Station(name)
            }
            catch{

            }
        }
    }
}
void Parser::setupTrams(Metronet& metro, std::string filename){

}

void Parser::setup(Metronet& metro, std::string filename) {

}