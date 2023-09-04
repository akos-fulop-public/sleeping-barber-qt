#include <QObject>


enum class Chair{Empty, Occupied, InProgress};

class BarberShop : public QObject
{
    Q_OBJECT;
public slots:
    void checkForAvailableCustomers();

signals:
    void customerAvailable(quint64 chairId);

};
