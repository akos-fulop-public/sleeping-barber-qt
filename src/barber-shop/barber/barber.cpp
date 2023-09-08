#include "barber.h"

#include <QDebug>

Barber::Barber(quint64 workTimeMsec) {
    workTimer.setInterval(workTimeMsec);
    workTimer.setSingleShot(true);
    connect(&workTimer, &QTimer::timeout, [=] () {
        emit finishedWithCustomer(currentChairId);
    });
}

void Barber::startWorkingOnCustomer(quint64 chairId) {
    qDebug() << __FUNCTION__ << "called with" << chairId;
    currentChairId = chairId;
    workTimer.start();
}
