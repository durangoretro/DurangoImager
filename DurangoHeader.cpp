#include "durangoheader.h"
#include <cstring>
#include <fstream>

/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

DurangoSignature readSignature(char*);

DurangoHeader::DurangoHeader(){
    durangoHeaderInfo header;
    this->headerInformation=header;
}
DurangoHeader::DurangoHeader(durangoHeaderInfo durangoHeaderInformation){
    this->headerInformation=durangoHeaderInformation;
}

DurangoHeader * DurangoHeader::ReadDurangoHeader(std::string path){
    durangoHeaderInfo durangoHeaderInformation;
    std::ifstream * romFile = new std::ifstream(path.c_str(),std::ios::binary);
    //Read Rom Header
    romFile->seekg(0,romFile->beg);
    char header[256];
    romFile->read(header,256);
    //Signature
    char signature[3]={header[1],header[2],'\0'};
    durangoHeaderInformation.signature=readSignature(signature);
    //Read ROM Name
    char romName[30];
    int currentChar=0;
    int i = 8;
    for(;header[i]!='\0';i++){
        romName[currentChar]=header[i];
        currentChar++;
    }
    strcpy(durangoHeaderInformation.filename,romName);
    i++;//next character
    //Read Comment
    char comment[220];
    currentChar=0;
    for(;header[i]!='\0';i++){
        comment[currentChar]=header[i];
        currentChar++;
    }
    strcpy(durangoHeaderInformation.comment,comment);
    //Step to user Field 1
    i=230;
    char userField1[8];
    currentChar=0;
    for(;i<239;i++){
        userField1[currentChar]=header[i];
        currentChar++;
    }
    strcpy(durangoHeaderInformation.userField1,userField1);
    i++;//Next Char
    char userField2[8];
    currentChar=0;
    for(;i<247;i++){
        userField2[currentChar]=header[i];
        currentChar++;
    }
    strcpy(durangoHeaderInformation.userField2,userField2);
    //Read Version
    int version = ((int)header[247]<<16)| ((int)header[248]<<8) | header[249];
    //Read date
    short date = ((short)header[250]<<8)| header[251];
    //Read time
    short time = ((short)header[252]<<8)| header[253];
    durangoHeaderInformation.time=time;
    durangoHeaderInformation.date=date;
    durangoHeaderInformation.version=version;
    return new DurangoHeader(durangoHeaderInformation);
}

DurangoSignature readSignature(char* signature){

    if(strcmp(signature,"dX")==0){
        return DurangoSignature::DX;
    }
    if(strcmp(signature,"pX")==00){
        return DurangoSignature::PX;
    }
    if(strcmp(signature,"dA")==00){
        return DurangoSignature::DA;
    }
    if(strcmp(signature,"dL")==00){
        return DurangoSignature::DL;
    }
    if(strcmp(signature,"dR")==00){
        return DurangoSignature::DR;
    }
    if(strcmp(signature,"dS")==00){
        return DurangoSignature::DS;
    }
    if(strcmp(signature,"dr")==00){
        return DurangoSignature::Dr;
    }
    if(strcmp(signature,"ds")==00){
        return DurangoSignature::Ds;
    }
    return DurangoSignature::INVALID;
}

durangoHeaderInfo DurangoHeader::getHeaderInformation(){
    return this->headerInformation;
}
