#include "AddressBook.h"
#include <iostream>
#include <fstream>

ContactNode::ContactNode(const std::string& n,const std::string p, const std::string m) : name(n), 
  phone(p), mail(m), next(nullptr) {}  

AddressBook::AddressBook(const std::string& file) :filePath(file) {
    head = nullptr;
    isLoadedFr = false;
    index = 0;
    loadContacts();
}
AddressBook::~AddressBook() { 
    saveContacts();
    clearContacts();
}

void AddressBook::addContact(const std::string& name, const std::string& phone, const std::string& mail) {
    ContactNode* newContact = new ContactNode(name, phone, mail);
    newContact -> next = head;
    head = newContact;
    isLoadedFr = false;
    saveContacts();
}

void AddressBook::removeContact(const std::string& name) {
    ContactNode* current  = head;
    ContactNode* prev = nullptr;
    bool found = {false};

    while (current != nullptr) {
        if(current -> name == name) {
            found = true;
            break;
        }
        prev = current;
        current = current -> next;
    }
        if(found) {
            if(prev != nullptr) {
                prev -> next = current ->next;
            }else {
                head = current -> next;
            }

            delete current;
            std::cout << "Contact with name " << name << " removed!" <<std::endl;
            std::cout << std::endl;
            saveContacts();
        }else {
            std::cout << "Contact with name " << name << " not found!" <<std::endl ;
            std::cout << std::endl;
        }
}

bool AddressBook::isNotValidNumber(const std::string& number) {  
    bool isNValid {false};
    
    if(number[0] != '0') return true;
        for(auto ch : number) {
            if(ch == 43) continue;
            ch < 48 || ch > 57 ? isNValid = true : isNValid;
        }
    return isNValid;
}

void AddressBook::changeContact(const std::string oldName, const std::string& name, const std::string& mail, const std::string& phone) {
    ContactNode* node = head;
    bool found = false;

    while (node != nullptr) {
        if(node -> name == oldName) {
            found = true;
            break;
        }
        node  = node -> next;
    }

    if(found) {
        node -> name = name;
        node -> phone = phone;
        node -> mail = mail;
        saveContacts();

        std::cout << "Contact updated successfully!" << std::endl;
        std::cout << std::endl;
    }else {
        std::cout << "Unabel update!" << std::endl;
        std::cout << std::endl;
    }
}

bool AddressBook::find (const  std::string& name) {
    ContactNode* node = head;

    while (node != nullptr) { 
        if(name == node -> name) {
            return true;
        }
        node = node -> next;
    }
    return false;
}
                
void AddressBook::searchContact(const std::string& name) {
    ContactNode* node  = head;
    bool found = false;

    while (node != nullptr) {
        if(node -> name == name) {
            found = true;
            break;
        }
        node  = node -> next;
    }

    if(found) {
        std::cout << "Name: " << node -> name << std::endl;
    	std::cout << "Phone: "	<< node -> phone << std::endl;
		std::cout << "Email: " << node-> mail << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << "Contact doesnt exist!" << std::endl;
    }
}   

bool AddressBook::isNValidEmail(std::string& mail) {
    bool isNVal {true};
    size_t checker {0};
    int len = mail.size();

    if(mail[0] == '@' || mail[0] == '.' || mail[len - 1] == '.' || mail[len - 1] =='@') return isNVal = true;

    for(int i = 0; i < len - 1; ++i) {
        if((mail[i] == '@' && mail[i+1] == '.') || (mail[i] == '.' && mail[i+1] == '@')) {
            return isNVal == true;
    }
        if(mail[0] != '@' || mail[0] != '.') {
            if(mail[i] == 64 || mail[i] == '.') { 
                 ++checker;
            }
        }
             
    }
    checker == 2 ? isNVal = false : isNVal;
    return isNVal;
}

void AddressBook::viewContact() {
    ContactNode* current = head;

    while(current != nullptr){
		std::cout << "Name: " << current -> name << std::endl;
		std::cout << "Phone: "	<< current -> phone << std::endl;
		std::cout << "Email: " << current -> mail << std::endl;
        std::cout << std::endl;
        current = current -> next;
    }
}

//Private member function definitions
void AddressBook::loadContacts() {
    isLoadedFr = false;
    std::ifstream inputFile(filePath);

    if (inputFile.is_open()) {
        clearContacts();
        std::string line;

        while (std::getline(inputFile, line)) {
            std::string name, phone, mail;
            if (line.find("Name: ") != std::string::npos) {
                name = line.substr(6);
                if (std::getline(inputFile, line) && line.find("Phone: ") != std::string::npos) {
                    phone = line.substr(7);
                    if (std::getline(inputFile, line) && line.find("Email: ") != std::string::npos) {
                        mail = line.substr(7);
                        std::getline(inputFile, line);
                        addContact(name, phone, mail);
                    }else {
                            std::cerr << "Invalid format for Email\n";
                            // Handle the error or skip the contact
                    }
                }else {
                        std::cerr << "Invalid format for Phone\n";
                        // Handle the error or skip the contact
                }
            }
        }
            inputFile.close();
            isLoadedFr = true; // Mark that contacts are loaded from the file
    }
}

void AddressBook::saveContacts() {
    std::ofstream outputFile(filePath, std::ofstream::out | std::ofstream:: trunc );

    if (outputFile.is_open()) {
        ContactNode* current = head;

        while(current != nullptr) {
            outputFile << index << std::endl;
            outputFile << "Name: " <<current -> name << std::endl;
            outputFile << "Phone: " << current -> phone << std::endl;
            outputFile << "Email: " <<current -> mail << std::endl;
            outputFile << std::endl;
            current = current -> next;
            ++index;
        }
        index = 0;
        outputFile.close();

    } else {
        std::cout << "Error opening the file.";
    }
}
        
void AddressBook::clearContacts() {
    while(head != nullptr) {
        ContactNode* tmp = head;
        head = head -> next;
        delete tmp;
    }
}
