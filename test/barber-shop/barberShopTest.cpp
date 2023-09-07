#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QSignalSpy>

#include <barberShop.h>

class BarberShopTest : public ::testing::Test {
public:
    BarberShopTest():
        shop(2),
        availableSpy(&shop, &BarberShop::customerAvailable),
        unavailableSpy(&shop, &BarberShop::customerUnavailable)
    {}
protected:
    BarberShop shop;
    QSignalSpy availableSpy, unavailableSpy;
};

TEST_F(BarberShopTest, customersAvailable) {
    emit shop.customerArrived();
    EXPECT_EQ(availableSpy.count(), 0);
    emit shop.checkForAvailableCustomers();
    availableSpy.wait(200);
    EXPECT_EQ(availableSpy.count(), 1);
    EXPECT_EQ(shop.getServicedCustomers(), 0);
    quint64 firstChairId = qvariant_cast<quint64>(availableSpy.at(0).at(0));
    EXPECT_EQ(shop.getServicedCustomers(), 0);
    emit shop.finishedWithCustomer(firstChairId);
    EXPECT_EQ(shop.getServicedCustomers(), 1);
}

TEST_F(BarberShopTest, customerUnavailable) {
    EXPECT_EQ(availableSpy.count(), 0);
    EXPECT_EQ(unavailableSpy.count(), 0);
    emit shop.checkForAvailableCustomers();
    availableSpy.wait(200);
    EXPECT_EQ(availableSpy.count(), 0);
    EXPECT_EQ(unavailableSpy.count(), 1);
}

TEST_F(BarberShopTest, availableCustomerChairIdsIncrease) {
    emit shop.customerArrived();
    emit shop.customerArrived();
    EXPECT_EQ(availableSpy.count(), 0);
    emit shop.checkForAvailableCustomers();
    availableSpy.wait(200);
    EXPECT_EQ(availableSpy.count(), 1);
    quint64 firstChairId = qvariant_cast<quint64>(availableSpy.at(0).at(0));
    qDebug() << firstChairId;
    emit shop.checkForAvailableCustomers();
    availableSpy.wait(200);
    EXPECT_EQ(availableSpy.count(), 2);
    quint64 secondChairId = qvariant_cast<quint64>(availableSpy.at(1).at(0));
    EXPECT_NE(firstChairId, secondChairId);
}

TEST_F(BarberShopTest, shopFull) {
    for (auto i = 0 ; i < 3 ; ++i) {
        emit shop.customerArrived();
    }
    for (auto i = 0 ; i < 3 ; ++i) {
        emit shop.checkForAvailableCustomers();
    }
    EXPECT_EQ(availableSpy.count(), 2);
    EXPECT_EQ(unavailableSpy.count(), 1);
    quint64 firstChairId = qvariant_cast<quint64>(availableSpy.at(0).at(0));
    quint64 secondChairId = qvariant_cast<quint64>(availableSpy.at(1).at(0));
    emit shop.finishedWithCustomer(firstChairId);
    emit shop.finishedWithCustomer(secondChairId);
    EXPECT_EQ(shop.getMissedCustomers(), 1);
    for (auto i = 0 ; i < 3 ; ++i) {
        emit shop.customerArrived();
    }
    for (auto i = 0 ; i < 3 ; ++i) {
        emit shop.checkForAvailableCustomers();
    }
    EXPECT_EQ(availableSpy.count(), 4);
    EXPECT_EQ(unavailableSpy.count(), 2);
    EXPECT_EQ(shop.getServicedCustomers(), 2);
    EXPECT_EQ(shop.getMissedCustomers(), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
