#include <QObject>
#include <QTimer>
#include <QRandomGenerator>

class CustomerSpawner : public QObject {
    Q_OBJECT;
public:
    CustomerSpawner(QObject* parent = nullptr, quint64 min_msec = 2000, quint64 max_msec = 10'000);
public slots:
    void startSpawning();
    void stopSpawning();
private slots:
    void resetTimerAndFireAgain();

signals:
    void customerArrives();

protected:
    QRandomGenerator generator;
    quint64 min_msec, max_msec;
private:
    QTimer timer;
};
