#include <iostream>
#include <string>
using namespace std;

//Class for bank accounts
class bankAccount{
private:

    //Private class for specific account information
    int accountNumber;           
    string accountHolderName;    
    double accountBalance;       

public:

    //Constructor with default values; sets accounts to 0
    bankAccount() : accountNumber(0), accountHolderName(""), accountBalance(0.0){}

    //Constructor that defines account info for parameters
    bankAccount(int num, string name, double balance){
        accountNumber = num;
        accountHolderName = name;
        accountBalance = balance;
    }

    //Obtains the user input and stores it into each respective variable
    int getAccountNumber() const {return accountNumber;}
    string getAccountHolderName() const {return accountHolderName;}
    double getBalance() const {return accountBalance;}

    //Declares the value equal to other variables
    void setAccountNumber(int num) {accountNumber = num;}
    void setAccountHolderName(string name) {accountHolderName = name;}
    void setBalance(double newBalance) {accountBalance = newBalance;}

    //Function for depositing money
    void deposit(double amount){
        if (amount <= 0){
            cout << "Deposit amount must be positive." << endl;
        } 
        else{
            accountBalance += amount;
            cout << "Deposit successful. New balance: $" << accountBalance << endl;
        }
    }

    //Function for withdrawing money
    void withdraw(double amount){
        if (amount <= 0){
            cout << "Withdrawal amount must be positive." << endl;
        }
        else if (amount > accountBalance){
            cout << "Insufficient funds. Withdrawal failed." << endl;
        } 
        else{
            accountBalance -= amount;
            cout << "Withdrawal successful. New balance: $" << accountBalance << endl;
        }
    }

    //Function that displays account information
    void displayAccountDetails() const{
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Balance: $" << accountBalance << endl;
    }

};

//Class for banking system
class bankSystem{

private:

    //Array and counter for logging accounts
    bankAccount accounts[100];    
    int accountCount;             

public:

    bankSystem() : accountCount(0) {}

    //Function for adding a new account
    void addAccount(){

        //Error message in case max number of accounts has been reached
        if (accountCount >= 100){
            cout << "Cannot add more accounts. Maximum limit reached." << endl;
            return;
        }

        int accNum;
        string accName;
        double initialBalance;

        //Prompts user for account information
        cout << "Enter account number: ";
        cin >> accNum;
        cin.ignore(); 
        cout << "Enter account holder name: ";
        getline(cin, accName);
        cout << "Enter initial balance: ";
        cin >> initialBalance;

        //Error in case entered balance is not a valid amount; negative
        if (initialBalance < 0){
            cout << "Initial balance cannot be negative. Account creation failed." << endl;
            return;
        }

        //Stores account into banking system
        accounts[accountCount] = bankAccount(accNum, accName, initialBalance);
        accountCount++;
        cout << "Successfully created account. Thank you!" << endl;
    }

    //Function for either withdrawing or depositing money
    void performTransaction(){

        int accNum;
        cout << "Enter account number: ";
        cin >> accNum;

        for (int i = 0; i < accountCount; i++){
            if (accounts[i].getAccountNumber() == accNum){
                int choice;
                double amount;
                cout << "1. Deposit\n2. Withdraw\nEnter your choice: ";
                cin >> choice;

                //If user wishes to deposit
                if (choice == 1){
                    cout << "How much would you like to deposit? ";
                    cin >> amount;
                    accounts[i].deposit(amount);
                } 
                //If user wishes to withdraw
                else if (choice == 2){
                    cout << "How much would you like to withdraw? ";
                    cin >> amount;
                    accounts[i].withdraw(amount);
                } 
                else{
                    cout << "Error. Invalid choice." << endl;
                }

                return;

            }
        }

        //Displays in case account is not found in bank system
        cout << "Account not found." << endl;

    }

    //Function for displaying account details; all accounts
    void displayAllAccounts() const{

        //In case no accounts have been entered
        if (accountCount == 0){
            cout << "No accounts to display." << endl;
            return;
        }

        for (int i = 0; i < accountCount; i++){
            cout << "Account " << i + 1 << " Details:" << endl;
            accounts[i].displayAccountDetails();
            cout << "--------------------------" << endl;
        }
    }
};

int main(){
    bankSystem bank;
    int choice;

    //Executes banking process
    do{
        cout << "\nBanking System Menu:\n";
        cout << "1. Add Account\n";
        cout << "2. Perform Transaction\n";
        cout << "3. Display All Accounts\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bank.addAccount();
            break;
        case 2:
            bank.performTransaction();
            break;
        case 3:
            bank.displayAllAccounts();
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