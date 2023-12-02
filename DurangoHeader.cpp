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

DurangoHeader* DurangoHeader::readDurangoHeader(char * headerInfo){
    durangoHeaderInfo durangoHeaderInformation;
    //Signature
    char signature[3]={headerInfo[1],headerInfo[2],'\0'};
    fprintf(stderr,"Signature...%s\n",signature);
    durangoHeaderInformation.signature=readSignature(signature);
    //Read ROM Name
    int i = 8;
    int currentChar=0;
    fprintf(stderr,"Reading Rom Name...\n");
    //Read Free Space
    if(durangoHeaderInformation.signature==DurangoSignature::DL){
        strncpy(durangoHeaderInformation.filename,"FreeSpace",currentChar+9);
        currentChar+=9;
    }else{
        char romName[30];
        for(;headerInfo[i]!='\0';i++){
            romName[currentChar]=headerInfo[i];
            currentChar++;
        }
        strncpy(durangoHeaderInformation.filename,romName,currentChar+1);
        fprintf(stderr,"Readed Rom Name...%s\n",romName);

    }
    i++;//next character
    //Read Comment
    char comment[220];
    currentChar=0;
    for(;headerInfo[i]!='\0';i++){
        comment[currentChar]=headerInfo[i];
        currentChar++;
    }
    strncpy(durangoHeaderInformation.comment,comment,currentChar+1);
    fprintf(stderr,"Readed Rom Comment...%s\n",comment);
    //Step to user Field 1
    i=230;
    char userField1[8];
    currentChar=0;
    for(;i<239;i++){
        userField1[currentChar]=headerInfo[i];
        currentChar++;
    }
    fprintf(stderr,"Readed User Field 1...%s\n",userField1);
    strncpy(durangoHeaderInformation.userField1,userField1,8);
    currentChar=0;
    char userField2[8];
    for(;i<247;i++){
        userField2[currentChar]=headerInfo[i];
        currentChar++;
    }
    fprintf(stderr,"Readed User Field 2...%s\n",userField2);
    strncpy(durangoHeaderInformation.userField2,userField2,8);
    fprintf(stderr,"Finish Read User Fields\n");

    //Read Version
    int version = ((int)headerInfo[247]<<16)| ((int)headerInfo[248]<<8) | headerInfo[249];
    //Read date
    short date = ((short)headerInfo[250]<<8)| headerInfo[251];
    //Read time
    short time = ((short)headerInfo[252]<<8)| headerInfo[253];
    durangoHeaderInformation.time=time;
    durangoHeaderInformation.date=date;
    durangoHeaderInformation.version=version;
    return new DurangoHeader(durangoHeaderInformation);
}

DurangoHeader * DurangoHeader::ReadDurangoHeader(std::string path){

    std::ifstream * romFile = new std::ifstream(path.c_str(),std::ios::binary);
    //Read Rom Header
    romFile->seekg(0,romFile->beg);
    char header[256];
    romFile->read(header,256);
    romFile->close();
    //Read DurangoHeader from array content
    return readDurangoHeader(header);
}

DurangoSignature readSignature(char* signature){

    if(strcmp(signature,"dX")==0){
        return DurangoSignature::DX;
    }
    if(strcmp(signature,"pX")==0){
        return DurangoSignature::PX;
    }
    if(strcmp(signature,"dA")==0){
        return DurangoSignature::DA;
    }
    if(strcmp(signature,"dL")==0){
        return DurangoSignature::DL;
    }
    if(strcmp(signature,"dR")==0){
        return DurangoSignature::DR;
    }
    if(strcmp(signature,"dS")==0){
        return DurangoSignature::DS;
    }
    if(strcmp(signature,"dr")==0){
        return DurangoSignature::Dr;
    }
    if(strcmp(signature,"ds")==0){
        return DurangoSignature::Ds;
    }
    return DurangoSignature::INVALID;
}

durangoHeaderInfo DurangoHeader::getHeaderInformation(){
    return this->headerInformation;
}
