#include <QObject>
#include <QTimer>

class CustomerSpawner : public QObject {
    Q_OBJECT;
public:
    CustomerSpawner(QObject* parent = nullptr, quint64 msec = 2000);
public slots:
    void startSpawning();
private slots:
    void customerArrives_slot();

signals:
    void customerArrives();

private:
    QTimer timer;
};
