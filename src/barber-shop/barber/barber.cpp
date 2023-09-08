#include "barber.h"

Barber::Barber(quint64 workTimeMsec) {
    workTimer.setInterval(workTimeMsec);
    workTimer.setSingleShot(true);
    connect(&workTimer, &QTimer::timeout, [=] () {
        emit finishedWithCustomer(currentChairId);
    });
}

void Barber::startWorkingOnCustomer(quint64 chairId) {
    currentChairId = chairId;
    workTimer.start();
}
