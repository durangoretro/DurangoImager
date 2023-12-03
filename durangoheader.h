#ifndef DURANGOHEADER_H
#define DURANGOHEADER_H
#include <string>

#define HEADER_SIZE 256

#define SIGNATURE_POS 1

#define ROM_NAME_POS 8

#define USER_FIELD1_POS 230

#define USER_FIELD_LEGNTH 8

#define USER_FIELD2_POS 238

#define VERSION_POS 246

#define DATE_POS 250

#define TIME_POS 248

#define SIZE_POS 252

#define MAGIC_1 0

#define MAGIC_2 7

#define MAGIC_3 255

typedef u_int8_t byte;
typedef u_int16_t word;
typedef u_int32_t dword;





/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

/**
 * @brief The DurangoSignature enum Enumeration for the Durango Rom Header Type
 */
enum DurangoSignature{
    /**
     * Durango Executable*/
    DX,
    /**
     * Durango Generic FIle */
    DA,
    /**
     * Durango Pocket Executable
     */
    PX,
    /**
     * Durango Free Space
     */
    DL,
    /**
     *Colour Screen Dump
     */
    DS,
    /**
     *HIRES screen dump
     **/
    DR,
    /**
     * RLE-compressed HIRES screen dump
     */
    Dr,
    /**
     * RLE-compressed Colour screen dump
     */
    Ds,
    /**
     * Invalid Signature
     */
    INVALID
};



/**
 * Durango Header Struct
 */
typedef struct{
    /**
     * @brief signature ROM Signature
     */
    DurangoSignature signature;
    /**
     * @brief filename ROM internal FileName
     */
    char    filename[220];
    /**
     * @brief comment ROM Comment
     */
    char    comment[220];
    /**
     * @brief userField1 User Field 1
     */
    char    userField1[8];
    /**
     * @brief userField2 User Field 2
     */
    char    userField2[8];
    /**
     * @brief version ROM Version in Little Endian Format
     */
    byte     version;
    /**
     * @brief revision revision Number
     */
    byte    revision;
    /**
     * @brief build Build Number
     */
    byte build;
    /**
     * @brief day modification day in FAT format
     */
    byte  day;
    /**
     * @brief month modification month in FAT format
     */
    byte month;
    /**
     * @brief year modification year in FAT format
     */
    byte year;
    /**
     * @brief hour modification hour in FAT format
     */
    byte hour;
    /**
     * @brief minute modification minute in FAT format
     */
    byte minute;
    /**
     * @brief seconds modification seconds in FAT format
     */
    byte seconds;
    /**
     * @brief size File Size
     */
    u_int32_t size;
}durangoHeaderInfo;
/**
 * @brief The DurangoHeader class Stores the Durango ROM Header Information.
 * @author Durango Computer Team (Victor Suarez)
 * @version 1.0(Nov 2023).
 */
class DurangoHeader{
public:
    /**
     * @brief DurangoHeader Default Class Constructor
     */
    DurangoHeader();
    /**
     * @brief DurangoHeader Class Constructor. Store the durangoHeader Struct
     * @param durangoHeader Durango Header Struct information
     */
    DurangoHeader(durangoHeaderInfo durangoHeader);
    /**
     * @brief getHeaderInformation Get The Header Information Struct
     * @return Header Information Struct
     */
    durangoHeaderInfo getHeaderInformation();
    /**
     * @brief ReadDurangoHeader Read a ROM File and create a new Durango Header Object
     * @param path path of the Durango ROM File
     * @return DurangoHeader Object
     */
    static DurangoHeader * ReadDurangoHeader(std::string path);
    /**
     * @brief readDurangoHeader read a Rom File from the headerINfo Content and create a new Durango Header Object
     * @param headerinfo 256 Bytes char array with the header Info
     * @return DurangoHeaderObject
     */
    static DurangoHeader * readDurangoHeader(char* headerinfo);

    char * generateHeader();

private:
    /**
     * @brief headerInformation Header Information
     */
    durangoHeaderInfo headerInformation;


};

#endif // DURANGOHEADER_H
