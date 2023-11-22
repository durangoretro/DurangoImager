/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

#include "durangoimagercontroller.h"
#include <fstream>

DurangoImagerController::DurangoImagerController()
{
    this->RomList = new std::vector<DurangoRom*>();
    this->destinationFile= "";
}

void DurangoImagerController::addRomFile(DurangoRom * rom){
    this->RomList->push_back(rom);
}

void DurangoImagerController::removeRomFile(int index){
    this->RomList->erase(this->RomList->begin()+index);
}

DurangoImagerController::~DurangoImagerController(){
    delete RomList;

}

void DurangoImagerController::storeDestinationPath(std::string path){
    this->destinationFile=path;
}

bool DurangoImagerController::hastDestination(){
    return !this->destinationFile.empty();
}

void DurangoImagerController::setEmptyEndSpace(bool emptySpace){
    this->addEmptySpace=emptySpace;
}

void DurangoImagerController::createVolume(){
    std::ofstream * durangoVolume = new std::ofstream(this->destinationFile.c_str(),std::ofstream::trunc|std::ofstream::binary);
    for(unsigned int i=0;i<this->RomList->size();i++){

        std::ifstream * currentFile= new std::ifstream(RomList->data()[i]->getPath().c_str(),std::ifstream::binary);
        currentFile->seekg(0,currentFile->end);
        size_t length = currentFile->tellg();
        currentFile->seekg(0,currentFile->beg);
        char * buffer=new char[length];
        currentFile->read(buffer,length);
        durangoVolume->write(buffer,length);
        delete[] buffer;
        currentFile->close();
     }
    durangoVolume->close();
}
