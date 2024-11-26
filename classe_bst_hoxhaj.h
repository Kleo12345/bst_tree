#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node* left;
    Node* right;

public:
    Node(int value) {
        this->data = value;
        this->left = nullptr;
        this->right = nullptr;
    }

    int getData() {
        return this->data;
    }

    void setData(int value) {
        this->data = value;
    }

    Node* getLeft() {
        return this->left;
    }

    void setLeft(Node* node) {
        this->left = node;
    }

    Node* getRight() {
        return this->right;
    }

    void setRight(Node* node) {
        this->right = node;
    }

    Node* insertIterative(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        Node* current = node;
        Node* newNode = new Node(value);
        while (true) {
            if (value < current->getData()) {
                if (current->getLeft() == nullptr) {
                    current->setLeft(newNode);
                    break;
                }
                current = current->getLeft();
            } else {
                if (current->getRight() == nullptr) {
                    current->setRight(newNode);
                    break;
                }
                current = current->getRight();
            }
        }
        return node;
    }

    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->getData()) {
            node->setLeft(this->insertRecursive(node->getLeft(), value));
        } else if (value > node->getData()) {
            node->setRight(this->insertRecursive(node->getRight(), value));
        }
        return node;
    }

    bool searchIterative(Node* node, int value) {
        while (node != nullptr) {
            if (value == node->getData()) {
                return true;
            }
            if (value < node->getData()) {
                node = node->getLeft();
            } else {
                node = node->getRight();
            }
        }
        return false;
    }

    bool searchRecursive(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (value == node->getData()) {
            return true;
        }
        if (value < node->getData()) {
            return this->searchRecursive(node->getLeft(), value);
        } else {
            return this->searchRecursive(node->getRight(), value);
        }
    }

    void preOrderTraversal(Node* node) {
        if (node != nullptr) {
            cout << node->getData() << " ";
            this->preOrderTraversal(node->getLeft());
            this->preOrderTraversal(node->getRight());
        }
    }

    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            this->inOrderTraversal(node->getLeft());
            cout << node->getData() << " ";
            this->inOrderTraversal(node->getRight());
        }
    }

    void postOrderTraversal(Node* node) {
        if (node != nullptr) {
            this->postOrderTraversal(node->getLeft());
            this->postOrderTraversal(node->getRight());
            cout << node->getData() << " ";
        }
    }

    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }
        if (value < node->getData()) {
            node->setLeft(this->deleteNode(node->getLeft(), value));
        } else if (value > node->getData()) {
            node->setRight(this->deleteNode(node->getRight(), value));
        } else {
            if (node->getLeft() == nullptr) {
                Node* temp = node->getRight();
                delete node;
                return temp;
            } else if (node->getRight() == nullptr) {
                Node* temp = node->getLeft();
                delete node;
                return temp;
            }
            Node* temp = this->minValueNode(node->getRight());
            node->setData(temp->getData());
            node->setRight(this->deleteNode(node->getRight(), temp->getData()));
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->getLeft() != nullptr) {
            current = current->getLeft();
        }
        return current;
    }

    bool isBST(Node* node, Node* min = nullptr, Node* max = nullptr) {
        if (node == nullptr) {
            return true;
        }
        if ((min != nullptr && node->getData() <= min->getData()) ||
            (max != nullptr && node->getData() > max->getData())) {
            return false;
        }
        return this->isBST(node->getLeft(), min, node) &&
               this->isBST(node->getRight(), node, max);
    }
};

int main() {
    Node* root = nullptr;
    root = root->insertIterative(root, 50);
    root = root->insertRecursive(root, 30);
    root = root->insertIterative(root, 20);
    root = root->insertRecursive(root, 40);

    cout << "InOrder: ";
    root->inOrderTraversal(root);
    cout << endl;

    cout << "PreOrder: ";
    root->preOrderTraversal(root);
    cout << endl;

    cout << "PostOrder: ";
    root->postOrderTraversal(root);
    cout << endl;

    cout << "Is BST: " << (root->isBST(root) ? "Yes" : "No") << endl;

    cout << "Search Recursive for 30: " << (root->searchRecursive(root, 30) ? "Found" : "Not Found") << endl;
    cout << "Search Iterative for 25: " << (root->searchIterative(root, 25) ? "Found" : "Not Found") << endl;

    root = root->deleteNode(root, 30);
    cout << "InOrder after deletion: ";
    root->inOrderTraversal(root);
    cout << endl;

    return 0;
}
