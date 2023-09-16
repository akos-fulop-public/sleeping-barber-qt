#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QSignalSpy>

#include <customerSpawner.h>

class DeterministicCustomerSpawner : public CustomerSpawner {
public:
    DeterministicCustomerSpawner(QObject* parent, quint64 min_msec, quint64 max_msec) :
        CustomerSpawner(parent, min_msec, max_msec) {
        generator.seed(7373);  // sequence for bounded(10, 20): 12 13 18 18 19 19 13
    }
};

class CustomerSpawnerTest : public ::testing::Test {
public:
    CustomerSpawnerTest():
        spawner(nullptr, 10, 20),
        spy(&spawner, &CustomerSpawner::customerArrives)
    {}
protected:
    DeterministicCustomerSpawner spawner;
    QSignalSpy spy;
};


TEST_F(CustomerSpawnerTest, spawnOneCustomer) {
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(13);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(CustomerSpawnerTest, spawnTwoCustomers) {
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(13);
    EXPECT_EQ(spy.count(), 1);
    spy.wait(14);
    EXPECT_EQ(spy.count(), 2);
}

TEST_F(CustomerSpawnerTest, waitLessTimeThanNeeded) {
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(13);
    EXPECT_EQ(spy.count(), 1);
    spy.wait(14);
    EXPECT_EQ(spy.count(), 2);
    spy.wait(11);
    EXPECT_EQ(spy.count(), 2);
}


TEST_F(CustomerSpawnerTest, stopSpawning) {
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(13);
    EXPECT_EQ(spy.count(), 1);
    spawner.stopSpawning();
    spy.wait(200);
    EXPECT_EQ(spy.count(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
