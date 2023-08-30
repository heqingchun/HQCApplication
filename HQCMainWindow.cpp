#include "HQCMainWindow.h"
#include "ui_HQCMainWindow.h"

/**
  yyyyMMdd-描述
  --1.更改位置
  --2.更改位置
  --3.更改位置
**/

HQCCMainWindow::HQCCMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HQCCMainWindow)
{
    ui->setupUi(this);
    m_SettingPath = qApp->applicationDirPath() + "/setting/setting.ini"; //配置文件（两个类用到)
    /*软件界面*/
    InitWindow();
    /*软件设置*/
    InitSetting();
    /*设置界面*/
    InitSettingWindow();
}

HQCCMainWindow::~HQCCMainWindow(){
    /*软件界面*/
    if(p_SystemTimer){
        p_SystemTimer->deleteLater(); //显示系统时间
    }
    /*软件设置*/
    if(p_Setting){
        p_Setting->deleteLater();
    }
    /*设置界面*/
    if(p_SettingDlg){
        p_SettingDlg->deleteLater();
    }
    /*日志处理*/
    HQCCLogHandle::Get().uninstallMessageHandler();
    delete ui;
}
/*软件界面*/
void HQCCMainWindow::InitWindow(){
    //加载皮肤
    QFile qss(":/qss/dark/darkStyle.qss");
    if(!qss.open(QFile::ReadOnly)){
        QMessageBox::information(this,"提示","qss文件打开失败");
    }
    setStyleSheet(qss.readAll());
    //美化窗口
    setWindowFlag(Qt::FramelessWindowHint);
    menuBar()->hide();
    statusBar()->hide();
    //图标
    ui->labLogoIcon->setPixmap(QPixmap::fromImage(QImage(":/icon/logo/logo.png")));
    ui->labLogoText->setPixmap(QPixmap::fromImage(QImage(":/icon/logo/logotext.png")));
    ui->tbtnSetting->setIcon(QIcon(":/icon/White/setting.ico"));
    ui->tbtnMin->setIcon(QIcon(":/icon/White/min.ico"));
    ui->tbtnMax->setIcon(QIcon(":/icon/White/normal.ico"));
    ui->tbtnClose->setIcon(QIcon(":/icon/White/close.ico"));
    //系统时间显示
    ui->lcdSystemTime->display(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    p_SystemTimer = new QTimer();
    connect(p_SystemTimer,&QTimer::timeout,[&](){
        ui->lcdSystemTime->display(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    });
    p_SystemTimer->start(1000);
} //初始化

void HQCCMainWindow::on_tbtnSetting_clicked(){
    p_SettingDlg->show();
} //设置

void HQCCMainWindow::on_tbtnMin_clicked(){
    showMinimized();
} //最小化

void HQCCMainWindow::on_tbtnMax_clicked(){
    if(windowState() == Qt::WindowFullScreen){
        showNormal();
        ui->tbtnMax->setIcon(QIcon(":/icon/White/max.ico"));
    }else{
        showFullScreen();
        ui->tbtnMax->setIcon(QIcon(":/icon/White/normal.ico"));
    }
} //最大化

void HQCCMainWindow::on_tbtnClose_clicked(){
    if(QMessageBox::question(this,"提示","是否确认退出软件?") == QMessageBox::Yes){
        exit(0);
    }
} //关闭

void HQCCMainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        m_MousePos = event->pos();
    }
} //鼠标按下

void HQCCMainWindow::mouseMoveEvent(QMouseEvent *event){
    //窗口最大化不可移动
    if(windowState() == Qt::WindowFullScreen){
        return;
    }
    //如果鼠标在控件上不可移动
    if(ui->tbtnSetting->underMouse() || ui->tbtnMin->underMouse() || ui->tbtnMax->underMouse() || ui->tbtnClose->underMouse()){
        return;
    }
    //左键点击并且移动,范围在窗口的上面部分
    if(event->buttons()&Qt::LeftButton
            && event->pos().x()>=0 && event->pos().y()>=0
            && event->pos().x()<= geometry().width()
            && event->pos().y() <= geometry().height()/10){
            setCursor(Qt::ClosedHandCursor); //改变鼠标形状
            move(event->pos()+pos()-m_MousePos); //移动窗口
        }
} //鼠标拖拽

void HQCCMainWindow::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
} //鼠标松开
/*软件设置*/
void HQCCMainWindow::InitSetting(){
    p_Setting = new HQCCSetting(m_SettingPath);
    //判断设置文件是否存在
    if(!QFile::exists(m_SettingPath)){
        QMap<QString,QVariant> defaultConfigure; //默认配置文件
        defaultConfigure.clear();
        defaultConfigure.insert("Detection/conf",0.60);
        defaultConfigure.insert("Detection/nms",0.45);
        defaultConfigure.insert("Detection/result",10);
        defaultConfigure.insert("Stream/VideoPath","./VideoTest");
        defaultConfigure.insert("Stream/PicturePath","./PictureTest");
        defaultConfigure.insert("Stream/flag",0);
        defaultConfigure.insert("ModbusTcp/ip","127.0.0.1");
        defaultConfigure.insert("ModbusTcp/port",502);
        defaultConfigure.insert("ModbusTcp/readRegister",0);
        defaultConfigure.insert("ModbusTcp/writeRegister",1);
        defaultConfigure.insert("Camera/cameraIp","192.168.192.110");
        defaultConfigure.insert("Camera/cameraPort","554");
        defaultConfigure.insert("Camera/cameraUsername","admin");
        defaultConfigure.insert("Camera/cameraPassword","Aa000000");
        p_Setting->Write(defaultConfigure);
    }
    m_SettingMap.clear();
    p_Setting->Read(m_SettingMap);
} //初始化
/*设置界面*/
void HQCCMainWindow::InitSettingWindow(){
    p_SettingDlg = new HQCCSettingDialog(m_SettingPath);
    //设置模态
    p_SettingDlg->setModal(true);
}
/*日志处理*/
void HQCCMainWindow::InitSettingLog(){
    HQCCLogHandle::Get().installMessageHandler();
}
