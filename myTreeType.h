#include <iostream>
#include <string>
#include <cassert>
template<class elemType>
struct AVLNode
{
    elemType info;//where data is stored
    int bfactor; //balance factor
    AVLNode<elemType> *llink;//left link point to root node of left subtree
    AVLNode<elemType> *rlink;//right link point to root node of right subtree
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class elemType>
class myTreeType
{
public:
    myTreeType();
//Default constructor
//Initialize AVL tree by setting root to NULL
//Set rotation counter to 0
    ~myTreeType();
//Destructor
//call destroyTree function to destroy AVL tree
    void rotateToLeft(AVLNode<elemType>* &root);
//Function that perform a left rotation of a node
//Also increase rotation counter by one
    void rotateToRight(AVLNode<elemType>* &root);
//Function that perform a right rotation of a node
//Also increase rotation counter by one
    void balanceFromLeft(AVLNode<elemType>* &root);
//Function that determine which rotation(left or right) to balance the tree
//Function also adjust the balance factor upon doing a rotation
    void balanceFromRight(AVLNode<elemType>* &root);
//Function that determine which rotation(left or right) to balance the tree
//Function also adjust the balance factor upon doing a rotation
    void insert(elemType &newItem);
//Function that create a node and store newItem in into the node before calling insertIntoAVL for tree insertion
    void insertIntoAVL(AVLNode<elemType>* &root, AVLNode<elemType> *newNode, bool& isTaller);
//Function that insert new node into AVL
//Function also call balanceFromLeft or balanceFromRight whenever tree needed adjustment for balance
    string toLowercase(elemType &newItem);
//Function that change newItem to lowercase
    string toUppercase(elemType &newItem);
//Function that change newItem to uppercase
    void printInorder(ofstream &ofs);
//Function that traverse the tree to print out all the word inorder
//Function also print out rotation counter at the end
    bool isEmpty() const;
//Function to check if AVL tree is empty
    int treeHeight() const;
//Function that returns the height of the AVL tree.
    int treeNodeCount() const;
//Function that returns the number of nodes in the AVL tree.
    int treeLeavesCount() const;
//Function that returns the number of leaves in the AVL tree.
    void destroyTree();
//Function that destroy AVL tree
protected:
    AVLNode<elemType> *root;
//Initializing root node pointer
private:
    int counter;
//Initializing rotation counter
    void destroy(AVLNode<elemType>* &p);
//Function to destroy the tree to which p points.
    void inorder(AVLNode<elemType> *p,ofstream &ofs);
//Function to do an inorder traversal
    int height(AVLNode<elemType> *p) const;
//Function to return the height of AVL tree
    int max(int x, int y) const;
//Returns the larger of x and y.
    int nodeCount(AVLNode<elemType> *p) const;
//Function to return the number of nodes in AVL tree
    int leavesCount(AVLNode<elemType> *p) const;
//Function to return the number of leaves in AVL tree
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that change newItem to lowercase
template <class elemType>
string myTreeType<elemType>::toLowercase(elemType &newItem)
{
    for(int i=0; i<newItem.length(); i++)
    {
        //for loop traverse all character in newItem and change them into lowercase
        newItem.at(i)=tolower(newItem.at(i));
    }
    return newItem;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that change newItem to uppercase
template <class elemType>
string myTreeType<elemType>::toUppercase(elemType &newItem)
{

    if(newItem.at(0)!='\'')
    {
        //change char at 0 to uppercase if char at 0 is not equal '
        newItem.at(0)=toupper(newItem.at(0));
    }
    else
    {
        //else change char at 1 to uppercase instead
        newItem.at(1)=toupper(newItem.at(1));
    }
    return newItem;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that traverse the tree to print out all the word in order
//Function also print out rotation counter at the end
template <class elemType>
void myTreeType<elemType>::printInorder(ofstream &ofs)
{
    inorder(root,ofs);
    //traverse the tree and print out all the word in order
    ofs<<counter<<endl;
    //print out rotation counter the end
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to do an inorder traversal
template <class elemType>
void myTreeType<elemType>::inorder(AVLNode<elemType> *p,ofstream &ofs)
{
    string word;
    if (p != NULL)
    {
        word=p->info;//assign info from p into word string
        toUppercase(word);//change word into uppercase
        inorder(p->llink,ofs);
        ofs <<word<< endl;//print out word
        inorder(p->rlink,ofs);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that perform a left rotation of a node
//Also increase rotation counter by one
template <class elemType>
void myTreeType<elemType>::rotateToLeft(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p; //pointer to the root of the
    if(root!=NULL&&root->rlink!=NULL)
    {
        p = root->rlink;
        root->rlink = p->llink; //the left subtree of p becomes
        //the right subtree of root
        p->llink = root;
        root = p; //make p the new root node
        counter++;

    }
}//rotateLeft
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that perform a right rotation of a node
//Also increase rotation counter by one
template <class elemType>
void myTreeType<elemType>::rotateToRight(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p; //pointer to the root of
//the left subtree of root
    if(root!=NULL&&root->llink!=NULL)
    {
        p = root->llink;
        root->llink = p->rlink; //the right subtree of p becomes
//the left subtree of root
        p->rlink = root;
        root = p; //make p the new root node
        counter++;

    }
}//end rotateRight
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that determine which rotation(left or right) to balance the tree
//Function also adjust the balance factor upon doing a rotation
template <class elemType>
void myTreeType<elemType>::balanceFromLeft(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p;
    AVLNode<elemType> *w;
    p = root->llink; //p points to the left subtree of root
    switch (p->bfactor)
    {
    case -1:
        root->bfactor = 0;
        p->bfactor = 0;
        rotateToRight(root);
        break;
    case 0:
        //cerr << "Error: Cannot balance from the left." << endl;
        break;
    case 1:
        w = p->rlink;
        switch (w->bfactor) //adjust the balance factors
        {
        case -1:
            root->bfactor = 1;
            p->bfactor = 0;
            break;
        case 0:
            root->bfactor = 0;
            p->bfactor = 0;
            break;
        case 1:
            root->bfactor = 0;
            p->bfactor = -1;
        }//end switch
        w->bfactor = 0;
        rotateToLeft(p);
        root->llink = p;
        rotateToRight(root);
    }//end switch;
}//end balanceFromLeft
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that determine which rotation(left or right) to balance the tree
//Function also adjust the balance factor upon doing a rotation
template <class elemType>
void myTreeType<elemType>::balanceFromRight(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p;
    AVLNode<elemType> *w;
    p = root->rlink; //p points to the left subtree of root
    switch (p->bfactor)
    {
    case -1:
        w = p->llink;
        switch (w->bfactor) //adjust the balance factors
        {
        case -1:
            root->bfactor = 0;
            p->bfactor = 1;
            break;
        case 0:
            root->bfactor = 0;
            p->bfactor = 0;
            break;
        case 1:
            root->bfactor = -1;
            p->bfactor = 0;
        }//end switch
        w->bfactor = 0;
        rotateToRight(p);
        root->rlink = p;
        rotateToLeft(root);
        break;
    case 0:
        //cerr << "Error: Cannot balance from the left." << endl;
        break;
    case 1:
        root->bfactor = 0;
        p->bfactor = 0;
        rotateToLeft(root);
    }//end switch;
}//end balanceFromRight
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that insert new node into AVL
//Function also call balanceFromLeft or balanceFromRight whenever tree needed adjustment for balance
template <class elemType>
void myTreeType<elemType>::insertIntoAVL(AVLNode<elemType>* &root,
        AVLNode<elemType> *newNode, bool& isTaller)
{
    if (root == NULL)
    {
        root = newNode;
        isTaller = true;
    }
    else if (root->info == newNode->info)
    {
        //cerr << "No duplicates are allowed." << endl;
    }
    else if (root->info > newNode->info) //newItem goes in
//the left subtree
    {
        insertIntoAVL(root->llink, newNode, isTaller);
        if (isTaller) //after insertion, the subtree grew in height
            switch (root->bfactor)
            {
            case -1:
                balanceFromLeft(root);
                isTaller = false;
                break;
            case 0:
                root->bfactor = -1;
                isTaller = true;
                break;
            case 1:
                root->bfactor = 0;
                isTaller = false;
            }//end switch
    }//end if
    else
    {
        insertIntoAVL(root->rlink, newNode, isTaller);
        if (isTaller) //after insertion, the subtree grew in
//height
            switch (root->bfactor)
            {
            case -1:
                root->bfactor = 0;
                isTaller = false;
                break;
            case 0:
                root->bfactor = 1;
                isTaller = true;
                break;
            case 1:
                balanceFromRight(root);
                isTaller = false;
            }//end switch
    }//end else
}//insertIntoAVL
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that create a node and store newItem in into the node before calling insertIntoAVL for tree insertion
template <class elemType>
void myTreeType<elemType>::insert(elemType &newItem)
{
    toLowercase(newItem);//set newItem to lowercase
    bool isTaller = false;//set is tall to false
    AVLNode<elemType> *newNode;//new node pointer
    newNode = new AVLNode<elemType>;//new node
    newNode->info = newItem;//set info to newItem
    newNode->bfactor = 0;//set bfactor to 0
    newNode->llink = NULL;//set left link to NULL
    newNode->rlink = NULL;//set right link to NULL
    insertIntoAVL(root, newNode, isTaller);//inserting new node to tree
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to check if AVL tree is empty
template <class elemType>
bool myTreeType<elemType>::isEmpty() const
{
    return (root == NULL);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that returns the height of the AVL tree.
template <class elemType>
int myTreeType<elemType>::treeHeight() const
{
    return height(root);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that returns the number of nodes in the AVL tree.
template <class elemType>
int myTreeType<elemType>::treeNodeCount() const
{
    return nodeCount(root);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that returns the number of leaves in the AVL tree.
template <class elemType>
int myTreeType<elemType>::treeLeavesCount() const
{
    return leavesCount(root);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to return the height of AVL tree
template <class elemType>
int myTreeType<elemType>::height(AVLNode<elemType> *p) const
{
    if (p == NULL)
        return 0;
    else
        return 1 + max(height(p->llink), height(p->rlink));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Returns the larger of x and y.
template <class elemType>
int myTreeType<elemType>::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to destroy tree to which p points.
template <class elemType>
void myTreeType<elemType>::destroy(AVLNode<elemType>* &p)
{
    if (p != NULL)
    {
        destroy(p->llink);
        destroy(p->rlink);
        delete p;
        p = NULL;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that destroy AVL tree
template <class elemType>
void myTreeType<elemType>::destroyTree()
{
    destroy(root);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destructor
//call destroyTree function to destroy AVL tree
template <class elemType>
myTreeType<elemType>::~myTreeType()
{
    destroy(root);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Default constructor
//Initialize AVL tree by setting root to NULL
//Set rotation counter to 0
template <class elemType>
myTreeType<elemType>::myTreeType()
{
    root = NULL;
    counter=0;
}
