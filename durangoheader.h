#ifndef DURANGOHEADER_H
#define DURANGOHEADER_H
#include <string>


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
    char    filename[30];
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
    short     version;
    /**
     * @brief date modification date in FAT format
     */
    short  date;
    /**
     * @brief time modification time in FAT format
     */
    short  time;
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

private:
    /**
     * @brief headerInformation Header Information
     */
    durangoHeaderInfo headerInformation;
};

#endif // DURANGOHEADER_H
