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
}

DurangoImager::~DurangoImager()
{
    delete ui;
    delete controller;
}

void DurangoImager::addItem(std::string path){
    ui->romList->addItem(QString(path.c_str()));
    controller->addRomFile(new DurangoRom(path,path));
}

void DurangoImager::addFileButtonPressed(){
    QString string = QFileDialog::getOpenFileName(this,QString("Add New ROM"));
    if(!string.isEmpty()){
        std::string fileName= string.toStdString();
        fileName= fileName.substr(fileName.find_last_of("/")+1);
        emit itemAdded(fileName);
    }
}

void DurangoImager::removeItem(){
    QModelIndexList list = ui->romList->selectionModel()->selectedIndexes();
    QModelIndexList::iterator i;
    for(i=list.begin();i!=list.end();i++){
        controller->removeRomFile(i->row());
        ui->romList->removeItemWidget(ui->romList->item(i->row()));
    }

}

void DurangoImager::addSpace(int state){
    if(state== Qt::CheckState::Checked){
        ui->sizeCombo->setEnabled(true);
    }
    else{
        ui->sizeCombo->setEnabled(false);
    }
}
