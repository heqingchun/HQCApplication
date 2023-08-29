#include "HQCSetting.h"

HQCCSetting::HQCCSetting(const QString& path,QObject *parent) : QObject(parent){
    this->m_FilePath = path;
}
void HQCCSetting::Read(QMap<QString,QVariant>& retConfigure){
    QSettings configure(m_FilePath,QSettings::IniFormat,this);
    QStringList sectionList = configure.childGroups();
    for(int i = 0;i < sectionList.size();i++){
        configure.beginGroup(sectionList.at(i));
        QStringList keyList = configure.childKeys();
        for(int j = 0;j < keyList.size();j++){
            retConfigure.insert(sectionList.at(i) + "/" + keyList.at(j),configure.value(keyList.at(j)));
        }
        configure.endGroup();
    }
}
void HQCCSetting::Write(const QMap<QString,QVariant>& configureMap){
    QSettings configure(m_FilePath,QSettings::IniFormat,this);
    QStringList keyList = configureMap.keys();
    for(int i = 0;i < keyList.size();i++){
        configure.setValue(keyList.at(i),configureMap.value(keyList.at(i)));
    }
}
