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
    if (count() == 0 || count() == 1)
    {
        return nullptr;
    }

    Node* n  = getNodeFor(value, this->root);

    if (n == nullptr)
        return 0;

    if (!n->left)
    {
        Node *temp = n;
        while (temp->parent)
        {
            temp = temp->parent;
            if (temp->info < value)
            {
                n = temp;
                break;
            }
        }
        if (n->info == value)
        {
            return 0;
        }
        else
        {
            return n;
        }
    }

    if (n->left)
    {
        n = n->left;
        while (n->right)
        {
            n = n->right;
        }
        return n;
    }
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
    if (count() == 0 || count() == 1)
    {
        return nullptr;
    }

    Node* n  = getNodeFor(value, this->root);

    if (n == nullptr)
        return 0;

    if (!n->right)
    {
        if (n->parent)
        {

        }
        Node *temp = n;
        while (temp->parent)
        {
            temp = temp->parent;
            if (temp->info > value)
            {
                n = temp;
                break;
            }
        }
        if (n->info == value)
        {
            return 0;
        }
        else
        {
            return n;
        }
    }

    if (n->right)
    {
        n = n->right;
        while (n->left)
        {
            n = n->left;
        }
        return n;
    }
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
    Node* n = getNodeFor(value,this->root);


    if (!n) // node does not exist
    {
        return false;
    } 

    bool isLeftChild;
    if (n->parent)
        isLeftChild = (n->info < n->parent->info);
    else
        isLeftChild = false;

    if (count() == 1) // one node case
    {
        this->root = nullptr;
        delete n;
        return true;
    }

    if (!n->left && !n->right) // no children case
    {
        // if (n == this->root) // one node case
        // {
        //     this->root = NULL;
        // } 
        if (isLeftChild) 
        {
            n->parent->left = NULL;
        } 
        else 
        {
            n->parent->right = NULL;
        }
        delete n;
        return true;
    } 

    // one child cases:

    else if (!n->left) 
    {
        if (n == this->root) // root case: does not have parent
        {
            this->root = n->right;
            this->root->parent = nullptr;
            delete n;
            return true;
        } 
        else if (isLeftChild) 
        {
            n->parent->left = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        } 
        else 
        {
            n->parent->right = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        }
    } 

    else if (!n->right) 
    {
        if (n == this->root) // root case, no parent
        {
            this->root = n->left;
            this->root->parent = nullptr;
            delete n;
            return true;
        } 
        else if (isLeftChild) 
        {
            n->parent->left = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        } 
        else 
        {
            n->parent->right = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        }
    } 
    else // two node case
    {
        Node* pre = getPredecessorNode(value);
        if (!pre) 
            return false;

        int newVal = pre->info;
        remove(pre->info);
        n->info = newVal;
        return true;
    }

    // Node *n = getNodeFor(value, this->root);

    // if (!n)
    // {
    //     return false;
    // }

    // if (n->parent && !n->left && !n->right)
    // {
    //     if (n->info < n->parent->info)
    //     {
    //         n->parent->left = nullptr;
    //     }
    //     else
    //     {
    //         n->parent->right = nullptr;
    //     }
    //     delete n;
    //     return true;
    // }

    // else if (n->parent && n->left && !n->right)
    // {
    //     Node *l = n->left;
    //     n->parent->left = l;
    //     l->parent = n->parent;
    //     delete n;
    //     return true;
    // }

    // else if (n->parent && n->right && !n->left)
    // {
    //     Node *r = n->right;
    //     n->parent->right = r;
    //     r->parent = n->parent;
    //     delete n;
    //     return true;
    // }

    // else if (n->left && n->right)
    // {
    //     Node *temp = getPredecessorNode(n->info);
    //     int val = temp->info;
    //     remove(temp->info);
    //     n->info = val;
    //     return true;
    // }

    // return false;
}
