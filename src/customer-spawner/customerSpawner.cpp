#include "customerSpawner.h"
#include <QTimer>


CustomerSpawner::CustomerSpawner(QObject* parent, quint64 msec) :
    QObject(parent),
    timer_intervall(msec)
{}

void CustomerSpawner::startSpawning() {
    QTimer::singleShot(timer_intervall, this, &CustomerSpawner::customerArrives_slot);
}

void CustomerSpawner::customerArrives_slot() {
    emit customerArrives();
}
