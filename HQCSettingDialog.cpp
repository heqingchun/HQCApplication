#include "HQCSettingDialog.h"
#include "ui_HQCSettingDialog.h"

HQCCSettingDialog::HQCCSettingDialog(const QString& path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HQCCSettingDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint); //无标题栏
    m_Path = path;
}

HQCCSettingDialog::~HQCCSettingDialog(){
    delete ui;
}

void HQCCSettingDialog::on_btnSave_clicked(){

}

void HQCCSettingDialog::on_btnCancel_clicked(){
    close();
}
