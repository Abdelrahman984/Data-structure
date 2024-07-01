#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val{};
    TreeNode *left{};
    TreeNode *right{};
    TreeNode(int val) : val(val) {}
};

struct BinaryTree
{
    TreeNode *root{};
    BinaryTree(int root_value) : root(new TreeNode(root_value)) {}

    void add(vector<int> values, vector<char> direction)
    {
        assert(values.size() == direction.size());
        TreeNode *current = this->root;
        // iterate on the path, create all necessary TreeNodes
        for (int i = 0; i < (int)values.size(); ++i)
        {
            if (direction[i] == 'L')
            {
                if (!current->left)
                    current->left = new TreeNode(values[i]);
                else
                    assert(current->left->val == values[i]);
                current = current->left;
            }
            else
            {
                if (!current->right)
                    current->right = new TreeNode(values[i]);
                else
                    assert(current->right->val == values[i]);
                current = current->right;
            }
        }
    }

    void _print_inorder(TreeNode *current)
    {
        if (!current)
            return;
        _print_inorder(current->left);
        cout << current->val << " ";
        _print_inorder(current->right);
    }
    void print_inorder()
    {
        _print_inorder(root);
        cout << "\n";
    }
    void level_order_traversal1()
    {
        queue<TreeNode *> qu;
        qu.push(root);
        int level = 0;
        while (!qu.empty())
        {
            cout << "Level " << level << ": ";
            int sz = qu.size();
            while (sz--)
            {
                TreeNode *cur = qu.front();
                qu.pop();
                cout << cur->val << " ";
                if (cur->left)
                    qu.push(cur->left);
                if (cur->right)
                    qu.push(cur->right);
            }
            cout << "\n";
            level++;
        }
    }
};
bool isLeaf(TreeNode *node)
{
    return node && !node->left && !node->right;
}
class Solution
{
public:
    int maxValue(TreeNode *root)
    {
        if (!root)
            return 0;
        int res = root->val;
        if (root->left)
            res = max(res, maxValue(root->left));
        if (root->right)
            res = max(res, maxValue(root->right));
        return res;
    }
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        int leftDepth = 1 + maxDepth(root->left);
        int rightDepth = 1 + maxDepth(root->right);
        return max(leftDepth, rightDepth);
    }
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return false;
        if (isLeaf(root))
            return targetSum == root->val;
        targetSum -= root->val;
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }

    bool isCompleteTree(TreeNode *root)
    {
        queue<TreeNode *> nodes_queue;
        nodes_queue.push(root);

        // Once there is a single missing node (left before right)
        // Nothing else should be there: on this level or next level
        bool no_more_allowed = false;

        while (!nodes_queue.empty())
        {
            int sz = nodes_queue.size();

            while (sz--)
            {
                TreeNode *cur = nodes_queue.front();
                nodes_queue.pop();

                if (cur->left)
                {
                    if (no_more_allowed)
                        return false;
                    nodes_queue.push(cur->left);
                }
                else
                    no_more_allowed = true;

                if (cur->right)
                {
                    if (no_more_allowed)
                        return false;
                    nodes_queue.push(cur->right);
                }
                else
                    no_more_allowed = true;
            }
        }
        return true;
    }
    bool is_mirror(TreeNode *first, TreeNode *second)
    {
        if (!first && !second)
            return true;
        if (first && !second || !first && second || first->val != second->val)
            return false;
        is_mirror(first->left, second->right) &&
            is_mirror(first->right, second->left);
    }
    int sumOfLeftLeaves(TreeNode *root)
    {
        if (!root)
            return 0;
        int sum = 0;
        if (isLeaf(root->left))
            sum += root->left->val;
        sum += sumOfLeftLeaves(root->left);
        sum += sumOfLeftLeaves(root->right);
        return sum;
    }
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> results;
        deque<TreeNode *> dq;
        if (!root)
            return results;
        dq.push_back(root);
        bool forwardlvl = true;
        while (!dq.empty())
        {
            int sz = dq.size();
            vector<int> lvlValues;
            while (sz--)
            {
                TreeNode *cur;
                if (forwardlvl)
                {
                    cur = dq.front();
                    dq.pop_front();

                    if (cur->left)
                        dq.push_back(cur->left);
                    if (cur->right)
                        dq.push_back(cur->right);
                }
                else
                {
                    cur = dq.back();
                    dq.pop_back();
                    if (cur->right)
                        dq.push_front(cur->right);
                    if (cur->left)
                        dq.push_front(cur->left);
                }
                lvlValues.push_back(cur->val);
            }
            forwardlvl = !forwardlvl;
            results.push_back(lvlValues);
        }
        return results;
    }
};

int main()
{
}
