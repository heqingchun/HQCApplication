#ifndef HQCCMAINWINDOW_H
#define HQCCMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>
#include <QMouseEvent>
/*软件设置*/
#include "HQCSetting.h"
/*设置界面*/
#include "HQCSettingDialog.h"
/*日志处理*/
#include "HQCLogHandle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HQCCMainWindow; }
QT_END_NAMESPACE

class HQCCMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HQCCMainWindow(QWidget *parent = nullptr);
    ~HQCCMainWindow();

private:
    Ui::HQCCMainWindow *ui;
/*MainWindow*/
private:
    QString m_SettingPath;
/*软件界面*/
private slots:
    void on_tbtnSetting_clicked(); //设置
    void on_tbtnMin_clicked(); //最小化
    void on_tbtnMax_clicked(); //最大化
    void on_tbtnClose_clicked(); //关闭
protected:
    void mousePressEvent(QMouseEvent *event); //鼠标拖拽
    void mouseMoveEvent(QMouseEvent *event); //鼠标拖拽
    void mouseReleaseEvent(QMouseEvent *event); //鼠标松开
private:
    void InitWindow(); //初始化
private:
    QTimer *p_SystemTimer = nullptr; //显示系统时间定时器
    QPoint m_MousePos; //鼠标拖拽窗口
/*软件设置*/
private:
    void InitSetting(); //初始化
private:
    HQCCSetting *p_Setting = nullptr;
    QMap<QString,QVariant> m_SettingMap;
/*设置界面*/
private:
    void InitSettingWindow();
private:
    HQCCSettingDialog *p_SettingDlg = nullptr;
/*日志处理*/
private:
    void InitSettingLog();
};
#endif // HQCCMAINWINDOW_H
