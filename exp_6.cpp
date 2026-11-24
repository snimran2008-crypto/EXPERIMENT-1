#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// Resource class
class Resource
{
private:
    string name;

public:
    explicit Resource(const string& resourceName) : name(resourceName)
    {
        cout << "Resource [" << name << "] acquired" << endl;
    }

    ~Resource()
    {
        cout << "Resource [" << name << "] released" << endl;
    }

    void use() const
    {
        cout << "Resource [" << name << "] is being used" << endl;
    }
};

// Manual Smart Pointer using RAII
class MySmartPointer
{
private:
    Resource* ptr;

public:
    explicit MySmartPointer(Resource* p) : ptr(p) {}

    ~MySmartPointer()
    {
        delete ptr;
        cout << "Manual smart pointer destroyed" << endl;
    }

    Resource* operator->()
    {
        return ptr;
    }

    // Disable copying to avoid double deletion
    MySmartPointer(const MySmartPointer&) = delete;
    MySmartPointer& operator=(const MySmartPointer&) = delete;
};

int main()
{
    int choice = 0;

    do
    {
        cout << "\n===== Smart Pointer Menu =====" << endl;
        cout << "1. Manual RAII Smart Pointer" << endl;
        cout << "2. std::unique_ptr" << endl;
        cout << "3. std::shared_ptr" << endl;
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

        if (choice >= 1 && choice <= 3)
        {
            string resourceName;
            cout << "Enter resource name: ";
            getline(cin, resourceName);

            if (resourceName.empty())
            {
                resourceName = "DefaultResource";
            }

            if (choice == 1)
            {
                cout << "\n----- Manual RAII Smart Pointer -----" << endl;
                {
                    MySmartPointer smartPtr(new Resource(resourceName));
                    smartPtr->use();
                }
            }
            else if (choice == 2)
            {
                cout << "\n----- unique_ptr -----" << endl;
                {
                    unique_ptr<Resource> uniquePtr = make_unique<Resource>(resourceName);
                    uniquePtr->use();
                }
            }
            else if (choice == 3)
            {
                int owners = 1;
                cout << "Enter number of shared_ptr owners (minimum 1): ";
                if (!(cin >> owners) || owners < 1)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    owners = 1;
                }

                cout << "\n----- shared_ptr -----" << endl;
                {
                    shared_ptr<Resource> sharedPtr1 = make_shared<Resource>(resourceName);
                    vector<shared_ptr<Resource>> extraOwners;

                    for (int i = 1; i < owners; ++i)
                    {
                        extraOwners.push_back(sharedPtr1);
                    }

                    sharedPtr1->use();
                    cout << "Shared Pointer Count: " << sharedPtr1.use_count() << endl;
                }
            }
        }
        else if (choice != 4)
        {
            cout << "Invalid choice. Please select 1-4." << endl;
        }

    } while (choice != 4);

    cout << "\nProgram completed successfully." << endl;
    return 0;
}