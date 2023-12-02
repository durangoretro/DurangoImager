/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

#include "durangoimagercontroller.h"
#include "durangorom.h"
#include <cstring>
#include <fstream>


DurangoImagerController::DurangoImagerController()
{
    this->RomList = new std::vector<DurangoRom*>();
    this->destinationFile= "";
    this->addEmptySpace=false;
    this->emptyspace=0;
}

std::string DurangoImagerController::addRomFile(std::string path){
    fprintf(stderr,"Adding Path %s\n", path.c_str());
    DurangoRom * durangoROM= DurangoRom::readDurangoROMFile(path);
    this->RomList->push_back(durangoROM);
    return durangoROM->getName();
}

void DurangoImagerController::removeRomFile(int index){
    this->RomList->erase(std::next(this->RomList->begin(),index));
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

void DurangoImagerController::setEmptySpaceSize(long emptySpaceSize){
    this->emptyspace=emptySpaceSize;
}

emptySpaceStruct DurangoImagerController::createEmptySpace(size_t emptySpaceSize){
    fprintf(stderr,"Creating Empty Space...Size: %lu\n",emptySpaceSize);
    emptySpaceStruct space;
    char* emptySpaceContent=new char[emptySpaceSize];
    char header[256];
    //fill header
    std::fill_n(header,256,0x00);
    //fill content
    std::fill_n(emptySpaceContent,emptySpaceSize,0xFF);
    //set as empty space signature
    header[1]='d';
    header[2]='L';
    header[7]=13;
    // add size to header
    //TODO Review how to store
    header[252]=emptySpaceSize&0xFF;
    header[253]=(emptySpaceSize>>8)&0xFF;
    header[254]=(emptySpaceSize>>16);

    //copy header in content
    memcpy(emptySpaceContent,header,256);
    space.emptySpaceContent=emptySpaceContent;
    space.emptySpaceSize=emptySpaceSize;
    return space;
}

std::vector<std::string> DurangoImagerController::openExistingVolume(std::string path){
    //Read Volume File
    fprintf(stderr,"Reading Volume File...%s\n",path.c_str());
    std::ifstream * volumeFile = new std::ifstream(path.c_str(),std::ios::binary);
    volumeFile->seekg(0,volumeFile->end);
    size_t volumeSize = volumeFile->tellg();
    volumeFile->seekg(0,volumeFile->beg);
    char * volumeContent = new char[volumeSize];
    volumeFile->read(volumeContent,volumeSize);
    fprintf(stderr,"Readed Volume File...%s\n",path.c_str());
    volumeFile->close();
    //get Each Rom
    std::vector<unsigned long> romPositions;
    std::vector<std::string> romNames;
    for(unsigned long i=0;i<volumeSize-1;i++){
        //if found a Durango Executable
        if(volumeContent[i]=='d' && volumeContent[i+1]=='X'){
            romPositions.push_back(i-1);
        }
        //Empty Space
        if(volumeContent[i]=='d' && volumeContent[i+1]=='L'){
            romPositions.push_back(i-1);
        }
        //TODO: Other File Types
    }
    romPositions.push_back(volumeSize);
    for(size_t i=0;i<romPositions.size()-1;i++){
        unsigned long initrompos = romPositions.data()[i];
        unsigned long endrompos = romPositions.data()[i+1]-1;
        unsigned long romSize = endrompos-initrompos;
        char * romContent = new char[romSize];
        memcpy(romContent,volumeContent+initrompos,romSize);
        //Read and create Rom
        DurangoRom * rom = DurangoRom::readDurangoROMFile(romContent,romSize);
        RomList->push_back(rom);
        romNames.push_back(rom->getName());
    }
    return romNames;
}

void DurangoImagerController::createVolume(){

    fprintf(stderr,"Creaing Volume File...%s\n",this->destinationFile.c_str());
    std::ofstream * durangoVolume = new std::ofstream(this->destinationFile.c_str(),std::ios::binary|std::ios::trunc);
    for(unsigned int i=0;i<this->RomList->size();i++){

        DurangoRom * currentRom = this->RomList->data()[i];
        durangoVolume->write(currentRom->getRomContent(),currentRom->getRomSize());
     }
    // create empty Space (If needed)
     if(addEmptySpace){
       emptySpaceStruct emptyspc= createEmptySpace(emptyspace);
       durangoVolume->write(emptyspc.emptySpaceContent,emptyspc.emptySpaceSize);

     }
    durangoVolume->close();
}


