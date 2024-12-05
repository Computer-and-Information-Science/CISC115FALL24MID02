#include<iostream>
#include<iomanip>
#include<cctype>
using namespace std;
//Creates class to handle individual accounts
class bankAccount{
private:
	int accountNumber;
	string accountHolderName;
	double accountBalance;
public:
	//creates a default constructor so that all new accounts have no balance by default
	bankAccount() {
		accountNumber = 0;
		accountHolderName = "N/A";
		accountBalance = 0;
	}
	//Sets account info to the parameters
	bankAccount(int number, string name, double balance) {
		accountNumber = number;
		accountHolderName = name;
		accountBalance = balance;
	}
	//searches if an account number exists and returns te result
	bool searchAccountNumber(int checkNumber) {
		if (checkNumber == accountNumber) {
			return true;
		}
		else {
			return false;
		}
	}
	//deposits money into an account
	void accountDeposit() {
		double depositAmount;
		//display the current balance with two decimal places
		cout << fixed << showpoint;
		cout << "Current balance: $" << setprecision(2) << accountBalance << endl;
			cout << "How much would you like to deposit?\n";
			cin >> depositAmount;
			//checks if deposit amount is more than zero to verify that it is a valid input
			//if it is valid then update balance, if input is not valid give an error
			if (depositAmount > 0) {
				accountBalance += depositAmount;
				cout << "New balance: $" << setprecision(2) << accountBalance << endl;
			}
			else {
				cin.clear();
			cin.ignore(1000, '\n');
			cout << "ERROR: Please enter a valid number (minimum 1) with no text characters (e.g. '$' or 'a')";
			return;
			}
			
		
	}
	//function to withdraw money from account
	void accountWithdraw() {
		//shows balance to two decimals
		double withdrawAmount;
		cout << fixed << showpoint;
		cout << "Current balance: $" << setprecision(2) << accountBalance << endl;
			cout << "How much would you like to withdraw?\n";
			cin >> withdrawAmount;
			//if the withdrawn amount is more than the current balance, this will stop the overdraft
			if (withdrawAmount > accountBalance) {
				cout << "ERROR: Cannot withdraw more money than is in account\n";
				return;
			} else if (withdrawAmount > 0) {
				accountBalance -= withdrawAmount;
				cout << "New balance: $" << setprecision(2) << accountBalance << endl;
			}
			else { //if the withdrawn amount is less than zero, it is an invalid input and an error with be output
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "ERROR: Please enter a valid number (minimum 1) with no text characters (e.g. '$' or 'a')\n";
				return;
			}

	}
	//outputs the information of the account
	const void accountDetails() {
		cout << "Account number: " << accountNumber << " Account name: " << accountHolderName;
		cout << fixed << showpoint;
		cout << " Account balance: " << setprecision(2) << accountBalance << endl;
	}

};
//class to handle all accounts
class bankSystem {
private:
	//creates an array of 100 accounts
	bankAccount accountArray[100];
	int counter = 0;
public:
	//function to add an account
	void addAccount() {
		string newAccountName;
		int newAccountNumber;
		double newAccountBalance;
		cout << "Please enter your name: ";
			cin >> newAccountName;
			//repeats as a loop until a valid account number is given
			do {
				cout << "Please enter the account number: ";
				cin >> newAccountNumber;
				//checks whether it is negative and therfore invalid
				if (newAccountNumber < 0) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ERROR: Please enter a positive number\n";
				}
				//takes the number user is attempting to assign to this account and checks it against the number of every existing account
				//if an account already has the number, it repeats the loop and gets a new number
				for (int i = 0; i < counter; i++) {
					if (accountArray[i].searchAccountNumber(newAccountNumber) == true) {
						cout << "Account number already exists, please select a different number\n";
						newAccountNumber = -1;
						break;
					}
				}
			} while (newAccountNumber < 0);
			//another loop to verify a valid number input
			do {
				cout << "Please enter the initial balance: ";
				cin >> newAccountBalance;
				if (newAccountBalance < 0) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "ERROR: Please enter a positive number\n";
				}
			} while (newAccountBalance < 0);
		//assigns inputted account information to the account using a parameterized constructor
		bankAccount newAccount(newAccountNumber, newAccountName, newAccountBalance);
		//assigns the new account to the array
		accountArray[counter] = newAccount;
		//increase the number of accounts by 1
		counter++;

	}
	//function to handle transactions
	void systemTransaction() {
		//check if there are no accounts
		if (counter == 0) {
			cout << "ERROR: No accounts in the system\n";
			return;
		}
		//declares i outside the for loop because it needs to be used outside the for loop to check for errors
		int transactionAccount, i;
		string transactionType;
		cout << "Please enter your account number: ";
		cin >> transactionAccount;
		//checks if the input is invalid
		if (isdigit(cin.peek()) == false && transactionAccount < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ERROR: Only positive numbers allowed\n";
			return;
		}
		//cycles through each existing account to check if the inputting account number matches
		//if it finds a match, it will continue the transaction for the account
		for (i = 0; i < counter; i++) {
			if (accountArray[i].searchAccountNumber(transactionAccount) == true) {
				do {
					cout << "Would you like to deposit or withdraw? (deposit)/(withdraw)\n";
					cin >> transactionType;
					if (transactionType == "deposit") {
						accountArray[i].accountDeposit();
					}
					else if (transactionType == "withdraw") {
						accountArray[i].accountWithdraw();
					}
					else { // checks for invalid input
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid input: Please enter either deposit or withdraw\n";
					}
				} while (transactionType != "deposit" && transactionType != "withdraw"); //repeats loop until there is a valid input
				break; //exit the loop if the correct account is found
			}
		}
		//if the account number inputted does not match the numbed of the last checked element of the array, there is no account with that number
		//this is because when the for loop finds an account with the correct account number, it will complete the transaction and end the loop
		//if it does not find an account with a matching account number, i will be the last element of the array and will still be false when checked
		if (accountArray[i].searchAccountNumber(transactionAccount) == false) {
			cout << "ERROR: INVALID ACCOUNT NUMBER\n";
		}
	}

	//cycles through each account and displays the information
	void systemDisplayAccounts() {
		//checks if there aren't any accounts
		if (counter == 0) {
			cout << "ERROR: No accounts in the system\n";
				return;
		}
		for (int i = 0; i < counter; i++) {
			accountArray[i].accountDetails();
		}
	}
};
int main() {
	int menuInput;
	bankSystem system;
	do {
		cout << "||==== Bank System Menu ====||\n";
		cout << "1. Add account\n";
		cout << "2. Display accounts\n";
		cout << "3. Perform transaction\n";
		cout << "4. Exit\n";
		cout << "Make a selection: ";
		cin >> menuInput;
		switch (menuInput) {
		case 1:
			system.addAccount();
			break;
		case 2:
			system.systemDisplayAccounts();
			break;
		case 3:
			system.systemTransaction();
			break;
		case 4:
			cout << "Thank you, goodbye";
			return 0;
		default:
			cout << "\nInvalid input, please select a number 1-4\n\n";
			cin.clear();
			cin.ignore(100, '\n');
		continue;
		}
	} while (menuInput != 4);
	return 0;
};