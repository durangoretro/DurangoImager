#include "durangoheader.h"
#include <cstring>
#include <fstream>




/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

DurangoSignature readSignature(char*);

DurangoHeader::DurangoHeader(){

}
DurangoHeader::DurangoHeader(durangoHeaderInfo durangoHeaderInformation){
    this->headerInformation=durangoHeaderInformation;
}

DurangoHeader* DurangoHeader::readDurangoHeader(char * headerInfo){
    durangoHeaderInfo durangoHeaderInformation;
    //Signature
    char signature[3]={headerInfo[SIGNATURE_POS],headerInfo[SIGNATURE_POS+1],'\0'};
    fprintf(stderr,"Signature...%s\n",signature);
    durangoHeaderInformation.signature=readSignature(signature);
    //Read ROM Name
    int i = ROM_NAME_POS;
    int currentChar=0;
    fprintf(stderr,"Reading Rom Name...\n");
    //Read Free Space
    if(durangoHeaderInformation.signature==DurangoSignature::DL){
        strncpy(durangoHeaderInformation.filename,"FreeSpace",currentChar+9);
        currentChar+=9;
    }else{
        char romName[220];
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
    char userField1[USER_FIELD_LEGNTH];
    memcpy(userField1,headerInfo+USER_FIELD1_POS,USER_FIELD_LEGNTH);
    fprintf(stderr,"Readed User Field 1...%s\n",userField1);
    strncpy(durangoHeaderInformation.userField1,userField1,USER_FIELD_LEGNTH);
    char userField2[USER_FIELD_LEGNTH];
    memcpy(userField2,headerInfo+USER_FIELD2_POS,USER_FIELD_LEGNTH);
    fprintf(stderr,"Readed User Field 2...%s\n",userField2);
    strncpy(durangoHeaderInformation.userField2,userField2,USER_FIELD_LEGNTH);
    fprintf(stderr,"Finish Read User Fields\n");

    //Read Version
    byte version = (headerInfo[VERSION_POS+1]>>4);
    byte revision = (headerInfo[VERSION_POS+1] & 0x0F) | (headerInfo[VERSION_POS] & 0x30);
    byte build = headerInfo[VERSION_POS] & 0x0F;
    //Read date
    byte day =  headerInfo[DATE_POS] & 0x1F;
    byte month = (headerInfo[DATE_POS+1] & 1)<<3 | headerInfo[DATE_POS]>>5;
    byte year = headerInfo[DATE_POS+1]>>1;
    //Read time
    byte hour = headerInfo[DATE_POS+1]>>3;
    byte minute = (headerInfo[DATE_POS+1] & 0x07)<<3 | headerInfo[DATE_POS]>>5;
    byte second = (headerInfo[DATE_POS] & 0x1F)<<1;
    //read Size
    u_int32_t size = headerInfo[SIZE_POS] | headerInfo[SIZE_POS+1]<<8 | headerInfo[SIZE_POS+2]<<16;

    durangoHeaderInformation.day=day;
    durangoHeaderInformation.month=month;
    durangoHeaderInformation.year=year;
    durangoHeaderInformation.hour=hour;
    durangoHeaderInformation.minute=minute;
    durangoHeaderInformation.seconds=second;
    durangoHeaderInformation.version=version;
    durangoHeaderInformation.revision=revision;
    durangoHeaderInformation.build=build;
    durangoHeaderInformation.size=size;
    return new DurangoHeader(durangoHeaderInformation);
}

DurangoHeader * DurangoHeader::ReadDurangoHeader(std::string path){

    std::ifstream * romFile = new std::ifstream(path.c_str(),std::ios::binary);
    //Read Rom Header
    romFile->seekg(0,romFile->beg);
    char header[HEADER_SIZE];
    romFile->read(header,HEADER_SIZE);
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

char * DurangoHeader::generateHeader(){
    char * header=new char[HEADER_SIZE];
    //Empty Header array Content
    std::fill_n(header,HEADER_SIZE,0);
    int src,dest;
    //Magic Numbers
    header[MAGIC_1]=0;
    header[MAGIC_2]=13;
    header[MAGIC_3]=0;
    //Signature
    //TODO: Write Signature
    //Name
    src=0;
    dest=ROM_NAME_POS;
    while(this->headerInformation.filename[src]){
        header[dest++]=this->headerInformation.filename[src++];
    }
    header[dest++]=0;
    //Comment
    src=0;
    while (this->headerInformation.comment[src]){
        header[dest++]=this->headerInformation.comment[src++];
    }
    header[dest++]=0;
    //User Field 1
    memcpy(header+USER_FIELD1_POS,this->headerInformation.userField1,USER_FIELD_LEGNTH);
    //User Field 2
    memcpy(header+USER_FIELD2_POS,this->headerInformation.userField2,USER_FIELD_LEGNTH);
    //TODO: Add other Information

        //        p[dest++] = h->comment[src++];					// copy comment
        //    p[dest++] = 0;


                            // ...and terminator (skipping it)
//    while (dest<H_LIB)		p[dest++] = 0xFF;			// safe padding
//    //	dest = H_LIB;										// library commit offset
//    for (src=0;src<8;src++)	p[dest++] = h->lib[src];	// copy library commit
//    //	dest = H_COMMIT;									// main commit offset (already there)
//    for (src=0;src<8;src++)	p[dest++] = h->commit[src];	// copy main commit afterwards
//    switch(h->phase) {
//    case 'a':
//        bits = 0;		// alpha				%00hhbbbb
//        break;
//    case 'b':
//        bits = 0x40;	// beta					%01hhbbbb
//        break;
//    case 'R':
//        bits = 0x80;	// Release candidate	%10hhbbbb
//        break;
//    case 'f':
//    default:
//        bits = 0xC0;	// final				%11hhbbbb
//    }
//    p[H_VERSION]	=	bits | (h->revision & 0x30)| h->build;
//    p[H_VERSION+1]	=	(h->version << 4) | (h->revision & 0x0F);		// coded version number
//    p[H_TIME]		=	((h->minute << 5) & 0xFF) | (h->second >> 1);
//    p[H_TIME+1]		=	(h->hour << 3) | (h->minute >> 3);				// coded time
//    p[H_DATE]		=	((h->month << 5) & 0xFF) | h->day;
//    p[H_DATE+1]		=	(h->year << 1) | (h->month >> 3);				// coded date
//    p[H_SIZE]		=	h->size & 0xFF;
//    p[H_SIZE+1]		=	(h->size >> 8) & 0xFF;
//    p[H_SIZE+2]		=	h->size >> 16;
    return header;
}
