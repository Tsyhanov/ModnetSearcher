#include "threadadm.h"
#include <QDebug>
#include <QThread>
#include "searcher.h"

Threadadm::Threadadm(QObject *parent) : QObject(parent)
{
    qDebug() << "threadadm";
}

void Threadadm::startSearch(int from, int to, QString sIpTemplate)
{
    qDebug() << "startSearch";
    QThread *searchthread = new QThread;
    Searcher *s = new Searcher();
    s->setStartAddr(from);
    s->setEndAddr(to);
    s->setCurrIpTemplate(sIpTemplate);
    s->moveToThread(searchthread);

    connect(searchthread, SIGNAL(started()), s, SLOT(doSearch()));

    searchthread->start();
}

void Threadadm::stopSearch()
{
    qDebug() << "stopSearch";
}
