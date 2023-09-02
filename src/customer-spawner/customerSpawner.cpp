#include "customerSpawner.h"

CustomerSpawner::CustomerSpawner(QObject* parent, quint64 msec) :
    QObject(parent)
{
    connect(&timer, &QTimer::timeout, this, &CustomerSpawner::customerArrives_slot);
    timer.setInterval(msec);
}

void CustomerSpawner::startSpawning() {
    timer.start();
}

void CustomerSpawner::stopSpawning() {
    timer.stop();
}

void CustomerSpawner::customerArrives_slot() {
    emit customerArrives();
}
