#include <iostream>
#include <unordered_map>  // Equivalent of Java HashMap
#include <string>

using namespace std;

// Base class: ATMSystem (Inheritance)
class ATMSystem {
protected: // Encapsulation: Protected members
    unordered_map<int, int> accounts; // HashMap equivalent: unordered_map to store PIN and balance
    int balance;
    
public:
    // Constructor to initialize balance
    ATMSystem() : balance(0) {}

    // Virtual function for menu options (Polymorphism: method overriding in derived classes)
    virtual void menu(int pin) {
        cout << "******************************************************************************" << endl;

        cout << "1. Check balance\n";
        cout<<"2. Withdraw money\n";
        cout<<"3. Deposit money\n";
        cout<<"4. Exit\n";
        cout<<"5. Check another account\n";

        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                checkBalance(pin);
                break;
            case 2:
                withdraw(pin);
                break;
            case 3:
                deposit(pin);
                break;
            case 4:
                cout << "Thank you for using our ATM." << endl;
                break;
            case 5:
                startATM();
                break;
            default:
                cout << "Invalid option." << endl;
                menu(pin); // Recursive call if the option is invalid
        }
    }

    // Abstraction: Simple function for checking balance
    void checkBalance(int pin) {
        cout << "Your current balance: " << accounts[pin] << endl;
        menu(pin);
    }

    // Abstraction: Function to deposit money
    void deposit(int pin) {
        cout << "Enter the amount to deposit: ";
        int amount;
        cin >> amount;
        accounts[pin] += amount;
        cout << "Amount deposited successfully.\n";
        menu(pin);
    }

    // Abstraction: Function to withdraw money
    void withdraw(int pin) {
        cout << "Enter the amount to withdraw: ";
        int amount;
        cin >> amount;
        if (amount > accounts[pin]) {
            cout << "Insufficient balance.\n";
        } else {
            accounts[pin] -= amount;
            cout << "Amount withdrawn successfully.\n";
        }
        menu(pin);
    }

    // Polymorphism: Derived class can override this function to change behavior
    virtual void startATM() {
        cout << "Welcome to the ATM\nEnter valid PIN: ";
        int pin;
        cin >> pin;

        // Check if the PIN exists in the unordered_map
        if (accounts.find(pin) != accounts.end()) {
            menu(pin); // Call the menu function with the existing account
        } else {
            cout << "Please create an account.\n";
            cout << "Set PIN (3-4 digits): ";
            int setpin;
            cin >> setpin;
            
            // Validate PIN length (Encapsulation: Protecting the logic)
            if (to_string(setpin).length() >= 3 && to_string(setpin).length() <= 4) {
                accounts[setpin] = 0; // Set initial balance to 0
                cout << "Account created successfully.\n";
                menu(setpin);
            } else {
                cout << "Invalid PIN. System terminated.\n";
            }
        }
    }
};

// Inheritance: Derived class from ATMSystem
class ATMop : public ATMSystem {
public:
    ATMop() {
        startATM(); // Inherited functionality from the base class
    }
};

int main() {
    ATMop atm; // Create an ATM object, which will invoke the constructor and start the system
    return 0;
}
