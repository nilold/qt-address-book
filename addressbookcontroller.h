#ifndef ADDRESSBOOKCONTROLLER_H
#define ADDRESSBOOKCONTROLLER_H

#include <QObject>

#include "addressbook.h"

class AddressBookController : public QObject
{
    Q_OBJECT
public:
    explicit AddressBookController(AddressBook *addressBook, QObject *parent = nullptr);

    AddressBookEntry *createEntry();
    bool deleteEntry (AddressBookEntry *entry);

signals:

private:
    AddressBook *m_addressBook;

};

#endif // ADDRESSBOOKCONTROLLER_H
