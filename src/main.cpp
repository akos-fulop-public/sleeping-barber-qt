#include <QTextStream>
#include <QCoreApplication>
#include <QCommandLineParser>

#include <QCommandLineOption>
#include <QObject>
#include <QTimer>

#include <barberShop.h>
#include <customerSpawner.h>
#include <barber.h>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("sleeping-barber");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;
    parser.setApplicationDescription("Example implementation of the Sleeping Barber Problem");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption chairOption{{"c", "chairs"}, "Number of <chairs> in the Barber Shop.","chairs"};
    QCommandLineOption workOption{{"w", "work"}, "Number of miliseconds it takes the Barber to <work>.","work"};
    parser.addOptions({chairOption, workOption});
    parser.process(app);
    auto numberOfChairs = 5;
    if (parser.isSet(chairOption)) {
        numberOfChairs = parser.value(chairOption).toULongLong();
    }
    auto workIntervall = 3500;
    if (parser.isSet(workOption)) {
        workIntervall = parser.value(workOption).toULongLong();
    }
    BarberShop shop(numberOfChairs);
    CustomerSpawner spawner(&app, 2000, 6000);
    Barber barber(workIntervall);
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
