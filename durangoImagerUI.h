#ifndef DURANGOIMAGERUI_H
#define DURANGOIMAGERUI_H

#include "durangoimagercontroller.h"
#include <QMainWindow>
/**
 * NameSpace for use with the UI Interface.
 */
namespace Ui {
class DurangoImager;
}
/**
 * @brief The DurangoImager class This class Contains all the needed logic for interact with the User Interface.
 * @author Durango Computer Team (Victor Suarez)
 * @version 1.0(Nov 2023).
 */
class DurangoImager : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief DurangoImager Class Constructor
     * @param parent Current Parent Widget.
     */
    explicit DurangoImager(QWidget *parent = nullptr);
    ~DurangoImager();
private slots:
    /**
     * @brief addItem Slot Used when a new Item is added.
     * @param fileAdded Rom Name to store in the ListWidget.
     */
    void addItem(std::string fileAdded);
    /**
     * @brief addFileButtonPressed This slot is used when the Add File Button is pressed. This Slot open a "openFile" dialog.
     */
    void addFileButtonPressed();
    /**
     * @brief removeItem Remove the selected Items from ListWidget and controller.
     */
    void removeItem();
    /**
     * @brief addSpace This Slot is launched when the Add Space CheckBox is checked or Unchecked
     * @param state current State @see Qt::CheckState for more information
     */
    void addSpace(int state);
signals:
    /**
     * @brief itemAdded This signal is emited when a new file is selected from de Open File Dialog.
     * @param fileAdded Rom File Name to be added.
     */
    void itemAdded(std::string fileAdded);
private:
    /**
     * @brief ui Current UI Setup
     */
    Ui::DurangoImager *ui;
    /**
     * @brief controller Durango Imager Controller.
     */
    DurangoImagerController * controller;
};

#endif // DURANGOIMAGERUI_H