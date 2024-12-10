#include <iostream>
#include <string>
using namespace std;

// BankAccount Class
class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    // Default constructor
    BankAccount() {
        accountNumber = 0;
        accountHolderName = "";
        balance = 0.0;
    }

    // Parameterized constructor
    BankAccount(int accNum, const string& accName, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = accName;
        balance = initialBalance;
    }

    // Accessor and mutator functions
    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void setAccountNumber(int accNum) {
        accountNumber = accNum;
    }

    void setAccountHolderName(const string& accName) {
        accountHolderName = accName;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }

    // Function to deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit of $" << amount << " successful. New balance: $" << balance << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    // Function to withdraw money
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal of $" << amount << " successful. New balance: $" << balance << endl;
        } else if (amount > balance) {
            cout << "Insufficient balance. Withdrawal failed." << endl;
        } else {
            cout << "Withdrawal amount must be positive." << endl;
        }
    }

    // Function to display account details
    void displayAccountDetails() const {
        cout << "Account Number: " << accountNumber << ", Holder: " << accountHolderName
             << ", Balance: $" << balance << endl;
    }
};

// BankSystem Class
class BankSystem {
private:
    BankAccount accounts[100];
    int accountCount;

public:
    // Constructor
    BankSystem() : accountCount(0) {}

    // Function to add a new account
    void addAccount() {
        if (accountCount < 100) {
            int accNum;
            string accName;
            double initialBalance;

            cout << "Enter account number: ";
            cin >> accNum;
            cin.ignore(); // Clear newline left in the buffer
            cout << "Enter account holder's name: ";
            getline(cin, accName);
            cout << "Enter initial balance: ";
            cin >> initialBalance;

            if (initialBalance < 0) {
                cout << "Balance cannot be negative. Account creation failed." << endl;
                return;
            }

            accounts[accountCount] = BankAccount(accNum, accName, initialBalance);
            accountCount++;
            cout << "Account created successfully!" << endl;
        } else {
            cout << "Maximum account limit reached. Cannot add more accounts." << endl;
        }
    }

    // Function to perform a transaction
    void performTransaction() {
        int accNum;
        cout << "Enter account number for transaction: ";
        cin >> accNum;

        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].getAccountNumber() == accNum) {
                int choice;
                cout << "1. Deposit\n2. Withdraw\nEnter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    double amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    accounts[i].deposit(amount);
                } else if (choice == 2) {
                    double amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    accounts[i].withdraw(amount);
                } else {
                    cout << "Invalid transaction choice." << endl;
                }
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    // Function to display all accounts
    void displayAllAccounts() const {
        if (accountCount == 0) {
            cout << "No accounts available to display." << endl;
        } else {
            for (int i = 0; i < accountCount; ++i) {
                accounts[i].displayAccountDetails();
            }
        }
    }
};

// Main Function
int main() {
    BankSystem bankSystem;
    int choice;

    do {
        cout << "\n=== Banking System Menu ===\n";
        cout << "1. Add Account\n2. Perform Transaction\n3. Display All Accounts\n4. Exit\n";
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
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
