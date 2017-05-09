//
// Created by sergio on 24/03/17.
//

#include "Parser.h"

Parser::Parser() {
    initCheck = this;
    ENSURE(this->properlyInitialised(),
           "Parser is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Parser::Parser(Exporter* exp) {
    Parser::exp = exp;
    initCheck = this;
    ENSURE(this->properlyInitialised(),
           "Parser is niet in de juiste staat geëindigd na aanroep van de constructor.");
}

Parser& Parser::operator=(const Parser& rhs) {
    if (this != &rhs) {
        this->exp = rhs.exp;
        this->initCheck = this;
    }
    ENSURE(this->properlyInitialised(),
           "Parser is niet in de juiste staat geëindigd na aanroep van de copy assignment.");
    return *this;
}

bool Parser::properlyInitialised() const {
    return initCheck == this;
}

SuccessEnum Parser::setup(Metronet& metronet, std::string filename, std::ostream& os){
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str())) {
        std::string out = "ERROR: Kan bestand " + filename + " niet openen.\n";
        exp->write(out, os);
        return BadImport;
    }
    TiXmlElement* root = doc.FirstChildElement();
    std::string rootName;
    if (root != NULL) rootName = root->Value();
    else {
        std::string out = "ERROR: Geen root gevonden. Gelieve een root object genaamd <ROOT> of <METRONET> aan te maken.\n";
        exp->write(out, os);
        return BadImport;
    }
    if (!(rootName == "ROOT" || rootName == "METRONET")) {
        std::string out = "ERROR: Geen root gevonden. Gelieve een root object genaamd <ROOT> of <METRONET> aan te maken.\n";
        exp->write(out, os);
        return BadImport;
    }

    SuccessEnum endResult = Success;
    // Iterate over all elements
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
        std::string elemName = elem->Value();
        if(elemName == "STATION") {
            std::string attrName;
            std::string type = "";
            std::string name = "";
            std::map<int, std::string> vorigeStations;
            std::map<int, std::string> volgendeStations;
            try {
                for(TiXmlNode* node = elem->FirstChild(); node != NULL; node = node->NextSibling()){
                    attrName = node->Value();
                    TiXmlText* text;
                    std::string t;
                    if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                    else continue;
                    if(text != NULL) t = text->Value();
                    else continue;
                    if (attrName == "naam") name = t;
                    else if (attrName == "type") {
                        if (t == "Metrostation" or t == "Halte") type = t;
                        else {
                            std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Station niet toegevoegd.\n";
                            exp->write(out, os);
                            endResult = PartialImport;
                        }
                    } else{
                        std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                        exp->write(out, os);
                        endResult = PartialImport;
                    }
                }
                for (TiXmlElement* spoorElem = elem->FirstChildElement();
                     spoorElem != NULL; spoorElem = spoorElem->NextSiblingElement()) {
                    int spoor = -1;
                    std::string vorige = "";
                    std::string volgende = "";
                    for(TiXmlNode* node = spoorElem->FirstChild(); node != NULL; node = node->NextSibling()){
                        attrName = node->Value();
                        TiXmlText* text;
                        std::string t;
                        if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                        else continue;
                        if(text != NULL) t = text->Value();
                        else continue;
                        if (attrName == "spoor") spoor = std::stoi(t);
                        else if (attrName == "vorige") vorige = t;
                        else if (attrName == "volgende") volgende = t;
                        else {
                            std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                            exp->write(out, os);
                            endResult = PartialImport;
                        }
                    }
                    if (spoor == -1 or vorige == "" or volgende == "") {
                        std::string out = "ERROR: Spoor mist een attribuut.\n";
                        exp->write(out, os);
                        endResult = PartialImport;
                        continue;
                    }
                    vorigeStations[spoor] = vorige;
                    volgendeStations[spoor] = volgende;
                    metronet.addSpoor(spoor);
                }
                if(name == "" or type == "" or vorigeStations.size() != volgendeStations.size()){
                    std::string out = "ERROR: Station mist een attribuut.\n";
                    exp->write(out, os);
                    endResult = PartialImport;
                    continue;
                }
                metronet.addStation(name, type, vorigeStations, volgendeStations);
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
            std::string type;
            int voertuigNr = -1;
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
                    else if(attrName == "type") {
                        if (t == "Albatros" or t == "PCC") type = t;
                        else {
                            std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Tram niet toegevoegd.\n";
                            exp->write(out, os);
                            endResult = PartialImport;
                        }
                    }
                    else if(attrName == "voertuigNr") voertuigNr = stoi(t);
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
                if (!metronet.bevatStation(beginS)){
                    endResult = PartialImport;
                    continue;
                }
                if(!metronet.getStation(beginS)->bevatSpoor(spoor)){
                    endResult = PartialImport;
                    continue;
                }
                metronet.addTram(zitpl, snelh, spoor, voertuigNr, type, beginS);
                metronet.addSpoor(spoor);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Tram niet toegevoegd.\n";
                exp->write(out, os);
                endResult = PartialImport;
                continue;
            }
        } else if (elemName == "PASSAGIER") {
            std::string attrName;
            std::string naam;
            std::string beginS = "";
            std::string eindS = "";
            int hoeveelheid = -1;
            try {
                for(TiXmlNode* node = elem->FirstChild(); node != NULL; node = node->NextSibling()){
                    attrName = node->Value();
                    TiXmlText* text;
                    std::string t;
                    if(node->FirstChild() != NULL) text = node->FirstChild()->ToText();
                    else continue;
                    if(text != NULL) t = text->Value();
                    else continue;
                    if(attrName == "naam") naam = t;
                    else if(attrName == "beginStation") beginS = t;
                    else if(attrName == "eindStation") eindS = t;
                    else if(attrName == "hoeveelheid"){
                        hoeveelheid = stoi(t);
                        if(hoeveelheid < 0) throw std::invalid_argument("Negatief aantal passagiers.");
                    }
                    else{
                        std::string out = "ERROR: Onherkenbaar attribuut '" + attrName + "' wordt overgeslaan.\n";
                        endResult = PartialImport;
                        exp->write(out, os);
                    }
                }
                if(naam == "" or beginS == "" or eindS == "" or hoeveelheid == -1){
                    std::string out = "ERROR: Passagier mist een attribuut.\n";
                    exp->write(out, os);
                    endResult = PartialImport;
                    continue;
                }
                metronet.addPassagier(naam, beginS, eindS, hoeveelheid);
            }
            catch(std::invalid_argument& ex) {
                std::string out = "ERROR: Attribuut '" + attrName + "' heeft een foute waarde. Passagier niet toegevoegd.\n";
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