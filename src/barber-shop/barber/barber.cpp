#include "barber.h"

#include <QDebug>

Barber::Barber(quint64 work_time_msec) {
    work_timer.setInterval(work_time_msec);
    work_timer.setSingleShot(true);
    connect(&work_timer, &QTimer::timeout, [=] () {
        emit finishedWithCustomer(current_chair_id);
    });
}

void Barber::startWorkingOnCustomer(quint64 chair_id) {
    qDebug() << __FUNCTION__ << "called with" << chair_id;
    current_chair_id = chair_id;
    work_timer.start();
}
