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

