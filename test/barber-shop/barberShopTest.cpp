#include <barberShop.h>

#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QSignalSpy>

class BarberShopTest : public ::testing::Test {
public:
	BarberShopTest():
		shop(2),
		available_spy(&shop, &BarberShop::customerAvailable),
		unavailable_spy(&shop, &BarberShop::customerUnavailable)
	{}
protected:
	BarberShop shop;
	QSignalSpy available_spy, unavailable_spy;
};

TEST_F(BarberShopTest, customersAvailable) {
	emit shop.customerArrived();
	EXPECT_EQ(available_spy.count(), 0);
	emit shop.checkForAvailableCustomers();
	available_spy.wait(200);
	EXPECT_EQ(available_spy.count(), 1);
	EXPECT_EQ(shop.getServicedCustomers(), 0);
	quint64 first_chair_id = qvariant_cast<quint64>(available_spy.at(0).at(0));
	EXPECT_EQ(shop.getServicedCustomers(), 0);
	emit shop.finishedWithCustomer(first_chair_id);
	EXPECT_EQ(shop.getServicedCustomers(), 1);
}

TEST_F(BarberShopTest, customerUnavailable) {
	EXPECT_EQ(available_spy.count(), 0);
	EXPECT_EQ(unavailable_spy.count(), 0);
	emit shop.checkForAvailableCustomers();
	available_spy.wait(200);
	EXPECT_EQ(available_spy.count(), 0);
	EXPECT_EQ(unavailable_spy.count(), 1);
}

TEST_F(BarberShopTest, availableCustomerChairIdsIncrease) {
	emit shop.customerArrived();
	emit shop.customerArrived();
	EXPECT_EQ(available_spy.count(), 0);
	emit shop.checkForAvailableCustomers();
	available_spy.wait(200);
	EXPECT_EQ(available_spy.count(), 1);
	quint64 first_chair_id = qvariant_cast<quint64>(available_spy.at(0).at(0));
	qDebug() << first_chair_id;
	emit shop.checkForAvailableCustomers();
	available_spy.wait(200);
	EXPECT_EQ(available_spy.count(), 2);
	quint64 second_chair_id = qvariant_cast<quint64>(available_spy.at(1).at(0));
	EXPECT_NE(first_chair_id, second_chair_id);
}

TEST_F(BarberShopTest, shopFull) {
	for (auto i = 0 ; i < 3 ; ++i) {
		emit shop.customerArrived();
	}
	for (auto i = 0 ; i < 3 ; ++i) {
		emit shop.checkForAvailableCustomers();
	}
	EXPECT_EQ(available_spy.count(), 2);
	EXPECT_EQ(unavailable_spy.count(), 1);
	quint64 first_chair_id = qvariant_cast<quint64>(available_spy.at(0).at(0));
	quint64 second_chair_id = qvariant_cast<quint64>(available_spy.at(1).at(0));
	emit shop.finishedWithCustomer(first_chair_id);
	emit shop.finishedWithCustomer(second_chair_id);
	EXPECT_EQ(shop.getMissedCustomers(), 1);
	for (auto i = 0 ; i < 3 ; ++i) {
		emit shop.customerArrived();
	}
	for (auto i = 0 ; i < 3 ; ++i) {
		emit shop.checkForAvailableCustomers();
	}
	EXPECT_EQ(available_spy.count(), 4);
	EXPECT_EQ(unavailable_spy.count(), 2);
	EXPECT_EQ(shop.getServicedCustomers(), 2);
	EXPECT_EQ(shop.getMissedCustomers(), 2);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	QCoreApplication a(argc, argv);
	return RUN_ALL_TESTS();
}
