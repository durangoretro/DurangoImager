#ifndef DURANGOIMAGERCONTROLLER_H
#define DURANGOIMAGERCONTROLLER_H

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
private:
    /**
     * @brief RomList Vector Containing all the Roms File in the current session.
     */
    std::vector<DurangoRom*> * RomList;
};

#endif // DURANGOIMAGERCONTROLLER_H
