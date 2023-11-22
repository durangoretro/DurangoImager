#ifndef DURANGOIMAGERCONTROLLER_H
#define DURANGOIMAGERCONTROLLER_H


/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

#include "durangorom.h"
#include <vector>

/**
 * @brief Durango Imager Controller Class. Contains the Business Logic of the application.
 * @author Durango Computer Team (Victor Suarez).
 * @version 1.0 (Nov 2023).
 */
class DurangoImagerController
{
public:
    /**
     * @brief DurangoImagerController Default Constructor
     */
    DurangoImagerController();
    /**
     * Destructor
     * */
    ~DurangoImagerController();
    /**
     * @brief addRomFile add a New Rom File to the current Session.
     * @param rom Durango Rom Information
     */
    void addRomFile(DurangoRom * rom);
    /**
     * @brief removeRomFile Remove an existing Rom from the current session.
     * @param index Index inside the list.
     */
    void removeRomFile(int index);

    /**
     * @brief storeDestinationPath Store the destination Path
     * @param path Destination File Path
     */
    void storeDestinationPath(std::string path);
    /**
     * @brief createVolume Create a new Durango Volume File
     */
    void createVolume();

    /**
     * @brief hastDestination Checks if a destination File is selected
     * @return True if the destination File is selected.
     */
    bool hastDestination();

    void setEmptyEndSpace(bool addEmptySpace);
private:
    /**
     * @brief RomList Vector Containing all the Roms File in the current session.
     */
    std::vector<DurangoRom*> * RomList;

    /**
     * @brief destinationFile Store the Destination File Path.
     */
    std::string destinationFile;

    /**
     * @brief addEmptySpace Check if need to add EmptySpace at The end of the Volume.
     */
    bool addEmptySpace;


};

#endif // DURANGOIMAGERCONTROLLER_H
