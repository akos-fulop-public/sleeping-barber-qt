#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QSignalSpy>

#include <customerSpawner.h>

TEST(CustomerSpawnerTest, createSpawner)
{
    CustomerSpawner spawner(nullptr, 10);
    QSignalSpy spy(&spawner, SIGNAL(customerArrives()));
    EXPECT_EQ(spy.count(), 0);
    spawner.startSpawning();
    spy.wait(2000);
    EXPECT_EQ(spy.count(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
