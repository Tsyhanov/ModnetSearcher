#include "threadadm.h"
#include <QDebug>
#include <QThread>
#include "searcher.h"

Threadadm::Threadadm(QObject *parent) : QObject(parent)
{
    qDebug() << "threadadm";
}

void Threadadm::startSearch(Searcher *s)
{
    qDebug() << "startSearch";
    QThread *searchthread = new QThread;
    s->moveToThread(searchthread);
    searchthread->start();
}

void Threadadm::stopSearch()
{
    qDebug() << "stopSearch";
}
