#include <QObject>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTimer>

#include <barberShop.h>
#include <customerSpawner.h>
#include <barber.h>

int main(int argc, char* argv[]) {
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("sleeping-barber");
	QCoreApplication::setApplicationVersion("1.0.0");
	QCommandLineParser parser;
	parser.setApplicationDescription("Example implementation of the Sleeping Barber Problem");
	parser.addHelpOption();
	parser.addVersionOption();
	QCommandLineOption chair_option{{"c", "chairs"}, "Number of <chairs> in the Barber Shop.", "chairs"};
	QCommandLineOption work_option{{"w", "work"}, "Number of miliseconds it takes the Barber to <work>.", "work"};
	QCommandLineOption min_spawner_option{{"m", "minimum"}, "The <minimum> number of miliseconds it takes a new customer to arrive.", "min"};
	QCommandLineOption max_spawner_option{{"M", "maximum"}, "The <maximum> number of miliseconds it takes a new customer to arrive.", "max"};
	parser.addOptions({chair_option, work_option, min_spawner_option, max_spawner_option});
	parser.process(app);
	auto number_of_chairs = 5;
	if (parser.isSet(chair_option)) {
		number_of_chairs = parser.value(chair_option).toULongLong();
	}
	auto work_intervall = 3500;
	if (parser.isSet(work_option)) {
		work_intervall = parser.value(work_option).toULongLong();
	}
	auto min_intervall = 2000;
	if (parser.isSet(min_spawner_option)) {
		min_intervall = parser.value(min_spawner_option).toULongLong();
	}
	auto max_intervall = 6000;
	if (parser.isSet(max_spawner_option)) {
		max_intervall = parser.value(max_spawner_option).toULongLong();
	}

	BarberShop shop(number_of_chairs);
	CustomerSpawner spawner(&app, min_intervall, max_intervall);
	Barber barber(work_intervall);
	QObject::connect(&shop, &BarberShop::customerAvailable, &barber, &Barber::startWorkingOnCustomer);
	QObject::connect(&barber, &Barber::finishedWithCustomer, &shop, &BarberShop::finishedWithCustomer);
	QObject::connect(&shop, &BarberShop::customerUnavailable, &app, &QCoreApplication::quit);
	QObject::connect(&shop, &BarberShop::stateChanged, &shop, &BarberShop::printState);
	QObject::connect(&spawner, &CustomerSpawner::customerArrives, &shop, &BarberShop::customerArrived);
	QObject::connect(&app, &QCoreApplication::aboutToQuit, &spawner, &CustomerSpawner::stopSpawning);
	QObject::connect(&app, &QCoreApplication::aboutToQuit, &shop, &BarberShop::printState);
	QObject::connect(&barber, &Barber::finishedWithCustomer, [&]() {
		emit shop.checkForAvailableCustomers();
	});
	emit spawner.startSpawning();
	emit shop.checkForAvailableCustomers();
	app.exec();
	return 0;
}
