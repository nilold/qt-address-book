#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(AddressBookController *addresBookController, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_addresBookController(addresBookController)
{
    Q_ASSERT(addresBookController);
    ui->setupUi(this);

    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createEntry()
{
    auto entry = m_addresBookController->createEntry();

    if(entry){
        ui->listWidget->addItem(entry->name());
        auto listItem = ui->listWidget->item(ui->listWidget->count()-1);
        m_entryMap.insert(listItem, entry);

        ui->listWidget->setCurrentItem(listItem);
        editEntry();
    }
}

void MainWindow::deleteEntry()
{
    auto listItem = ui->listWidget->currentItem();

    if(listItem){
        auto entry = m_entryMap.value(listItem);
        if(entry){
            if(m_addresBookController->deleteEntry(entry)){
                m_entryMap.remove(listItem);
                delete listItem;
            }
        }
    }
}

void MainWindow::editEntry()
{
    auto listItem = ui->listWidget->currentItem();

    if(listItem){
        auto entry = m_entryMap.value(listItem);
        if(entry){
            ui->stackedWidget->setCurrentWidget(ui->detailsPage);
            ui->menuEntries->setEnabled(false);
            ui->newEntryButton->hide();

            setEntryEditItem(entry);
        }
    }
}

void MainWindow::saveEntry()
{
    auto listItem = ui->listWidget->currentItem();

    if(listItem){
        auto entry = m_entryMap.value(listItem);
        if(entry){
            setEntry(entry);
            cancel();
            listItem->setText(entry->name());
        }
    }
}

void MainWindow::setEntryEditItem(AddressBookEntry *entry)
{
    ui->nameEdit->setText(entry->name());
    ui->birthdayEdit->setDate(entry->birthday());
    ui->addressEdit->setPlainText(entry->address());
    ui->phoneNumbersEdit->setPlainText(entry->phoneNumbers().join("\n"));
}

void MainWindow::setEntry(AddressBookEntry *entry)
{
    entry->setName(ui->nameEdit->text());
    entry->setBirthday(ui->birthdayEdit->date());
    entry->setAddress(ui->addressEdit->toPlainText());
    entry->setPhoneNumbers(ui->phoneNumbersEdit->toPlainText().split("\n"));
}


void MainWindow::resetEntry()
{
    auto listItem = ui->listWidget->currentItem();

    if(listItem){
        auto entry = m_entryMap.value(listItem);
        if(entry){
            setEntryEditItem(entry);
        }
    }
}

void MainWindow::cancel(){
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    ui->menuEntries->setEnabled(true);
    ui->newEntryButton->show();
}

void MainWindow::discardEntry()
{
    cancel();
}

void MainWindow::setupConnections()
{
    //Menu actions
    connect(ui->actionAdd,  &QAction::triggered,this, &MainWindow::createEntry);
    connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::deleteEntry);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::editEntry);

    //Main interface actions
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editEntry()));
    connect(ui->newEntryButton, &QPushButton::clicked, this, &MainWindow::createEntry);

    //Details page actions
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &MainWindow::saveEntry);
    connect(ui->buttonBox->button(QDialogButtonBox::Discard), &QPushButton::clicked, this, &MainWindow::discardEntry);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked, this, &MainWindow::resetEntry);

}
