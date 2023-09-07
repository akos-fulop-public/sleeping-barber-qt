#include <gtest/gtest.h>
#include <QCoreApplication>

#include <barber.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);
    return RUN_ALL_TESTS();
}
