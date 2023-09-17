#include <barber.h>

#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QSignalSpy>

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
	const auto expected_chair_id{1};
	barber.startWorkingOnCustomer(expected_chair_id);
	spy.wait(200);
	EXPECT_EQ(spy.count(), 1);
	quint64 chair_id = qvariant_cast<quint64>(spy.at(0).at(0));
	EXPECT_EQ(chair_id, expected_chair_id);
}

TEST_F(BarberTest, customerNotReady) {
	const auto expected_chair_id{4};
	barber.startWorkingOnCustomer(expected_chair_id);
	spy.wait(10);
	EXPECT_EQ(spy.count(), 0);
	spy.wait(200);
	EXPECT_EQ(spy.count(), 1);
	quint64 chair_id = qvariant_cast<quint64>(spy.at(0).at(0));
	EXPECT_EQ(chair_id, expected_chair_id);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	QCoreApplication a(argc, argv);
	return RUN_ALL_TESTS();
}
