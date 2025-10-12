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
    bool is_empty() { return count == 0; }

    int size() { return count; }

    T start_item() { return head->item; }
    T end_item() { return tail->item; }

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
// Main function to test all implementations
int main()
{
    // Initialize random seed for consistent results
    srand(static_cast<unsigned>(time(nullptr)));

    auto start_time = high_resolution_clock::now();
    auto end_time = high_resolution_clock::now();
    duration<double, milli> elapsed;

    // ========================================
    // Test Stack
    // ========================================
    {
        printHeader("STACK OPERATIONS");

        Stack<int> stack;

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
    // ========================================
    // Test Queue
    // ========================================
    {
        printHeader("QUEUE OPERATIONS");

        Queue<int> queue;

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
    // ========================================
    // Test Linked List
    // ========================================
    {
        printHeader("LINKED LIST OPERATIONS");

        LinkedList<int> list;

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
    // ========================================
    // Test Sorting Algorithms
    // ========================================
    {
        ofstream outFile("output.txt", ios::app);
        const int n = 20;
        printHeader_for_sorting("SORTING ALGORITHMS of -> ", n);
        int arr[n];
        // const int n = sizeof(arr) / sizeof(arr[0]);
        int size = n;
        // Initialize array with random values for fair comparison
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % n;
        }

        int arr1[n];
        int arr3[n];
        int arr5[n];
        int arr6[n];
        int arr7[n];
        int arr2[n];
        int arr8[n];
        int arr4[n];
        int arr9[n];
        int arr10[n];

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
        printArray(arr2, n, "Original Array");
        start_time = high_resolution_clock::now();
        bubbleSort(arr2, n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Bubble Sort", elapsed.count());

        // Insertion Sort
        memcpy(arr3, arr, sizeof(arr));
        printArray(arr3, n, "Original Array");
        start_time = high_resolution_clock::now();
        insertionSort(arr3, n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Insertion Sort", elapsed.count());

        // Merge Sort
        memcpy(arr4, arr, sizeof(arr));
        printArray(arr4, n, "Original Array");
        start_time = high_resolution_clock::now();
        mergeSort(arr4, 0, n - 1);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Merge Sort", elapsed.count());
        string s_merge = "mergeSort";
        printArray(arr4, n, s_merge);

        // Quick Sort
        memcpy(arr5, arr, sizeof(arr));
        printArray(arr5, n, "Original Array");
        start_time = high_resolution_clock::now();
        quickSort(arr5, 0, n - 1);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Quick Sort", elapsed.count());
        string s_quick = "quickSort";
        printArray(arr5, n, s_quick);

        // Random Quick Sort
        memcpy(arr6, arr, sizeof(arr));
        printArray(arr6, n, "Original Array");
        start_time = high_resolution_clock::now();
        random_quickSort(arr6, 0, n - 1);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Random Quick Sort", elapsed.count());
        string s_random_quick = "random_quickSort";
        printArray(arr6, n, s_random_quick);

        // Shell Sort
        memcpy(arr7, arr, sizeof(arr));
        printArray(arr7, n, "Original Array");
        start_time = high_resolution_clock::now();
        shellSort(arr7, n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Shell Sort", elapsed.count());

        // Heap Sort
        memcpy(arr8, arr, sizeof(arr));
        printArray(arr8, n, "Original Array");
        start_time = high_resolution_clock::now();
        heapSort(arr8, n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Heap Sort", elapsed.count());

        // Counting Sort
        memcpy(arr9, arr, sizeof(arr));
        printArray(arr9, n, "Original Array");
        start_time = high_resolution_clock::now();
        CountingSort(arr9, n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Counting Sort", elapsed.count());
        cout << endl;

        // Radix Sort
        memcpy(arr10, arr, sizeof(arr));
        printArray(arr10, n, "Original Array");
        start_time = high_resolution_clock::now();
        CountingSort(arr10, n);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        printTime("Radix Sort", elapsed.count());
        string s_radix = "radixSort";
        printArray(arr6, n, s_radix);

        // closing the output file of sorting algorithms
        outFile.close();

        // ========================================
        // Test Binary Search
        // ========================================
        printHeader("BINARY SEARCH");

        int sorted_arr[100];
        for (int i = 0; i < 100; i++)
            sorted_arr[i] = i * 2;

        start_time = high_resolution_clock::now();
        int index = binary_search(sorted_arr, 0, 99, 50);
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;

        cout << "Searching for 50 in sorted array..." << endl;
        cout << "Found at index: " << index << endl;
        printTime("Binary Search", elapsed.count());
    }
    // ========================================
    // Test Balanced Parentheses
    // ========================================
    printHeader("BALANCED PARENTHESES CHECK");

    string expressions[] = {
        "{[()]}",
        "{[(])}",
        "((()))",
        "({[}])"};

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
    // test power function
    printHeader("POWER FUNCTION");
    cout << "Calculating power using recursion:" << endl;
    int base = 2;
    int p = 30; // Smaller values to avoid overflow
    start_time = high_resolution_clock::now();
    long long pow_result = power(base, p);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << base << " raised to the power of " << p << " is " << pow_result << endl;
    printTime("Recursive Power", elapsed.count());

    cout << "Calculating power using iterative method:" << endl;
    start_time = high_resolution_clock::now();
    long long pow_iterative_result = power_iterative(base, p);
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << base << " raised to the power of " << p << " is " << pow_iterative_result << endl;
    printTime("Iterative Power", elapsed.count());

    // ========================================
    // Summary
    // ========================================
    printHeader("ALL TESTS COMPLETED");
    cout << "All data structures and algorithms have been tested successfully!" << endl;
    cout << string(60, '=') << "\n"
         << endl;

    return 0;
}
