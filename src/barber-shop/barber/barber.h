#pragma once

#include <QObject>
#include <QTimer>

class Barber : public QObject {
Q_OBJECT;
public:
	Barber(quint64 work_time_msec);

public slots:
	void startWorkingOnCustomer(quint64 chair_id);

signals:
	void finishedWithCustomer(quint64 chair_id);

private:
	QTimer work_timer;
	quint64 current_chair_id{0};
};
