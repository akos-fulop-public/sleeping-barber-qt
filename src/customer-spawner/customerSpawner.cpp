#include "customerSpawner.h"

#include <QDebug>

CustomerSpawner::CustomerSpawner(QObject* parent, quint64 min_msec, quint64 max_msec) :
    QObject(parent),
    generator(QRandomGenerator::global()->generate()),
    min_msec(min_msec),
    max_msec(max_msec) {
    connect(&timer, &QTimer::timeout, this, &CustomerSpawner::resetTimerAndFireAgain);
    timer.setSingleShot(true);
}

void CustomerSpawner::startSpawning() {
    qDebug() << __FUNCTION__ << "called";
    resetTimerAndFireAgain();
}

void CustomerSpawner::stopSpawning() {
    qDebug() << __FUNCTION__ << "called";
    timer.stop();
}

void CustomerSpawner::resetTimerAndFireAgain() {
    qDebug() << __FUNCTION__ << "called";
    timer.start(generator.bounded(min_msec, max_msec));
    emit customerArrives();
}
