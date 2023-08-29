#ifndef HQCCSETTING_H
#define HQCCSETTING_H

#include <QObject>
#include <QSettings>

class HQCCSetting : public QObject
{
    Q_OBJECT
public:
    explicit HQCCSetting(const QString& path,QObject *parent = nullptr);

signals:
public:
    void Write(const QMap<QString,QVariant>& configureMap/*[(section/key),(value)]*/);
    void Read(QMap<QString,QVariant>& retConfigure);
private:
    QString m_FilePath;
};

#endif // HQCCSETTING_H
