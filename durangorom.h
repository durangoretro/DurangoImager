#ifndef DURANGOROM_H
#define DURANGOROM_H

#include"durangoheader.h"
/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

#include <string>


/**
 * @brief The DurangoRom class. Contains all the information from a Durango ROM.
 * @author Durango Computer Team (Victor Suarez)
 * @version 1.0 (Nov 2023).
 */
class DurangoRom
{
public:

    /**
     * @brief getName Get The current Name
     * @return Current name
     */
    std::string getName();
    /**
     * @brief setName Set the current Name
     * @param name Current Name
     */
    void setName(std::string name);

    /**
     * @brief getHeader get Header Info
     * @return Header Info
     */
    DurangoHeader getHeader();

    /**
     * @brief setHeader Set header Info
     * @param header Header Info
     */
    void setHeader(DurangoHeader header);

    /**
     * @brief getRomSize Get Current Rom Size
     * @return Rom Size in Bytes
     */
    size_t getRomSize();

    /**
     * @brief getRomContent Get the current Rom Content
     * @return Char Array Pointer to the Rom COntent (check RomSize for array length).
     */
    char * getRomContent();


    /**
     * @brief readDurangoROMFile Read an existing Durango ROM FIle from a File path
     * @param path Durango ROm File Path
     * @return Pointer to a new DurangoRom Object with all the information
     */
    static DurangoRom * readDurangoROMFile(std::string path);

    /**
     * @brief readDurangoROMFile Read an existing Durango Rom File Information from the content
     * @param romContent Durango Rom Content (including header)
     * @param romSize Durango Rom File Size in Bytes
     * @return Pointer to a new DurangoRom Object
     */
    static DurangoRom* readDurangoROMFile(char * romContent, size_t romSize);
private:
    /**
     * @brief name Rom Name
     */
    std::string name;

    /**
     * @brief romContent Rom Content
     */
    char * romContent;

    /**
     * @brief romSize Rom size in Bytes
     */
    size_t romSize;
    /**
     * @brief header DurangoHeader
     */
    DurangoHeader header;

};

#endif // DURANGOROM_H
