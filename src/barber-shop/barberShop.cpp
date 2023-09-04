#include "barberShop.h"

void BarberShop::checkForAvailableCustomers() {
    emit customerAvailable(chairCounter++);
}
