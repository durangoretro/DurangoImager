#include "durangoimagercontroller.h"

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
