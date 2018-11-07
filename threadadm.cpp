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
    if (!m_startflag){
        qDebug() << "startSearch";
        searchthread = new QThread;
        s = new Searcher();
        s->setStartAddr(from);
        s->setEndAddr(to);
        s->setCurrIpTemplate(sIpTemplate);
        s->moveToThread(searchthread);

        connect(searchthread, &QThread::started, s, &Searcher::doSearch);
        connect(searchthread, &QThread::finished, searchthread, &QThread::deleteLater);
        connect(this, &Threadadm::signalStop, this, &Threadadm::stopSearch);

        searchthread->start();
        m_startflag = true;
    } else {
        qDebug() << "stopSearch";
        emit signalStop(*searchthread, *s);
        m_startflag = false;
    }
}


void Threadadm::stopSearch(QThread &searchthread, Searcher &s)
{
    searchthread.quit();
    searchthread.wait(100);
    s.deleteLater();
}
