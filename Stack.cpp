#include <bits/stdc++.h>
#define ll long long
using namespace std;

// simple trick to avoid re-changing the class
typedef char type;

class Stack
{
private:
    int size{};
    int top{};
    type *array{};

public:
    Stack(int size) : size(size), top(-1)
    {
        array = new type[size];
    }

    ~Stack()
    {
        delete[] array;
    }

    void push(type x)
    {
        assert(!isFull());
        array[++top] = x;
    }

    type pop()
    {
        assert(!isEmpty());
        return array[top--];
    }

    type peek()
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
    void display_reversed()
    {
        for (int i = 0; i <= top; i++)
            cout << array[i] << " ";
        cout << "\n";
    }
    void insert_at_bottom(int x)
    {
        if (isEmpty())
            push(x);
        else
        {
            int cur = pop();
            insert_at_bottom(x);
            push(cur);
        }
    }
    void reverse()
    {
        if (isEmpty())
            return;
        int cur = pop();
        reverse();
        insert_at_bottom(cur);
    }
};
string reverse_subwords(string line)
{
    string result;
    // simple trick. add dummy space to force last group to be formed
    line += ' ';
    Stack stk(line.size());
    for (int i = 0; i < (int)line.size(); ++i)
    {
        if (line[i] == ' ')
        { // get content (now reversed)
            while (!stk.isEmpty())
                result += stk.pop();
            result += ' ';
        }
        else
            stk.push(line[i]);
    }
    return result; // has extra space in its end

    // Tip: adding elements in stack then getting = reversed content
}
int reverse_num(int num)
{
    if (num == 0)
        return 0;
    Stack s(25);
    while (num)
    {
        s.push(num % 10);
        num /= 10;
    }
    int tens = 1;
    while (!s.isEmpty())
    {
        num = s.pop() * tens + num;
        tens *= 10;
    }
    return num;
}
char get_open_match(char ch)
{
    if (ch == ')')
        return '(';
    if (ch == ']')
        return '[';
    return '{';
}
bool isValid(string str)
{
    Stack parentheses(str.size());

    for (int i = 0; i < (int)str.size(); ++i)
    {
        char ch = str[i];

        if (ch == '(' || ch == '[' || ch == '{')
            parentheses.push(ch);
        else if (parentheses.isEmpty() || parentheses.pop() != get_open_match(ch))
            return false; // There must be an open match of the right type
    }
    return parentheses.isEmpty();
}
string removeDuplicates(string s)
{
    stack<char> stk;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if (!stk.empty() && stk.top() == c)
            stk.pop();
        else
            stk.push(c);
    }
    string r = "";
    while (!stk.empty())
    {
        r += stk.top();
        stk.pop();
    }
    reverse(r.begin(), r.end());
    return r;
}
void asteroidCollision(int arr[], int len)
{
    Stack s(len);
    for (int i = 0; i < len; i++)
    {
        int asteroid = arr[i];
        bool isExplosed = false;
        while (!s.isEmpty() && asteroid < 0 && s.peek() >= 0)
        {
            if (-asteroid > s.peek())
            {
                s.pop();
                continue;
            }
            else if (-asteroid == s.peek())
            {
                s.pop();
            }
            isExplosed = true;
            break;
        }
        if (!isExplosed)
            s.push(asteroid);
    }
    s.display_reversed();
}
int scoreOfParentheses(string str)
{
    Stack stk(str.size());
    stk.push(0);
    for (int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if (c == '(')
            stk.push(0);
        else
        {
            int last = stk.peek();
            stk.pop();
            if (last == 0)
                last += 1;
            else
                last *= 2;
            int parent_par = stk.peek() + last; // new total sum
            stk.pop();
            stk.push(parent_par);
        }
    }
    return stk.pop();
}
void next_greater_num(int v[], int len)
{
    Stack pos(len);
    for (int i = 0; i < (int)len; ++i)
    {
        while (!pos.isEmpty() && v[i] > v[pos.peek()])
            v[pos.pop()] = v[i];
        pos.push(i);
    }
    // all items in the stack are not answered
    while (!pos.isEmpty())
        v[pos.pop()] = -1;

    for (int i = 0; i < (int)len; ++i)
        cout << v[i] << " ";
    cout << "\n";
}
//*------------------------------------------------------------------------------------
int presedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}
string evalaute_postfix(string s)
{
    Stack stk(s.size() / 2 + 1);
    s += '-';
    stk.push('#');
    string output;
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
            output += s[i];
        else if (s[i] == '(')
            stk.push(s[i]);
        else if (s[i] == ')')
        {
            while (stk.peek() != '(')
                output += stk.pop();
            stk.pop();
        }
        else
        {
            while (presedence(stk.peek()) >= presedence(s[i]))
                output += stk.pop();
            stk.push(s[i]);
        }
    }
    return output;
}
int main()
{
    string postfix = "(1+2)*(3-4)";
    cout << evalaute_postfix(postfix) << "\n";
}
