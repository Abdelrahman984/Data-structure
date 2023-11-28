#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void input()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
}

class Vector
{
private:
    int *arr{nullptr};
    int size{0};    // user size
    int capacity{}; // actual size

    void expand_capacity()
    {
        // Double the actual array size
        capacity *= 2;
        cout << "Expand capacity to "
             << capacity << "\n";
        int *arr2 = new int[capacity]{};
        for (int i = 0; i < size; ++i)
            arr2[i] = arr[i]; // copy data

        swap(arr, arr2);
        delete[] arr2;
    }

public:
    Vector(int size) : size(size)
    {
        if (size < 0)
            size = 1;
        capacity = size + 10;
        arr = new int[capacity]{};
    }

    ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }

    int get_size()
    {
        return size;
    }

    int get(int idx)
    {
        assert(0 <= idx && idx < size);
        return arr[idx];
    }

    void set(int idx, int val)
    {
        assert(0 <= idx && idx < size);
        arr[idx] = val;
    }

    void print()
    {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }

    int find(int value)
    {
        for (int i = 0; i < size; ++i)
            if (arr[i] == value)
                return i;
        return -1; // -1 for NOT found
    }

    int get_front()
    {
        return arr[0];
    }

    int get_back()
    {
        return arr[size - 1];
    }

    void push_back(int value)
    {
        if (size == capacity)
            expand_capacity();
        arr[size++] = value;
    }
    void insert(int idx, int value)
    {
        assert(0 <= idx && idx < size);

        if (size == capacity)
            expand_capacity();

        // Shift all the data to right first
        for (int p = size - 1; p >= idx; --p)
            arr[p + 1] = arr[p];

        arr[idx] = value;
        ++size;
    }
    void right_rotate()
    {
        if (size <= 1)
            return;
        int end = arr[size - 1];
        for (int i = size - 1; i >= 1; --i) // 0 1 2 3 4
            arr[i] = arr[i - 1];            // 4 0 1 2 3
        arr[0] = end;
    }
    void right_rotate(int times)
    {
        if (size <= 1)
            return;
        times = times % size;
        while (times--)
        {
            right_rotate();
        }
    }
    void left_rotate()
    {
        if (size <= 1)
            return;
        int start = arr[0];
        for (int i = 0; i < size - 1; ++i) // 0 1 2 3 4
            arr[i] = arr[i + 1];           // 1 2 3 4 0
        arr[size - 1] = start;
    }
    void left_rotate(int times)
    {
        if (size <= 1)
            return;
        times = times % size;
        while (times--)
        {
            left_rotate();
        }
    }
    int pop(int idx)
    {
        assert(0 <= idx && idx < size);
        int val = arr[idx];
        for (int i = idx; i < size - 1; i++)
            arr[i] = arr[i + 1];
        --size;
        return val;
    }
    int find_transposition(int value)
    {
        int idx = find(value);
        if (idx == -1)
            return -1;
        if (idx == 0)
            return 0;
        swap(arr[idx], arr[idx - 1]);
        return idx - 1;
    }
};

int main()
{
    input();
    fast();

    int n = 5;
    Vector v(n);
    for (int i = 0; i < n; ++i)
        v.set(i, i);

    v.print(); // 0 1 2 3 4
    v.right_rotate(5 * 1000);
    v.print(); // 0 1 2 3 4
    v.right_rotate(2);
    v.print(); // 3 4 0 1 2
    v.left_rotate();
    v.print(); // 4 0 1 2 3

    int val = v.pop(2);
    cout << val << "\n"; // 1
    v.print();           // 4 0 2 3

    cout << v.find_transposition(3) << "\n"; // 2
    v.print();                               // 4 0 3 2

    return 0;
}
