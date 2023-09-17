#include "barberShop.h"

#include <QTextStream>
#include <QDebug>

const quint64 BarberShop::getServicedCustomers() {
	qDebug() << __FUNCTION__ << "called";
	return serviced_customers;
}

const quint64 BarberShop::getMissedCustomers() {
	qDebug() << __FUNCTION__ << "called";
	return missed_customers;
}

void BarberShop::customerArrived() {
	qDebug() << __FUNCTION__ << "called";
	auto available_seat = chairs.indexOf(Chair::Empty);
	if (available_seat == -1) {
		++missed_customers;
		return;
	}
	chairs[available_seat] = Chair::Occupied;
}

void BarberShop::checkForAvailableCustomers() {
	qDebug() << __FUNCTION__ << "called";
	auto available_seat = chairs.indexOf(Chair::Occupied);
	if (available_seat == -1) {
		qDebug() << __FUNCTION__ << "no customer is available";
		emit customerUnavailable();
		return;
	}
	qDebug() << __FUNCTION__ << "customer is available at" << available_seat;
	chairs[available_seat] = Chair::InProgress;
	emit customerAvailable(available_seat);
}

void BarberShop::finishedWithCustomer(quint64 chair_id) {
	qDebug() << __FUNCTION__ << "called with" << chair_id;
	chairs[chair_id] = Chair::Empty;
	++serviced_customers;
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
	out << Qt::endl << "Serviced customers: " << serviced_customers << Qt::endl <<
	"Missed customers: " << missed_customers << Qt::endl << Qt::endl;
}
