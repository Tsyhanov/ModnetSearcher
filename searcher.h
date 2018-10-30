#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QtSerialBus/QModbusClient>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

class Searcher: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int m_currSearchAddr READ currSearchAddr WRITE setCurrSearchAddr NOTIFY currSearchAddrChanged);
    Q_PROPERTY(int m_startAddr READ startAddr WRITE setStartAddr NOTIFY startAddrChanged);
    Q_PROPERTY(int m_endAddr READ endAddr WRITE setEndAddr NOTIFY endAddrChanged);

public:
    Searcher(QObject *parent = nullptr);
    virtual ~Searcher() {};


    QString currIP();
    void setCurrIP(const QString &s);

    int currSearchAddr();
    void setCurrSearchAddr(const int &addr);

    int startAddr();
    void setStartAddr(const int &addr);

    int endAddr();
    void setEndAddr(const int &addr);


//    void startSearch();
    void sendRequest3(const int &addr);
    void readReady3();

signals:

    void currSearchAddrChanged();
    void startAddrChanged();
    void endAddrChanged();

public slots:
    void doSearch();

private slots:
    void on_Timer();

private:
    //timer
    QTimer *timer;
    //modbus device
    QModbusClient *modbusDevice;
    //device IP
    QString m_currIP;
    //stop flag
    bool m_StopTimer = true;
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
