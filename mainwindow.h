#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>

#include "addressbookcontroller.h"


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class QListWidgetItem;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(AddressBookController *m_addresBookController, QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    // menu actions
    void createEntry();
    void deleteEntry();
    void editEntry();

    //details page actions
    void saveEntry();
    void discardEntry();
    void resetEntry();
    void showAboutDialog();

private:
    Ui::MainWindow *ui;
    AddressBookController *m_addresBookController;
    QHash<QListWidgetItem*, AddressBookEntry*> m_entryMap;

    void setupConnections();
    void cancel();
    void setEntryEditItem(AddressBookEntry *entry);
    void setEntry(AddressBookEntry *entry);
};
#endif // MAINWINDOW_H
