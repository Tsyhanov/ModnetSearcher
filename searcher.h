#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QtSerialBus/QModbusClient>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

class Searcher: public QObject
{
    Q_OBJECT

//    Q_PROPERTY(int m_currSearchAddr READ currSearchAddr WRITE setCurrSearchAddr NOTIFY currSearchAddrChanged);

public:
    Searcher(QObject *parent = nullptr);
    virtual ~Searcher() {};

    QString createCurrIP(const int &i);

    int currSearchAddr();
    void setCurrSearchAddr(const int &addr);

    int startAddr();
    void setStartAddr(const int &addr);

    int endAddr();
    void setEndAddr(const int &addr);

    QString currIpTemplate();
    void setCurrIpTemplate(const QString &s);


    void sendRequest3();
    void readReady3();

signals:


public slots:
    void doSearch();
    void onStateChanged();

private slots:
    void on_Timer();

private:
    //timer
    QTimer *timer;
    //modbus device
    QModbusClient *modbusDevice;
    //device IP
    QString m_currIP;
    QString m_currIpTemplate;//192.168.1.
    //next search flag
    bool m_NextSearchFlag = true;
    //current search address
    int m_currSearchAddr;
    //current find address
    int m_currFindAddr;
    //search settings
    int m_startAddr;
    int m_endAddr;
    //find param
    int m_currAddr;
    int m_currSpeed;

};
#endif // SEARCHER_H
