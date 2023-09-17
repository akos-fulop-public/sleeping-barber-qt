#pragma once

#include <QObject>
#include <QList>

enum class Chair{Empty, Occupied, InProgress};

class BarberShop : public QObject
{
Q_OBJECT;

public:
	BarberShop(quint64 number_of_chairs) : chairs(number_of_chairs, Chair::Empty) {
	}

	const quint64 getServicedCustomers();
	const quint64 getMissedCustomers();

public slots:
	void customerArrived();
	void checkForAvailableCustomers();
	void finishedWithCustomer(quint64 chair_id);
	void printState();

signals:
	void customerAvailable(quint64 chair_id);
	void customerUnavailable();

private:
	QList<Chair> chairs;
	quint64 serviced_customers{0};
	quint64 missed_customers{0};
};
