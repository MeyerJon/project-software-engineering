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
    std::map<std::string, Station> parsedStations;
    TiXmlDocument doc;
    doc.LoadFile(filename);
    TiXmlElement* root = doc.FirstChildElement();
    // Iterate over all elements
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        if(elem->Value() == "STATION") {
            std::string attrName;
            try {
                for(TiXmlNode* node = elem->FirstChild(); node != NULL; node = node->NextSibling()){
                    attrName = node->Value();
                    TiXmlText* text;
                    std::string t;
                    if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                    else continue;
                    if(text != NULL) t = text->Value();
                    else continue;
                    if(attrName == "naam")
                }
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