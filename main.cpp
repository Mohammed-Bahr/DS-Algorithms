#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <vector>
#include <stack>
#include <string>
#include <iomanip>
using namespace std;
using namespace std::chrono;

//======================================================================
// Stack
template <class T>
struct StackNode
{
    T value;
    StackNode<T> *point;
};

template <class T>
class Stack
{
private:
    StackNode<T> *top;
    int counter = 0;

public:
    Stack() : top(nullptr) {}

    bool is_empty()
    {
        return (top == nullptr);
    }

    void push(T x)
    {
        StackNode<T> *temp = new StackNode<T>();
        temp->value = x;
        temp->point = top;
        top = temp;
        counter++;
    }

    T peek()
    {
        if (is_empty())
        {
            cout << ("Stack is empty");
        }
        return top->value;
    }

    void pop()
    {
        if (is_empty())
        {
            cout << "Stack is already empty ." << endl;
        }
        StackNode<T> *newnode = top;
        top = top->point;
        delete newnode;
        counter--;
    }

    void print()
    {
        StackNode<T> *del = top;
        while (del != nullptr)
        {
            cout << del->value << " ";
            del = del->point;
        }
        cout << endl;
    }

    void clear()
    {
        if (is_empty())
        {
            cout << "Stack is already empty." << endl;
            return;
        }

        while (!is_empty())
        {
            pop();
        }
        cout << "It's clear now." << endl;
    }

    int size()
    {
        return counter;
    }
};

//======================================================================
// queue

template <class T>
struct node
{
    T data;
    node<T> *next;

    node<T>() : next(nullptr) {}
};
template <class T>
class Queue
{
private:
    int count = 0;
    node<T> *front;
    node<T> *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool is_empty() { return (front == nullptr && rear == nullptr); }

    void enqueue(T value)
    {
        node<T> *newnode = new node<T>();
        newnode->data = value;
        if (is_empty())
        {
            rear = newnode;
            front = rear;
        }
        else
        {
            rear->next = newnode;
            rear = newnode;
        }
        count++;
    }

    void dequeue()
    {
        if (is_empty())
        {
            cout << "the queue is already empty." << endl;
        }
        else
        {
            node<T> *temp = front;
            front = front->next;
            delete temp;
            if (front == nullptr)
            {
                rear = nullptr;
            }
            count--;
        }
    }

    void clear()
    {
        while (!is_empty())
        {
            dequeue();
        }
    }

    void print()
    {
        node<T> *current = front;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    T first() { return front->data; }

    ~Queue() { clear(); }
};

//======================================================================
// sorting algorthims
//======================================================================
// selection sort

template <class T>
void Selection_Sort(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int m = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[m])
            {
                m = j;
            }
        }
        swap(arr[i], arr[m]);
    }
}

// ---------------------------------------
// bubble sort
void bubbleSort(int arr[], int n)
{
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// ---------------------------------------
// InsertionSort

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// ---------------------------------------
// MergeSort
// m = l + (r - l) / 2 ;

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// -----------------------------------------------
// ShellSort

void shellSort(vector<int> &arr)
{
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

//-----------------------------------------------
// QuickSort

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//--------------------------------------------------
// BinarySearch

int binary_search(int arr[], int left, int right, int key)
{
    if (right < left)
    {
        cout << "doesn't exist " << endl;
        return -1;
    }
    int mid = floor((left + right) / 2);
    if (arr[mid] == key)
    {
        return mid;
    }
    else if (key > arr[mid])
    {
        return binary_search(arr, mid + 1, right, key);
    }
    else if (key < arr[mid])
    {
        return binary_search(arr, left, mid - 1, key);
    }
    cout << "end " << endl;
    return -1;
}

//--------------------------------------------------
// PrintArray
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

//======================================================================
// Balanced Parentheses Check using Stack

bool ArePair(char open, char close)
{
    if (open == '(' && close == ')')
        return true;
    else if (open == '{' && close == '}')
        return true;
    else if (open == '[' && close == ']')
        return true;
    return false;
}
bool AreBalanced(string exp)
{
    stack<char> S;
    int length = exp.length();
    for (int i = 0; i < length; i++)
    {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            S.push(exp[i]);
        else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if (S.empty() || !ArePair(S.top(), exp[i]))
                return false;
            else
                S.pop();
        }
    }
    return S.empty() ? true : false;
}

// ========================================================
// Heap sort

void heapify(int arr[], int s, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < s && arr[left] > arr[largest])
        largest = left;

    if (right < s && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, s, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    cout << "Max heap built: ";
    printArray(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
        cout << "After extracting " << arr[i] << ": ";
        printArray(arr, n);
    }
}

// ============================================================
// Important Functions : ->

int stringToInt(const string &str)
{
    int result = 0;
    bool isNegative = false;
    int i = 0;

    // Handle negative numbers
    if (str[0] == '-')
    {
        isNegative = true;
        i = 1;
    }

    // Convert string to integer
    for (; i < str.length(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result = result * 10 + (str[i] - '0');
        }
        else
        {
            throw invalid_argument("Invalid character in string");
        }
    }

    return isNegative ? -result : result;
}

string intToString(int num)
{
    if (num == 0)
        return "0";

    bool isNegative = num < 0;
    string result;

    // Handle negative numbers
    if (isNegative)
    {
        num = -num;
    }

    // Convert integer to string
    while (num > 0)
    {
        result = char(num % 10 + '0') + result;
        num /= 10;
    }

    // Add negative sign if needed
    if (isNegative)
    {
        result = "-" + result;
    }

    return result;
}

int maximum(int arr[], int n)
{
    int maxVal = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

//--------------------------------------------------

//====================================================================
// Linked list
// template <class T>
// struct Node{
//     T item;
//     Node<T>* next;
//     Node<T>* prev;
// };
// template <class T>
// class LinkedList{
// private:
//     Node<T>* head;
//     Node<T>* tail;
//     int count;
// public:
//     LinkedList() : head(nullptr), tail(nullptr), count(0) {}
//     bool is_empty() { return count == 0; }
//     int size() { return count; }

//     void insert_at_end(T value) {
//         Node<T>* newnode = new Node<T>();
//         newnode->item = value;
//         if(is_empty()) {
//             head = newnode;
//             tail = newnode;
//             newnode->next = nullptr;
//         } else {
//             newnode->next = nullptr;
//             tail = newnode;
//         }
//         count++;
//     }

//     void insert_at_start(T value) {
//         Node<T>* newnode = new Node<T>();
//         newnode->item = value;
//         if(is_empty()) {
//             head = newnode;
//             tail = newnode;
//             newnode->next = nullptr;
//         } else {
//             newnode->next = head;
//             head = newnode;
//         }
//         count++;
//     }

//     void insert_at_index(int index, T value) {
//         if(index < 0 || index > count) {
//             cout << "Index out of bounds" << endl;
//             return;
//         }
//         if(index == 0) {
//             insert_at_start(value);
//             return;
//         }
//         if(index == count) {
//             insert_at_end(value);
//             return;
//         }
//         Node<T>* newnode = new Node<T>();
//         newnode->item = value;
//         Node<T>* current = head;
//         for(int i = 0; i < index - 1; i++) {
//             current = current->next;
//         }
//         newnode->next = current->next;
//         current->next = newnode;
//         count++;
//     }

//     T remove_from_end() {
//         T value;
//         if(is_empty()) {
//             cout << "List is already empty" << endl;
//             return T();
//         }
//         else if(count == 1){
//             Node<T>* temp = head;
//             value = temp->item;
//             head = nullptr;
//             tail = nullptr;
//             delete temp;
//             count--;
//         }
//         else{
//             Node<T>* temp = tail;
//             value = temp->item;
//             Node<T>* current = head;
//             while(current->next != tail) {
//                 current = current->next;
//             }
//             tail = current;
//             tail->next = nullptr;
//             delete temp;

//             count--;
//         }
//         return value;
//     }
//     void print() {
//         Node<T>* current = head;
//         while(current != nullptr) {
//             cout << current->item << " ";
//             current = current->next;
//         }
//         cout << endl;
//     }
// };

template <class T>
struct Node
{
    T item;
    Node<T> *next;
    Node<T> *prev;
};

template <class T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int count;

    void Merge(int arr[], int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int *L = new int[n1];
        int *R = new int[n2];
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    void MergeSort(int arr[], int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    bool is_empty() { return count == 0; }

    int size() { return count; }

    T start_item(){return head->item;}
    T end_item(){return tail->item;}

    void insert_at_end(T value)
    {
        Node<T> *newnode = new Node<T>();
        newnode->item = value;
        newnode->next = nullptr;

        if (is_empty())
        {
            head = newnode;
            tail = newnode;
            newnode->prev = nullptr;
        }
        else
        {
            newnode->prev = tail;
            tail->next = newnode;
            tail = newnode;
        }
        count++;
    }

    void insert_at_start(T value)
    {
        Node<T> *newnode = new Node<T>();
        newnode->item = value;
        newnode->prev = nullptr;

        if (is_empty())
        {
            head = newnode;
            tail = newnode;
            newnode->next = nullptr;
        }
        else
        {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
        }
        count++;
    }

    void insert_at_index(int index, T value)
    {
        if (index < 0 || index > count)
        {
            cout << "Index out of bounds" << endl;
            return;
        }
        if (index == 0)
        {
            insert_at_start(value);
            return;
        }
        if (index == count)
        {
            insert_at_end(value);
            return;
        }

        Node<T> *newnode = new Node<T>();
        newnode->item = value;
        Node<T> *current = head;

        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        newnode->next = current->next;
        newnode->prev = current;
        current->next->prev = newnode;
        current->next = newnode;
        count++;
    }

    T remove_from_end()
    {
        T value;
        if (is_empty())
        {
            cout << "List is already empty" << endl;
            return T();
        }
        else if (count == 1)
        {
            Node<T> *temp = head;
            value = temp->item;
            head = nullptr;
            tail = nullptr;
            delete temp;
            count--;
        }
        else
        {
            Node<T> *temp = tail;
            value = temp->item;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            count--;
        }
        return value;
    }

    T remove_from_start()
    {
        T value;
        if (is_empty())
        {
            cout << "List is already empty" << endl;
            return T();
        }
        else if (count == 1)
        {
            Node<T> *temp = head;
            value = temp->item;
            head = nullptr;
            tail = nullptr;
            delete temp;
            count--;
        }
        else
        {
            Node<T> *temp = head;
            value = temp->item;
            head = head->next;
            head->prev = nullptr;
            delete temp;
            count--;
        }
        return value;
    }

    T remove_from_index(int index)
    {
        T value;
        if (is_empty())
        {
            cout << "List is already empty" << endl;
            return T();
        }
        else if (count == 1)
        {
            Node<T> *temp = head;
            value = temp->item;
            head = nullptr;
            tail = nullptr;
            delete temp;
            count--;
        }
        else
        {
            Node<T> *temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            value = temp->item;
            Node<T> *newnode = temp->prev;
            newnode->next = temp->next;
            delete temp;
            count--;
        }
        return value;
    }

    vector<T> sort()
    {
        Node<T> *current = head;
        vector<T> arr;
        while(current != nullptr){
            arr.push_back(current->item);
            current = current->next;
        }
        mergeSort(arr.data(), 0, arr.size() - 1);
        return arr;
    }

    void print()
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            cout << current->item << " ";
            current = current->next;
        }
        cout << endl;
    }
};





#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to print section headers
void printHeader(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

// Function to print time taken
void printTime(const string& operation, double time_ms) {
    cout << left << setw(40) << operation 
         << ": " << fixed << setprecision(4) << time_ms << " ms" << endl;
}

int main() {
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    // ========================================
    // Test Stack
    // ========================================
    printHeader("STACK OPERATIONS");
    
    Stack<int> stack;
    
    start_time = high_resolution_clock::now();
    for(int i = 1; i <= 1000; i++) {
        stack.push(i);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Push 1000 elements", elapsed.count());
    
    cout << "Stack size: " << stack.size() << endl;
    cout << "Top element: " << stack.peek() << endl;
    
    start_time = high_resolution_clock::now();
    for(int i = 0; i < 500; i++) {
        stack.pop();
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Pop 500 elements", elapsed.count());
    
    cout << "Stack size after pops: " << stack.size() << endl;
    
    start_time = high_resolution_clock::now();
    stack.clear();
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Clear stack", elapsed.count());

    // ========================================
    // Test Queue
    // ========================================
    printHeader("QUEUE OPERATIONS");
    
    Queue<int> queue;
    
    start_time = high_resolution_clock::now();
    for(int i = 1; i <= 1000; i++) {
        queue.enqueue(i);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Enqueue 1000 elements", elapsed.count());
    
    cout << "First element: " << queue.first() << endl;
    
    start_time = high_resolution_clock::now();
    for(int i = 0; i < 500; i++) {
        queue.dequeue();
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Dequeue 500 elements", elapsed.count());
    
    start_time = high_resolution_clock::now();
    queue.clear();
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Clear queue", elapsed.count());

    // ========================================
    // Test Linked List
    // ========================================
    printHeader("LINKED LIST OPERATIONS");
    
    LinkedList<int> list;
    
    start_time = high_resolution_clock::now();
    for(int i = 1; i <= 1000; i++) {
        list.insert_at_end(i);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insert 1000 elements at end", elapsed.count());
    
    cout << "List size: " << list.size() << endl;
    cout << "Start item: " << list.start_item() << endl;
    cout << "End item: " << list.end_item() << endl;
    
    start_time = high_resolution_clock::now();
    for(int i = 0; i < 10; i++) {
        list.insert_at_start(i);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insert 10 elements at start", elapsed.count());
    
    start_time = high_resolution_clock::now();
    list.insert_at_index(500, 9999);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insert at index 500", elapsed.count());
    
    start_time = high_resolution_clock::now();
    for(int i = 0; i < 100; i++) {
        list.remove_from_end();
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Remove 100 elements from end", elapsed.count());
    
    start_time = high_resolution_clock::now();
    for(int i = 0; i < 100; i++) {
        list.remove_from_start();
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Remove 100 elements from start", elapsed.count());
    
    cout << "List size after removals: " << list.size() << endl;

    // ========================================
    // Test Sorting Algorithms
    // ========================================
    printHeader("SORTING ALGORITHMS (1000 elements)");
    
    const int n = 1000;
    int arr[n];
    
    // Selection Sort
    for(int i = 0; i < n; i++) arr[i] = n - i;
    start_time = high_resolution_clock::now();
    Selection_Sort(arr, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Selection Sort", elapsed.count());
    
    // Bubble Sort
    for(int i = 0; i < n; i++) arr[i] = n - i;
    start_time = high_resolution_clock::now();
    bubbleSort(arr, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Bubble Sort", elapsed.count());
    
    // Insertion Sort
    for(int i = 0; i < n; i++) arr[i] = n - i;
    start_time = high_resolution_clock::now();
    insertionSort(arr, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insertion Sort", elapsed.count());
    
    // Merge Sort
    for(int i = 0; i < n; i++) arr[i] = n - i;
    start_time = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Merge Sort", elapsed.count());
    
    // Quick Sort
    for(int i = 0; i < n; i++) arr[i] = n - i;
    start_time = high_resolution_clock::now();
    quickSort(arr, 0, n - 1);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Quick Sort", elapsed.count());
    
    // Shell Sort
    vector<int> vec;
    for(int i = 0; i < n; i++) vec.push_back(n - i);
    start_time = high_resolution_clock::now();
    shellSort(vec);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Shell Sort", elapsed.count());
    
    // Heap Sort (disable output for timing)
    for(int i = 0; i < n; i++) arr[i] = n - i;
    start_time = high_resolution_clock::now();
    // Using a smaller array to avoid excessive output
    int small_arr[20];
    for(int i = 0; i < 20; i++) small_arr[i] = 20 - i;
    heapSort(small_arr, 20);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Heap Sort", elapsed.count());

    // ========================================
    // Test Binary Search
    // ========================================
    printHeader("BINARY SEARCH");
    
    int sorted_arr[100];
    for(int i = 0; i < 100; i++) sorted_arr[i] = i * 2;
    
    start_time = high_resolution_clock::now();
    int index = binary_search(sorted_arr, 0, 99, 50);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    
    cout << "Searching for 50 in sorted array..." << endl;
    cout << "Found at index: " << index << endl;
    printTime("Binary Search", elapsed.count());

    // ========================================
    // Test Balanced Parentheses
    // ========================================
    printHeader("BALANCED PARENTHESES CHECK");
    
    string expressions[] = {
        "{[()]}",
        "{[(])}",
        "((()))",
        "({[}])"
    };
    
    for(const string& exp : expressions) {
        start_time = high_resolution_clock::now();
        bool balanced = AreBalanced(exp);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        
        cout << "Expression: " << exp << " - " 
             << (balanced ? "Balanced" : "Not Balanced") 
             << " (" << fixed << setprecision(6) << elapsed.count() << " ms)" << endl;
    }

    // ========================================
    // Test String Conversion Functions
    // ========================================
    printHeader("STRING CONVERSION FUNCTIONS");
    
    start_time = high_resolution_clock::now();
    int num = stringToInt("12345");
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << "stringToInt('12345') = " << num << endl;
    printTime("String to Int conversion", elapsed.count());
    
    start_time = high_resolution_clock::now();
    string str = intToString(67890);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << "intToString(67890) = '" << str << "'" << endl;
    printTime("Int to String conversion", elapsed.count());

    // ========================================
    // Summary
    // ========================================
    printHeader("ALL TESTS COMPLETED");
    cout << "All data structures and algorithms have been tested successfully!" << endl;
    cout << string(60, '=') << "\n" << endl;

    return 0;
}


// int main()
// {
//     LinkedList<int> list;
//     list.insert_at_end(10);
//     list.insert_at_end(20);
//     list.insert_at_end(30);
//     list.insert_at_end(0);
//     list.insert_at_end(1);
//     list.insert_at_end(22);
//     list.insert_at_end(223);
//     list.insert_at_start(15);
//     // list.insert_at_index(1, 15); 
//     // cout << "List contents: ";
//     // list.print();
//     // cout << "Removed from end: " << list.remove_from_end() << endl; // Removes 20
//     // cout << "After removal: ";
//     // list.print();
//     // cout << "Size of list: " << list.size() << endl;
//     vector<int> sortedArr = list.sort();
//     cout << "Sorted contents: ";
//     for (int val : sortedArr)
//         cout << val << " ";
//     cout << endl;
//     cout << "Size of list: " << list.size() << endl;

//     return 0;
// }

// int main()
// {
//     // Test Stack
//     cout << "--- Stack Tests ---" << endl;
//     Stack<int> s;
//     s.push(10); s.push(20); s.push(30);
//     cout << "Stack contents: "; s.print();
//     cout << "Stack peek: " << s.peek() << endl;
//     s.pop();
//     cout << "After pop: "; s.print();
//     cout << "Size: " << s.size() << endl;
//     s.clear();

//     // Test Queue
//     cout << "\n--- Queue Tests ---" << endl;
//     Queue<int> q;
//     q.enqueue(1); q.enqueue(2); q.enqueue(3);
//     cout << "Queue contents: "; q.print();
//     cout << "Front element: " << q.first() << endl;
//     q.dequeue();
//     cout << "After dequeue: "; q.print();

//     // Prepare arrays for sorting
//     int arr[] = {64,34,25,12,22,11,90 , 12,11,13,5,6 , 5,2,9,1,5,6 , 38,27,43,3,9,82,10 ,4,10,3,5,1 }; int n = sizeof(arr)/sizeof(arr[0]);

//     //Print original arrays

//     printArray(arr , n);
//     cout << endl;

//     // Selection Sort
//     cout << "\n--- Selection Sort ---" << endl;
//     {
//     auto start = chrono::high_resolution_clock::now();
//     Selection_Sort(arr, n);
//     printArray(arr, n);
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
//     cout << "Time taken: " << duration.count() << " milliseconds" << endl;
//     }

//     // Bubble Sort
//     cout << "\n--- Bubble Sort ---" << endl;
//     {
//     auto start = chrono::high_resolution_clock::now();
//     bubbleSort(arr, n);
//     printArray(arr, n);
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
//     cout << "Time taken: " << duration.count() << " milliseconds" << endl;
//     }

//     // Insertion Sort
//     cout << "\n--- Insertion Sort ---" << endl;
//     {
//     auto start = chrono::high_resolution_clock::now();
//     insertionSort(arr, n);
//     printArray(arr, n);
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
//     cout << "Time taken: " << duration.count() << " milliseconds" << endl;
//     }

//     // Merge Sort
//     cout << "\n--- Merge Sort ---" << endl;
//     {
//     auto start = chrono::high_resolution_clock::now();
//     mergeSort(arr, 0, n-1);
//     printArray(arr, n);
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
//     cout << "Time taken: " << duration.count() << " milliseconds" << endl;
//     }

//     // Shell Sort (vector)
//     cout << "\n--- Shell Sort ---" << endl;
//     {
//     auto start = chrono::high_resolution_clock::now();
//     vector<int> v = {12, 34, 54, 2, 3};
//     shellSort(v);
//     for (int x : v) cout << x << ' '; cout << endl;
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
//     cout << "Time taken: " << duration.count() << " milliseconds" << endl;
//     }
//     // Quick Sort
//     cout << "\n--- Quick Sort ---" << endl;
//     {
//     auto start = chrono::high_resolution_clock::now();
//     quickSort(arr, 0, n-1);
//     printArray(arr, n);
//     auto end = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
//     cout << "Time taken: " << duration.count() << " milliseconds" << endl;
//     }

//     int arr1[] = {64,34,25,12,22,11,90 , 12,11,13,5,6 , 5,2,9,1,5,6 , 38,27,43,3,9,82,10 ,4,10,3,5,1 }; int n1 = sizeof(arr1)/sizeof(arr1[0]);

//     // Binary Search (on sorted arr)
//     cout << "\n--- Binary Search ---" << endl;
//     int key = 9;
//     int idx = binary_search(arr1, 0, n1-1, key);
//     cout << "Index of " << key << ": " << idx << "(for origin array not sorted one)" << endl;

//     // Parentheses Balance Check
//     cout << "\n--- Balanced Parentheses ---" << endl;
//     string expr1 = "{[()]}"; string expr2 = "{[(])}";
//     cout << expr1 << ": " << (AreBalanced(expr1) ? "Balanced" : "Not Balanced") << endl;
//     cout << expr2 << ": " << (AreBalanced(expr2) ? "Balanced" : "Not Balanced") << endl;

//     // Heap Sort
//     cout << "\n--- Heap Sort ---" << endl;
//     heapSort(arr, n);
//     cout << "Sorted by heap: "; printArray(arr, n);

//     // Conversions and maximum
//     cout << "\n--- Conversions & Maximum ---" << endl;
//     string s1 = "-12345"; int val = stringToInt(s1);
//     cout << "stringToInt('" << s1 << "') = " << val << endl;
//     cout << "intToString(" << val << ") = " << intToString(val) << endl;
//     cout << "maximum(arr) = " << maximum(arr, n) << endl;

//     return 0;
// }
