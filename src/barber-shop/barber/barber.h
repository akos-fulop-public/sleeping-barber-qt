#pragma once

#include <QObject>
#include <QTimer>

class Barber : public QObject {
Q_OBJECT;
public:
    Barber(quint64 workTimeMsec);

public slots:
    void startWorkingOnCustomer(quint64 chairId);

signals:
    void finishedWithCustomer(quint64 chairId);

private:
    QTimer workTimer;
    quint64 currentChairId{0};
};
