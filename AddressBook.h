#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <string>

struct ContactNode {
    std::string name;
    std::string phone;
    std::string mail;
    ContactNode* next;
    ContactNode(const std::string& n, const std::string p, const std::string m);
};

class AddressBook {
public:
    AddressBook(const std::string& file);
    ~AddressBook();

    void addContact(const std::string& name, const std::string& phone, const std::string& mail);
    void removeContact(const std::string& name);
    bool isNotValidNumber(const std::string& number);
    void changeContact(const std::string oldName, const std::string& name, const std::string& mail, const std::string& phone);
    bool find (const  std::string& name);
    void searchContact(const std::string& name);
    bool isNValidEmail(std::string& mail);
    void viewContact();

private:
    ContactNode* head;
    std::string filePath;
    bool isLoadedFr;
    size_t index;

    void loadContacts();
    void saveContacts();
    void clearContacts();
};

#endif
