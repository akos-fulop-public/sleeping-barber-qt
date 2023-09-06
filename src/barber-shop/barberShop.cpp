#include "barberShop.h"

void BarberShop::checkForAvailableCustomers() {
    auto availableSeat = chairs.indexOf(Chair::Occupied);
    chairs[availableSeat] = Chair::InProgress;
    emit customerAvailable(availableSeat);
}

void BarberShop::finishedWithCustomer(quint64 chairId) {

}
