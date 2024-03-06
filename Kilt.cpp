#include <QApplication>
#include "kiltide.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    KiltIDE ide;
    ide.show();

    return app.exec();
}
