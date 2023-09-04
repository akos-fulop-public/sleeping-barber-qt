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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
