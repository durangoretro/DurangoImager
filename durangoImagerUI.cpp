/*
 * SPDX-License-Identifier: LGPL v3.0
 * Copyright (C) 2023 Durango Computer Team (durangoretro.com)
 */

#include "durangoImagerUI.h"
#include "ui_durangoImagerUI.h"
#include <QFileDialog>
#include <QMessageBox>

long emptySpaceSizes[11]={
    16384,32768,65536,131072,
    262144,524288,1048576,2097152,
    4194304,8388608,16777216
};

DurangoImager::DurangoImager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DurangoImager)
{

    controller = new DurangoImagerController();
    ui->setupUi(this);
    //Set fixed size
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    this->setWindowTitle(QString((std::string("Durango Imager v")+std::string(_VERSION_)).c_str()));
    connect(this,SIGNAL(itemAdded(std::string)),this,SLOT(addItem(std::string)));
    connect(ui->addFileButton,SIGNAL(clicked(bool)),this,SLOT(addFileButtonPressed()));
    connect(ui->RemoveFileButton,SIGNAL(clicked(bool)),this, SLOT(removeItem()));
    connect(ui->CheckSpace, SIGNAL(stateChanged(int)),this, SLOT(addSpace(int)));
    connect(ui->destinationButton, SIGNAL(clicked(bool)),this, SLOT(selectDestinationButtonPressed()));
    connect(this, SIGNAL(destinationSelected(std::string)),this, SLOT(storeDestination(std::string)));
    connect(ui->createVolumeButton, SIGNAL(clicked(bool)),this,SLOT(createVolume()));
    connect(ui->sizeCombo,SIGNAL(currentIndexChanged(int)),this, SLOT(emptySpaceChanged(int)));
    connect(ui->openVolumeButton, SIGNAL(clicked(bool)), this, SLOT(openVolumePressed()));
    connect(this,SIGNAL(volumeSelected(std::string)),this,SLOT(openExistingVolume(std::string)));
    fprintf(stderr,"Initiated Durango Imager Application v%s\n",_VERSION_);
}

DurangoImager::~DurangoImager()
{
    delete ui;
    delete controller;
}

void DurangoImager::addItem(std::string path){
    std::string fileName=controller->addRomFile(path);
    ui->romList->addItem(QString(fileName.c_str()));
}

void DurangoImager::addFileButtonPressed(){
    QString selfilter = tr("Durango Roms (*.dux *.pdx)");
    QString string = QFileDialog::getOpenFileName(this,QString("Add New ROM"),QString(),selfilter,&selfilter);
    if(!string.isEmpty()){
        fprintf(stderr,"Selected File: %s\n", string.toStdString().c_str());
        emit itemAdded(string.toStdString());
    }
}

void DurangoImager::removeItem(){
    QModelIndexList list = ui->romList->selectionModel()->selectedIndexes();
    QModelIndexList::iterator i;
    for(i=list.begin();i!=list.end();i++){
        controller->removeRomFile(i->row());
        QListWidgetItem* item =ui->romList->takeItem(i->row());
        delete item;
    }
    ui->romList->update();

}

void DurangoImager::addSpace(int state){
    if(state== Qt::CheckState::Checked){
        ui->sizeCombo->setEnabled(true);
        controller->setEmptyEndSpace(true);
    }
    else{
        ui->sizeCombo->setEnabled(false);
        controller->setEmptyEndSpace(false);
    }
}

void DurangoImager::selectDestinationButtonPressed(){
    QString selfilter = tr("Durango Volume File (durango.av)");
    QString string = QFileDialog::getSaveFileName(this,QString("Destination For durango.av"),QString(),selfilter,&selfilter);
    if(!string.isEmpty()){
        emit destinationSelected(string.toStdString());
    }
}

void DurangoImager::storeDestination(std::string path){
    controller->storeDestinationPath(path);
    ui->DestinationPath->setText(QString(path.c_str()));
}

void DurangoImager::emptySpaceChanged(int index){
    controller->setEmptySpaceSize(emptySpaceSizes[index]);
}


void DurangoImager::createVolume(){
    if(controller->hastDestination()){
        controller->createVolume();
        QMessageBox::information(this,QString("Operation Sucessfull"),QString("Durango Volume Created Succesffully"));
    }else{
        QMessageBox::warning(this,QString("Destination File Required"),QString("Please; select a Destination File"));
    }

}

void DurangoImager::openVolumePressed(){
    QString selfilter = tr("Durango Volume File (durango.av)");
    QString string = QFileDialog::getOpenFileName(this,QString("Destination For durango.av"),QString(),selfilter,&selfilter);
    if(!string.isEmpty()){
        emit volumeSelected(string.toStdString());
    }
}

void DurangoImager::openExistingVolume(std::string path){
    std::vector<std::string> romNames=controller->openExistingVolume(path);
    ui->romList->clear();
    for(size_t i =0;i<romNames.size();i++){
        ui->romList->addItem(QString(romNames.data()[i].c_str()));
    }
    storeDestination(path);
}
