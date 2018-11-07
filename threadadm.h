#ifndef THREADADM_H
#define THREADADM_H

#include <QObject>
#include "searcher.h"

class Threadadm: public QObject
{
    Q_OBJECT


public:
    Threadadm(QObject *parent = nullptr);
    virtual ~Threadadm() {};

public slots:
    void startSearch(int from, int to, QString sIpTemplate);
    void stopSearch(QThread& searchthread, Searcher& s);

signals:
    void signalStop(QThread& searchthread, Searcher& s);

private:
    //start stop flag
    bool m_startflag = false;
    //QThread
    QThread *searchthread;
    //Searcher
    Searcher *s;
};

#endif // THREADADM_H
