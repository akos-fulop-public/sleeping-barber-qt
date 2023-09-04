#include <QObject>


enum class Chair{Empty, Occupied, InProgress};

class BarberShop : public QObject
{
Q_OBJECT;

public:
    BarberShop() : chairCounter(0) {
    }

public slots:
    void checkForAvailableCustomers();

signals:
    void customerAvailable(quint64 chairId);

private:
    quint64 chairCounter;
};
