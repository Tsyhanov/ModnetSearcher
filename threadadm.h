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
    void stopSearch();

public slots:
    void startSearch(int from, int to, QString sIpTemplate);


private:
    Searcher *s;
};

#endif // THREADADM_H
