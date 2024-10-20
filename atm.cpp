#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <random>

using namespace std;

struct Transaction
{
    string type;
    double amount;
};

struct User
{
    string username;
    string pin;
    double balance;
    string AccountNo;
    vector<Transaction> transactionHistory;
};

bool is_6_digit(string pin);
bool isPresent(vector<User> &p, string &user_no, int& index1);
void viewBalance(vector<User> &p, int index);
void transferfunds(vector<User> &p, int &index);
void changeusername(vector<User> &p, int &index);
void show_user(vector<User> &p, int index);
void viewTransactionHistory(vector<User> &p, int &index);
bool isAuthenticated(vector<User> &p, string Username, string Userpin, int &index);
void instruction();
void withdrawCash(vector<User> &p, int index);
void depositCash(vector<User> &p, int &index);
void userAuthentication(vector<User> &p);
void modify(vector<User> &p, int index);
void changePIN(vector<User> &p, int index);
void logout(vector<User> &p);
void exit1(vector<User> &p);
void displayMainMenu2(vector<User> &p);
void showOptions(vector<User> &p, int index);
void login(vector<User> &p);
void displayMainMenu1(vector<User> &p);


int main()
{
    vector<User> Customers;

    displayMainMenu1(Customers);
    return 0;
}


bool is_6_digit(string pin)
{
    int len = pin.size();
    if (len == 6)
    {
        return true;
    }
    return false;
}
bool isPresent(vector<User> &p, string &user_no, int& index1)
{
    int size = p.size();
    if (size == 0)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (p[i].AccountNo == user_no)
            {
                index1 = i;
                return true;
            }
        }
        return false;
    }
}

void viewBalance(vector<User> &p, int index)
{
    cout << "Your current balance is: $" << fixed << setprecision(2) << p[index].balance << "\n";
}

void transferfunds(vector<User> &p, int &index)
{
    string pin1;
    cout << "Enter Your Pin" << endl;
    cin>>pin1;
    if (p[index].pin == pin1)
    {
        string user_no;
        string user_pin;
        double amount;
        int index1;
        cout << "Enter the Account no. of the user to whom you want to transfer: $";
        cin >> user_no;
        if (isPresent(p, user_no, index1))
        {
            cout << "Enter the amount you want to transfer" << endl;
            cin >> amount;
            if (amount <= p[index].balance)
            {
                p[index].balance -= amount;
                p[index1].balance += amount;
                Transaction transferdtransaction{"TransferTransaction", amount};
                p[index].transactionHistory.push_back(transferdtransaction);
            }
            else
            {
                cout << "You can't transfer this much amount" << endl;
            }
        }
        else
        {
            cout << "No such Account exists!!" << endl;
        }
    }
    else
    {
        cout << "Wrong Pin has been entered!!" << endl;
        transferfunds(p, index);
    }
}

void changeusername(vector<User> &p, int &index)
{
    string changedname;
    cout << "Enter the new username to change" << endl;
    cin >> changedname;
    p[index].username = changedname;
    cout << "Username is successfully Changed!!" << endl;
}

void show_user(vector<User> &p, int index){
    cout<<"Username-"<<p[index].username<<endl;
    cout<<"Pin-"<<p[index].pin<<endl;
    cout<<"Account-No-"<<p[index].AccountNo<<endl;
    cout<<"Balance-"<<p[index].balance<<endl;

}

void viewTransactionHistory(vector<User> &p, int &index)
{
    if (p[index].transactionHistory.empty())
    {
        cout << "No transactions available.\n";
    }
    else
    {
        cout << "Transaction History:\n";
        for (const auto &transaction : p[index].transactionHistory)
        {
            cout << "Type: " << transaction.type << ", Amount: $" << transaction.amount << "\n";
        }
    }
}

bool isAuthenticated(vector<User> &p, string Username, string Userpin, int &index)
{
    int size = p.size();
    if (size == 0)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (p[i].username == Username && p[i].pin == Userpin)
            {
                index = i;
                return true;
            }
        }
        return false;
    }
}

void instruction()
{
    cout << "\nMain Menu:\n";
    cout << "1. View Balance\n";
    cout << "2. Withdraw Cash\n";
    cout << "3. Deposit Cash\n";
    cout << "4. Transfer Funds\n";
    cout << "5. Show User\n";
    cout << "6. Change Pin\n";
    cout << "7. View Transaction History\n";
    cout << "8. Logout\n";
    cout << "Enter your choice: ";
}

void withdrawCash(vector<User> &p, int index)
{
    double withdrawalAmount;

    cout << "Enter the amount you want to withdraw: $";
    cin >> withdrawalAmount;

    if (withdrawalAmount > 0 && withdrawalAmount <= p[index].balance)
    {
        p[index].balance -= withdrawalAmount;
        Transaction withdrawalTransaction{"Withdrawal", withdrawalAmount};
        p[index].transactionHistory.push_back(withdrawalTransaction);
        cout << "Withdrawal successful. You withdrew: $" << withdrawalAmount << "\n";
        viewBalance(p, index); // Show updated balance
    }
    else
    {
        cout << "Invalid withdrawal amount or insufficient balance.\n";
    }
}

void depositCash(vector<User> &p, int &index)
{
    double depositAmount;

    cout << "Enter the amount you want to deposit: $";
    cin >> depositAmount;

    if (depositAmount > 0)
    {
        p[index].balance += depositAmount;
        Transaction depositTransaction{"Deposit", depositAmount};
        p[index].transactionHistory.push_back(depositTransaction);
        cout << "Deposit successful. You deposited: $" << depositAmount << "\n";
        viewBalance(p, index); // Show updated balance
    }
    else
    {
        cout << "Invalid deposit amount.\n";
    }
}




void userAuthentication(vector<User> &p)
{
    string enteredUsername, enteredPIN, confirmPIN;

    cout << "\nEnter username: ";
    cin >> enteredUsername;

    cout << "Enter PIN: ";
    cin >> enteredPIN;
    if (is_6_digit(enteredPIN))
    {
        cout << "Confirm PIN: ";
        cin >> confirmPIN;
        if (confirmPIN == enteredPIN)
        {
            cout << "User is Successfully created!!" << endl;

            User t;
            random_device rd;
            mt19937 gen(rd());

            uniform_int_distribution<int> distribution(10000000, 99999999);
            int random_number = distribution(gen);
            t.AccountNo = "PNB" + to_string(random_number);
            t.username = enteredUsername;
            t.pin = enteredPIN;
            t.balance = 0;
            t.transactionHistory = {};
            p.push_back(t);
        }

        else
        {
            cout << "Wrong input is given" << endl;
            userAuthentication(p);
        }
    }
    else
    {
        cout << "Pin should be of 6 digit!!" << endl;
        userAuthentication(p);
    }
}


void modify(vector<User> &p, int index)
{
    string newPIN;
    cout << "Enter your new PIN: ";
    cin >> newPIN;
    if (is_6_digit(newPIN))
    {
        p[index].pin = newPIN;
        cout << "PIN change successful. Your new PIN is: " << newPIN << "\n";
    }
    else
    {
        cout << "Pin should be of 6 digits!!" << endl;
        modify(p, index);
    }
}

void changePIN(vector<User> &p, int index)
{
    string newPIN, PIN;

    cout << "Enter Your Previous PIN: ";
    cin >> PIN;
    if (PIN == p[index].pin)
    {
        cout << "Enter your new PIN: ";
        cin >> newPIN;
        if (is_6_digit(newPIN))
        {
            p[index].pin = newPIN;
            cout << "PIN change successful. Your new PIN is: " << newPIN << "\n";
        }
        else
        {
            cout << "Pin should be of 6 digits!!" << endl;
            modify(p, index);
        }
    }
    else
    {
        cout << "Wrong Pin has been given" << endl;
        changePIN(p, index);
    }
}

void logout(vector<User> &p)
{
     // Reset the current user
    cout << "Logout successful. Thank you for using the ATM!\n";
    

}


void exit1(vector<User> &p)
{
    p={};
    cout << "Logout successful. Thank you for using the ATM!\n";
}

void displayMainMenu2(vector<User> &p)
{ // right
    int choice;

    do
    {
        cout << "\nMain Menu:\n";
        cout << "1. Login\n";
        cout << "2. User Authentication\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            login(p);
            break;
        case 2:
            userAuthentication(p);
            break;
        case 3: 
            exit1(p);
            
            cout << "Thank you for using the ATM. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);
}

void showOptions(vector<User> &p, int index)
{
    char choice;
    do
    {
        instruction();
        cin >> choice;

        switch (choice)
        {
        case '1':
            viewBalance(p, index);
            break;
        case '2':
            withdrawCash(p, index);
            break;
        case '3':
            depositCash(p, index);
            break;
        case '4':
            transferfunds(p, index);
            break;
        case '5':
            show_user(p, index);
            break;
        case '6':
            changePIN(p, index);
            break;
        case '7':
            viewTransactionHistory(p, index);
            break;
        case '8':
            logout(p);
            displayMainMenu2(p);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != '8');
}

void login(vector<User> &p)
{
    string enteredUsername, enteredPIN;

    cout << "\nEnter username: ";
    cin >> enteredUsername;

    cout << "Enter PIN: ";
    cin >> enteredPIN;
    int index = 0;
    // Assume you have a database or some mechanism to validate user credentials
    // For simplicity, a dummy user is used in this example
    if (isAuthenticated(p, enteredUsername, enteredPIN, index))
    {
        User currentUser = {enteredUsername, enteredPIN, 0, {}};
        cout << "Login successful. Welcome, " << currentUser.username << "!\n";
        // After successful login, display the main menu for transaction options
        showOptions(p, index); // For demonstration purposes, viewBalance is called directly after login
    }
    else
    {
        cout << "Login failed. Invalid username or PIN.\n";
    }
}

void displayMainMenu1(vector<User> &p)
{ // right
    int choice;

    do
    {
        cout << "\nMain Menu:\n";
        cout << "1. Login\n";
        cout << "2. User Authentication\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            login(p);
            break;
        case 2:
            userAuthentication(p);
            break;
        case 3: 
            exit1(p);
            
            cout << "Thank you for using the ATM. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);
}