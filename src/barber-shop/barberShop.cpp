#include "barberShop.h"

#include <QTextStream>
#include <QDebug>

const quint64 BarberShop::getServicedCustomers() {
    qDebug() << __FUNCTION__ << "called";
    return servicedCustomers;
}

const quint64 BarberShop::getMissedCustomers() {
    qDebug() << __FUNCTION__ << "called";
    return missedCustomers;
}

void BarberShop::customerArrived() {
    qDebug() << __FUNCTION__ << "called";
    auto availableSeat = chairs.indexOf(Chair::Empty);
    if (availableSeat == -1) {
        ++missedCustomers;
        return;
    }
    chairs[availableSeat] = Chair::Occupied;
}

void BarberShop::checkForAvailableCustomers() {
    qDebug() << __FUNCTION__ << "called";
    auto availableSeat = chairs.indexOf(Chair::Occupied);
    if (availableSeat == -1) {
        qDebug() << __FUNCTION__ << "no customer is available";
        emit customerUnavailable();
        return;
    }
    qDebug() << __FUNCTION__ << "customer is available at" << availableSeat;
    chairs[availableSeat] = Chair::InProgress;
    emit customerAvailable(availableSeat);
}

void BarberShop::finishedWithCustomer(quint64 chairId) {
    qDebug() << __FUNCTION__ << "called with" << chairId;
    chairs[chairId] = Chair::Empty;
    ++servicedCustomers;
}

void BarberShop::printState() {
    qDebug() << __FUNCTION__ << "called";
    QTextStream out(stdout);
    out << "Chairs:" << Qt::endl;
    for (auto i = 0 ; i < chairs.size() ; ++i) {
        if (chairs[i] == Chair::Occupied) {
            out << "# ";
        } else if (chairs[i] == Chair::Empty) {
            out << "O ";
        } else {
            out << "X ";
        }
    }
    out << Qt::endl << "Serviced customers: " << servicedCustomers << Qt::endl <<
    "Missed customers: " << missedCustomers << Qt::endl << Qt::endl;
}
