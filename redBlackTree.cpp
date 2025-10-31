#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
    
    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    
    void rotateLeft(Node* &root, Node* &pt) {
        Node* pt_right = pt->right;
        pt->right = pt_right->left;
        
        if (pt->right != nullptr)
            pt->right->parent = pt;
        
        pt_right->parent = pt->parent;
        
        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;
        
        pt_right->left = pt;
        pt->parent = pt_right;
    }
    
    void rotateRight(Node* &root, Node* &pt) {
        Node* pt_left = pt->left;
        pt->left = pt_left->right;
        
        if (pt->left != nullptr)
            pt->left->parent = pt;
        
        pt_left->parent = pt->parent;
        
        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;
        
        pt_left->right = pt;
        pt->parent = pt_left;
    }
    
    void fixViolation(Node* &root, Node* &pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;
        
        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;
            
            // Case A: Parent is left child of grandparent
            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;
                
                // Case 1: Uncle is RED - only recoloring
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    // Case 2: pt is right child - left rotation
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    // Case 3: pt is left child - right rotation
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            // Case B: Parent is right child of grandparent
            else {
                Node* uncle_pt = grand_parent_pt->left;
                
                // Case 1: Uncle is RED - only recoloring
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    // Case 2: pt is left child - right rotation
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    // Case 3: pt is right child - left rotation
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }
    
    Node* BSTInsert(Node* root, Node* pt) {
        if (root == nullptr)
            return pt;
        
        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }
        
        return root;
    }
    
    Node* minValueNode(Node* node) {
        Node* ptr = node;
        while (ptr->left != nullptr)
            ptr = ptr->left;
        return ptr;
    }
    
    void fixDeletion(Node* &root, Node* &x) {
        if (x == nullptr)
            return;
        
        if (x == root) {
            root->color = BLACK;
            return;
        }
        
        if (x->color == RED || (x->left != nullptr && x->left->color == RED) || 
            (x->right != nullptr && x->right->color == RED)) {
            Node* child = (x->left != nullptr) ? x->left : x->right;
            
            if (x == x->parent->left) {
                x->parent->left = child;
                if (child != nullptr)
                    child->parent = x->parent;
                child->color = BLACK;
                delete x;
            } else {
                x->parent->right = child;
                if (child != nullptr)
                    child->parent = x->parent;
                child->color = BLACK;
                delete x;
            }
        } else {
            Node* sibling = nullptr;
            Node* ptr = x;
            ptr->color = BLACK;
            
            while (ptr != root && ptr->color == BLACK) {
                if (ptr == ptr->parent->left) {
                    sibling = ptr->parent->right;
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        ptr->parent->color = RED;
                        rotateLeft(root, ptr->parent);
                    } else {
                        if ((sibling->left == nullptr || sibling->left->color == BLACK) && 
                            (sibling->right == nullptr || sibling->right->color == BLACK)) {
                            sibling->color = RED;
                            if (ptr->parent->color == RED)
                                ptr->parent->color = BLACK;
                            else
                                ptr->parent->color = BLACK;
                            ptr = ptr->parent;
                        } else {
                            if (sibling->right == nullptr || sibling->right->color == BLACK) {
                                if (sibling->left != nullptr)
                                    sibling->left->color = BLACK;
                                sibling->color = RED;
                                rotateRight(root, sibling);
                                sibling = ptr->parent->right;
                            }
                            sibling->color = ptr->parent->color;
                            ptr->parent->color = BLACK;
                            if (sibling->right != nullptr)
                                sibling->right->color = BLACK;
                            rotateLeft(root, ptr->parent);
                            break;
                        }
                    }
                } else {
                    sibling = ptr->parent->left;
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        ptr->parent->color = RED;
                        rotateRight(root, ptr->parent);
                    } else {
                        if ((sibling->left == nullptr || sibling->left->color == BLACK) && 
                            (sibling->right == nullptr || sibling->right->color == BLACK)) {
                            sibling->color = RED;
                            if (ptr->parent->color == RED)
                                ptr->parent->color = BLACK;
                            else
                                ptr->parent->color = BLACK;
                            ptr = ptr->parent;
                        } else {
                            if (sibling->left == nullptr || sibling->left->color == BLACK) {
                                if (sibling->right != nullptr)
                                    sibling->right->color = BLACK;
                                sibling->color = RED;
                                rotateLeft(root, sibling);
                                sibling = ptr->parent->left;
                            }
                            sibling->color = ptr->parent->color;
                            ptr->parent->color = BLACK;
                            if (sibling->left != nullptr)
                                sibling->left->color = BLACK;
                            rotateRight(root, ptr->parent);
                            break;
                        }
                    }
                }
            }
            
            if (x == x->parent->left)
                x->parent->left = nullptr;
            else
                x->parent->right = nullptr;
            delete x;
            root->color = BLACK;
        }
    }
    
    Node* deleteNode(Node* root, int data) {
        if (root == nullptr)
            return root;
        
        if (data < root->data)
            return deleteNode(root->left, data);
        
        if (data > root->data)
            return deleteNode(root->right, data);
        
        if (root->left == nullptr || root->right == nullptr)
            return root;
        
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        return deleteNode(root->right, temp->data);
    }
    
    void inorderHelper(Node* root) {
        if (root == nullptr)
            return;
        
        inorderHelper(root->left);
        cout << root->data << "(" << (root->color == RED ? "R" : "B") << ") ";
        inorderHelper(root->right);
    }
    
    int blackHeight(Node* node) {
        if (node == nullptr)
            return 1;
        
        int leftHeight = blackHeight(node->left);
        int rightHeight = blackHeight(node->right);
        
        int add = (node->color == BLACK) ? 1 : 0;
        
        if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight)
            return -1;
        else
            return leftHeight + add;
    }
    
    bool checkRedProperty(Node* node) {
        if (node == nullptr)
            return true;
        
        if (node->color == RED) {
            if ((node->left != nullptr && node->left->color == RED) ||
                (node->right != nullptr && node->right->color == RED)) {
                return false;
            }
        }
        
        return checkRedProperty(node->left) && checkRedProperty(node->right);
    }
    
public:
    RedBlackTree() : root(nullptr) {}
    
    void insert(int data) {
        Node* pt = new Node(data);
        root = BSTInsert(root, pt);
        fixViolation(root, pt);
        
        cout << "Inserted " << data << " - Balance check: ";
        if (isBalanced())
            cout << "BALANCED ✓" << endl;
        else
            cout << "NOT BALANCED ✗" << endl;
    }
    
    void deleteValue(int data) {
        Node* node = deleteNode(root, data);
        if (node == nullptr) {
            cout << "Value " << data << " not found!" << endl;
            return;
        }
        fixDeletion(root, node);
        cout << "Deleted " << data << " - Balance check: ";
        if (isBalanced())
            cout << "BALANCED ✓" << endl;
        else
            cout << "NOT BALANCED ✗" << endl;
    }
    
    void inorder() {
        cout << "Inorder: ";
        inorderHelper(root);
        cout << endl;
    }
    
    bool isBalanced() {
        if (root != nullptr && root->color != BLACK) {
            cout << "(Root not black) ";
            return false;
        }
        
        if (!checkRedProperty(root)) {
            cout << "(Red property violated) ";
            return false;
        }
        
        int bh = blackHeight(root);
        if (bh == -1) {
            cout << "(Black height mismatch) ";
            return false;
        }
        
        return true;
    }
    
    void levelOrder() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }
        
        queue<Node*> q;
        q.push(root);
        
        cout << "Level-order: ";
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            
            cout << temp->data << "(" << (temp->color == RED ? "R" : "B") << ") ";
            
            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);
        }
        cout << endl;
    }
};

int main() {
    RedBlackTree tree;
    
    cout << "=== Red-Black Tree Operations ===" << endl << endl;
    
    cout << "Inserting values: 10, 20, 30, 15, 25, 5, 1" << endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);
    
    cout << "\n";
    tree.inorder();
    tree.levelOrder();
    
    cout << "\n=== Deletion Operations ===" << endl;
    tree.deleteValue(20);
    tree.inorder();
    tree.levelOrder();
    
    cout << "\n";
    tree.deleteValue(30);
    tree.inorder();
    tree.levelOrder();
    
    cout << "\n";
    tree.deleteValue(5);
    tree.inorder();
    tree.levelOrder();
    
    return 0;
}