#include <QObject>
#include <QList>

enum class Chair{Empty, Occupied, InProgress};

class BarberShop : public QObject
{
Q_OBJECT;

public:
    BarberShop(quint64 numberOfChairs) : chairs(numberOfChairs, Chair::Empty) {
    }

    const quint64 getServicedCustomers();

public slots:
    void customerArrived();
    void checkForAvailableCustomers();
    void finishedWithCustomer(quint64 chairId);

signals:
    void customerAvailable(quint64 chairId);
    void customerUnavailable();

private:
    QList<Chair> chairs;
    quint64 servicedCustomers{0};
};
