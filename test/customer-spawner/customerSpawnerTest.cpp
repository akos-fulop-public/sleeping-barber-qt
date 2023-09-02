#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QSignalSpy>

#include <customerSpawner.h>

class CustomerSpawnerTest : public ::testing::Test {
public:
    CustomerSpawnerTest():
        spawner(nullptr, 10, 20),
        spy(&spawner, &CustomerSpawner::customerArrives)
    {}
protected:
    CustomerSpawner spawner;
    QSignalSpy spy;
};


TEST_F(CustomerSpawnerTest, spawnOneCustomer)
{
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(2000);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(CustomerSpawnerTest, spawnTwoCustomers)
{
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(2000);
    EXPECT_EQ(spy.count(), 1);
    spy.wait(2000);
    EXPECT_EQ(spy.count(), 2);
}

TEST_F(CustomerSpawnerTest, stopSpawning)
{
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(2000);
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
