#include "bits/stdc++.h"
#include <cstring>
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
// Priority Queue
//======================================================================
class PriorityQueue
{
private:
    MaxHeap heap;
    unordered_map<int, queue<int>> Values_Map;

public:
    void insert(int value, int priority)
    {
        heap.insert(priority);
        Values_Map[priority].push(value);
    }

    pair<int, int> extractHighestPriority()
    {
        if (heap.isEmpty())
            cout << "Queue is empty!";

        int highestPriority = heap.ExtractMax();
        int value = Values_Map[highestPriority].front();
        Values_Map[highestPriority].pop();

        if (Values_Map[highestPriority].empty())
            Values_Map.erase(highestPriority);

        return {value, highestPriority};
    }

    bool isEmpty()
    {
        return heap.isEmpty();
    }
};


//======================================================================
// sorting algorthims
//======================================================================

// PrintArray
ofstream outFile("output.txt");
void printArray(int arr[], int n, const string &s)
{

    if (!outFile.is_open())
    {
        cout << "Error: Could not open output.txt" << endl;
        return;
    }

    outFile << s << " -> ";
    for (int i = 0; i < n; i++)
    {
        outFile << arr[i] << " ";
        if ((i + 1) % 20 == 0)
        {
            outFile << "\n";
        }
    }
    if (s != "Original Array")
    {
        outFile << "\n\n";
    }
}
//--------------------------------------------------
// selection sort

template <class T>
void Selection_Sort(T arr[], const int n)
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
    string s = "selectionSort";
    printArray(arr, n, s);
}

// ---------------------------------------
// bubble sort
void bubbleSort(int arr[], const int n)
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
    string s = "bubbleSort";
    printArray(arr, n, s);
}

// ---------------------------------------
// InsertionSort

void insertionSort(int arr[], const int n)
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
    string s = "insertionSort";
    printArray(arr, n, s);
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

    // transfar the data from the main array to the two sub arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left; // i is for left sub array , j is for right sub array , k is for main array and all three are pointers
    while (i < n1 && j < n2)
    {
        // check for which element is smaller and put that in the main array
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

    delete[] L;
    delete[] R;
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

    // Note: Cannot determine array size in mergeSort - size is passed as parameters
}

// -----------------------------------------------
// ShellSort

void shellSort(int arr[], const int n)
{

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

    string s = "shellSort";
    printArray(arr, n, s);
}

//-----------------------------------------------
// QuickSort
// this put the pivot in its right place and put all smaller elements to left of pivot and all greater elements to right of pivot
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // here pivot is at the last index , i am telling this to avoid confusion as there is some other ways to choose pivot (like first index or middle index)
    int i = low - 1;       // start from -1 index of low
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

//-----------------------------------------------
// Randomized QuickSort
int random_partition(int arr[], int low, int high)
{
    // Generate random index between low and high
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]); // Move random pivot to end
    return partition(arr, low, high);  // Use existing partition function
}
static int counter_for_printing = 0;
void random_quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = random_partition(arr, low, high);
        random_quickSort(arr, low, pi - 1);
        random_quickSort(arr, pi + 1, high);
    }
}

////======================================================================
// BinarySearch

int binary_search(const int arr[], int left, int right, const int key)
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
    return -1;
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

void heapify(int arr[], const int s, const int i)
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

void heapSort(int arr[], const int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    string s = "heapSort";
    printArray(arr, n, s);
}

//===========================================================
// Counting Sort

void CountingSort(int arr[], const int n)
{
    int maxval = 0;
    for (int i = 0; i < n; i++)
        maxval = max(maxval, arr[i]);
    int newSize = maxval + 1;
    int countArr[newSize] = {0};
    int res[n];

    // for(int i = 0; i < newSize; i++){
    //     countArr[i] = 0;
    // }

    for (int i = 0; i < n; i++)
    {
        countArr[arr[i]]++;
    }

    for (int i = 1; i < newSize; i++)
    {
        countArr[i] += countArr[i - 1];
    }

    for (int j = n - 1; j >= 0; j--)
    {
        res[countArr[arr[j]] - 1] = arr[j];
        countArr[arr[j]]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = res[i];
    }

    string s = "CountingSort";
    printArray(arr, n, s);
}

////===========================================================
// radix Sort

// A utility function to get maximum
// value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(int arr[], int n, int exp)
{

    // Output array
    int output[n];
    int i, count[10] = {0};

    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(int arr[], int n)
{

    // Find the maximum number to
    // know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// ============================================================
// Important Functions : ->

void prefixSum(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        arr[i] = arr[i] + arr[i - 1];
    }
}

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

int maximum(const int arr[], const int n)
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

long long binToDec(const string &bin)
{
    long long val = 0;
    for (char c : bin)
    {
        val = val * 2 + (c - '0');
    }
    return val;
}

string decToBin(long long n)
{
    if (n == 0)
        return "0";
    string s = "";
    while (n > 0)
    {
        s = char((n % 2) + '0') + s;
        n /= 2;
    }
    return s;
}

//--------------------------------------------------
//====================================================================
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

        delete[] L;
        delete[] R;
    }

    void MergeSort(int arr[], int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            MergeSort(arr, left, mid);
            MergeSort(arr, mid + 1, right);

            Merge(arr, left, mid, right);
        }
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    bool is_empty() const { return count == 0; }

    int size() const { return count; }

    T start_item() const { return head->item; }
    T end_item() const { return tail->item; }

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
        while (current != nullptr)
        {
            arr.push_back(current->item);
            current = current->next;
        }
        MergeSort(arr.data(), 0, arr.size() - 1);
        return arr;
    }

    void print() const
    {
        if (is_empty())
        {
            cout << "[empty]" << endl;
            return;
        }
        Node<T> *current = head;
        while (current != nullptr)
        {
            cout << current->item << " ";
            current = current->next;
        }
        cout << endl;
    }
};

//============================================================
// Hashing algorithm using replacement method

template <class H>
class Hashing
{
private:
    const int TableSize;
    vector<H> hashTable;
    vector<LinkedList<H>> chainTable;

    int hashFunction(H key)
    {
        return key % TableSize;
    }

    int hashFunction2(H key)
    {
        const int R = 7;
        return R - (key % R);
    }

public:
    Hashing(int size) : TableSize(size), hashTable(size, -1), chainTable(size) {}

    void insertByReplacement(H key)
    {
        int idx = hashFunction(key);
        hashTable[idx] = key;
    }

    void insertLinearProbing(H key)
    {
        int idx = hashFunction(key);
        if (hashTable[idx] == -1)
        {
            hashTable[idx] = key;
            return;
        }

        for (int i = 1; i < TableSize; ++i)
        {
            int pos = (idx + i) % TableSize;
            if (hashTable[pos] == -1)
            {
                hashTable[pos] = key;
                return;
            }
        }
    }

    void insertQuadraticProbing(H key)
    {
        int idx = hashFunction(key);
        if (hashTable[idx] == -1)
        {
            hashTable[idx] = key;
            return;
        }

        for (int i = 1; i < TableSize; ++i)
        {
            int pos = (idx + i * i) % TableSize;
            if (hashTable[pos] == -1)
            {
                hashTable[pos] = key;
                return;
            }
        }
    }

    void insertChaining(H key)
    {
        int idx = hashFunction(key);
        chainTable[idx].insert_at_end(key);
    }

    void insertDoubleHashing(H key)
    {
        int idx = hashFunction(key);

        if (hashTable[idx] == -1)
        {
            hashTable[idx] = key;
            return;
        }

        int step = hashFunction2(key);

        for (int i = 1; i < TableSize; ++i)
        {
            int pos = (idx + i * step) % TableSize;
            if (hashTable[pos] == -1)
            {
                hashTable[pos] = key;
                return;
            }
        }
    }

    void print() const
    {
        cout << "Hash Table (Open Addressing):" << endl;
        for (int i = 0; i < TableSize; ++i)
        {
            cout << i << ": ";
            if (hashTable[i] == -1)
                cout << "[empty]";
            else
                cout << hashTable[i];
            cout << endl;
        }
    }

    void printChaining() const
    {
        cout << "Hash Table (Chaining):" << endl;
        for (int i = 0; i < TableSize; ++i)
        {
            cout << i << ": ";
            chainTable[i].print();
        }
    }
};

//======================================================================
// Function to print section headers
void printHeader(const string &title)
{
    cout << "\n"
         << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

void printHeader_for_sorting(const string &title, int n)
{
    cout << "\n"
         << string(60, '=') << endl;
    cout << "  " << title << n << " Element" << endl;
    cout << string(60, '=') << endl;
}

// Function to print time taken
void printTime(const string &operation, double time_ms)
{
    cout << left << setw(40) << operation << ": " << fixed << setprecision(4) << time_ms << " ms" << endl;
}
//======================================================================
// power functions
int power(int a, int b)
{
    if (b == 0)
        return 1;

    int half = power(a, b / 2);

    if (b % 2 == 0)
        return half * half;
    else
        return a * half * half;
}

long long power_iterative(int num, int p)
{
    if (p == 0)
        return 1;
    if (p < 0)
        return 0; // Handle negative exponents

    long long result = 1;
    long long base = num;

    while (p > 0)
    {
        if (p & 1)
        { // If p is odd
            result *= base;
        }
        base *= base;
        p >>= 1; // Divide p by 2
    }
    return result;
}


//======================================================================
// Implement the Fibonacci series using divide and conquer (matrix multiplication)

struct Matrix
{
    long long M[2][2]; // transformation matrix

    Matrix()
    {
        M[0][0] = 1;
        M[0][1] = 1;
        M[1][0] = 1;
        M[1][1] = 0;
    }

    Matrix operator*(const Matrix &other) const
    {
        Matrix result;
        result.M[0][0] = M[0][0] * other.M[0][0] + M[0][1] * other.M[1][0];
        result.M[0][1] = M[0][0] * other.M[0][1] + M[0][1] * other.M[1][1];
        result.M[1][0] = M[1][0] * other.M[0][0] + M[1][1] * other.M[1][0];
        result.M[1][1] = M[1][0] * other.M[0][1] + M[1][1] * other.M[1][1];
        return result;
    }
    
    Matrix Rec_matrix(Matrix base, long long n)
    {
        if (n == 1)
            return base;
    
        Matrix half = Rec_matrix(base, n / 2);
        Matrix result ;
    
        if (n % 2 == 1) // in case n is odd number
        {
            result = half * half;
            result = result * base;
        }
        else // in case n is even number
        {
            result = half * half;
        }
        return result;
    }
    
    int fib_matrix(long long n)
    {
        if (n < 0)
            return -1;
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
    
        --n;
        Matrix base;
        Matrix result = Rec_matrix(base, n);
    
    
        return result.M[0][0];
    }
};

//======================================================================
// Binary trees
//----------------------------------------------
template <class T>
struct BTNode
{
    T data;
    BTNode<T> *left;
    BTNode<T> *right;

    BTNode(T val) : data(val), left(nullptr), right(nullptr) {}
    BTNode() : left(nullptr), right(nullptr) {}
};

template <class T>
class BinaryTree
{
private:
    BTNode<T> *root;
    int count;

    // Helper function for recursive insertion
    BTNode<T> *insertRec(BTNode<T> *node, T value)
    {
        if (node == nullptr)
        {
            return new BTNode<T>(value);
        }
        if (value < node->data)
        {
            node->left = insertRec(node->left, value);
        }
        else
        {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    // Helper function for recursive search
    BTNode<T> *searchRec(BTNode<T> *node, T value)
    {
        if (node == nullptr || node->data == value)
        {
            return node;
        }
        if (value < node->data)
        {
            return searchRec(node->left, value);
        }
        return searchRec(node->right, value);
    }

    // Helper function to find minimum value node
    BTNode<T> *findMin(BTNode<T> *node)
    {
        while (node && node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Helper function for recursive deletion
    BTNode<T> *deleteRec(BTNode<T> *node, T value)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (value < node->data)
        {
            node->left = deleteRec(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = deleteRec(node->right, value);
        }
        else
        {
            // Node with only one child or no child
            if (node->left == nullptr)
            {
                BTNode<T> *temp = node->right;
                delete node;
                count--;
                return temp;
            }
            else if (node->right == nullptr)
            {
                BTNode<T> *temp = node->left;
                delete node;
                count--;
                return temp;
            }

            // Node with two children
            BTNode<T> *temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteRec(node->right, temp->data);
            count++; // Adjust because deleteRec will decrement
        }
        return node;
    }

    // Helper for inorder traversal
    void inorderRec(BTNode<T> *node, vector<T> &result)
    {
        if (node != nullptr)
        {
            inorderRec(node->left, result);
            result.push_back(node->data);
            inorderRec(node->right, result);
        }
    }

    // Helper for preorder traversal
    void preorderRec(BTNode<T> *node, vector<T> &result)
    {
        if (node != nullptr)
        {
            result.push_back(node->data);
            preorderRec(node->left, result);
            preorderRec(node->right, result);
        }
    }

    // Helper for postorder traversal
    void postorderRec(BTNode<T> *node, vector<T> &result)
    {
        if (node != nullptr)
        {
            postorderRec(node->left, result);
            postorderRec(node->right, result);
            result.push_back(node->data);
        }
    }

    // Helper to count nodes
    int countNodesRec(BTNode<T> *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + countNodesRec(node->left) + countNodesRec(node->right);
    }

    // Helper to count leaf nodes
    int countLeavesRec(BTNode<T> *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }
        return countLeavesRec(node->left) + countLeavesRec(node->right);
    }

    // Helper to clear tree
    void clearRec(BTNode<T> *node)
    {
        if (node != nullptr)
        {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr), count(0) {}

    ~BinaryTree()
    {
        clear();
    }

    bool is_empty() const
    {
        return root == nullptr;
    }

    // Get height of tree
    int height(BTNode<T> *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    // Get balance factor
    int getBalance(BTNode<T> *node) const
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // Check if node is leaf
    bool isLeaf(BTNode<T> *node) const
    {
        if (node == nullptr)
        {
            return false;
        }
        return (node->left == nullptr && node->right == nullptr);
    }

    // Get root node
    BTNode<T> *getRoot() const
    {
        return root;
    }

    // Check if tree is balanced
    bool isBalanced(BTNode<T> *node) const
    {
        if (node == nullptr)
            return true;

        int balance = getBalance(node);

        if (abs(balance) > 1)
            return false;

        return isBalanced(node->left) && isBalanced(node->right);
    }

    // Insert value
    void insert(T value)
    {
        root = insertRec(root, value);
        count++;
    }

    // Search for value
    bool search(T value)
    {
        return searchRec(root, value) != nullptr;
    }

    // Delete value
    void deleteNode(T value)
    {
        root = deleteRec(root, value);
    }

    // Get size
    int size() const
    {
        return count;
    }

    // Inorder traversal (Left, Root, Right)
    vector<T> inorder()
    {
        vector<T> result;
        inorderRec(root, result);
        return result;
    }

    // Preorder traversal (Root, Left, Right)
    vector<T> preorder()
    {
        vector<T> result;
        preorderRec(root, result);
        return result;
    }

    // Postorder traversal (Left, Right, Root)
    vector<T> postorder()
    {
        vector<T> result;
        postorderRec(root, result);
        return result;
    }

    // Level order traversal (BFS)
    vector<T> levelorder()
    {
        vector<T> result;
        if (root == nullptr)
            return result;

        queue<BTNode<T> *> q;
        q.push(root);

        while (!q.empty())
        {
            BTNode<T> *current = q.front();
            q.pop();
            result.push_back(current->data);

            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }

        return result;
    }

    // Find minimum value
    T findMinValue()
    {
        if (is_empty())
        {
            throw runtime_error("Tree is empty");
        }
        BTNode<T> *minNode = findMin(root);
        return minNode->data;
    }

    // Find maximum value
    T findMaxValue()
    {
        if (is_empty())
        {
            throw runtime_error("Tree is empty");
        }
        BTNode<T> *current = root;
        while (current->right != nullptr)
        {
            current = current->right;
        }
        return current->data;
    }

    // Count total nodes
    int countNodes() const
    {
        return countNodesRec(root);
    }

    // Count leaf nodes
    int countLeaves() const
    {
        return countLeavesRec(root);
    }

    // Count internal nodes
    int countInternalNodes() const
    {
        return countNodes() - countLeaves();
    }

    // Clear tree
    void clear()
    {
        clearRec(root);
        root = nullptr;
        count = 0;
    }

    // Print tree structure
    void printTree(BTNode<T> *node, string indent = "", bool isRight = true)
    {
        if (node != nullptr)
        {
            cout << indent;
            if (isRight)
            {
                cout << "R----";
                indent += "     ";
            }
            else
            {
                cout << "L----";
                indent += "|    ";
            }
            cout << node->data << endl;

            printTree(node->left, indent, false);
            printTree(node->right, indent, true);
        }
    }

    // Print tree (wrapper)
    void print()
    {
        if (is_empty())
        {
            cout << "Tree is empty" << endl;
            return;
        }
        printTree(root);
    }
};
//======================================================================
// Max Heap implementation
class MaxHeap
{
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int i)
    {
        while (i > 0 && heap[parent(i)] < heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i)
    {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] > heap[largest])
            largest = left;

        if (right < heap.size() && heap[right] > heap[largest])
            largest = right;

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(int value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int ExtractMin()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty!");

        int leaf_start = heap.size() / 2;

        int index = leaf_start;

        for (int i = leaf_start; i < heap.size(); i++)
            if (heap[i] < heap[index])
                index = i;

        int min_val = heap[index];

        heap[index] = heap.back();
        heap.pop_back();

        return min_val;
    }


    bool isEmpty()
    {
        return heap.empty();
    }

    int size()
    {
        return heap.size();
    }

    void display()
    {
        if (heap.empty())
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        for (int val : heap)
            cout << val << " ";
        cout << endl;
    }

    int getLevels(int n)
    {
        if (n == 0)
            return 0;
        return floor(log2(n)) + 1;
    }

    void displayTree()
    {
        if (heap.empty())
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        int n = heap.size();
        int totalLevels = 1 + log2(n);

        int index = 0;

        for (int level = 0; level < totalLevels; level++)
        {
            int nodesInLevel = 1 << level;
            int spaces = (1 << (totalLevels - level));

            for (int s = 0; s < spaces; s++)
                cout << " ";

            for (int j = 0; j < nodesInLevel && index < n; j++, index++)
            {
                cout << heap[index];

                for (int s = 0; s < (1 << (totalLevels - level + 1)); s++)
                    cout << " ";
            }
            cout << "\n\n";
        }
    }

    int ExtractMax()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty!");

        int maxValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return maxValue;
    }
};



////======================================================================
// Function prototypes for menu operations
void testStack();
void testQueue();
void testLinkedList();
void testSortingAlgorithms();
void testBinarySearch();
void testHashing();
void testBalancedParentheses();
void testStringConversion();
void testPowerFunction();
void testBinaryTree();
void testFibonacci();
void displayMenu();
void TestMaxHeap();
void TestPriorityQueue();
int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    int choice;
    bool running = true;

    cout << "\n";
    cout << string(70, '=') << endl;
    cout << "    DATA STRUCTURES AND ALGORITHMS TESTING SUITE" << endl;
    cout << string(70, '=') << endl;

    while (running)
    {
        displayMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[ERROR] Invalid input! Please enter a number.\n";
            continue;
        }

        cout << "\n";

        switch (choice)
        {
        case 1:
            testStack();
            break;
        case 2:
            testQueue();
            break;
        case 3:
            testLinkedList();
            break;
        case 4:
            testSortingAlgorithms();
            break;
        case 5:
            testBinarySearch();
            break;
        case 6:
            testHashing();
            break;
        case 7:
            testBalancedParentheses();
            break;
        case 8:
            testStringConversion();
            break;
        case 9:
            testPowerFunction();
            break;
        case 10:
            testBinaryTree();
            break;
        case 11:
            testFibonacci();
            break;
        case 12:
            TestMaxHeap();
            break;
        case 13:
            TestPriorityQueue();
            break;
        
        case 0:
            running = false;
            printHeader("PROGRAM TERMINATED");
            cout << "Thank you for using the testing suite!\n";
            break;
        default:
            cout << "[ERROR] Invalid choice! Please select a valid option (0-11).\n";
        }

        if (running && choice >= 1 && choice <= 11)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    return 0;
}

void displayMenu()
{
    cout << "\n" << string(70, '-') << endl;
    cout << "                           MAIN MENU" << endl;
    cout << string(70, '-') << endl;
    cout << " 1.  Test Stack Operations" << endl;
    cout << " 2.  Test Queue Operations" << endl;
    cout << " 3.  Test Linked List Operations" << endl;
    cout << " 4.  Test Sorting Algorithms" << endl;
    cout << " 5.  Test Binary Search" << endl;
    cout << " 6.  Test Hashing Algorithms" << endl;
    cout << " 7.  Test Balanced Parentheses" << endl;
    cout << " 8.  Test String Conversion Functions" << endl;
    cout << " 9.  Test Power Functions" << endl;
    cout << " 10. Test Binary Tree Operations" << endl;
    cout << " 11. Test Fibonacci (Matrix Method)" << endl;
    cout << " 12. Test Max Heap Operations" << endl;
    cout << " 13. Test Priority Queue Operations" << endl;
    cout << " 0.  Exit Program" << endl;
    cout << string(70, '-') << endl;
}

void testStack()
{
    printHeader("STACK OPERATIONS");

    Stack<int> stack;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    start_time = high_resolution_clock::now();
    for (int i = 1; i <= 1000; i++)
    {
        stack.push(i);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Push 1000 elements", elapsed.count());

    cout << "Stack size: " << stack.size() << endl;
    cout << "Top element: " << stack.peek() << endl;

    start_time = high_resolution_clock::now();
    for (int i = 0; i < 500; i++)
    {
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
}

void testQueue()
{
    printHeader("QUEUE OPERATIONS");

    Queue<int> queue;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    start_time = high_resolution_clock::now();
    for (int i = 1; i <= 1000; i++)
    {
        queue.enqueue(i);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Enqueue 1000 elements", elapsed.count());

    cout << "First element: " << queue.first() << endl;

    start_time = high_resolution_clock::now();
    for (int i = 0; i < 500; i++)
    {
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
}

void testLinkedList()
{
    printHeader("LINKED LIST OPERATIONS");

    LinkedList<int> list;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    start_time = high_resolution_clock::now();
    for (int i = 1; i <= 1000; i++)
    {
        list.insert_at_end(i);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insert 1000 elements at end", elapsed.count());

    cout << "List size: " << list.size() << endl;
    cout << "Start item: " << list.start_item() << endl;
    cout << "End item: " << list.end_item() << endl;

    start_time = high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
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
    for (int i = 0; i < 100; i++)
    {
        list.remove_from_end();
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Remove 100 elements from end", elapsed.count());

    start_time = high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {
        list.remove_from_start();
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Remove 100 elements from start", elapsed.count());

    cout << "List size after removals: " << list.size() << endl;
}

void testSortingAlgorithms()
{
    printHeader("SORTING ALGORITHMS");

    const int n = 20;
    int arr[n];
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % n;
    }

    int arr1[n], arr2[n], arr3[n], arr4[n], arr5[n];
    int arr6[n], arr7[n], arr8[n], arr9[n], arr10[n];

    cout << "\nArray size: " << n << " elements\n" << endl;

    // Selection Sort
    memcpy(arr1, arr, sizeof(arr));
    printArray(arr1, n, "Original Array");
    start_time = high_resolution_clock::now();
    Selection_Sort(arr1, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Selection Sort", elapsed.count());

    // Bubble Sort
    memcpy(arr2, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    bubbleSort(arr2, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Bubble Sort", elapsed.count());

    // Insertion Sort
    memcpy(arr3, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    insertionSort(arr3, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insertion Sort", elapsed.count());

    // Merge Sort
    memcpy(arr4, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    mergeSort(arr4, 0, n - 1);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Merge Sort", elapsed.count());

    // Quick Sort
    memcpy(arr5, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    quickSort(arr5, 0, n - 1);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Quick Sort", elapsed.count());

    // Random Quick Sort
    memcpy(arr6, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    random_quickSort(arr6, 0, n - 1);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Random Quick Sort", elapsed.count());

    // Shell Sort
    memcpy(arr7, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    shellSort(arr7, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Shell Sort", elapsed.count());

    // Heap Sort
    memcpy(arr8, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    heapSort(arr8, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Heap Sort", elapsed.count());

    // Counting Sort
    memcpy(arr9, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    CountingSort(arr9, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Counting Sort", elapsed.count());

    // Radix Sort
    memcpy(arr10, arr, sizeof(arr));
    start_time = high_resolution_clock::now();
    radixsort(arr10, n);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Radix Sort", elapsed.count());

    cout << "\nSorted array sample: ";
    for (int i = 0; i < min(10, n); i++)
    {
        cout << arr10[i] << " ";
    }
    cout << "..." << endl;
}

void testBinarySearch()
{
    printHeader("BINARY SEARCH");

    int sorted_arr[100];
    for (int i = 0; i < 100; i++)
        sorted_arr[i] = i * 2;

    auto start_time = high_resolution_clock::now();
    int index = binary_search(sorted_arr, 0, 99, 50);
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed = end_time - start_time;

    cout << "Searching for 50 in sorted array (0, 2, 4, ..., 198)..." << endl;
    cout << "Found at index: " << index << endl;
    cout << "Value at index: " << sorted_arr[index] << endl;
    printTime("Binary Search", elapsed.count());
}

void testHashing()
{
    printHeader("HASHING ALGORITHMS");

    Hashing<int> hash(10);
    vector<int> keys = {5, 15, 25, 35, 45};

    cout << "\nTesting Replacement Method:" << endl;
    for (int key : keys)
    {
        hash.insertByReplacement(key);
    }
    hash.print();

    cout << "\nTesting Linear Probing:" << endl;
    Hashing<int> hashLinear(10);
    for (int key : keys)
    {
        hashLinear.insertLinearProbing(key);
    }
    hashLinear.print();

    cout << "\nTesting Quadratic Probing:" << endl;
    Hashing<int> hashQuad(10);
    for (int key : keys)
    {
        hashQuad.insertQuadraticProbing(key);
    }
    hashQuad.print();

    cout << "\nTesting Chaining:" << endl;
    Hashing<int> hashChain(10);
    for (int key : keys)
    {
        hashChain.insertChaining(key);
    }
    hashChain.printChaining();
}

void testBalancedParentheses()
{
    printHeader("BALANCED PARENTHESES CHECK");

    string expressions[] = {
        "{[()]}",
        "{[(])}",
        "((()))",
        "({[}])"};

    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    for (const string &exp : expressions)
    {
        start_time = high_resolution_clock::now();
        bool balanced = AreBalanced(exp);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;

        cout << "Expression: " << exp << " - "
             << (balanced ? "Balanced" : "Not Balanced")
             << " (" << fixed << setprecision(6) << elapsed.count() << " ms)" << endl;
    }
}

void testStringConversion()
{
    printHeader("STRING CONVERSION FUNCTIONS");

    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

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
}

void testPowerFunction()
{
    printHeader("POWER FUNCTION");

    int base = 2;
    int p = 30;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    cout << "Calculating power using recursion:" << endl;
    start_time = high_resolution_clock::now();
    long long pow_result = power(base, p);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << base << " raised to the power of " << p << " is " << pow_result << endl;
    printTime("Recursive Power", elapsed.count());

    cout << "\nCalculating power using iterative method:" << endl;
    start_time = high_resolution_clock::now();
    long long pow_iterative_result = power_iterative(base, p);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << base << " raised to the power of " << p << " is " << pow_iterative_result << endl;
    printTime("Iterative Power", elapsed.count());
}

void testBinaryTree()
{
    printHeader("BINARY TREE OPERATIONS");

    BinaryTree<int> tree;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    cout << "\nInserting elements: 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 65" << endl;
    start_time = high_resolution_clock::now();
    vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 65};
    for (int val : values)
    {
        tree.insert(val);
    }
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insert 11 elements", elapsed.count());

    cout << "\nTree size: " << tree.size() << endl;
    cout << "Tree height: " << tree.height(tree.getRoot()) << endl;
    cout << "Is balanced: " << (tree.isBalanced(tree.getRoot()) ? "Yes" : "No") << endl;

    cout << "\nTree structure:" << endl;
    tree.print();

    cout << "\n--- Traversals ---" << endl;
    vector<int> inorder = tree.inorder();
    cout << "Inorder (L-Root-R): ";
    for (int val : inorder)
        cout << val << " ";
    cout << endl;

    cout << "\n--- Search Operations ---" << endl;
    int searchVals[] = {40, 100, 10};
    for (int val : searchVals)
    {
        start_time = high_resolution_clock::now();
        bool found = tree.search(val);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        cout << "Searching for " << val << ": " << (found ? "Found" : "Not Found");
        cout << " (" << fixed << setprecision(6) << elapsed.count() << " ms)" << endl;
    }

    cout << "\n--- Min/Max Operations ---" << endl;
    cout << "Minimum value: " << tree.findMinValue() << endl;
    cout << "Maximum value: " << tree.findMaxValue() << endl;

    cout << "\n--- Node Counting ---" << endl;
    cout << "Total nodes: " << tree.countNodes() << endl;
    cout << "Leaf nodes: " << tree.countLeaves() << endl;
    cout << "Internal nodes: " << tree.countInternalNodes() << endl;
}

void testFibonacci()
{
    printHeader("FIBONACCI SEQUENCE (MATRIX METHOD)");

    Matrix matrix;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    cout << "Computing Fibonacci numbers using matrix exponentiation:\n" << endl;

    vector<int> test_values = {5, 10, 15, 20, 30, 40, 50};

    for (int n : test_values)
    {
        start_time = high_resolution_clock::now();
        long long result = matrix.fib_matrix(n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;

        cout << "F(" << n << ") = " << result;
        cout << " (" << fixed << setprecision(6) << elapsed.count() << " ms)" << endl;
    }

    cout << "\n--- Custom Input ---" << endl;
    cout << "Enter a Fibonacci position (0-90): ";
    int custom_n;
    cin >> custom_n;

    if (custom_n >= 0 && custom_n <= 90)
    {
        start_time = high_resolution_clock::now();
        long long result = matrix.fib_matrix(custom_n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;

        cout << "F(" << custom_n << ") = " << result << endl;
        printTime("Calculation time", elapsed.count());

        cout << "\nNote: Matrix exponentiation computes Fibonacci in O(log n) time!" << endl;
    }
    else
    {
        cout << "[ERROR] Please enter a value between 0 and 90." << endl;
    }
}





void TestMaxHeap()
{
    printHeader("MAX HEAP OPERATIONS");

    MaxHeap maxHeap;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    cout << "\nInserting elements into Max Heap: ";
    for (int i = 10; i >= 1; i--)
    {
        cout << i << " ";
        maxHeap.insert(i);
    }
    cout << endl;

    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insert 10 elements", elapsed.count());

    cout << "\nMax Heap structure:\n";
    maxHeap.displayTree();

    start_time = high_resolution_clock::now();
    int maxElement = maxHeap.ExtractMax();
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << "\nExtracted Max Element: " << maxElement << endl;
    printTime("Extract Max", elapsed.count());

    cout << "\nMax Heap after extraction:\n";
    maxHeap.displayTree();
}   


void TestPrioriyQueue()
{
    printHeader("PRIORITY QUEUE OPERATIONS USING MAX HEAP");

    MaxHeap priorityQueue;
    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    cout << "\nInserting elements into Priority Queue: ";
    for (int i = 15; i >= 1; i--)
    {
        cout << i << " ";
        priorityQueue.insert(i);
    }
    cout << endl;

    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    printTime("Insert 15 elements", elapsed.count());

    cout << "\nPriority Queue structure:\n";
    priorityQueue.displayTree();

    start_time = high_resolution_clock::now();
    int maxElement = priorityQueue.ExtractMax();
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << "\nExtracted Max Element: " << maxElement << endl;
    printTime("Extract Max", elapsed.count());

    cout << "\nPriority Queue after extraction:\n";
    priorityQueue.displayTree();
}