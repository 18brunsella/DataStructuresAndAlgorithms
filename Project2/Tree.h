/**
 * Binary Search Tree Class
 * Completed by Arvid Brunsell
 */

#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include <iostream>
#include <fstream>
#include <functional>

using namespace std;
template<class T> class BinarySearchTree
{
    public:
    BinarySearchTree() {root = nullptr;}
    //destructor
    ~BinarySearchTree() {
        filter([](int n){
            if (n%1 != 0) return 1;
            return 0;
        });
    }
    
    void insert(const T &t)
    {
        _insert(root,t);
    }
    void display() const
    {
        int level=0;
        _display(root,level);
    }
    void inOrderTraverse(vector<T>& vec) const
    {
        _inOrderTraverse(root, vec);
    }
    void deleteNode(const T &t)
    {
        _deleteNode(root, t);
    }
    void forEachInterval(const T &a, const T&b, function<void (const T)> func) const
    {
        _forEachInterval(root, a, b, func);
    }
    void filter(function<bool (const T)> isIn)
    {
        _filter(root, isIn);
    }
    bool verifyBinarySearchTree() const
    {
        Node *min = nullptr;
        Node *max = nullptr;
        bool result = _verifyBinarySearchTree(root, min, max);
        delete(min);
        delete(max);
        return result;
    }
    

    private:
        // class Node (you can modify,but it is not necessary)
        // The nested node class for objects in our tree.
        struct Node
        {
                friend class BinarySearchTree;

                Node() {m_ll = nullptr;  m_rl = nullptr;}

                Node(const T &t) {m_num = t;  m_ll = nullptr;  m_rl = nullptr;}
                Node(const T &t, Node * l, Node *r) : m_num{t}, m_ll{l}, m_rl{r} {}

                T &data() {return m_num;}

                const T &data() const {return m_num;}

                Node    *m_ll;
                Node    *m_rl;
                T       m_num;
        };

     Node *root;

    //inserts node into tree
    void _insert(Node*& parent, T data)
    {
        //if tree is empty
        if(parent == nullptr)
        {
            parent = new Node(data);
            return;
        }
        
        //if the value of the node is greater than the key given
        if(parent->m_num > data)
        {
            if(parent->m_ll == nullptr)
            {
                parent->m_ll = new Node(data);
            }
            _insert(parent->m_ll, data);
        }
        
        //if the value of the node is less than the key given
        if(parent->m_num < data)
        {
            if(parent->m_rl == nullptr)
            {
                parent->m_rl = new Node(data);
            }
            _insert(parent->m_rl, data);
        }
    
    }
    
    //internal method; do not change this function
    void _display(Node *p,int level) const
    {
        if (p ==nullptr) return;
        level++;
        if (p->m_rl != nullptr)
        {
            _display(p->m_rl,level);
        }
        for (int i = 0; i <= level; i++)
        {
            cout<<"    ";
        } 
        cout << "__" << p->data()<<endl;
        if (p->m_ll != nullptr)
        {
            _display(p->m_ll, level);
        }
    }
    
    //creates vector to print out in inorder traversal
    void _inOrderTraverse(Node *current, vector<T> &vec) const
    {
        if(current == nullptr) return;
    
        _inOrderTraverse(current->m_ll, vec);
        
        vec.push_back(current->m_num);
        
        _inOrderTraverse(current->m_rl, vec);
    }
    
    //finds the minimum value of the tree
    Node* _findMinValue(Node* node)
    {
        Node * current = node;
        
        while(current && current->m_ll != nullptr)
        {
            current = current->m_ll;
        }
        
        return current;
    }
    
    // deletes node from tree
    void _deleteNode(Node* &current, T delete_num)
    {
        // checks if the tree is empty
        if(current == nullptr) return;
        
        // recursively calls the deletenode function if the value of delete_num is different than the current node value
        if(delete_num < current->m_num)
        {
            _deleteNode(current->m_ll, delete_num);
        }
        else if(delete_num > current->m_num)
        {
            _deleteNode(current->m_rl, delete_num);
        }
        // case if the node value and delete_num are the same
        else
        {
            // if case that node deleted has no child
            if(current->m_rl == nullptr && current->m_ll == nullptr)
            {
                delete(current);
                current = nullptr;
            }
            
            // if case that node deleted has one child: if
            else if(current->m_ll == nullptr)
            {
                //stores the current node in temp
                Node* temp = current;
                current = current->m_rl;
                delete(temp);
            }
            
            else if(current->m_rl == nullptr)
            {
                //stores the current node into temp
                Node* temp = current;
                current = current->m_ll;
                delete(temp);
            }
            
            //if case that node deleted has two children
            else if(current->m_rl != nullptr && current->m_ll != nullptr)
            {
                Node *temp = _findMinValue(current->m_rl);
                
                current->m_num = temp->m_num;
                
                _deleteNode(current->m_rl, temp->m_num);
            }
        }
        
    }
    
    //finds any node that is in between the ranges given and the nodes do whatever is in the function
    void _forEachInterval(Node *root, const T& a, const T& b, function<void (const T)> func) const
    {
        if(root == nullptr) return;
        if(a < root->m_num)
        {
            _forEachInterval(root->m_ll, a, b, func);
        }
        if(root->m_num >= a && root->m_num <= b)
        {
            func(root->m_num);
        }
        if(b > root->m_num)
        {
            _forEachInterval(root->m_rl, a, b, func);
        }
    }
    
    //deletes any node that complies with the function
    void _filter(Node*& root, function<bool (const T)> & isIn)
    {
        // deletes nodes that comply with the function
        if(root == nullptr) return;
        // recursively calls for the right subtree
        _filter(root->m_rl, isIn);
        // recursively calls for the left subtree
        _filter(root->m_ll, isIn);
        // if the function is false for the function then it deletes the node
        if(isIn(root->m_num) == 0)
        {
            _deleteNode(root, root->m_num);
        }
    }
    
    //verifies that tree is an actual tree
    bool _verifyBinarySearchTree(Node *root, Node* min, Node* max) const
    {
        //checks if tree is empty
        if(root == nullptr) return true;
        //false conditions : if the value of node is less than minimum
        if(min != nullptr && root->m_num <= min->m_num) return false;
        // if the value of node is greater than maximum
        if(max != nullptr && root->m_num >= max->m_num) return false;
        //recursively calls for left and right subtree
        return _verifyBinarySearchTree(root->m_ll, min, root) && _verifyBinarySearchTree(root->m_rl, root, max);
    }
};


#endif
