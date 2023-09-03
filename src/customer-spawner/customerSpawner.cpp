#include "customerSpawner.h"

CustomerSpawner::CustomerSpawner(QObject* parent, quint64 min_msec, quint64 max_msec) :
    QObject(parent),
    generator(QRandomGenerator::global()->generate()),
    min_msec(min_msec),
    max_msec(max_msec)
{
    connect(&timer, &QTimer::timeout, this, &CustomerSpawner::resetTimerAndFireAgain);
    timer.setSingleShot(true);
}

void CustomerSpawner::startSpawning() {
    resetTimerAndFireAgain();
}

void CustomerSpawner::stopSpawning() {
    timer.stop();
}

void CustomerSpawner::resetTimerAndFireAgain() {
    timer.start(generator.bounded(min_msec, max_msec));
    emit customerArrives();
};
