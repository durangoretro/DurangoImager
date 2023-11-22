/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */
#include "durangorom.h"

DurangoRom::DurangoRom()
{
    DurangoRom("","");
}
DurangoRom::DurangoRom(std::string path,std::string name){
    this->setPath(path);
    this->setName(name);
}

void DurangoRom::setName(std::string name){
    this->name=name;
}

void DurangoRom::setPath(std::string path){
    this->path=path;
}

std::string DurangoRom::getName(){
    return this->name;
}

std::string DurangoRom::getPath(){
    return this->path;
}
DurangoHeader DurangoRom::getHeader(){
    return this->header;
}

void DurangoRom::setHeader(DurangoHeader header){
    this->header=header;
}

DurangoRom * DurangoRom::readDurangoROMFile(std::string path){

    std::string fileName= path.substr(path.find_last_of("/")+1);
    DurangoHeader* header = DurangoHeader::ReadDurangoHeader(path);
    DurangoRom* rom =  new DurangoRom(path,fileName);
    rom->setHeader(*header);
    return rom;
}

