// intbst.cpp
// Implements class IntBST
// Oviya Seeniraj, 2/9/23

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST()
{
    this->root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST()
{
    clear(this->root);
}

// recursive helper for destructor
void IntBST::clear(Node *n)
{
    // if (n != nullptr && n->left)
    // {
    //     clear(n->left);
    // }

    // if (n != nullptr && n->right)
    // {
    //     clear(n->right);
    // }

    // if (n != nullptr)
    // {
    //     if (n->parent != nullptr && n->parent->left != nullptr)
    //     {
    //         n->parent->left = nullptr;
    //     }
    //     else if (n->parent != nullptr && n->parent->right != nullptr)
    //     {
    //         n->parent->right = nullptr;
    //     }
    //     delete n;
    // }

    // return;

    // post-order deletion

    if (n == nullptr)
    {
        return;
    }

    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value)
{
    return (insert(value, this->root));
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n)
{
    // base case:
    if (n == nullptr)
    {
        n = new Node(value);
        this->root = n;

        return true;
    }

    else if (n->left == nullptr && value < n->info)
    {
        n->left = new Node(value);
        n->left->parent = n;
    }

    else if (n->right == nullptr && value > n->info)
    {
        n->right = new Node(value);
        n->right->parent = n;
    }

    else if (value < n->info)
    {
        insert(value, n->left);
    }

    else if (value > n->info)
    {
        insert(value, n->right);
    }

    return false;
    // if (n->info == value)
    // {
    //     return false;
    // }

    // if (n->info > value)
    // {
    //     if (n->left != nullptr && n->left->info >= value)
    //     {
    //         insert(value, n->left);
    //     }
    //     else
    //     {
    //         Node *toInsert = new Node(value);
    //         n->left->parent = toInsert;
    //         toInsert->parent = n;
    //         return true;
    //     }
    // }

    // else
    // {
    //     if (n->right != nullptr && n->right->info >= value)
    //     {
    //         insert(value, n->right);
    //     }
    //     else
    //     {
    //         Node *toInsert = new Node(value);
    //         n->right->parent = toInsert;
    //         toInsert->parent = n;
    //         return true;
    //     }
    // }

    // return false;
}

// print tree data pre-order
void IntBST::printPreOrder() const
{
    printPreOrder(this->root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const
{
    printInOrder(this->root); // IMPLEMENT HERE
}

void IntBST::printInOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const
{
    printPostOrder(this->root);
}

void IntBST::printPostOrder(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const
{
    return sum(this->root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const
{
    return count(this->root);
}

// recursive helper for count
int IntBST::count(Node *n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node *IntBST::getNodeFor(int value, Node *n) const
{

    if (n == nullptr)
    {
        return NULL;
    }

    if (n->info == value)
    {
        return n;
    }

    if (value < n->info)
    {
        return getNodeFor(value, n->left);
    }
    else
    {
        return getNodeFor(value, n->right);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const
{
    if (getNodeFor(value, this->root) != NULL)
    {
        return true;
    }
    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node *IntBST::getPredecessorNode(int value) const
{
    Node *n = getNodeFor(value, this->root);

    if (n == NULL)
    {
        return nullptr;
    }

    if (!n->left && !n->right)
    {
        return n->parent;
    }

    if (n->left && n->left->right)
    {
        n = n->left;
        while (n->right)
        {
            n = n->right;
        }
        return n;
    }

    else if (n->left)
    {
        return n->left;
    }

    return n;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const
{
    if (getPredecessorNode(value))
    {
        return getPredecessorNode(value)->info;
    }

    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node *IntBST::getSuccessorNode(int value) const
{
    Node *n = getNodeFor(value, this->root);

    if (n == NULL)
    {
        return nullptr;
    }

    if (!n->right)
    {
        while (n->parent && n->info < n->parent->info)
        {
            n = n->parent;
        }
        return n;
    }

    if (n->right && n->right->left)
    {
        n = n->right;
        while (n->left)
        {
            n = n->left;
        }
        return n;
    }

    else if (n->right)
    {
        return n->right;
    }

    return n;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const
{
    if (getSuccessorNode(value))
    {
        return getSuccessorNode(value)->info;
    }

    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value)
{
    // Node *n = getNodeFor(value, this->root);

    // if (!n)
    // {
    //     return false;
    // }

    // if (n->parent && !n->left && !n->right)
    // {
    //     n->parent == nullptr;
    //     return true;
    // }

    // if (n->parent && n->info == n->parent->left->info)
    // {
    //     Node *temp = getSuccessorNode(n->info);
    //     n->info = temp->info;
    //     delete temp;
    //     return true;
    // }

    // if (n->info == n->parent->right->info)
    // {
    //     Node *temp = getPredecessorNode(n->info);
    //     n->info = temp->info;
    //     delete temp;
    //     return true;
    // }

    return false;
}
