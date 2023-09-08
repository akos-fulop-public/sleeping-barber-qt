#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QSignalSpy>

#include <barber.h>

class BarberTest : public ::testing::Test {
public:
    BarberTest():
        spy(&barber, &Barber::finishedWithCustomer)
    {}
protected:
    Barber barber{100};
    QSignalSpy spy;
};

TEST_F(BarberTest, workOnCustomer) {
    barber.startWorkingOnCustomer();
    spy.wait(200);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(BarberTest, customerNotReady) {
    barber.startWorkingOnCustomer();
    spy.wait(10);
    EXPECT_EQ(spy.count(), 0);
    spy.wait(200);
    EXPECT_EQ(spy.count(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
