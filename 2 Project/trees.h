//importing libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

//defining the binary search tree data structure
struct bst
{
    int key;
    char string[20];
    struct bst *left;
    struct bst *right;
    struct bst *parent;
};

//defining the avl data structure
struct avl
{
    int key;
    char string[20];
    struct avl *left;
    struct avl *right;
    struct avl *parent;
    int height;
};

//defining the red-balck tree data structure
struct rbt
{
    int key;
    char string[20];
    struct rbt *left;
    struct rbt *right;
    struct rbt *parent;
    char color;
};

typedef struct bst bst;
typedef struct avl avl;
typedef struct bst bst;





//------------------------------------------------------
// IMPLEMENTATION OF THE METHODS OF A BINARY SEARCH TREE

//method for the complete and correct insertion of a key in the bst
void bstInsertion(bst **root, int key, char *value)
{
    bst *node = newNodeBst(key, value);

    (*root) = insertBst(*root, node);
}

//create a new bst node
bst *newNodeBst(int key, char *value)
{
    bst *node=(bst *)malloc(sizeof(bst));
    node->key=key;
    strcpy(node->string, value);
    node->left=NULL; 
    node->right=NULL;
    return node;
}


//insert a new node in the bst
bst *insertBst(bst *root, bst *node)
{
    if(root == NULL)
    {
        root = node;
    }
    else if((node->key)<(root->key))
    {
        root->left = insertBst(root->left, node);
        root->left->parent = root; 
    }
    else
    {
        root->right = insertBst(root->right, node);
        root->right->parent = root; 
    }

    return root;
}

//print the bst in pre-order notation
void printPreOrderBst(bst *root){
    if(root!=NULL){
        printf("%d:%s ", root->key, root->string);
        printPreOrderBst(root->left);
        printPreOrderBst(root->right);
    }else{
        printf("NULL ");    
    }
}

//given a key, find the node of the bst that match with that key
void findBst(bst *node, int toFind){
    if((node->key)==toFind){
        printf("%s\n", node->string);
    }else if(toFind<(node->key)){
        findBst(node->left, toFind);
    }else{
        findBst(node->right, toFind);
    }
}





//----------------------------------------
// IMPLEMENTATION OF THE METHODS OF AN AVL

//method for the complete and correct insertion of a key in the avl
void avlInsertion(avl **root, int key, char *value)
{
    avl *node = newNodeAvl(key, value);

    (*root) = insertAvl(*root, node);

    reHeight(root);
    
    *root = fixUpAvl(*root, key);
}

//create a new avl node
avl *newNodeAvl(int key, char *value)
{
    avl *node=(avl *)malloc(sizeof(avl));
    node->key=key;
    strcpy(node->string, value);
    node->left=NULL; 
    node->right=NULL;
    node->height=1;
    return node;
}

//insert a new node in the avl tree
avl *insertAvl(avl *root, avl *node)
{
    if(root == NULL)
    {
        root = node;
    }
    else if((node->key)<(root->key))
    {
        root->left = insertAvl(root->left, node);
        root->left->parent = root; 
    }
    else
    {
        root->right = insertAvl(root->right, node);
        root->right->parent = root; 
    }

    return root;
}

//re-adjust the height of each node of the avl tree
void reHeight(avl **node){
    (*node)->height = 1 + max(height((*node)->left), height((*node)->right));
}

//find the max value between two int
int max(int first, int second){
    if(first>second){
        return first;
    }else{
        return second;
    }
}

//return the int value of the height of the node
int height(avl *node){ 
    if(node == NULL){
        return 0; 
    }else{
        return node->height; 
    }  
    
}

//fix the tree if the avl's properties are violated
avl *fixUpAvl(avl *root, int key){

    int difference = getBalance(root);

    if(difference>1 && key<root->left->key){ //LL
        return rightRotateAvl(root); 
    }

    if(difference>1 && key>root->left->key){ //LR 
        root->left = leftRotateAvl(root->left); 
        return rightRotateAvl(root); 
    }
    
    if(difference<-1 && key>root->right->key){ //RR
        return leftRotateAvl(root); 
    }

    if(difference<-1 && key<root->right->key){  //RL 
        root->right = rightRotateAvl(root->right); 
        return leftRotateAvl(root);
    } 

    return root; 
}

//return the balance of a node, so the difference between the heights of the left and right child of the node
int getBalance(avl *node){ 
    if(node==NULL){
        return 0; 
    }else{
        return height(node->left) - height(node->right); 
    }
}

//right rotate the given avl node
avl *rightRotateAvl(avl *node){ 
    avl *child = node->left; 
    avl *nephew = child->right;
  
    child->right = node;
    node->left = nephew; 
  
    reHeight(&node);
    reHeight(&child);

    return child;
}

//left rotate the given avl node
avl *leftRotateAvl(avl *node){ 
    avl *child = node->right; 
    avl *nephew = child->left;
  
    child->left = node; 
    node->right = nephew; 
  
    reHeight(&node);
    reHeight(&child);

    return child;
}


//print the avl tree in pre-order notation
void printPreOrderAvl(avl *root){
    if(root!=NULL){
        printf("%d:%s:%d ", root->key, root->string, root->height);
        printPreOrderAvl(root->left);
        printPreOrderAvl(root->right);
    }else{
        printf("NULL ");    
    }
}


//given a key, find the node of the avl tree that match with that key
void findAvl(avl *node, int toFind){
    if((node->key)==toFind){
        printf("%s\n", node->string);
    }else if(toFind<(node->key)){
        findAvl(node->left, toFind);
    }else{
        findAvl(node->right, toFind);
    }
}





//--------------------------------------------------
// IMPLEMENTATION OF THE METHODS OF A RED-BLACK TREE

//method for the complete and correct insertion of a key in the avl
void rbtInsertion(rbt **root, int key, char *value)
{
    rbt *node = newNodeRbt(key, value);

    (*root) = insertRbt(*root, node);

    fixUpRbt(root, node);
}

//create a new rbt node
rbt *newNodeRbt(int key, char *value){
    rbt *node=(rbt *)malloc(sizeof(rbt));
    node->key=key;
    strcpy(node->string, value);
    node->left=NULL; 
    node->right=NULL;
    node->color = 'R';
    return node;
}


//insert a new node in the rbt
rbt *insertRbt(rbt *root, rbt *node)
{
    if(root == NULL)
    {
        root = node;
    }
    else if((node->key)<(root->key))
    {
        root->left = insertRbt(root->left, node);
        root->left->parent = root; 
    }
    else
    {
        root->right = insertRbt(root->right, node);
        root->right->parent = root; 
    }

    return root;
}

//fix the tree if the avl's properties are violated
void fixUpRbt(rbt **root, rbt *node)
{

    // iterate until node is not the root and node's parent color is red
    while ((node != *root) && (node->color == 'R') && (node->parent->color == 'R'))
    {
        rbt *uncle;

        // Find uncle and store uncle
        if (node->parent == node->parent->parent->left)
            uncle = node->parent->parent->right;
        else
            uncle = node->parent->parent->left;

        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move node to grandparent
        if(uncle != NULL && (uncle->color == 'R'))
        {
            uncle->color = 'B';
            node->parent->color = 'B';
            node->parent->parent->color = 'R';
            node = node->parent->parent;
        }

        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            
            // Left-Left (LL) case
            // (i)  Right Rotate Grandparent
            // (ii) Swap color of parent and grandparent
            
            if (node->parent == node->parent->parent->left)
            {

                // Left-Right (LR) case
                // (i) Left Rotate Parent
                if (node == node->parent->right)
                {
                    leftRotateRbt(root,node->parent);
                    node = node->left;
                }

                printf("%i %i %i\n", node->key, node->parent->key, node->parent->parent->key);
                rightRotateRbt(root,node->parent->parent);

                char ch = node->parent->color ;
                node->parent->color = node->parent->right->color;
                node->parent->right->color = ch;

            }

            // Right-Right (RR) case
            // (i)  Left Rotate Grandparent
            // (ii) Swap color of parent and grandparent
            else
            {
                
                // Right-Left (RL) case
                // (i) Right Rotate Parent
                if (node == node->parent->left)
                {
                    rightRotateRbt(root,node->parent);
                    node = node->right;
                }

                leftRotateRbt(root,node->parent->parent);
                
                char ch = node->parent->color ;
                node->parent->color = node->parent->left->color;
                node->parent->left->color = ch;
            }
        }
    }

    (*root)->color = 'B'; //keep root always black
}


//left rotate the node uncle
void leftRotateRbt(rbt **root,rbt *uncle)
{
    if (!uncle || !uncle->right)
        return ;
    //uncle stored pointer of right child of uncle
    rbt *uncle = uncle->right;

    //store uncle's left subtree's pointer as uncle's right child
    uncle->right = uncle->left;

    //update parent pointer of uncle's right child
    if (uncle->right != NULL)
        uncle->right->parent = uncle;

    //update uncle's parent pointer
    uncle->parent = uncle->parent;

    // if uncle's parent is null make uncle as root of tree
    if (uncle->parent == NULL)
        (*root) = uncle;

    // store uncle at the place of uncle
    else if (uncle == uncle->parent->left)
        uncle->parent->left = uncle;
    else    
        uncle->parent->right = uncle;

    // make uncle as left child of uncle
    uncle->left = uncle;

    //update parent pointer of uncle
    uncle->parent = uncle;
}


//right rotate the node uncle
void rightRotateRbt(rbt **root,rbt *uncle)
{
    if (!uncle || !uncle->left)
        return ;

    rbt *node = uncle->left;
    uncle->left = node->right;

    if (uncle->left != NULL)
        uncle->left->parent = uncle;

    node->parent = uncle->parent;

    if (uncle->parent == NULL)
        (*root) = node;
    else if (uncle == uncle->parent->left)
        uncle->parent->left = node;
    else 
        uncle->parent->right = node;

    node->right = uncle;
    uncle->parent = node;
}


//print the avl tree in pre-order notation
void printPreOrderRbt(rbt *root){
    if(root!=NULL){
        printf("%d:%s:", root->key, root->string);
        printColor(root);
        printPreOrderRbt(root->left);
        printPreOrderRbt(root->right);
    }else{
        printf("NULL ");    
    }
}

//print the color of the given node
void printColor(rbt *node){
    if(node->color == 'R'){
        printf("red ");
    }else{
        printf("black ");
    }
}


//given a key, find the node of the rbt that match with that key
void findRbt(rbt *node, int toFind){
    if((node->key)==toFind){
        printf("%s\n", node->string);
    }else if(toFind<(node->key)){
        findRbt(node->left, toFind);
    }else{
        findRbt(node->right, toFind);
    }
}