#include <iostream>
#include <string>

using namespace std;

// Classes for the bank account
class bankAccount {
    private:
    int accountNumber;
    string accountHolderName;
    double accountBalance;

    public:
    // default constructor
    bankAccount () {
        accountNumber = 0;
        accountHolderName = "";
        accountBalance = 0.0;
    }

    // constructor for parameters 
    bankAccount(int number, string& holderName, double balance){
        accountNumber = number;
        accountHolderName = holderName;
        accountBalance = balance;
    }

    // Functions for the accessors and mutators
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getAccountBalance() const { return accountBalance; }

    void setAccountNumber(int number) { accountNumber = number; }
    void setAccountHolderName(const string& holderName) { accountHolderName = holderName; }
    void setBalance(double newBalance) { accountBalance = newBalance; }

    // Functions for depositing and withdrawing money

    void deposit(double amount) {
        if (amount > 0)
            accountBalance += amount;
        else
            cout << "The deposit amount is invalid. Deposit be greater than 0.\n";
    }
    
    void withdraw(double amount) {
        if (amount > 0 && amount <= accountBalance)
            accountBalance -= amount;
        else if (amount > accountBalance)
            cout << "You have an insufficient amount for your balance.\n";
        else
            cout << "The withdrawal amount is invalid. Withdrawl be greater than 0.\n";
    }

    // Function to display account details
    void displayAccountDetails() const {
        cout << "Your account number is: " << accountNumber << "\n";
        cout << "The name of this account holder is: " << accountHolderName << "\n";
        cout << "Your account balance is: $" << accountBalance << "\n";
    }
};

// Banking system class
class bankSystem {
    private:
    bankAccount accounts[100];
    int countAccounts;

    public: 
        // Constructor for this class
        bankSystem() : countAccounts(0) {}

        // Function to add new accounts
        void addAccount() {
        if (countAccounts < 100) {
            int number;
            string holderName;
            double balance;

            cout << "Enter account number: ";
            cin >> number;
            cin.ignore();
            cout << "Enter account holder's name: ";
            getline(cin, holderName);
            cout << "Enter initial balance: ";
            cin >> balance;

            if (balance < 0) {
                cout << "Balance cannot be negative. Account creation failed." << endl;
                return;
            }

            accounts[countAccounts] = bankAccount(number, holderName, balance);
            countAccounts++;
            cout << "Account created successfully!" << endl;
        } else {
            cout << "Cannot add more accounts." << endl;
        }
    }  
    void performTransaction() {
        int number;
        char transactionType;
        double amount;

        cout << "Enter Account Number: ";
        cin >> number;

        // Using account number to find accounts    
        int index = -1;
        for (int i = 0; i < countAccounts; i++) {
            if (accounts[i].getAccountNumber() == number) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter what type of transaction you would like to do (D for Deposit, W for Withdraw): ";
        cin >> transactionType;
        cout << "Enter the amount of money you want to use: ";
        cin >> amount;

        if (transactionType == 'D' || transactionType == 'd')
            accounts[index].deposit(amount);
        else if (transactionType == 'W' || transactionType == 'w')
            accounts[index].withdraw(amount);
        else
            cout << "The type of transaction is invalid.\n";  
    }
    
    // Function to display every bank account
    void allAccounts() const {
        if (countAccounts == 0) {
            cout << "No accounts available.\n";
            return;
        }

        for (int i = 0; i < countAccounts; i++) {
            cout << "\n--- Account " << (i + 1) << " ---\n";
            accounts[i].displayAccountDetails();
        }
    }
};

// Main function
int main() {
    bankSystem bankSystem;
    int choice;

    do {
        cout << "\n--- Banking System Menu ---\n";
        cout << "Hello. Please select what you would like to do in the banking system today.\n";
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
                bankSystem.allAccounts();
                break;
            case 4:
                cout << "Exiting program. Have a good day!\n";
                break;
            default:
                cout << "Invalid choice. Please select integers 1-4.\n";
        }
    } while (choice != 4);

    return 0;
}