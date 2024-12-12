//Solomon Archer

#include <iostream>
#include <string>
using namespace std;

// bank account
class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    // default constructor
    BankAccount() : accountNumber(0), accountHolderName(""), balance(0.0) {}

    //  arameterized constructor
    BankAccount(int accNum, string accName, double startingBalance) {
        accountNumber = accNum;
        accountHolderName = accName;
        if (startingBalance >= 0) {
            balance = startingBalance;
        } else {
            balance = 0.0;
            cout << "Invalid balance amount. Using zero instead..\n";
        }
    }

    // getters
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // setters
    void setAccountNumber(int accNum) { accountNumber = accNum; }
    void setAccountHolderName(string accName) { accountHolderName = accName; }
    void setBalance(double bal) { balance = bal; }

    // deposit ammount
    void deposit(double amount) {
      //check if amount is above zero
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Deposit amount must be greater than 0.\n";
        }
    }

    // withdraw amount 
    void withdraw(double amount) {
        //check if withdrawl is above zero and balance is sufficient
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        } else if (amount > balance) {
            cout << "Insufficient balance.\n";
        } else {
            cout << "Withdrawal amount must be greater than 0.\n";
        }
    }

    // display account details
    void displayAccountDetails() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder Name: " << accountHolderName << "\n";
        cout << "Balance: " << balance << "\n";
    }
};

// banking system
class BankingSystem {
private:
    BankAccount accounts[100]; // bank account object array
    int accountCounter;        // number of accounts 

public:
    // constructor
    BankingSystem() : accountCounter(0) {}

    // add account
    void addAccount() {
        if (accountCounter >= 100) {
            cout << "Account limit reached. Cannot add more accounts.\n";
            return;
        }

        int accNum;
        string accName;
        double startingBalance;

        cout << "Enter Account Number: ";
        cin >> accNum;
        cin.ignore(); // to consume newline character
        cout << "Enter Account Holder Name: ";
        getline(cin, accName);
        cout << "\n Enter Initial Balance: ";
        cin >> startingBalance;

        if (startingBalance < 0) {
            cout << "Initial balance cannot be negative. Account not created.\n";
            return;
        }

        accounts[accountCounter++] = BankAccount(accNum, accName, startingBalance);
        cout << "Account created successfully!\n";
    }

    // process transaction
    void processTransaction() {
        int accNum;
        char transactionType;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNum;

        // find account 
        int index = -1;
        for (int i = 0; i < accountCounter; i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter desired transaction type: D = Deposit, W = Withdraw: ";
        cin >> transactionType;
        cout << "Enter Amount: ";
        cin >> amount;

        if (transactionType == 'D' || transactionType == 'd') {
            accounts[index].deposit(amount);
        } else if (transactionType == 'W' || transactionType == 'w') {
            accounts[index].withdraw(amount);
        } else {
            cout << "Invalid transaction type.\n";
        }
    }

    // display all accounts
    void displayAllAccounts() const {
        if (accountCounter == 0) {
            cout << "No accounts available.\n";
            return;
        }

        for (int i = 0; i < accountCounter; i++) {
            cout << "Account " << i + 1 << ":\n";
            accounts[i].displayAccountDetails();
            cout << "----------------------\n";
        }
    }
};

// main interface
int main() {
    BankingSystem bankingSystem;
    int choice;

    do {
        cout << "Archer Online Banking \n";
        cout << "1. Add Account\n";
        cout << "2. Perform Transaction\n";
        cout << "3. Display All Accounts\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bankingSystem.addAccount();
            break;
        case 2:
            bankingSystem.processTransaction();
            break;
        case 3:
            bankingSystem.displayAllAccounts();
            break;
        case 4:
            cout << "Ending session. Hope to see you again! \n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
