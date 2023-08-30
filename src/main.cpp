#include <QTextStream>

int main(int argc, char* argv[]) {
    QTextStream(stdout) << "Hello World!" << Qt::endl;
    return 0;
}
