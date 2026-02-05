#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class GraphvizBST {
public:
    static void saveDotFile(const std::string &filename, const std::string &dotContent) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << dotContent;
            outFile.close();
            std::cout << "DOT file saved: " << filename << std::endl;
        } else {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }
    }

    static std::string generateDot(const Node *root) {
        std::string dot = "digraph BST {\n";
        dot += "    node [fontname=\"Arial\"];\n";
        dot += generateDotHelper(root);
        dot += "}\n";
        return dot;
    }

private:
    static std::string generateDotHelper(const Node *node) {
        if (!node)
            return "";
        std::string result;
        if (node->left) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->left->data) + " [label=\"L\"];\n";
            result += generateDotHelper(node->left);
        } else {
            std::string nullNode = "nullL" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        if (node->right) {
            result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->right->data) + " [label=\"R\"];\n";
            result += generateDotHelper(node->right);
        } else {
            std::string nullNode = "nullR" + std::to_string(node->data);
            result += "    " + nullNode + " [shape=point];\n";
            result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
        }
        return result;
    }
};

class Bst {
    Node *root;

    void _print(Node *subroot) {
        if (!subroot) return;
        _print(subroot->left);
        cout << subroot->data << " ";
        _print(subroot->right);
    }

    void _insert(Node *&subroot, int x) {
        if (!subroot) {
            subroot = new Node(x);
        } else if (x < subroot->data) {
            _insert(subroot->left, x);
        } else {
            _insert(subroot->right, x);
        }
    }

    int _ipl(Node *root, int depth = 0) {
        if (!root) return 0;
        return depth + _ipl(root->left, depth + 1) + _ipl(root->right, depth + 1);
    }

    /**
     * Helper function to find the minimum value node in a subtree.
     * Used to find the inorder successor.
     */
    Node* minimumValue(Node* node) {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    /**
     * Deletes a node with the given x from the BST.
     */
    void deleteNode(Node*& subroot, int x) {
        if (!subroot)
            return; // If x not found

        if (x < subroot->data) {
            deleteNode(subroot->left, x);
        } 
        else if (x > subroot->data) {
            deleteNode(subroot->right, x);
        } 
        else {
            // Node found

            // Case 1: No children (leaf node)
            if (!subroot->left && !subroot->right) {
                delete subroot;
                subroot = nullptr;
            }
            // Case 2: 
            //1st instance: child (right)
            else if (!subroot->left) {
                Node* temp = subroot;
                subroot = subroot->right;
                delete temp;
            }
            // 2nd instance: One child (left)
            else if (!subroot->right) {
                Node* temp = subroot;
                subroot = subroot->left;
                delete temp;
            }
            // Case 3: Two children
            else {
                //Inorder Successor (smallest in right subtree)
                Node* successor = minimumValue(subroot->right);
                subroot->data = successor->data;
                deleteNode(subroot->right, successor->data);

                /*
                //Inorder Predecessor (largest in left subtree)
                Node* predecessor = _maxValueNode(subroot->left);
                subroot->data = predecessor->data;
                deleteNode(subroot->left, predecessor->data);
                */
            }
        }
    }

public:
    Bst() { root = nullptr; }

    void insert(int x) { _insert(root, x); }

    void remove(int x) { deleteNode(root, x); }

    void print() { _print(root); }

    void saveDotFile(const std::string &filename) {
        std::string dotContent = GraphvizBST::generateDot(root);
        GraphvizBST::saveDotFile(filename, dotContent);
    }

    int ipl() {
        return _ipl(root);
    }
};

bool unique_value(int *arr, int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return false;
        }
    }
    return true;
}

int main() {
    Bst tree;
    int root = pow(2, 15) / 2;
    int max = pow(2, 15) - 1;
    vector<int> arr;
    arr.push_back(root);
    tree.insert(root);
    for (int i = 1; i < 50; i++) {
        int r = rand() % max;
        while (!unique_value(arr.data(), arr.size(), r)) {
            r = rand() % max;
        }
        tree.insert(r);
        arr.push_back(r);
    }

    tree.print();
    tree.saveDotFile("bst_snapshot.dot");
    
    Bst tree2;
    tree2.insert(10);
    tree2.insert(5);
    tree2.insert(15);
    tree2.insert(2);
    tree2.insert(7);
    tree2.insert(20);

    cout << "Before deletion: ";
    tree2.print();
    cout << endl;

    tree2.remove(10); // delete node with two children

    cout << "After deletion: ";
    tree2.print();
    cout << endl;

    cout << "Internal Path Length: " << tree2.ipl() << endl;
}
