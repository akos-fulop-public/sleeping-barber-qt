#include <QObject>

class CustomerSpawner : public QObject {
    Q_OBJECT;
public:
    CustomerSpawner(QObject*parent = nullptr) : QObject(parent)
    {}
public slots:
    void startSpawning();
private slots:
    void customerArrives_slot();

signals:
    void customerArrives();
};
