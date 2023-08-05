#include "AddressBook.h"
#include <iostream>

void userInt(AddressBook& book) {
    char choise;
    do{
        std::cout << "Address Book menu:\n";
        std::cout << "View all contacts, enter _ 1:" << std::endl;
        std::cout << "Add new contact, enter ___ 2:" << std::endl;
        std::cout << "Remove contact, enter ____ 3:" << std::endl;
        std::cout << "Find contact, enter ______ 4:" << std::endl;
        std::cout << "Refresh contact, enter ___ 5:" << std::endl;
        std::cout << "Exit, enter ______________ 6:" << std::endl;
        std::cout << "Enter your choise: " << std::endl;
        std::cin >> choise;

        std::cin.ignore();

        switch(choise) {
            case '1': {
                book.viewContact();
                break;
            }
            case '2': { 
                std::string name, number, mail;
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter number: ";
                std::getline(std::cin, number);

                if(book.isNotValidNumber(number)) {
                    std::cout << "Please enter valid Phone number\n";
                    break;
                }
                std::cout << "Enter mail: ";
                std::getline(std::cin, mail);

                if (book.isNValidEmail(mail)) {
                    std::cout << "Please enter valid Email\n";
                    break;
                }
        
                book.addContact(name,number,mail);
                std::cout << "Contact added successfully !\n";
                std::cout << std::endl;
                        break;
            }
            case '3': {
                std::cout << "Enter contact name you want to remove!\n";
                std::string name;
                std::getline(std::cin, name);
                book.removeContact(name);
                break;
                
            }
            case '4': {
                std::cout << "Enter contact name you are searching" << std::endl;
                std::string name {""};
                std::getline(std::cin, name);
                book.searchContact(name);
                break;
            }
            case '5': {
                std::cout << "Enter contact name you want to change" << std::endl;
                std::string name {""};
                std::getline(std::cin, name);
                bool found = book.find(name);

                if(book.find(name)) { 
                    std::cout << "Enter new name: ";
                    std::string nName {""};
                    std::getline(std::cin, nName);

                    std::cout << "Enter new phone number: ";
                    std::string nNumber {""};
                    std::getline(std::cin, nNumber);
                    if(book.isNotValidNumber(nNumber)) {
                        std::cout << "Please enter valid Phone number\n";
                        break;
                    }

                    std::cout << "Enter new mail: ";
                    std::string nMail {" "};
                    std::getline(std::cin, nMail);

                    if (book.isNValidEmail(nMail)) {
                        std::cout << "Please enter valid Email\n";
                        break;
                    }
                    book.changeContact(name, nName, nNumber, nMail); 
                }else { 
                    std::cout << "Contact doesnt exist! " << std:: endl;
                }
            }
            case '6': {
                std::cout << "Exit:" <<std::endl; 
                break;
            }
            default:{
                std::cout <<"Invalid choise, Try again:\n";
                break;
            }
        } 
    } while(choise != '6');

}

int main() {
    AddressBook book("addrBook.txt");
    userInt(book);
    return 0;
}
