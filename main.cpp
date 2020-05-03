#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AddressBook addressBook;
    AddressBookController addressBookControler(&addressBook);

    MainWindow w(&addressBookControler);

    w.show();
    return a.exec();
}
