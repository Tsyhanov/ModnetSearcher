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
    void startSearch(Searcher *s);
    void stopSearch();
};

#endif // THREADADM_H
