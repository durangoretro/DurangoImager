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
     * @brief DurangoRom Default Constructor. Store all the information with an Empty String
     */
    DurangoRom();
    /**
     * @brief DurangoRom Class Constructor
     * @param path Durango Rom Path
     * @param name Durango Rom Name.
     */
    DurangoRom(std::string path, std::string name);
    /**
     * @brief getPath Get the current Path
     * @return current Path
     */
    std::string getPath();
    /**
     * @brief setPath Set the current Path
     * @param path Current Path
     */
    void setPath(std::string path);
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
     * @brief readDurangoROMFile Read an existing Durango ROM FIle
     * @param path Durango ROm File Path
     * @return Pointer to a new DurangoRom Object with all the information
     */
    static DurangoRom * readDurangoROMFile(std::string path);
private:
    /**
     * @brief path Rom File Path
     */
    std::string path;
    /**
     * @brief name Rom Name
     */
    std::string name;
    /**
     * @brief header DurangoHeader
     */
    DurangoHeader header;

};

#endif // DURANGOROM_H
