#include <bits/stdc++.h>
#define ll long long
using namespace std;
void fast()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
struct Node
{
    int data{};
    Node *next{};
    Node *prev{}; // Previous node!

    Node(int data) : data(data) {}

    void set(Node *next, Node *prev)
    {
        this->next = next;
        this->prev = prev;
    }

    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class LinkedList
{
private:
    Node *head{};
    Node *tail{};
    int length = 0;

    // let's maintain how many nodes

    vector<Node *> debug_data; // add/remove nodes you use

    void debug_add_node(Node *node)
    {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node *node)
    {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }

public:
    // Below 2 deletes prevent copy and assign to avoid this mistake
    LinkedList() {}
    LinkedList(const LinkedList &) = delete;
    LinkedList &operator=(const LinkedList &another) = delete;

    void debug_print_address()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }
    void debug_print_node(Node *node, bool is_seperate = false)
    {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr)
        {
            cout << "nullptr\n";
            return;
        }

        if (node->prev == nullptr)
            cout << "X\t";
        else
            cout << node->prev->data << "\t";

        cout << " <= [" << node->data << "]\t => \t";

        if (node->next == nullptr)
            cout << "X\t";
        else
            cout << node->next->data << "\t";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    void debug_print_list(string msg = "")
    {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int)debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "************\n"
             << flush;
    }
    string debug_to_string()
    {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node *cur = head; cur; cur = cur->next)
        {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }
    void debug_verify_data_integrity()
    {
        if (length == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else
        {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
        {
            if (len == length - 1) // make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        assert(length == (int)debug_data.size());

        len = 0;
        for (Node *cur = tail; cur; cur = cur->prev, len++)
        {
            if (len == length - 1) // make sure we end at head
                assert(cur == head);
        }
        cout << "\n";
    }
    ////////////////////////////////////////////////////////////
    // These 2 simple functions just to not forget changing the vector and length
    void delete_node(Node *node)
    {
        debug_remove_node(node);
        --length;
        delete node;
    }
    void add_node(Node *node)
    {
        debug_add_node(node);
        ++length;
    }
    void print()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }
    void print_reversed()
    {
        for (Node *cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    void link(Node *first, Node *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }
    void insert_end(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
        {
            head = tail = item;
        }
        else
        {
            link(tail, item);
            tail = item;
        }
        debug_verify_data_integrity();
    }
    void insert_front(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
        {
            link(item, head);
            head = item;
        }
        debug_verify_data_integrity();
    }
    void insert_sorted(int value)
    {
        if (!length || value <= head->data)
            insert_front(value);
        else if (value >= tail->data)
            insert_end(value);
        else
        {
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (value <= cur->data)
                {
                    embed_after(cur->prev, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();
    }
    void embed_after(Node *node_before, int value)
    { // Add a node with value between node and its next
        Node *middle = new Node(value);
        add_node(middle);
        Node *node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);
    }

    void delete_front()
    {
        if (!length)
            return;
        else if (length == 1)
        {
            delete_node(head);
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            delete_node(head->prev);
            head->prev = nullptr;
        }
        debug_verify_data_integrity();
    }
    void delete_end()
    {
        if (!length)
            return;
        else if (length == 1)
        {
            delete_node(tail);
            head = tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            delete_node(tail->next);
            tail->next = nullptr;
        }
        debug_verify_data_integrity();
    }
    Node *delete_and_link(Node *cur)
    {
        Node *prv = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);
        return prv;
    }

    void delete_node_with_key(int value)
    {
        if (!length)
            return;
        if (head->data == value)
            delete_front();
        else
        {
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (value == cur->data)
                {
                    cur = delete_and_link(cur);
                    if (!cur->next) // we removed last node!
                        tail = cur;
                }
            }
        }
        debug_verify_data_integrity();
    }

    void delete_all_nodes_with_key(int value)
    {
        if (!length)
            return;
        insert_front(value - 1); // dummy
        for (Node *cur = head->next; cur;)
        {
            if (cur->data == value)
            {
                cur = delete_and_link(cur);
                if (!cur->next)
                    tail = cur;
            }
            else
                cur = cur->next;
        }
        delete_front();

        debug_verify_data_integrity();
    }

    void delete_even_positions()
    {
        if (length <= 1)
            return;
        // cur is always odd and ->next is even
        for (Node *cur = head; cur && cur->next; cur = cur->next)
        {
            delete_and_link(cur->next);
            if (!cur->next)
                tail = cur; // in even length, the tail will change
        }
        debug_verify_data_integrity();
    }
    void delete_odd_positions()
    {
        // let's make odd positions even! Reuse old code :)
        insert_front(-1); // dummy node
        delete_even_positions();
        delete_front();
    }
    bool is_palindrome()
    {
        if (length <= 1)
            return true;
        for (Node *cur1 = head, *cur2 = tail; cur1 != cur2; cur1 = cur1->next, cur2 = cur2->prev)
        {
            if (cur1->data != cur2->data)
            {
                return false;
            }
        }
        return true;
    }
    int middle_value1()
    {
        assert(head);
        if (length == 1)
            return head->data;
        else if (length <= 3)
            return head->next->data;
        else
        {
            int len = length / 2 + 1;

            for (Node *cur = head; len--; cur = cur->next)
            {
                if (len == 1)
                {
                    return cur->next->data;
                }
            }
        }
    }
    int middle_value2()
    {
        assert(head);
        Node *slow = head, *fast = head;
        while (fast && fast->next)
        {
            fast = fast->next->next; // Hare: jump 2 steps
            slow = slow->next;       // Tortoise: jump 1 step
        }
        return slow->data;
    }
    Node *get_nth(int n)
    {
        int cnt = 0;
        for (Node *cur = head; cur; cur = cur->next)
            if (++cnt == n)
                return cur;
        return nullptr;
    }
    Node *get_nth_back(int n)
    {
        int cnt = 0;
        for (Node *cur = tail; cur; cur = cur->prev)
            if (++cnt == n)
                return cur;

        return nullptr;
    }
    void swap_kth(int k)
    {
        if (k > length)
            return;
        int kth_back = length - k + 1;

        if (k == kth_back)
            return; // same node

        if (k > kth_back)
            swap(k, kth_back);

        Node *first = get_nth(k);
        Node *last = get_nth(kth_back);

        Node *first_prev = first->prev;
        Node *first_next = first->next;

        Node *last_prev = last->prev;
        Node *last_next = last->next;

        if (k + 1 == kth_back) // consecutive (neighbours)
        {
            link(first_prev, last);
            link(last, first);
            link(first, last_next);
        }
        else
        {
            link(first_prev, last);
            link(last, first_next);

            link(last_prev, first);
            link(first, last_next);
        }
        if (k == 1)
            swap(head, tail);
    }
    void reverse()
    {
        if (length <= 1)
            return;
        Node *h = head, *nxt = head->next;
        while (nxt)
        {
            Node *tmp = nxt->next;
            link(nxt, h);

            h = nxt;
            nxt = tmp;
        }

        swap(head, tail);
        head->prev = tail->next = nullptr;
        debug_verify_data_integrity();
    }
    void merge_2sorted_lists(LinkedList &other)
    {
        if (!other.length)
            return;
        if (!length)
        {
            head = other.head;
            tail = other.tail;
            length = other.length;
            debug_data.insert(debug_data.end(), other.debug_data.begin(), other.debug_data.end()); // add other nodes
            return;
        }

        Node *new_head = head, *new_tail = tail;
        if (head->data > other.head->data)
            new_head = other.head;
        if (tail->data < other.tail->data)
            new_tail = other.tail;

        Node *c1 = head, *nc1 = head->next;
        Node *c2 = other.head, *nc2 = other.head->next;
        while (c1 && c2)
        {
            if (c1->data <= c2->data)
            {
                if (nc1)
                {
                    if (c2->data <= nc1->data)
                    {
                        link(c1, c2);
                    }
                    c1 = nc1;
                    nc1 = nc1->next;
                }
                else
                {
                    link(c1, c2);
                    c1 = nc1;
                }
            }
            else
            {
                if (nc2)
                {
                    if (c1->data <= nc2->data)
                    {
                        link(c2, c1);
                    }
                    c2 = nc2;
                    nc2 = nc2->next;
                }
                else
                {
                    link(c2, c1);
                    c2 = nc2;
                }
            }
        }
        head = new_head, tail = new_tail;
        length += other.length;
        debug_data.insert(debug_data.end(), other.debug_data.begin(), other.debug_data.end()); // add other nodes
        debug_verify_data_integrity();
    }
};

int main()
{
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";

    return 0;
}
