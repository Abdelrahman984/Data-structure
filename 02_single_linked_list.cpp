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
    int data;
    Node *next;
    Node(int data) : data(data) {}
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
    int length = 0; // let's maintain how many nodes

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
        cout << node->data << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

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
            return;
        }

        assert(head != nullptr);
        assert(tail != nullptr);
        assert(tail->next == nullptr);

        if (length == 1)
            assert(head == tail);
        else
        {
            assert(head != tail);

            if (length == 2)
                assert(head->next == tail);
            else if (length == 3)
            {
                assert(head->next);
                assert(head->next->next == tail);
            }
        }
        int len = 0;
        Node *prev = nullptr;
        for (Node *cur = head; cur; prev = cur, cur = cur->next, len++)
            assert(len < 10000); // Consider infinite cycle?

        assert(length == len);
        assert(length == (int)debug_data.size());
        assert(prev == tail); // last node is tail
    }
    //////////////////////////////////////////////////////////////////////////////////
    void print()
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            cout << cur->data << " ";
        }
        cout << "\n";
    }
    void print1()
    {
        Node *temp_head = head;
        while (temp_head)
        {
            cout << temp_head->data << " ";
            temp_head = temp_head->next;
        }
        cout << "\n";
    }
    void print2(Node *head)
    {
        if (head == nullptr)
        {
            cout << "\n";
            return;
        }
        cout << head->data << " ";
        print2(head->next);
    }
    void print3(Node *head)
    {
        if (head == nullptr)
        {
            cout << "\n";
            return;
        }
        print3(head->next);
        cout << head->data << " ";
    }
    //----------------------------------------------------------------
    Node *get_nth(int n)
    {
        int cnt = 0;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (++cnt == n)
                return cur;
        }
        return nullptr;
    }
    Node *get_nth_back(int n)
    {
        if (n > length)
            return nullptr;
        return get_nth(length - n + 1);
    }
    Node *get_tail() // without tail/length!
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->next == nullptr)
            {
                return cur;
            }
        }
        return nullptr;
    }
    Node *get_previous(Node *target)
    {
        for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
        {
            if (cur == target)
                return prv;
        }
        return nullptr;
    }
    //----------------------------------------------------------------
    int search(int value)
    {
        int idx = 0;
        for (Node *cur = head; cur; cur = cur->next, idx++)
        {
            if (cur->data == value)
                return idx;
        }
        return -1;
    }
    int search_improved(int value)
    {
        int idx = 0;
        for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
        {
            if (cur->data == value)
            {
                if (!prv)
                {
                    return idx;
                }
                return idx - 1;
            }
            ++idx;
        }
        return -1;
    }
    //----------------------------------------------------------------
    void add_node(Node *node)
    {
        debug_add_node(node);
        ++length;
    }
    void insert_end(int value)
    {
        Node *item = new Node(value);
        add_node(item);
        if (!head) // list is empty
            head = tail = item;
        else // list is not empty
        {
            tail->next = item;
            tail = item;
        }
        debug_verify_data_integrity();
    }
    void insert_front(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        item->next = head;
        head = item;

        if (length == 1)
            tail = head;

        debug_verify_data_integrity();
    }
    void add_element(int value) // without tail/length!
    {                           // reversed
        Node *item = new Node(value);
        item->next = head;
        head = item;
    }
    void embed_after(Node *node, int value)
    {
        // Add a node with value between node and its next
        Node *item = new Node(value);
        add_node(item);

        item->next = node->next;
        node->next = item;
    }
    void insert_after(Node *src, Node *target)
    {
        // Given node src, link target after it with my list before/after
        assert(src && target);
        target->next = src->next;
        src->next = target;
        debug_add_node(target);
        ++length;
    }
    void insert_sorted(int value)
    { // 3 special cases for simplicity
        if (!length || value <= head->data)
            insert_front(value);
        else if (tail->data <= value)
            insert_end(value);
        else
        {
            // Find the node I am less than. Then I am before it
            for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
            {
                if (value <= cur->data)
                {
                    embed_after(prv, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();

        // This idea is used in Insertion Sort Algorithm
    }
    void insert_alternate(LinkedList &another)
    {
        if (!another.length)
            return;
        if (!length)
        {
            head = another.head;
            tail = another.tail;
            length = another.length;
            debug_data = another.debug_data;
            return;
        }
        Node *new_tail;
        if (length <= another.length)
            new_tail = another.tail;
        else
            new_tail = tail;

        Node *cur1 = head, *cur2 = another.head;
        while (cur1 && cur2)
        {
            Node *next1 = cur1->next, *next2 = cur2->next;
            insert_after(cur1, cur2);
            another.length--;

            cur1 = next1;
            cur2 = next2;
        }
        tail = new_tail;
        tail->next = nullptr;
        debug_verify_data_integrity();
    }

    void delete_node(Node *node)
    {
        debug_remove_node(node);
        --length;
        delete node;
    }
    void delete_front()
    {
        assert(length);
        Node *cur = head->next;
        delete_node(head);
        head = cur;
        if (length <= 1)
            tail = head;
        debug_verify_data_integrity();
    }
    void delete_first()
    {
        if (head)
        {
            // Move to next in the list
            //  and remove current
            Node *cur = head;
            head = head->next;
            delete_node(cur);

            if (!head) // data integrity!
                tail = nullptr;
            debug_verify_data_integrity();
        }
    }
    void delete_last()
    {
        if (length <= 1)
        {
            delete_first();
            return;
        }
        // Get the node before tail: its order is length-1 node
        Node *previous = get_nth(length - 1);

        delete_node(tail);
        tail = previous;
        tail->next = nullptr;

        debug_verify_data_integrity();
    }
    void delete_nth_node(int n)
    {
        if (n < 1 || n > length)
            cout << "Error. No such nth node\n";
        else if (n == 1)
            delete_first();
        else
        {
            // Connect the node before nth with node after nth
            Node *before_nth = get_nth(n - 1);
            Node *nth = before_nth->next;
            bool is_tail = nth == tail;
            // connect before node with after
            before_nth->next = nth->next;
            if (is_tail)
                tail = before_nth;

            delete_node(nth);

            debug_verify_data_integrity();
        }
    }
    void delete_next_node(Node *node)
    {
        Node *to_delete = node->next;
        bool is_tail = to_delete == tail;
        // node->next in middle to delete
        node->next = node->next->next;
        delete_node(to_delete);

        if (is_tail)
            tail = node;
    }
    void delete_node_with_key(int value)
    {
        if (!length)
            cout << "Empty list!\n";
        else if (head->data == value)
        {
            delete_first();
        }
        else
        {
            bool found = false;
            for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
            {
                if (cur->data == value)
                {
                    delete_next_node(prv);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Not found\n";
            }
        }
        debug_verify_data_integrity();
    }
    void delete_even_positions()
    {
        int cnt = 1;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cnt % 2 != 0 && cur->next)
            {
                delete_next_node(cur);
                cnt += 2;
            }
        }
        debug_verify_data_integrity();
    }
    void remove_duplicates_from_not_sorted()
    { // O(n^2) time - O(1) memory
        if (length <= 1)
            return;

        // Just like 2 nested loops, find all duplicates and delete

        for (Node *cur1 = head; cur1; cur1 = cur1->next)
        {
            for (Node *cur2 = cur1->next, *prv = cur1; cur2;)
            {
                if (cur1->data == cur2->data)
                {
                    delete_next_node(prv);
                    cur2 = prv->next;
                }
                else
                    prv = cur2, cur2 = cur2->next; // normal move
            }
        }
        debug_verify_data_integrity();
    }
    void delete_last_occurrence(int target)
    { // O(n) time - O(1) memory
        if (!length)
            return;

        Node *delete_my_next_node = nullptr;
        bool is_found = false;

        // Find the last one and remove it

        for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
        {
            if (cur->data == target)
                is_found = true, delete_my_next_node = prv;
        }
        if (is_found)
        {
            if (delete_my_next_node)
                delete_next_node(delete_my_next_node);
            else
                // if prv is null, then found at head
                delete_front();
        }
        debug_verify_data_integrity();
    }
    //----------------------------------------------------------------
    ~LinkedList()
    {
        while (head)
        {
            Node *cur = head->next;
            delete head;
            head = cur;
        }
    }

    bool is_same1(const LinkedList &other) // using length
    {
        if (length == other.length)
        {
            for (Node *cur1 = head, *cur2 = other.head; cur1; cur1 = cur1->next, cur2 = cur2->next)
            {
                if (cur1->data != cur2->data)
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    bool is_same(const LinkedList &other) // without using length
    {
        for (Node *cur1 = head, *cur2 = other.head; cur1 || cur2; cur1 = cur1->next, cur2 = cur2->next)
        {
            if (cur1 == nullptr || cur2 == nullptr)
            {
                return false;
            }
            if (cur1->data != cur2->data)
            {
                return false;
            }
        }
        return true;
    }
    // bool is_same(const LinkedList &other)
    // { // O(n) time - O(1) memory
    //     Node *h1 = head, *h2 = other.head;
    //     while (h1 && h2)
    //     {
    //         if (h1->data != h2->data)
    //             return false;
    //         h1 = h1->next, h2 = h2->next;
    //     }
    //     return !h1 && !h2; // make sure both ends together
    // }

    //----------------------------------------------------------------
    void swap_pairs()
    {
        for (Node *cur = head; cur; cur = cur->next->next)
        {
            if (!cur->next)
            {
                break;
            }
            swap(cur->data, cur->next->data);
        }
    }
    void swap_head_tail()
    { // O(n) time - O(1) memory
        // 0 or 1 node. We can use length also if(length <= 1)
        if (!head || !head->next)
            return;

        if (length == 2)
        {
            swap(tail, head);
            head->next = tail;
            tail->next = nullptr;
            return;
        }

        Node *prv = get_previous(tail); // node before tail

        // Let's make current tail as head
        // Link tail to the 2nd node
        tail->next = head->next;

        // Let's make current head as tail
        // Link tail's previous to head
        prv->next = head;
        head->next = nullptr;

        swap(tail, head); // Set new head and tail

        debug_verify_data_integrity();
    }

    void reverse()
    {
        if (length <= 1)
            return;

        tail = head;
        Node *prv = head;
        head = head->next;
        while (head)
        {
            // store & reverse link
            Node *next = head->next;
            head->next = prv;

            // move step
            prv = head;
            head = next;
        }
        // Finalize head and tail
        head = prv;
        tail->next = nullptr;

        debug_verify_data_integrity();
    }
    void left_rotate(int k) // without using loop
    {
        if (length <= 1 || k % length == 0)
            return; // 0 or 1 elements or useless rotation

        k %= length; // Remove useless cycles

        Node *nth = get_nth(k);
        tail->next = head; // create cycle

        // Reset tail/head
        tail = nth;
        head = nth->next;

        tail->next = nullptr; // disconnect cycle
        debug_verify_data_integrity();
    }
    // void left_rotate(int k) //using loop
    // {
    //     if (length <= 1 || k % length == 0)
    //         return;
    //     k %= length;
    //     while (k--)
    //     {
    //         Node *next = head->next;
    //         Node *prv = get_previous(tail);
    //         tail->next = head;
    //         head->next = nullptr;
    //         tail = head;
    //         head = next;
    //     }
    //     debug_verify_data_integrity();
    // }

    Node *move_to_end(Node *cur, Node *prv)
    {
        if (cur == tail) // Fix
            return cur;  // already at the end

        Node *next = cur->next;
        tail->next = cur;

        if (prv)
            prv->next = next;
        else
            head = next; // cur was head

        tail = cur;
        tail->next = nullptr;
        return next;
    }
    void move_key_occurance_to_end(int key)
    {
        if (length <= 1)
            return;
        int len = length;
        for (Node *cur = head, *prv = nullptr; len--;)
        {
            if (cur->data == key)
            {
                cur = move_to_end(cur, prv);
            }
            else
            {
                prv = cur;
                cur = cur->next;
            }
        }
        debug_verify_data_integrity();
    }
    Node *move_and_delete(Node *node)
    {
        Node *tmp = node->next;
        delete_node(node);
        return tmp;
    }
    int max(Node *head = nullptr, bool is_first_call = true)
    { // O(n) time - O(n) memory
        // It is tricky to have function name same as standard
        // use std for standard and this-> for the class for clarity
        if (is_first_call)
            return this->max(this->head, false);

        if (head == nullptr)
            return INT_MIN; // initial min value
        return std::max(head->data, this->max(head->next, false));
    }

    void odd_pos_even_pos() // by: me
    {
        if (length <= 2)
            return;
        int len = length / 2;
        for (Node *cur = head->next, *prv = head; len--; prv = cur, cur = cur->next)
        {
            cur = move_to_end(cur, prv);
        }
        debug_verify_data_integrity();
    }
    // void odd_pos_even_pos()//by: dr.mostafa
    // { // O(n) time - O(1) memory
    //     if (length <= 2)
    //         return;
    //     Node *first_even = head->next;
    //     Node *cur_odd = head;
    //     while (cur_odd->next && cur_odd->next->next)
    //     {
    //         Node *next_even = cur_odd->next;
    //         // connect odd with odd and even with even
    //         cur_odd->next = cur_odd->next->next;
    //         next_even->next = next_even->next->next;
    //         cur_odd = cur_odd->next;
    //         // for odd length, tail is changed to last even node
    //         if (length % 2 == 1)
    //             tail = next_even;
    //     }
    //     // connect last odd with the first even
    //     cur_odd->next = first_even;
    //     debug_verify_data_integrity();
    // }

    void add_num(LinkedList &another)
    {
        // let X = max(length, another.length)
        // let Y = max(length, another.length) - min(length, another.length)
        // O(X) time - O(Y) memory
        if (!another.length)
            return;

        Node *my_cur = head;
        Node *his_cur = another.head;
        int carry = 0, my_value, his_value;

        // refresh first adding 2 numbers and handling their carry
        // Iterate sequentially over both
        // take the current values, add and compute the value and the carry

        while (my_cur || his_cur)
        {
            my_value = 0, his_value = 0;
            if (my_cur)
                my_value = my_cur->data;
            if (his_cur)
            {
                his_value = his_cur->data;
                his_cur = his_cur->next;
            }

            my_value += his_value + carry;
            carry = my_value / 10;
            my_value %= 10;

            if (my_cur)
            {
                my_cur->data = my_value;
                my_cur = my_cur->next;
            }
            else
                insert_end(my_value);
            // we can even stop earlier
        }
        if (carry)
            insert_end(carry);

        debug_verify_data_integrity();
    }

    void remove_all_repeated_from_sorted()
    { // O(n) time - O(1) memory
        if (length <= 1)
            return;

        // Add dummy head for easier prv linking
        insert_front(-1234);

        tail = head;
        Node *previous = head;
        Node *cur = head->next; // Our actual head

        while (cur)
        {
            // 2 cases: Either blocks of repeated so remove it. Or single node, keep it

            // keep removing blocks of SAME value
            bool any_removed = false;
            while (cur && cur->next && cur->data == cur->next->data)
            {
                int block_value = cur->data;
                any_removed = true;
                while (cur && cur->data == block_value)
                    cur = move_and_delete(cur);
            }
            if (any_removed)
            {
                if (!cur)
                    tail = previous;
                previous->next = cur; // link after the removed nodes
                previous = cur;
            }
            else
            {
                // No duplicates. Connect and use as tail for now
                tail = cur;
                previous = cur;
                cur = cur->next;
            }
        }
        previous = head->next; // actual head
        delete_front();        // remove dummy head
        head = previous;
        if (!head)
            tail = head;
        debug_verify_data_integrity();
    }

    pair<Node *, pair<Node *, Node *>> reverse_subchain(Node *cur_head, int k)
    { // O(n) time - O(1) memory
        // Given a node: reverse only a chain of k nodes
        // return: current chain head, current chain tail, next head
        // Logic same as normal reverse function

        Node *cur_tail = cur_head; // the head is tail once reversed
        Node *prv = cur_head;
        cur_head = cur_head->next; // Start from next

        for (int s = 0; s < k - 1 && cur_head; ++s)
        { // k-1 links reversed
            // store & reverse link
            Node *next = cur_head->next;
            cur_head->next = prv;

            // move step
            prv = cur_head;
            cur_head = next;
        }
        return make_pair(prv, make_pair(cur_tail, cur_head)); // C++17 can use tie/tuple
    }
    void reverse_chains(int k)
    {
        // Reverse each K consecutive nodes
        if (length <= 1 || k == 1)
            return;

        Node *last_tail = nullptr;
        Node *next_chain_head = head;
        head = nullptr;

        while (next_chain_head)
        {
            // Keep reversing a chain of K nodes, and link with prv chain
            pair<Node *, pair<Node *, Node *>> p = reverse_subchain(next_chain_head, k);
            Node *chain_head = p.first;
            Node *chain_tail = p.second.first;
            next_chain_head = p.second.second;
            tail = chain_tail;

            if (!head) // first chain
                head = chain_head;
            else // connect last chain tail with next chain head
                last_tail->next = chain_head;
            last_tail = chain_tail;
        }
        tail->next = nullptr;
        debug_verify_data_integrity();
    }
};

int main()
{

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";

    return 0;
}
