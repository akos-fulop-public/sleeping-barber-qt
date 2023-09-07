#include <QTextStream>
#include <QCoreApplication>
#include <QObject>
#include <QTimer>

#include <barberShop.h>
#include <customerSpawner.h>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    BarberShop shop(5);
    CustomerSpawner spawner;
    QTimer printTimer;
    QObject::connect(&printTimer, &QTimer::timeout, &shop, &BarberShop::printState);
    QObject::connect(&spawner, &CustomerSpawner::customerArrives, &shop, &BarberShop::customerArrived);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &spawner, &CustomerSpawner::stopSpawning);
    QTextStream(stdout) << "Hello World!" << Qt::endl;
    emit spawner.startSpawning();
    printTimer.start(1000);
    app.exec();
    return 0;
}
