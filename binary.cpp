#include "binary.h"
using namespace std;

/***
A Tree Node constructor. Set all the
member variables (key_, data_, left, right)
of the Node class. 

Input: 
T key - The key for the node
Y data - The actual value from the node

Output:
N/A
Intro Paragraph: 
Partner: anara32
This C++ implementation defines a generic BinarTree and Node class structure using tempaltes to allow for flexibility in key and data types. 
The node class encapsulates the properites of a tree node, including its key, data, and left and right children, with appropriate getters and setters. The binaryTree class 
supports a variety of core operations such as node insertion, deletiong, searching, and traversal (pre, in, post order). Memory management is handled through a custom destructor 
to prevent memory leaks by recurisvely deallocating nodes. 
***/
template <class T, class Y>
Node<T, Y>::Node(T key, Y data){
    /**
        Your code goes below here
    **/
    key_ = key; 
    data_ = data; 
    left = NULL; 
    right = NULL; 
} 

/***
A Node member getter function. This returns the
key of the node. 

Input: 
N/A

Output:
T - returns the key of the node that is of type T
***/
template <class T, class Y>
T Node<T, Y>::getKey(){
    /**
        Your code goes below here
    **/
   return key_;
}

/***
A Node member getter function. This returns the
actual data of the node. 

Input: 
N/A

Output:
Y - Returns the data of the node that is of type Y
***/
template <class T, class Y>
Y Node<T, Y>::getData(){
    /**
        Your code goes below here
    **/
   return data_;
}

/***
A Node member setter function. This sets the key
of a Node.

Input: 
T key - Sets the key of the Node of type T

Output:
N/A
***/
template <class T, class Y>
void Node<T, Y>::setKey(T key){
    /**
        Your code goes below here
    **/
    key_ = key; 
}

/***
A Node member setter function. This sets the actual
data of a Node.

Input: 
Y data - Sets the value of the Node of type Y

Output:
N/A
***/
template <class T, class Y>
void Node<T, Y>::setData(Y data){
    /**
        Your code goes below here
    **/
    data_ = data; 
}


/***
The BinaryTree constructor. Implicitly set the 
values of the member variables


Input: 
N/A

Output:
N/A
***/

template <class T, class Y>
BinaryTree<T,Y>::BinaryTree(){
    /**
        Your code goes below here
    **/
    root = NULL; 
}


/***
A BinaryTree Member fuction. This function takes in two arguments
and inserts a node. If the key already exists in the tree do nothing.

Input: 
Node<T,Y> *parent_node - The current root node
Node<T,Y> *data - The Node that you want to insert into the tree

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::insert_node(Node<T,Y> *parent_node, Node<T,Y> *data){
    /**
        Your code goes below here
    **/
    //if the tree is empty, make the data node the root 
    if (root == NULL){
        root = data; 
        return; 
    }
    //if parentNode is null, we can't insert
    if (parent_node == NULL){
        return; 
    }
    //if the key already exists, do nothing
    if (find_node(data->getKey()) != NULL){
        return; 
    }
    //insert node 
    if (data->getKey() < parent_node->getKey()){
        if (parent_node->left == NULL){
            parent_node->left = data; 
        } else{
            insert_node(parent_node->left, data); 
        }
    } else if (data->getKey() > parent_node->getKey()){
        if (parent_node->right == NULL){
            parent_node->right = data; 
        } else{
            insert_node(parent_node->right, data); 
        }
    }
}

/***
A BinaryTree Member fuction. This function takes in one arguments
and finds the parent of a node given a key.
If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are searching for.

Output:
Node<T,Y> * - returns the parent of the node you are searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node_parent(T key){
    /**
        Your code goes below here
    **/
   return find_node_parent(root, key);
}

/***
A BinaryTree Member fuction. This function takes in one arguments
and finds the node given a key.
If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are searching for.

Output:
Node<T,Y> * - returns the node you are searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node(T key){
    /**
        Your code goes below here
    **/
   return find_node(root, key);
}


/***
A BinaryTree Member fuction. This function deletes a node in
the binary tree. If the key does not exist do not do anything.

Input: 
T key - The key of the node you are trying to delete.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::delete_node(T key){
    /**
        Your code goes below here
    **/
    root = delete_node(root, key); 
}


/***
A BinaryTree helper fuction. This function deletes a node in
the binary tree. If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are trying to delete.
Node<T,Y>*node - The root of the current subtree

Output:
Node<T,Y> * - The new root since the root can be deleted.
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::delete_node(Node<T,Y>* node, T key){
    /**
        Your code goes below here
    **/
    if (node == NULL){
        return node; 
    } else if (key < node->getKey()){
        node->left = delete_node(node->left, key); 
    } else if (key > node->getKey()){
        node->right = delete_node(node->right, key); 
    } else { //node has been found
        if (node->left == NULL && node->right == NULL){
            //no children 
            delete node; 
            return NULL; 
        } else if (node->left == NULL) {
            //only right child 
            Node<T,Y>* temp = node->right; 
            delete node; 
            return temp; 
        } else if (node->right == NULL){
            //only left child 
            Node<T,Y>* temp = node->left; 
            delete node; 
            return temp; 
        } else{
            //two children 
            Node<T,Y>* temp = node->right; 
            //find the leftmost child of the right subtree
            while (temp->left != NULL){
                temp = temp->left; 
            }
            //copy the inorder successor's content to this node 
            node->setKey(temp->getKey()); 
            node->setData(temp->getData()); 

            //delete 
            node->right = delete_node(node->right, temp->getKey());
        }
    }
    return node; 
}


/***
A BinaryTree helper fuction. This function finds the parent node of
a node with a given key for the binary tree. If the key does not exist in the tree return NULL.

Input: 
T key - The key of the node you are trying to find.
Node<T,Y>*node - The root of the current subtree

Output:
Node<T,Y> * - Returns the parent of the key you were searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node_parent(Node<T,Y> *node,T key){
    /**
        Your code goes below here
    **/
    //Empty tree check & root node is node we are searching for check 
    if (node == NULL || (node->getKey() == key)){
        return NULL; 
    }
    //if the node is immediate child of the curr node 
    if ((node->left != NULL && node->left->getKey() == key) || (node->right != NULL && node->right->getKey() == key)){
        return node; 
    }
    //recursive check of left and right subtrees
    if (key < node->getKey() && node->left != NULL){
        return find_node_parent(node->left, key); 
    } else if (key > node->getKey() && node->right != NULL){
        return find_node_parent(node->right, key); 
    }
    return NULL; 
}

/***
A BinaryTree helper fuction. This function finds the node with 
a given key for the binary tree. If the key does not exist in 
the tree return NULL.

Input: 
T key - The key of the node you are trying to find.
Node<T,Y>*node - The root of the current subtree

Output:
Node<T,Y> * - Returns the Node in the Tree
              for the key you were searching for
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::find_node(Node<T,Y> *node,T key){
    /**
        Your code goes below here
    **/
    if (node == NULL || node->getKey() == key){
        return node; 
    }

    if (key < node->getKey()){
        return find_node(node->left, key); 
    } else {
        return find_node(node->right, key); 
    }
}

/***
A BinaryTree member fuction. This function performs
pre_order traversal on the tree and stores the nodes
inside a list

Input: 
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::pre_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    /**
        Your code goes below here
    **/
    if (node == NULL){
        return; 
    }
    list.push_back(*node); //traverse curr node

    //traverse left subtree 
    pre_order(node->left, list); 

    //traverse right subtree 
    pre_order(node->right, list); 
}

/***
A BinaryTree member fuction. This function performs
in_order traversal on the tree and stores the nodes
inside a list

Input: 
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::in_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    /**
        Your code goes below here
    **/
    if (node == NULL){
        return; 
    }
    //left subtree traversal 
    in_order(node->left, list); 

    //curr node 
    list.push_back(*node); 

    //right subtree traversal 
    in_order(node->right, list); 
}

/***
A BinaryTree member fuction. This function performs
post_order traversal on the tree and stores the nodes
inside a list

Input: 
Node<T,Y> *node - The current root of the subtree
List<Node<T,Y>> - A list to store all the nodes.

Output:
N/A
***/
template <class T, class Y>
void BinaryTree<T,Y>::post_order(Node<T,Y> *node, std::list<Node<T,Y> > &list){
    /**
        Your code goes below here
    **/
    if (node == NULL){
        return; 
    }

    //left subtree 
    post_order(node->left, list); 

    //right subtree
    post_order(node->right, list); 

    // curr node 
    list.push_back(*node); 
}

/***
A BinaryTree getter fuction. This function gets
the current root of the binary tree.

Input: 
N/A
Output:
Outputs the root of the binary tree
***/
template <class T, class Y>
Node<T,Y> * BinaryTree<T,Y>::getRoot(){
    /**
        Your code goes below here
    **/
   return root;
}


/***
The BinaryTree destructor. Make sure all
the TreeNodes that have been created get destroyed
and make sure there are no memory leaks.

Input: 
N/A

Output:
N/A
***/
template <class T, class Y>
BinaryTree<T,Y>::~BinaryTree(){
    /**
        Your code goes below here
    **/
    std::list<Node<T, Y>*> stack; 
    if (root != NULL){ 
        stack.push_back(root); 
    }

    while(!stack.empty()) {
        Node<T, Y>* current = stack.back();
        stack.pop_back(); 

        if (current->left != NULL){
            stack.push_back(current->left); 
        }
        if (current->right != NULL){
            stack.push_back(current->right); 
        }
        delete current; 
    }
}

template class Node<int, std::string>;
template class Node<std::string, std::string>;
template class Node<int, int>;
template class Node<double, double>;
template class Node<std::string, long>;
template class Node<std::string, std::list<std::string> >;
template class Node<std::string, int >;

template class BinaryTree<std::string, std::list<std::string> >;
template class BinaryTree<std::string, std::string>;
template class BinaryTree<int, int>;
template class BinaryTree<int, std::string>;
template class BinaryTree<std::string, int>;
