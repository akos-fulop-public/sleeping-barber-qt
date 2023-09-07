#include "barberShop.h"

const quint64 BarberShop::getServicedCustomers() {
    return servicedCustomers;
}

const quint64 BarberShop::getMissedCustomers() {
    return missedCustomers;
}

void BarberShop::customerArrived() {
    auto availableSeat = chairs.indexOf(Chair::Empty);
    if (availableSeat == -1) {
        ++missedCustomers;
        return;
    }
    chairs[availableSeat] = Chair::Occupied;
}

void BarberShop::checkForAvailableCustomers() {
    auto availableSeat = chairs.indexOf(Chair::Occupied);
    if (availableSeat == -1) {
        emit customerUnavailable();
        return;
    }
    chairs[availableSeat] = Chair::InProgress;
    emit customerAvailable(availableSeat);
}

void BarberShop::finishedWithCustomer(quint64 chairId) {
    chairs[chairId] = Chair::Empty;
    ++servicedCustomers;
}
