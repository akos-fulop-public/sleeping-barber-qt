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
    const auto expectedChairId{1};
    barber.startWorkingOnCustomer(expectedChairId);
    spy.wait(200);
    EXPECT_EQ(spy.count(), 1);
    quint64 chairId = qvariant_cast<quint64>(spy.at(0).at(0));
    EXPECT_EQ(chairId, expectedChairId);
}

TEST_F(BarberTest, customerNotReady) {
    const auto expectedChairId{4};
    barber.startWorkingOnCustomer(expectedChairId);
    spy.wait(10);
    EXPECT_EQ(spy.count(), 0);
    spy.wait(200);
    EXPECT_EQ(spy.count(), 1);
    quint64 chairId = qvariant_cast<quint64>(spy.at(0).at(0));
    EXPECT_EQ(chairId, expectedChairId);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
