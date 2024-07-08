#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int process_id;
    int vruntime;
    Color color;
    Node* parent, * left, * right;

    Node(int process_id, int vruntime) : process_id(process_id), vruntime(vruntime) {
        parent = left = right = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixViolation(Node* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            }
            else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    void deleteFix(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int process_id, int vruntime) {
        Node* z = new Node(process_id, vruntime);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->vruntime < x->vruntime)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->vruntime < y->vruntime)
            y->left = z;
        else
            y->right = z;

        fixViolation(z);
    }

    Node* minimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void deleteNode(Node* z) {
        if (z == nullptr) return;

        Node* y = z;
        Color yOriginalColor = y->color;
        Node* x;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x != nullptr) x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == BLACK && x != nullptr)
            deleteFix(x);
        delete z;
    }

    Node* getRoot() {
        return root;
    }

    void inorderHelper(Node* root, ofstream& dotFile) {
        if (root != nullptr) {
            inorderHelper(root->left, dotFile);
            dotFile << "\"" << root->process_id << "," << root->vruntime << "\""
                    << "[label=\"P" << root->process_id << "," << root->vruntime << "\",";
            if (root->color == RED)
                dotFile << "color=red, style=filled, fillcolor=red];\n";
            else
                dotFile << "color=black, style=filled, fillcolor=grey];\n";
            if (root->parent != nullptr)
                dotFile << "\"" << root->parent->process_id << "," << root->parent->vruntime << "\""
                        << " -> "
                        << "\"" << root->process_id << "," << root->vruntime << "\";\n";
            inorderHelper(root->right, dotFile);
        }
    }

    void inorder() {
        ofstream dotFile;
        dotFile.open("red_black_tree.dot");
        dotFile << "digraph RedBlackTree {\n";
        inorderHelper(root, dotFile);
        dotFile << "}\n";
        dotFile.close();
        system("dot -Tpng red_black_tree.dot -o red_black_tree.png && xdg-open red_black_tree.png");
    }
};

int main() {
    RedBlackTree rbTree;
    queue<int> processQueue;
    map<int, int> burstTimes;

    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter process ID, virtual runtime, and burst time for each process:\n";

    for (int i = 0; i < n; ++i) {
        int process_id, vruntime, burst_time;
        cin >> process_id >> vruntime >> burst_time;
        rbTree.insert(process_id, vruntime);
        burstTimes[process_id] = burst_time;
    }

    cout << "Inorder traversal of the Red-Black Tree after insertion: ";
    
    cout << endl;

    // Dequeue leftmost nodes and enqueue their process IDs
    Node* root = rbTree.getRoot();
    while (root != nullptr) {
	    rbTree.inorder();
        Node* leftmost = rbTree.minimum(root);
        processQueue.push(leftmost->process_id);
        rbTree.deleteNode(leftmost);
        root = rbTree.getRoot();
        
    }
	int t=0;
    cout << "\n\n\nOrder of execution\nIDs\tStart\tBT\n";
    while (!processQueue.empty()) {
        int pid = processQueue.front();
        cout << pid <<"\t"<< t <<"\t"<< burstTimes[pid] << endl;
	t+=burstTimes[pid];
        processQueue.pop();
    }

    return 0;
}
