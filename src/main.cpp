#include <QTextStream>
#include <QCoreApplication>
#include <QObject>
#include <QTimer>

#include <barberShop.h>
#include <customerSpawner.h>
#include <barber.h>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    BarberShop shop(5);
    CustomerSpawner spawner(&app, 2000, 6000);
    Barber barber(3500);
    QTimer printTimer;
    QObject::connect(&shop, &BarberShop::customerAvailable, &barber, &Barber::startWorkingOnCustomer);
    QObject::connect(&barber, &Barber::finishedWithCustomer, &shop, &BarberShop::finishedWithCustomer);
    QObject::connect(&shop, &BarberShop::customerUnavailable, &app, &QCoreApplication::quit);
    QObject::connect(&printTimer, &QTimer::timeout, &shop, &BarberShop::printState);
    QObject::connect(&spawner, &CustomerSpawner::customerArrives, &shop, &BarberShop::customerArrived);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &spawner, &CustomerSpawner::stopSpawning);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &shop, &BarberShop::printState);
    QObject::connect(&barber, &Barber::finishedWithCustomer, [&]() {
        emit shop.checkForAvailableCustomers();
    });
    QTextStream(stdout) << "Hello World!" << Qt::endl;
    emit spawner.startSpawning();
    printTimer.start(1000);
    emit shop.checkForAvailableCustomers();
    app.exec();
    return 0;
}
