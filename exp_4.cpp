#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

template <class T>
class MyStack
{
private:
    T* data;
    int top;
    int capacity;

public:
    MyStack(int size)
    {
        capacity = size;
        data = new T[capacity];
        top = -1;
    }

    ~MyStack()
    {
        delete[] data;
    }

    void push(T value)
    {
        if (top < capacity - 1)
            data[++top] = value;
    }

    void pop()
    {
        if (top >= 0)
            top--;
    }
};

template <class T>
class MyQueue
{
private:
    T* data;
    int front, rear;
    int capacity;

public:
    MyQueue(int size)
    {
        capacity = size;
        data = new T[capacity];
        front = 0;
        rear = -1;
    }

    ~MyQueue()
    {
        delete[] data;
    }

    void enqueue(T value)
    {
        if (rear < capacity - 1)
            data[++rear] = value;
    }

    void dequeue()
    {
        if (front <= rear)
            front++;
    }
};

int main()
{
    int N;
    cout << "Enter the number of elements: ";
    cin >> N;

    if (N <= 0)
    {
        cout << "Number of elements must be positive." << endl;
        return 1;
    }

    vector<int> values(N);
    cout << "Enter " << N << " integer values: ";
    for (int i = 0; i < N; i++)
    {
        cin >> values[i];
    }

    // Custom Stack Benchmark
    auto start = high_resolution_clock::now();
    MyStack<int> myStack(N);
    for (int i = 0; i < N; i++)
        myStack.push(values[i]);
    for (int i = 0; i < N; i++)
        myStack.pop();
    auto end = high_resolution_clock::now();
    auto customStackTime = duration_cast<microseconds>(end - start);

    // STL Stack Benchmark
    start = high_resolution_clock::now();
    stack<int> stlStack;
    for (int i = 0; i < N; i++)
        stlStack.push(values[i]);
    for (int i = 0; i < N; i++)
        stlStack.pop();
    end = high_resolution_clock::now();
    auto stlStackTime = duration_cast<microseconds>(end - start);

    // Custom Queue Benchmark
    start = high_resolution_clock::now();
    MyQueue<int> myQueue(N);
    for (int i = 0; i < N; i++)
        myQueue.enqueue(values[i]);
    for (int i = 0; i < N; i++)
        myQueue.dequeue();
    end = high_resolution_clock::now();
    auto customQueueTime = duration_cast<microseconds>(end - start);

    // STL Queue Benchmark
    start = high_resolution_clock::now();
    queue<int> stlQueue;
    for (int i = 0; i < N; i++)
        stlQueue.push(values[i]);
    for (int i = 0; i < N; i++)
        stlQueue.pop();
    end = high_resolution_clock::now();
    auto stlQueueTime = duration_cast<microseconds>(end - start);

    cout << "\nCustom Stack Time: " << customStackTime.count() << " microseconds" << endl;
    cout << "STL Stack Time:    " << stlStackTime.count() << " microseconds" << endl;
    cout << "Custom Queue Time: " << customQueueTime.count() << " microseconds" << endl;
    cout << "STL Queue Time:    " << stlQueueTime.count() << " microseconds" << endl;

    return 0;
}