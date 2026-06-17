#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("QUIZ GAME");
    w.setWindowIcon(QIcon("img/icon/quiz.png"));
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);

    w.show();
    w.setFixedSize(w.size());
    return a.exec();
}
