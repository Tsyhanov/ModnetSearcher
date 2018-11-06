#include "searcher.h"
#include <QDebug>
#include <QModbusTcpClient>
#include <QtTest/QTest>
#include <QNetworkProxyFactory>

Searcher::Searcher(QObject *parent) : QObject(parent){

    qDebug("Searcher constructor");
    setCurrSearchAddr(1);
    timer = new QTimer;

    QNetworkProxyFactory::setUseSystemConfiguration(false);//seems like a qt bug

            modbusDevice = new QModbusTcpClient(this);
    if (!modbusDevice) {
        qDebug("Could not create Modbus Master");
        return;
    } else {
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
//        modbusDevice->setTimeout(500);
        modbusDevice->setNumberOfRetries(3);
    }

}

void Searcher::doSearch()
{
    if (!modbusDevice){
        qDebug() << "Wrong Modbus device";
        return;
    }
        int i = 2;
//    for (int i=startAddr(); i<=endAddr();i++){
        setCurrSearchAddr(i);
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, createCurrIP(i));
        if (!modbusDevice->connectDevice()){
            qDebug() << "connect failed";
        } else {
            qDebug() << "connected:" + currIpTemplate() + QString::number(currSearchAddr());
            connect(modbusDevice, &QModbusTcpClient::stateChanged,this, &Searcher::onStateChanged);
        }
//    }
}


void Searcher::on_Timer()
{
    qDebug() << "onTimer:" << QString::number(currSearchAddr()) ;
}

void Searcher::sendRequest3()
{
    int addr = 1;
    qDebug() << "sendRequest3";
    const auto table = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 100, 2);
    if (auto *reply = modbusDevice->sendReadRequest(table, addr)){
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &Searcher::readReady3);
        else
            delete reply;//broadcast
    } else {
        qDebug() << "error:" + modbusDevice->errorString();
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

void Searcher::onStateChanged()
{
    switch (modbusDevice->state())
    {
    case QModbusDevice::UnconnectedState:
        qDebug() << "UnconnectedState";
        break;
    case QModbusDevice::ConnectingState:
        qDebug() << "ConnectingState";
        break;
    case QModbusDevice::ConnectedState:
        sendRequest3();
        break;
    case QModbusDevice::ClosingState:
        qDebug() << "ClosingState";
        break;
    }
}


QString Searcher::createCurrIP(const int &i){
    return (currIpTemplate() + QString::number(i));
}

void Searcher::setCurrIpTemplate(const QString &s){
    m_currIpTemplate = s;
}

QString Searcher::currIpTemplate(){
    return m_currIpTemplate;
}

int Searcher::currSearchAddr(){
    return m_currSearchAddr;
}

void Searcher::setCurrSearchAddr(const int &addr){
    m_currSearchAddr = addr;
}

int Searcher::startAddr(){
    return m_startAddr;
}

void Searcher::setStartAddr(const int &addr){
    m_startAddr = addr;
}

int Searcher::endAddr(){
    return m_endAddr;
}

void Searcher::setEndAddr(const int &addr){
    m_endAddr = addr;
}
