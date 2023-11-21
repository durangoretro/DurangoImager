#include "durangoimagercontroller.h"
#include <fstream>

DurangoImagerController::DurangoImagerController()
{
    this->RomList = new std::vector<DurangoRom*>();
    this->destinationFile= new std::string();
}

void DurangoImagerController::addRomFile(DurangoRom * rom){
    this->RomList->push_back(rom);
}

void DurangoImagerController::removeRomFile(int index){
    this->RomList->erase(this->RomList->begin()+index);
}

DurangoImagerController::~DurangoImagerController(){
    delete RomList;
    delete destinationFile;
}

void DurangoImagerController::storeDestinationPath(std::string* path){
    this->destinationFile=path;
}

void DurangoImagerController::createVolume(){
    std::ofstream * durangoVolume = new std::ofstream(destinationFile->c_str(),std::ofstream::binary);
    for(unsigned int i=0;i<this->RomList->size();i++){
        std::ifstream * currentFile= new std::ifstream(RomList->data()[i]->getName().c_str(),std::ifstream::binary);
        char * buffer=new char[1024];
        while(!currentFile->eof()){
            currentFile->read(buffer,1024);
            *durangoVolume<<buffer;
        }
        delete[] buffer;
        currentFile->close();
     }
    durangoVolume->close();
}
