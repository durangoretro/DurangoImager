#include "durangoImagerUI.h"
#include "ui_durangoImagerUI.h"
#include <QFileDialog>

DurangoImager::DurangoImager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DurangoImager)
{
    controller = new DurangoImagerController();
    ui->setupUi(this);
    connect(this,SIGNAL(itemAdded(std::string)),this,SLOT(addItem(std::string)));
    connect(ui->addFileButton,SIGNAL(clicked(bool)),this,SLOT(addFileButtonPressed()));
    connect(ui->RemoveFileButton,SIGNAL(clicked(bool)),this, SLOT(removeItem()));
    connect(ui->CheckSpace, SIGNAL(stateChanged(int)),this, SLOT(addSpace(int)));
    connect(ui->destinationButton, SIGNAL(clicked(bool)),this, SLOT(selectDestinationButtonPressed()));
    connect(this, SIGNAL(destinationSelected(std::string)),this, SLOT(storeDestination(std::string)));
    connect(ui->createVolumeButton, SIGNAL(clicked(bool)),this,SLOT(createVolume()));
}

DurangoImager::~DurangoImager()
{
    delete ui;
    delete controller;
}

void DurangoImager::addItem(std::string path){
    std::string fileName= path.substr(path.find_last_of("/")+1);
    controller->addRomFile(new DurangoRom(path,fileName));
    ui->romList->addItem(QString(fileName.c_str()));
}

void DurangoImager::addFileButtonPressed(){
    QString selfilter = tr("Durango Roms (*.dux *.pdx)");
    QString string = QFileDialog::getOpenFileName(this,QString("Add New ROM"),QString(),selfilter,&selfilter);
    if(!string.isEmpty()){
        emit itemAdded(string.toStdString());
    }
}

void DurangoImager::removeItem(){
    QModelIndexList list = ui->romList->selectionModel()->selectedIndexes();
    QModelIndexList::iterator i;
    for(i=list.begin();i!=list.end();i++){
        controller->removeRomFile(i->row());
        ui->romList->removeItemWidget(ui->romList->item(i->row()));
    }
    ui->romList->update();

}

void DurangoImager::addSpace(int state){
    if(state== Qt::CheckState::Checked){
        ui->sizeCombo->setEnabled(true);
    }
    else{
        ui->sizeCombo->setEnabled(false);
    }
}

void DurangoImager::selectDestinationButtonPressed(){
    QString string = QFileDialog::getSaveFileName(this,QString("Destination For durango.av"));
    if(!string.isEmpty()){
        emit destinationSelected(string.toStdString());
    }
}

void DurangoImager::storeDestination(std::string path){
    controller->storeDestinationPath(path);
    ui->DestinationPath->setText(QString(path.c_str()));
}

void DurangoImager::createVolume(){
    controller->createVolume();
}
