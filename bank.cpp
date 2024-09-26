#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>
using namespace std;

// Function to check if input is a valid numeric string
bool isValidNum(const string &input)
{
    bool Decimal = false;

    for (char ch : input)
    {
        if (ch == '.')
        {
            if (Decimal)
            {
                return false;
            }
            Decimal = true;
        }
        else if (!isdigit(ch))
        {
            return false;
        }
    }
    return !input.empty();
}

// Function to get a valid amount from the user
void getValidAmount(double &amount)
{
    string input;
    while (true)
    {
        cout << "\nEnter amount: ";
        cin >> input;

        if (isValidNum(input))
        {
            amount = stod(input);
            if (amount <= 0)
            {
                cout << "Error: Amount must be greater than zero." << endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "Error: Please enter a valid positive numeric amount." << endl;
        }
    }
}

// function to clear and pause screen
void clearScreen();
void pause();

class Bank
{
private:
    double balance;

public:
    Bank() : balance(0) {}
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void menu() = 0;

    double getBalance()
    {
        return balance;
    }

    void setBalance(double newBalance)
    {
        balance = newBalance;
    }
};

class CurrentAccount : public Bank
{
public:
    CurrentAccount() {}

    // function for deposit
    void deposit(double amount) override
    {
        setBalance(getBalance() + amount);
        cout << "\nYou deposited " << amount;
        cout << "\nYour new balance is " << getBalance() << endl;
    }

    // function for withdraw
    void withdraw(double amount) override
    {
        if (amount > getBalance())
        {
            cout << "Error: Insufficient funds." << endl;
            return;
        }
        setBalance(getBalance() - amount);
        cout << "You withdrew " << amount;
        cout << "\nYour new balance is " << getBalance() << endl;
    }

    // function to display the current account menu
    void menu() override
    {
        string subChoice;
        while (subChoice != "4")
        {
            clearScreen();
            cout << "\n--- Current Account Menu ---\n";
            cout << "1 - Deposit\n";
            cout << "2 - Withdraw\n";
            cout << "3 - Check Balance\n";
            cout << "4 - Back\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            clearScreen();

            if (subChoice == "1")
            {
                double amount;
                getValidAmount(amount);
                deposit(amount);
                pause();
            }
            else if (subChoice == "2")
            {
                double amount;
                getValidAmount(amount);
                withdraw(amount);
                pause();
            }
            else if (subChoice == "3")
            {
                cout << "\nYour balance is " << getBalance() << endl;
                pause();
            }
            else if (subChoice == "4")
            {
                cout << "Returning to main menu..." << endl;
            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
                pause();
            }
        }
    }
};

class SavingAccount : public Bank
{
public:
    SavingAccount(double initializeBalance)
    {
        setBalance(initializeBalance);
    };

    // function for deposit
    void deposit(double amount) override
    {
        setBalance(getBalance() + amount);
        cout << "You have deposited " << amount;
        cout << "\nYour new balance is " << getBalance() << endl;
    }

    // function for withdraw
    void withdraw(double amount) override
    {
        if (amount > getBalance())
        {
            cout << "Error: Insufficient funds." << endl;
            return;
        }

        if (getBalance() - amount < 1000)
        {
            cout << "Error: Saving Account should have a minimum of 1000";
            return;
        }
        setBalance(getBalance() - amount);
        cout << "You withdrew " << amount;
        cout << "\nYour new balance is " << getBalance() << endl;
    }

    // function to display the menu for saving
    void menu() override
    {
        string subChoice;
        while (subChoice != "4")
        {
            clearScreen();
            cout << "\n--- Saving Account Menu ---\n";
            cout << "1 - Deposit\n";
            cout << "2 - Withdraw\n";
            cout << "3 - Check Balance\n";
            cout << "4 - Back\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            clearScreen();

            if (subChoice == "1")
            {
                double amount;
                getValidAmount(amount);
                deposit(amount);
                pause();
            }
            else if (subChoice == "2")
            {
                double amount;
                getValidAmount(amount);
                withdraw(amount);
                pause();
            }
            else if (subChoice == "3")
            {
                cout << "Your balance is " << getBalance() << endl;
                pause();
            }
            else if (subChoice == "4")
            {
                cout << "Returning to main menu..." << endl;
            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
                pause();
            }
        }
    }
};

// clear screen
void clearScreen()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

// pause
void pause()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int main()
{
    const double minimumBalanceSaving = 1000;
    string choice;
    CurrentAccount current;
    SavingAccount saving(minimumBalanceSaving);

    while (choice != "3")
    {
        clearScreen();
        cout << "\n--- Main Menu ---\n";
        cout << "1 - Saving Account\n";
        cout << "2 - Current Account\n";
        cout << "3 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        clearScreen();

        if (choice == "1")
        {
            saving.menu();
        }
        else if (choice == "2")
        {
            current.menu();
        }
        else if (choice == "3")
        {
            cout << "Thank you!" << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            pause();
        }
    }

    return 0;
}
