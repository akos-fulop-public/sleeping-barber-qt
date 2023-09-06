#include <QObject>
#include <QList>

enum class Chair{Empty, Occupied, InProgress};

class BarberShop : public QObject
{
Q_OBJECT;

public:
    BarberShop(quint64 numberOfChairs) : chairs(numberOfChairs, Chair::Occupied) {
    }

public slots:
    void checkForAvailableCustomers();
    void finishedWithCustomer(quint64 chairId);

signals:
    void customerAvailable(quint64 chairId);

private:
    QList<Chair> chairs;
};
