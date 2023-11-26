/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */
#include "durangorom.h"
#include <cstring>
#include <fstream>



void DurangoRom::setName(std::string name){
    this->name=name;
}


std::string DurangoRom::getName(){
    return this->name;
}

DurangoHeader DurangoRom::getHeader(){
    return this->header;
}

void DurangoRom::setHeader(DurangoHeader header){
    this->header=header;
}

size_t DurangoRom::getRomSize(){
    return this->romSize;
}

char * DurangoRom::getRomContent(){
    return this->romContent;
}

DurangoRom * DurangoRom::readDurangoROMFile(std::string path){

    std::string fileName= path.substr(path.find_last_of("/")+1);
    //Read Rom From disck
    std::ifstream * romFile = new std::ifstream(path.c_str(),std::ios::binary);
    romFile->seekg(0,romFile->end);
    //get Rom Size
    size_t romSize= romFile->tellg();
    romFile->seekg(0,romFile->beg);
    //Read all the rom content
    char* content = new char[romSize];
    romFile->read(content,romSize);
    romFile->close();
    return readDurangoROMFile(content, romSize);
}

DurangoRom* DurangoRom::readDurangoROMFile(char * romContent, size_t romSize){
    DurangoRom* rom =  new DurangoRom();
    rom->romContent=romContent;
    rom->romSize=romSize;
    //Copy Header Info (first 256 bytes)
    char headercontent[256];
    memcpy(headercontent,romContent,256);
    DurangoHeader* header = DurangoHeader::readDurangoHeader(headercontent);
    rom->setHeader(*header);
    rom->setName(header->getHeaderInformation().filename);
    return rom;
}

