#include <iostream>
#include <string>
using namespace std;

// Class for Bank Accounts
class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    // Default Constructor
    BankAccount() : accountNumber(0), accountHolderName(""), balance(0.0) {}

    // Parameterized Constructor
    BankAccount(int accNum, string holderName, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = holderName;
        balance = initialBalance > 0 ? initialBalance : 0.0; // Prevent negative balance
    }

    // Accessor Functions
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // Deposit Function
    void deposit(double amount) {
        if (amount > 0)
            balance += amount;
        else
            cout << "Invalid deposit amount. Must be greater than 0.\n";
    }

    // Withdraw Function
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance)
            balance -= amount;
        else if (amount > balance)
            cout << "Insufficient balance!\n";
        else
            cout << "Invalid withdrawal amount. Must be greater than 0.\n";
    }

    // Display Account Details
    void displayAccountDetails() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder: " << accountHolderName << "\n";
        cout << "Balance: $" << balance << "\n";
    }
};

// Class for the Banking System
class BankSystem {
private:
    BankAccount accounts[100]; // Array to store accounts
    int accountCount;          // Counter for total accounts

public:
    // Constructor
    BankSystem() : accountCount(0) {}

    // Add New Account
    void addAccount() {
        if (accountCount >= 100) {
            cout << "Bank account limit reached!\n";
            return;
        }

        int accNum;
        string holderName;
        double initialBalance;

        cout << "Enter Account Number: ";
        cin >> accNum;
        cin.ignore(); // Clear input buffer
        cout << "Enter Account Holder Name: ";
        getline(cin, holderName);
        cout << "Enter Initial Balance: ";
        cin >> initialBalance;

        if (initialBalance < 0) {
            cout << "Initial balance cannot be negative.\n";
            return;
        }

        accounts[accountCount] = BankAccount(accNum, holderName, initialBalance);
        accountCount++;
        cout << "Account added successfully!\n";
    }

    // Perform Transaction
    void performTransaction() {
        int accNum;
        char transactionType;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNum;

        // Find account by account number
        int index = -1;
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter Transaction Type (D for Deposit, W for Withdraw): ";
        cin >> transactionType;
        cout << "Enter Amount: ";
        cin >> amount;

        if (transactionType == 'D' || transactionType == 'd')
            accounts[index].deposit(amount);
        else if (transactionType == 'W' || transactionType == 'w')
            accounts[index].withdraw(amount);
        else
            cout << "Invalid transaction type.\n";
    }

    // Display All Accounts
    void displayAllAccounts() const {
        if (accountCount == 0) {
            cout << "No accounts available.\n";
            return;
        }

        for (int i = 0; i < accountCount; i++) {
            cout << "\n--- Account " << (i + 1) << " ---\n";
            accounts[i].displayAccountDetails();
        }
    }
};

// Main Function
int main() {
    BankSystem bankSystem;
    int choice;

    do {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Add Account\n";
        cout << "2. Perform Transaction\n";
        cout << "3. Display All Accounts\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bankSystem.addAccount();
                break;
            case 2:
                bankSystem.performTransaction();
                break;
            case 3:
                bankSystem.displayAllAccounts();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}