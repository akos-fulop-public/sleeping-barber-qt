#include "customerSpawner.h"
#include <QTimer>


void CustomerSpawner::startSpawning() {
    QTimer::singleShot(1000, this, &CustomerSpawner::customerArrives_slot);
}

void CustomerSpawner::customerArrives_slot() {
    emit customerArrives();
}
