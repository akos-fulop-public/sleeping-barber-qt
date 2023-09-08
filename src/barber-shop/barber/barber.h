#include <QObject>

#include <QTimer>

class Barber : public QObject {
Q_OBJECT;
public:
    Barber(quint64 workTimeMsec);

public slots:
    void startWorkingOnCustomer();

signals:
    void finishedWithCustomer();

private:
    QTimer workTimer;
};
