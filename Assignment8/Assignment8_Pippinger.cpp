#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class banking_System 
{
    //Public Member Functions
    public:
    // constructors:
    banking_System() {}; // constructor default
    banking_System(int number, string holder_Name, double balance); //constuctor with parameter
    //------------------------------------------
    // mutator functions:
    void deposit(int number, double amount); // mutator member function to deposit money
    void withdraw(int number, double amount); // mutator member function to withdraw money
    //------------------------------------------
    // Accessor functions:
    void display_account_details() const; // Accessor member fucntion to display details
    //
    int retrieve_existing_account();
    //-----------------------------------------------------------------------
    // Private Member Variables
    private:
    int account_Number = 0; //store a unique account number
    std::string account_Holder_Name = "";// store the account holder's name
    double account_balance = 0; // store the account balance
};
//-----------------------------------------------------
// Function prototypes for input veriifcation
bool clear_input_stream_foo(int choice);
bool Check_clear_input_stream_foo1(int number);
void clear_input_stream();
//----------------------------------------------------
// Main Function
int main()
{
    // Variables 
    const int size = 100; // Max number of banking accounts
    banking_System BankAccounts[size]; // Creation of Banking array
    int Number_of_accounts_in_Bank = 0; // Current number of accounts in array and current empty spot
    bool sentinel = true; 
    int choice; // variable for function choice in class
    bool banking_ready = true; // bool decides if user input is ready to initialize class
    //
    //
    while (sentinel)
    {
        // Display options for users
        cout << endl << "=== Banking System Menu ===" << endl;
        cout << "1. Add Account" << endl;
        cout << "2. Perform Transaction" << endl;
        cout << "3. Display All Accounts" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        //
        // choice input and verification
        cin >> choice;
        if (clear_input_stream_foo(choice)) // input verification for non ints/0/and negatives
            continue; // if true resets loop
        //--------------------------------------------------------------
        // Account Creation
        if (choice == 1)
        {
            int account_number = 0; // vairable for new account number
            string holder_Name = ""; // variable for user name
            double initial_balance = 0; // How much the user wants to put into theri account
            //
            // Prompt for user account and input plus function check_clear for zeros/ negatives anmd failed state
            cout << "Enter New Account Number: ";
            cin >> account_number;
            if (Check_clear_input_stream_foo1(account_number))
                continue;
            //
            // Prompt for user name
            cout << "Enter Account Holder Name: ";
            getline(cin, holder_Name);
            //
            // Prompt for user Balanace
            cout << "Enter Initial Balance:";
            cin >> initial_balance;
            if (Check_clear_input_stream_foo1(initial_balance)) // input verification for non ints/0/and negatives
                continue;
            //
            // for loop that calls my member function retrieve_exisitng_account 
            for (int i = 0; i < Number_of_accounts_in_Bank; i++) // checks if account chosen is already in the class array
            {                                                    // to avoid duplication
                if ((BankAccounts[i].retrieve_existing_account()) != account_number) // compares all existing accounts with user input
                {
                    banking_ready = true; // if user account is not in bank array via comparison ^^ bool is true
                    continue; // loop continues
                }
                else
                {
                    banking_ready = false; // if user account is in bank array banking_ready is false preventing user class initialization
                    cout << endl << "Account number already exist in the system, pick another!" << endl;
                    break;
                }
            }
            // 
            //
            if (banking_ready) // if true user information is made into class object and put into array BankAccounts
            {
                banking_System userBankAccount(account_number, holder_Name, initial_balance); // user class object
                //
                BankAccounts[Number_of_accounts_in_Bank] = userBankAccount; // puts user object into array
                Number_of_accounts_in_Bank++; // updates current empty spot for next object
            }
        }
            //---------------------------------------------------------------
            // Transaction type option for withdrawel adn deposit
        else if (choice == 2) 
        {
            int account_number2; // account number to choose account to withdraw/deposit to/from
            string transaction; // user decides transaction type
            double amount; // the amount of money 
            //
            // prompt for account number
            cout << "Enter Account Number: ";
            cin >> account_number2;
            if (Check_clear_input_stream_foo1(account_number2)) // input verification for non ints/0/and negatives
                continue;
            //
            // prompt foe transaction type
            cout << "Enter Transaction type (deposit/withdraw): ";
            cin >> transaction;
            //
            // prompt for money amount
            cout << "Enter Amount: ";
            cin >> amount;
            if (Check_clear_input_stream_foo1(amount)) // input verification for non ints/0/and negatives
                continue;
            //
            // changes the string transaction to lower charcters for easier comparison
            std::transform(transaction.begin(), transaction.end(), transaction.begin(), ::tolower);

            if (transaction == "deposit") // if "deposit" call class memeber function deposit
            {
                for (int i = 0; i < Number_of_accounts_in_Bank; i++) // loop through all accounts
                    BankAccounts[i].deposit(account_number2, amount); // member function deposit is called on all accounts
            }                                                        // if account_number matches existing account number amount is deposited
            else if (transaction == "withdraw")                  // same logic is used for withdraw
            {
                for (int i = 0; i < Number_of_accounts_in_Bank; i++)  // same logic is used for this loop
                    BankAccounts[i].withdraw(account_number2, amount); // same logic is used for memebr fucntion withdraw
            }
            else
                cout << "Enter a valid transaction" << endl; // if neither is called tell user eneter valid transaction
        }
            //-------------------------------------------------------------
            // Option to display all accounts
        else if (choice == 3)
        {
                for (int i = 0; i < Number_of_accounts_in_Bank; i++) // loop and cout information
                    BankAccounts[i].display_account_details(); // fucntion
        }
            //--------------------------------------------------------------
            // Exit
        else if (choice == 4) // exit chocie
        {
                sentinel = false; // breaks while loop
                cout << "Now Exiting!";
        }
    }
}
//--------------------------------------------------------------------------
// Function definitions for input verification
bool clear_input_stream_foo(int choice)
{
    if(cin.fail() || choice < 1 || choice > 4) // input verification for non ints/0/and negatives
    {
        clear_input_stream();
        return true;
    }
    else 
    {
        cin.ignore(1000, '\n');
        return false;
    }
}
bool Check_clear_input_stream_foo1(int number)
{
    if (cin.fail() || number <= 0) // input verification for non ints/0/and negatives
    {
        clear_input_stream();
        return true;
    }
    else 
    {
        cin.ignore(1000, '\n');
        return false;
    }
}
void clear_input_stream() // function clear input stream
{
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "[You entered an invalid input, TRY AGAIN!]" << endl; // output for bad input
}

//------------------------------------------------------------------------------
// member definitons:
banking_System::banking_System(int user_acct_number, string holder_Name, double balance) // constructor for banking_system
{
    account_Number = user_acct_number;         // All user information is stored access private member variables
    account_Holder_Name = holder_Name;
    account_balance = balance;
    cout << endl << "Account created succesfully" << endl;
}
void banking_System::deposit(int user_acct_number, double amount) // deposit member function
{
    if (user_acct_number == account_Number)    //if input account matches private account.. deposit amount
    {
        account_balance += amount;
        cout << endl << "Succesfully deposited $" << amount << " into account " << user_acct_number << endl;
    }
}
void banking_System::withdraw(int user_acct_number, double amount) // withdraw member function
{
    if (user_acct_number == account_Number)   // if input account matches private account.. withdraw amount
    {
        if (amount <= account_balance) // checks first that account balance is greater than amount withdrawn requested
        {
            account_balance -= amount;
            cout << endl << "Succesfully withdrew $" << amount << " from account " << user_acct_number << endl;
        }
        else
            cout << "You do not have sufficent funds!" << endl;   
    }
}
void banking_System::display_account_details() const // member fucntion to display all account information
{
    cout << endl << "Accounct number: " << account_Number << " ";
    cout << "| Holder: " << account_Holder_Name << " ";
    cout << "| Balance: " << account_balance << " " << endl ;
}
//
int banking_System::retrieve_existing_account() // member function to retrieve account number
{
    return account_Number;
}