#include "searcher.h"
#include <QDebug>
#include <QtSerialBus/QModbusRtuSerialMaster>
#include <QtTest/QTest>

Searcher::Searcher(QObject *parent) : QObject(parent){

    qDebug("Searcher constructor");
    setCurrSearchAddr(1);
    timer = new QTimer;

    modbusDevice = new QModbusRtuSerialMaster(this);
    if (!modbusDevice) {
        qDebug("Could not create Modbus Master");
        return;
    } else {
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
    }

}

void Searcher::doSearch()
{
    qDebug() << "do search";
    if (!modbusDevice){
        qDebug() << "Wrong Modbus device";
        return;
    }
    for (int i=startAddr(); i<=endAddr();i=currSearchAddr()+1){
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, currIP());
        sendRequest3(i);
    }
//    const QUrl url =
}


void Searcher::on_Timer()
{
    qDebug() << "onTimer:" << QString::number(currSearchAddr()) ;
}

void Searcher::sendRequest3(const int &addr)
{
    qDebug() << "sendRequest3" + QString::number(addr);
    const auto table = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 100, 2);
    if (auto *reply = modbusDevice->sendReadRequest(table, addr)){
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &Searcher::readReady3);
        else
            delete reply;//broadcast
    } else {
        qDebug() << "sendRequest error";
    }
}

void Searcher::readReady3()
{
    qDebug("readReady3");
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        qDebug() << "valueCount:" + QString::number(unit.valueCount());
        for (uint i = 0; i < unit.valueCount(); i++) {
            qDebug() << "Address:" + QString::number(unit.startAddress() + i);
            qDebug() << "Value:" + QString::number(unit.value(i));
        }}
    else {
        qDebug() << "read error";
    }
}


QString Searcher::currIP(){
    return m_currIP;
}

void Searcher::setCurrIP(const QString &s){
    m_currIP = s;
}


int Searcher::currSearchAddr(){
    return m_currSearchAddr;
}

void Searcher::setCurrSearchAddr(const int &addr){
    m_currSearchAddr = addr;
    emit currSearchAddrChanged();
}

int Searcher::startAddr(){
    return m_startAddr;
}

void Searcher::setStartAddr(const int &addr){
    m_startAddr = addr;
    emit startAddrChanged();
}

int Searcher::endAddr(){
    return m_endAddr;
}

void Searcher::setEndAddr(const int &addr){
    m_endAddr = addr;
    emit endAddrChanged();
}
