#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Queue
{
    int size{};
    int front{};
    int rear{};
    int *array{};
    int added_elements{};

public:
    Queue(int size) : size(size) { array = new int[size]; }
    ~Queue() { delete[] array; }

    int next(int idx) { return (idx + 1) % size; }
    bool isFull() { return added_elements == size; }
    bool isEmpty() { return added_elements == 0; }
    int front_element() { return array[front]; }
    void enqueue(int val)
    {
        assert(!isFull());
        array[rear] = val;
        rear = next(rear);
        added_elements++;
    }
    int dequeue()
    {
        assert(!isEmpty());
        int val = array[front];
        front = next(front);
        added_elements--;
        return val;
    }
    void display()
    {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty())
        {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";
        for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
            cout << array[cur] << " ";
        cout << "\n";
    }
};
class Deque
{
    int size{};
    int front{};
    int rear{};
    int *array{};
    int added_elements{};

public:
    Deque(int size) : size(size) { array = new int[size]; }
    ~Deque() { delete[] array; }
    bool isFull() { return added_elements == size; }
    bool isEmpty() { return added_elements == 0; }
    int next(int idx) { return (idx + 1) % size; }
    int prev(int idx) { return (idx - 1 + size) % size; }

    void enqueue_rear(int value)
    {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }
    int dequeue_front()
    {
        assert(!isEmpty());
        int val = array[front];
        front = next(front);
        added_elements--;
        return val;
    }
    void enqueue_front(int value)
    {
        assert(!isFull());
        front = prev(front);
        array[front] = value;
        added_elements++;
    }
    int dequeue_rear()
    {
        assert(!isEmpty());
        rear = prev(rear);
        int val = array[rear];
        added_elements--;
        return val;
    }
    void display()
    {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty())
        {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";

        for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
            cout << array[cur] << " ";
        cout << "\n\n";
    }
};
class QStack
{
    Queue q;
    int added_elements{};

public:
    QStack(int size) : q(size) {}
    void push(int x)
    {
        q.enqueue(x);
        int sz = added_elements;
        while (sz--)
        {
            q.enqueue(q.dequeue());
        }
        added_elements++;
    }
    int pop() { return q.dequeue(); }
    int peek() { return q.front_element(); }
    bool isFull() { return q.isFull(); }
    bool isEmpty() { return q.isEmpty(); }
};
class Stack
{
private:
    int size{};
    int top{};
    int *array{};

public:
    Stack(int size) : size(size), top(-1)
    {
        array = new int[size];
    }

    ~Stack()
    {
        delete[] array;
    }

    void push(int x)
    {
        assert(!isFull());
        array[++top] = x;
    }

    int pop()
    {
        assert(!isEmpty());
        return array[top--];
    }

    int peek()
    {
        assert(!isEmpty());
        return array[top];
    }

    int isFull()
    {
        return top == size - 1;
    }

    int isEmpty()
    {
        return top == -1;
    }

    void display()
    {
        for (int i = top; i >= 0; i--)
            cout << array[i] << " ";
        cout << "\n";
    }
};
class QueueS
{
private:
    int size;
    int added_elements{};
    Stack s1;
    Stack s2;

    void move(Stack &from, Stack &to)
    { // O(n)
        while (!from.isEmpty())
            to.push(from.pop());
    }

public:
    QueueS(int size) : size(size), s1(size), s2(size)
    {
    }
    // assume we enqueue: [1, 2, 3, 4]
    // assume we built stack to be s1 = [4, 3, 2, 1 (top)]
    // That is: it matches queue output
    // let's enqueue 5
    // move s1 to s2: s2 = [1, 2, 3, 4]
    // push 5 to s1: s1 = [5]
    // move s2 to s1: [5, 4, 3, 2 ,1]
    // 2 moves: reverse and cancel it

    void enqueue(int value)
    { // O(n)
        assert(!isFull());
        move(s1, s2);
        s1.push(value);
        move(s2, s1);
        added_elements++;
    }

    int dequeue()
    { // O(1)
        assert(!isEmpty());
        int value = s1.pop();
        --added_elements;
        return value;
    }

    int isEmpty()
    {
        return added_elements == 0;
    }

    bool isFull()
    {
        return added_elements == size;
    }
};
int main()
{
}
