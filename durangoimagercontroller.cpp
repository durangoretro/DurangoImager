#include "durangoimagercontroller.h"

DurangoImagerController::DurangoImagerController()
{
    this->RomList = new std::vector<DurangoRom*>();
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
