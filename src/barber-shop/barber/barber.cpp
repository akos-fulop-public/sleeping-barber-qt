#include "barber.h"

Barber::Barber(quint64 workTimeMsec) {
    workTimer.setInterval(workTimeMsec);
    workTimer.setSingleShot(true);
    connect(&workTimer, &QTimer::timeout, this, &Barber::finishedWithCustomer);
}

void Barber::startWorkingOnCustomer() {
    workTimer.start();
}
