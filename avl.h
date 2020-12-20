#ifndef AVL_H
#define AVL_H

#include <iostream>

using namespace std;

class AVL{
    public:
        AVL();
        ~AVL();
        void insert(int x, int y);
        void search(int x, int y);
        void approxSearch(int x, int y);
        void remove(int x, int y);
        void inorder();
        void preorder();
        void setk(int temp);

    private:
        struct Node{
            int whole;
            int fraction;
            Node *left, *right, *parent;
            Node(int x, int y) : whole(x), fraction(y), left(0), right(0), parent(0) {}
        };

        int k;
        Node *root;
        void clearNode(Node *n);
        void insertHelper(int x, int y, Node *r);
        void removeHelper(int x, int y, Node *r);
        void approxSearchHelper(int x, int y, Node *n, int* xdiff, int* ydiff);
        Node* inorderpred(Node *n);
        int nodeLevel(Node *n);
        int balance(Node *n);
        void rotateRight(Node *n);
        void rotateRight2(Node *n);
        void rotateLeft(Node *n);
        void rotateLeft2(Node *n);
        bool search2(int x, int y);
        string preorderHelper(Node *n);
        string inorderHelper(Node *n);
};

#endif