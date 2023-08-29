#ifndef HQCSETTINGDIALOG_H
#define HQCSETTINGDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class HQCCSettingDialog;
}

class HQCCSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HQCCSettingDialog(const QString& path,QWidget *parent = nullptr);
    ~HQCCSettingDialog();

private slots:
    void on_btnSave_clicked();

    void on_btnCancel_clicked();

private:
    Ui::HQCCSettingDialog *ui;
private:
    QString m_Path;
};

#endif // HQCSETTINGDIALOG_H
