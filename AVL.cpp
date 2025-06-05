#include <iostream>
#include <algorithm>
using namespace std;

class NodeAVL {
public:
    int key; // as fi picat poo-ul daca faceam asta acolo, hope this is not illegal =))
    int height;
    NodeAVL* left;
    NodeAVL* right;
    NodeAVL(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int height(NodeAVL* node) {
    return node ? node->height : 0; //se presupune ca frunzele au height = 1
}

int getBalance(NodeAVL* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

NodeAVL* RightR(NodeAVL* x) {
    NodeAVL* y = x->left;
    NodeAVL* b = y->right; // cand scriu b, ma gandesc la faptul ca x->right are un subtree a, y->right are b si y->left are c, la Left Rotation nu se schimba x->left si y->right, doar b

    y->right = x;
    x->left = b;

    x->height = 1 + max(height(x->left), height(x->right)); // x este acum y->right, deci am nevoie de inaltimea lui x mai intai pt a calcula inaltimea lui y
    y->height = 1 + max(height(y->left), height(y->right));

    return y; 
}

NodeAVL* LeftR(NodeAVL* x) {
    NodeAVL* y = x->right;
    NodeAVL* b = y->left; // cand scriu b, ma gandesc la faptul ca x->left are un subtree a, x-> right este y, y->left este b si y->right este c, x->left si y->right nu se schimba, doar b

    y->left = x;
    x->right = b;

    x->height = 1 + max(height(x->left), height(x->right)); // incep cu x pentru ca acum y->left este x, deci am nevoie de el in determinarea inaltimii lui y
    y->height = 1 + max(height(y->left), height(y->right));

    return y; 
}

NodeAVL* insert(NodeAVL* node, int key) {
    // Step 1: Perform normal BST insert
    if (!node) return new NodeAVL(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // fara duplicate

    node->height = 1 + max(height(node->left), height(node->right));

    // pentru fiecare comparatie pe care am facut-o pentru a gasi locatia nodului inserat, se va apela recursiv secventa asta de cod, care calculeaza balance-ul nodului si ajusteaza pe cazurile discutate la curs
    int balance = getBalance(node);

    //balansarea functioneaza pe metoda (citat din curs):
    /*
    1 Find the imbalanced node.
    2 Go down two nodes towards the newly inserted node.
    3 If the path is straight, use single rotation.
    4 If the path zig-zags, use double rotation.
    */
    //daca balance era x, x > 0, atunci subtree-ul din stanga era mai mare cu x layer-e
    //daca balance era 0, subtree-urile aveau acelasi heaight
    //daca balance era x, x < 0  atunci subtree-ul din dreapta era mai mare cu abs(x) layer-e
    if (balance > 1 && key < node->left->key)         // LL Case
        return RightR(node);
    if (balance < -1 && key > node->right->key)       // RR Case
        return LeftR(node);
    if (balance > 1 && key > node->left->key) {       // LR Case
        node->left = LeftR(node->left);
        return RightR(node);
    }
    if (balance < -1 && key < node->right->key) {     // RL Case
        node->right = RightR(node->right);
        return LeftR(node);
    }

    return node; 
}

bool search(NodeAVL* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

NodeAVL* minValueNodeAVL(NodeAVL* node) {
    NodeAVL* current = node;
    while (current->left)
        current = current->left;
    return current;
}

NodeAVL* deleteNodeAVL(NodeAVL* node, int key) {
    // Stergere standard din BST
    if (!node)
        return node;

    if (key < node->key)
        node->left = deleteNodeAVL(node->left, key);
    else if (key > node->key)
        node->right = deleteNodeAVL(node->right, key);
    else {
        // Daca am doar un copil sau niciunul, il iau si il conectez recursiv cu parintele nodului pe care vreau sa il sterg
        if (!node->left || !node->right) {
            NodeAVL* child = node->left ? node->left : node->right;
            delete node;
            return child;
        }

        // Daca am 2 copii, urmez algoritmul urmator (citat din curs):
        /*
        replace node with
        y = Tree-Successor(node)
        remove y (1 child!)
        */
        NodeAVL* minChild = minValueNodeAVL(node->right);
        node->key = minChild->key;
        node->right = deleteNodeAVL(node->right, minChild->key);
    }

    node->height = 1 + max(height(node->left), height(node->right));

    //rebalansez AVL-ul cu acelasi algoritm ca la insert
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return RightR(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = LeftR(node->left);
        return RightR(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
        return LeftR(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = RightR(node->right);
        return LeftR(node);
    }

    return node;
}

//afisarea elementelor sortate
void inOrder(NodeAVL* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// debug
void printDetails(NodeAVL* node) {
    if (!node) return;
    printDetails(node->left);
    cout << "NodeAVL " << node->key << ", Height: " << node->height << ", Balance: " << getBalance(node) << endl;
    printDetails(node->right);
}

int main() {
    NodeAVL* root = nullptr;

    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int key : keys)
        root = insert(root, key);

    cout << "Elementele ordonate din AVL\n";
    inOrder(root);
    cout << "\n\nDebug\n";
    printDetails(root);

    return 0;
}
