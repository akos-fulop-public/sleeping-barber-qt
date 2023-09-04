#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QSignalSpy>

#include <barberShop.h>

class BarberShopTest : public ::testing::Test {
public:
    BarberShopTest():
        spy(&shop, &BarberShop::customerAvailable)
    {}
protected:
    BarberShop shop;
    QSignalSpy spy;
};

TEST_F(BarberShopTest, customersAvailable) {
    EXPECT_EQ(spy.count(), 0);
    emit shop.checkForAvailableCustomers();
    spy.wait(200);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(BarberShopTest, availableCustomerChairIdsIncrease) {
    EXPECT_EQ(spy.count(), 0);
    emit shop.checkForAvailableCustomers();
    spy.wait(200);
    EXPECT_EQ(spy.count(), 1);
    quint64 firstChairId = qvariant_cast<quint64>(spy.at(0).at(0));
    qDebug() << firstChairId;
    emit shop.checkForAvailableCustomers();
    spy.wait(200);
    EXPECT_EQ(spy.count(), 2);
    quint64 secondChairId = qvariant_cast<quint64>(spy.at(1).at(0));
    EXPECT_NE(firstChairId, secondChairId);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
