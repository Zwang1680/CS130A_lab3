#include "avl.h"
#include <iostream>

using namespace std;

AVL::AVL() : root(0), k(1) {}

AVL::~AVL(){
    if (root){
        clearNode(root);
    }
}

void AVL::clearNode(Node *n)
{
    if (n)
    {
        clearNode(n->left);
        clearNode(n->right);
        delete n;
    }
}

void AVL::insert(int x, int y){
    if (!root){
        root = new AVL::Node(x, y);
        cout << x << "." << y << " inserted" << endl;
        return;
    }
    insertHelper(x, y, root);
}

void AVL::insertHelper(int x, int y, Node *r){
    int count = 1;
    if (r->whole > x){
        //cout << "d" << endl;
        if (r->left){
            insertHelper(x, y, r->left);
        } else {
            r->left = new Node(x, y);
            r->left->parent = r;
            cout << x << "." << y << " inserted" << endl;
        }
        if (abs(nodeLevel(r->left) - nodeLevel(r->right)) == k+1){
            //cout << "d" << endl;
            if (r->left->whole > x){
                rotateLeft(r);
            } else if (r->left->whole == x && r->left->fraction > y){
                rotateLeft(r);
            } else {
                rotateLeft2(r);
            }
        }
    } else if (r->whole < x){
        //cout << "c" << endl;
        if (r->right){
            insertHelper(x, y, r->right);
        } else {
            r->right = new Node(x, y);
            r->right->parent = r;
            cout << x << "." << y << " inserted" << endl;
        }
        if (abs(nodeLevel(r->right) - nodeLevel(r->left)) == k+1){
            //cout << "c" << endl;
            if (r->right->whole < x){
                rotateRight(r);
            } else if (r->right->whole == x && r->right->fraction < y){
                rotateRight(r);
            } else {
                rotateRight2(r);
            }
        }
    } else {
        if (r->fraction > y){
            //cout << "b" << endl;
            if (r->left){
                insertHelper(x, y, r->left);
            } else {
                r->left = new Node(x, y);
                r->left->parent = r;
                cout << x << "." << y << " inserted" << endl;

            }
            if (abs(nodeLevel(r->left) - nodeLevel(r->right)) == k+1){
                //cout << "b" << endl;
                if (r->left->whole > x){
                    rotateLeft(r);
                } else if (r->left->whole == x && r->left->fraction > y){
                    rotateLeft(r);
                } else {
                    rotateLeft2(r);
                }
            }
        } else if (r->fraction < y){
            //cout << "a" << endl;
            if (r->right){
                insertHelper(x, y, r->right);
            } else {
                r->right = new Node(x, y);
                r->right->parent = r;
                cout << x << "." << y << " inserted" << endl;
            }
            if (abs(nodeLevel(r->right) - nodeLevel(r->left)) == k+1){
                //cout << "a" << endl;
                if (r->right->whole < x){
                    rotateRight(r);
                } else if (r->right->whole == x && r->right->fraction < y){
                    rotateRight(r);
                } else {
                    rotateRight2(r);
                }
            }
        }
    }
}

void AVL::rotateRight(Node* n){
    Node* temp = n->right;
    n->right = temp -> left;
    if (temp->left){
        temp->left->parent = n;
    }
    if (n->parent){
        if (n->parent->left == n){
            n->parent->left = temp;
            temp->parent = n->parent;
        } else {
            n->parent->right = temp;
            temp->parent = n->parent;
        }
    } else {
        temp->parent = 0;
        root = temp;
    }
    n->parent = temp;
    temp->left = n;
}

void AVL::rotateLeft(Node* n){
    Node* temp = n->left;
    n->left = temp->right;
    if(temp->right){
        temp->right->parent = n;
    }
    if (n->parent){
        if(n->parent->left == n){
            n->parent->left = temp;
            temp->parent = n->parent;
        } else {
            n->parent->right = temp;
            temp->parent = n->parent;
        }
    } else {
        temp->parent = 0;
        root = temp;
    }
    n->parent = temp;
    temp->right = n;
}

void AVL::rotateRight2(Node *n){
    rotateLeft(n->right);
    rotateRight(n);
}

void AVL::rotateLeft2(Node *n){
    rotateRight(n->left);
    rotateLeft(n);
}

int AVL::nodeLevel(Node *n){
    if (n){
        int lheight = nodeLevel(n->left);
        int rheight = nodeLevel(n->right);
        if (lheight >= rheight){
            return lheight + 1;
        } else {
            return rheight + 1;
        }
    }
    return 0;
}

void AVL::remove(int x, int y){
    if (!(search2(x,y))){
        //cout << "not found" << endl;
        return; 
    }
    removeHelper(x, y, root);
    preorder();
    cout << x << "." << y << " deleted" << endl;
}

void AVL::removeHelper(int x, int y, Node *n){
    if (n == NULL){
        return;
    }
    //cout << n->whole << n->fraction << endl;
    if (x < n->whole){
        removeHelper(x, y, n->left);
    } else if (x > n->whole){
        removeHelper(x, y, n->right);
    } else {
        if (y < n->fraction){
            removeHelper(x, y, n->left);
        } else if (y > n->fraction){
            removeHelper(x ,y, n->right);
        } else {
            if (!(n->left) || !(n->right)){
                // if (n->parent){
                //     if (n->parent->left == n){
                //         n->parent->left = 0;
                //     } else {
                //         n->parent->right = 0;
                //     }
                //     delete(n);
                // } else {
                //     root = 0;
                //     delete(n);
                // }
                //cout << "b" << endl;
                Node* temp = 0;
                if (n->left){
                    temp = n->left;
                } else if (n->right){
                    temp = n->right;
                }
                if (!temp){
                    temp = n;
                    //cout << temp->whole << temp->fraction << endl;
                    if (temp->parent){
                        //cout << temp->whole << temp->fraction << endl;
                        //cout << temp->parent->left << endl;
                        if (temp->parent->left == temp){
                            temp->parent->left = 0;
                            //cout << temp->parent->left << endl;
                        } else {
                            temp->parent->right = 0;
                        }
                    } else {
                        root = 0;
                    }
                    //cout << temp->whole << temp->fraction << endl;
                    //cout << temp->whole << temp->fraction << endl;
                    free(temp);
                    //cout << temp << endl;
                } else {
                    //cout << "b" << endl;
                    n->fraction = temp->fraction;
                    n->whole = temp->whole;
                    n->right = temp->right;
                    n->left = temp->left;
                    //cout << n->whole << n->fraction << endl;
                    free(temp);
                }
            } else {
                //cout << n->whole << endl;
                Node* pred = inorderpred(n);
                //cout << pred->whole << pred->fraction << endl;
                n->whole = pred->whole;
                n->fraction = pred->fraction;
                //cout << n->left->parent << n << endl;
                //cout << "a" << endl;
                removeHelper(pred->whole, pred->fraction, n->left);
                //removeHelper(pred->whole, pred->fraction, n->right);
            }
        }
    }
    if (n == NULL){
        return;
    }
    //cout << root->whole << endl;
    //preorder();
    cout << "a" << endl;
    if (balance(n) > k){
        cout<< "c" << endl;
        if(balance(n->left) >= 0){
            rotateLeft(n);
        } else if (balance(n->left) < 0){
            rotateLeft2(n);
        }
    } else if (balance(n) < (k * -1)){
        cout<< "d" << endl;
        if(balance(n->right) <= 0){
            //cout<< "d" << endl;
            rotateRight(n);
        } else if (balance(n->right) > 0){
            //cout<< "c" << endl;
            rotateRight2(n);
        }
    }
    cout << "b" << endl;
    preorder();
    //cout << root->whole << root->fraction << endl; 
}

// void AVL::rightRotate(Node* n){
//     Node* tmp1 = n->left;
//     Node* tmp2 = tmp1->right;
//     if(n->parent){

//     }
// }

int AVL::balance(Node *n){
    if (!n){
        return 0;
    } else {
        return nodeLevel(n->left) - nodeLevel(n->right);
    }
}

AVL::Node* AVL::inorderpred(Node *n){
    if (n->left){
        Node* tmp = n->left;
        while(tmp->right){
            tmp=tmp->right;
        }
        return tmp;
    }
    // } else if (n->right){
    //     Node* tmp = n->right;
    //     while(tmp->left){
    //         tmp=tmp->left;
    //     }
    //     return tmp;
    // }
    return 0;
} 

void AVL::setk(int temp){
    k = temp;
}

bool AVL::search2(int x, int y){
    Node *n = root;
    while (n){
        if (n->whole == x){
            if (n->fraction == y){
                return true;
            } else if (n->fraction < y){
                n = n->right;
            } else {
                n = n->left;
            }
        } else if (n->whole < x){
            n = n->right;
        } else {
            n = n->left;
        }
    }
    return false;
}

void AVL::search(int x, int y){
    Node *n = root;
    while (n){
        if (n->whole == x){
            if (n->fraction == y){
                cout << x << "." << y << " found" << endl;
                return;
            } else if (n->fraction < y){
                n = n->right;
            } else {
                n = n->left;
            }
        } else if (n->whole < x){
            n = n->right;
        } else {
            n = n->left;
        }
    }
    cout << x << "." << y << " not found" << endl;
    return;
}

void AVL::approxSearch(int x, int y){
    int xdiff, ydiff;
    approxSearchHelper(x, y, root, &xdiff, &ydiff);
    cout << "closet to " <<  x << "." << y << " is " << xdiff << "." << ydiff << endl;
}

void AVL::approxSearchHelper(int x, int y, Node *n, int* xdiff, int* ydiff){
    if (n){
        if (abs(n->whole - x) < abs(*xdiff - x)){
            *xdiff = n->whole;
            *ydiff = n->fraction;
        } else if (abs(n->whole - x) == abs(*xdiff - x)){
            if (abs(n->fraction - y)  < abs(*ydiff - y)){
                *xdiff = n->whole;
                *ydiff = n->fraction;
            }
        }
        approxSearchHelper(x, y, n->left, xdiff, ydiff);
        approxSearchHelper(x, y, n->right, xdiff, ydiff);
    }
}

void AVL::preorder(){
    string answer = preorderHelper(root);
    if (answer.size() > 0){
        answer.erase(answer.size()-1);
        cout << answer << endl;
    }
}

string AVL::preorderHelper(Node *n){
    if (!n){
        return "";
    }
    string answer = to_string(n->whole) + "." + to_string(n->fraction) + " ";
    // if (n->parent){
    //     cout << n->parent << ", " << n << endl;
    // }
    //cout << answer << endl;
    return answer + preorderHelper(n->left) + preorderHelper(n->right);
}

void AVL::inorder(){
    string answer = inorderHelper(root);
    answer.erase(answer.size() -1);
    cout << answer << endl;
}

string AVL::inorderHelper(Node *n){
    if (!n){
        return "";
    }
    string answer = to_string(n->whole) + "." + to_string(n->fraction) + " ";
    return inorderHelper(n->left) + answer + inorderHelper(n->right);
}