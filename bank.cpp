#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

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
        if (amount <= 0)
        {
            cout << "Error: Deposit amount should be greater than zero." << endl;
            return;
        }
        setBalance(getBalance() + amount);
        cout << "\nYou deposited " << amount;
        cout << "\nYour new balance is " << getBalance() << endl;
    }

    // function for withdraw
    void withdraw(double amount) override
    {
        if (amount <= 0)
        {
            cout << "Error: Withdrawal amount should be greater than zero." << endl;
            return;
        }
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
        int subChoice = 0;
        while (subChoice != 4)
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

            // switch statement
            switch (subChoice)
            {
            case 1:
            {
                double amount;
                cout << "Enter the amount you want to deposit: ";

                while (!(cin >> amount))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid amount: ";
                }

                deposit(amount);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause();
                break;
            }
            case 2:
            {
                double amount;
                cout << "Enter the amount you want to withdraw: ";

                while (!(cin >> amount))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid amount: ";
                }

                withdraw(amount);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause();
                break;
            }
            case 3:
                cout << "\nYour balance is " << getBalance() << endl;
                pause();
                break;
            case 4:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        if (amount <= 0)
        {
            cout << "Error: Deposit amount should be greater than zero." << endl;
            return;
        }
        setBalance(getBalance() + amount);
        cout << "You have deposited " << amount;
        cout << "\nYour new balance is " << getBalance() << endl;
    }
    // function for withdraw
    void withdraw(double amount) override
    {
        if (amount <= 0)
        {
            cout << "Error: Withdrawal amount should be greater than zero." << endl;
            return;
        }
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
        int subChoice = 0;
        while (subChoice != 4)
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

            switch (subChoice)
            {
            case 1:
            {
                double amount;
                cout << "Enter the amount you want to deposit: ";

                while (!(cin >> amount))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid amount: ";
                }

                deposit(amount);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause();
                break;
            }
            case 2:
            {
                double amount;
                cout << "Enter the amount you want to withdraw: ";

                while (!(cin >> amount))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid amount: ";
                }

                withdraw(amount);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause();
                break;
            }
            case 3:
                cout << "Your balance is " << getBalance() << endl;
                pause();
                break;
            case 4:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    int choice = 0;
    CurrentAccount current;
    SavingAccount saving(minimumBalanceSaving);

    while (choice != 3)
    {
        clearScreen();
        cout << "\n--- Main Menu ---\n";
        cout << "1 - Saving Account\n";
        cout << "2 - Current Account\n";
        cout << "3 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        clearScreen();

        switch (choice)
        {
        case 1:
            saving.menu();
            break;
        case 2:
            current.menu();
            break;
        case 3:
            cout << "Thank you!" << endl;
            break;
        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again." << endl;
            pause();
        }
    }

    return 0;
}
