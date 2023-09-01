#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QSignalSpy>

#include <customerSpawner.h>

TEST(CustomerSpawnerTest, createSpawner)
{
    CustomerSpawner spawner;
    QSignalSpy spy(&spawner, SIGNAL(customerArrives()));
    spawner.startSpawning();
    spy.wait(2000);
    EXPECT_EQ(spy.count(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
