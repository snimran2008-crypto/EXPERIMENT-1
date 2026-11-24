#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

// Base custom exception class
class BankException : public exception
{
protected:
    string message;

public:
    explicit BankException(const string& msg) : message(msg) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// Derived exception class for insufficient balance
class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for withdrawal.")
    {
    }
};

// Derived exception class for invalid transaction amounts
class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Amount must be greater than zero.")
    {
    }
};

class BankAccount
{
private:
    string name;
    double balance;

public:
    BankAccount(const string& n, double b) : name(n), balance(b) {}

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
        cout << "Deposited Rs. " << amount << " successfully." << endl;
    }

    void withdraw(double amount)
    {
        // Validate first before modifying the balance
        if (amount <= 0)
            throw InvalidAmountException();
        if (amount > balance)
            throw InsufficientFundsException();

        // State changes only after all checks succeed
        balance -= amount;
        cout << "Withdrawn Rs. " << amount << " successfully." << endl;
    }

    void display() const
    {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

int main()
{
    string holderName;
    double initialBalance = 0.0;

    cout << "Enter Account Holder Name: ";
    getline(cin, holderName);
    if (holderName.empty())
    {
        holderName = "Customer";
    }

    cout << "Enter Initial Balance (Rs.): ";
    while (!(cin >> initialBalance) || initialBalance < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid balance. Enter a non-negative amount: ";
    }

    BankAccount account(holderName, initialBalance);

    cout << "\nInitial Account Details:" << endl;
    account.display();

    int choice = 0;
    do
    {
        cout << "\n===== Bank Menu =====" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Account Details" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            continue;
        }

        try
        {
            if (choice == 1)
            {
                double amount;
                cout << "Enter amount to deposit (Rs.): ";
                if (!(cin >> amount))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw BankException("Error: Invalid numeric input.");
                }
                account.deposit(amount);
            }
            else if (choice == 2)
            {
                double amount;
                cout << "Enter amount to withdraw (Rs.): ";
                if (!(cin >> amount))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw BankException("Error: Invalid numeric input.");
                }
                account.withdraw(amount);
            }
            else if (choice == 3)
            {
                account.display();
            }
            else if (choice != 4)
            {
                cout << "Invalid choice. Please select 1-4." << endl;
            }
        }
        catch (const InsufficientFundsException& e)
        {
            cout << e.what() << endl;
        }
        catch (const InvalidAmountException& e)
        {
            cout << e.what() << endl;
        }
        catch (const BankException& e)
        {
            cout << "Bank Exception: " << e.what() << endl;
        }
        catch (const exception& e)
        {
            cout << "General Exception: " << e.what() << endl;
        }

    } while (choice != 4);

    cout << "\nFinal Account Details:" << endl;
    account.display();

    return 0;
}