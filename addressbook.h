#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QObject>
#include <QList>

#include "addressbookentry.h"

class AddressBook : public QObject
{
    Q_OBJECT
public:
    typedef QList<AddressBookEntry*> Entries;
    explicit AddressBook(QObject *parent = nullptr);

    Entries entries() const;

    AddressBookEntry* createEntry();
    bool deleteEntry(AddressBookEntry *entry);

signals:
    void entryAdded(AddressBookEntry *entry);
    void entryRemoved(AddressBookEntry *entry);
private:
    Entries m_entries;

};

#endif // ADDRESSBOOK_H
