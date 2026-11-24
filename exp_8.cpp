#include <chrono>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <utility>

using namespace std;
using namespace chrono;

class String
{
private:
    char* data;
    size_t length;

public:
    // Constructor
    String(const char* str = "")
    {
        if (str == nullptr)
        {
            str = "";
        }
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    // Copy Constructor
    String(const String& other)
    {
        if (other.data != nullptr)
        {
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        else
        {
            data = nullptr;
            length = 0;
        }
    }

    // Move Constructor
    String(String&& other) noexcept
    {
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }

    // Copy Assignment Operator
    String& operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] data;
            if (other.data != nullptr)
            {
                length = other.length;
                data = new char[length + 1];
                strcpy(data, other.data);
            }
            else
            {
                data = nullptr;
                length = 0;
            }
        }
        return *this;
    }

    // Move Assignment Operator
    String& operator=(String&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // Destructor
    ~String()
    {
        delete[] data;
    }

    void display() const
    {
        if (data != nullptr)
            cout << data << endl;
        else
            cout << "[Empty / Moved-from]" << endl;
    }
};

// Perfect Forwarding Function
template <typename T>
String createString(T&& value)
{
    return String(forward<T>(value));
}

int main()
{
    int choice = 0;

    do
    {
        cout << "\n===== Copy, Move & Perfect Forwarding Menu =====" << endl;
        cout << "1. Demonstrate Copy & Move Semantics" << endl;
        cout << "2. Demonstrate Perfect Forwarding" << endl;
        cout << "3. Benchmark Copy vs Move Operations" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            string inputText;
            cout << "Enter a string: ";
            getline(cin, inputText);

            String original(inputText.c_str());
            String copied = original;        // Copy constructor
            String moved = move(original);   // Move constructor

            cout << "\nOriginal (after move): ";
            original.display();
            cout << "Copied String: ";
            copied.display();
            cout << "Moved String: ";
            moved.display();
        }
        else if (choice == 2)
        {
            string inputText;
            cout << "Enter a string for perfect forwarding: ";
            getline(cin, inputText);

            String forwarded = createString(inputText.c_str());
            cout << "Perfect Forwarding Result: ";
            forwarded.display();
        }
        else if (choice == 3)
        {
            string inputText;
            int iterations = 0;

            cout << "Enter a string to benchmark: ";
            getline(cin, inputText);
            if (inputText.empty())
            {
                inputText = "This is a resource-heavy string used to demonstrate copy and move semantics in C++.";
            }

            cout << "Enter number of iterations (e.g., 100000): ";
            while (!(cin >> iterations) || iterations <= 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid number. Enter a positive integer: ";
            }

            String original(inputText.c_str());

            // Benchmark Copy Operations
            auto startCopy = high_resolution_clock::now();
            for (int i = 0; i < iterations; i++)
            {
                String copy = original;
            }
            auto endCopy = high_resolution_clock::now();
            duration<double, milli> copyTime = endCopy - startCopy;

            // Benchmark Move Operations (without re-allocating inside the loop)
            String moveSource(inputText.c_str());
            auto startMove = high_resolution_clock::now();
            for (int i = 0; i < iterations; i++)
            {
                String moved = move(moveSource);
                moveSource = move(moved);
            }
            auto endMove = high_resolution_clock::now();
            duration<double, milli> moveTime = endMove - startMove;

            cout << "\nCopy Operation Time: " << copyTime.count() << " milliseconds" << endl;
            cout << "Move Operation Time: " << moveTime.count() << " milliseconds" << endl;
        }
        else if (choice != 4)
        {
            cout << "Invalid choice. Please select 1-4." << endl;
        }

    } while (choice != 4);

    cout << "\nProgram completed successfully." << endl;
    return 0;
}