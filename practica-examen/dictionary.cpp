#include <iostream>

using namespace std;

template <typename T>
struct LessThan
{
    int compare(const T& a, const T& b) const
    {
        if (a < b)
            return -1;

        if (b < a)
            return 1;

        if (!(a < b) && !(b < a))
            return 0;
    }
};

template <typename K, typename V>
struct Node
{
    K key;
    V value;
    Node* left;
    Node* right;

    Node(K key, V value): left {nullptr}, right {nullptr}, key {key}, value {value} 
    {

    }
};

template <typename K, typename V, typename Comparator = LessThan<K>>
class BST
{
public:
    Node<K, V>* root;
    Comparator comparator;

    BST()
    {
        root = nullptr;
    }

    void add(const K& key, const V& val)
    {
        try {
            find(key);
        }
        catch(const char* status) {
            printf("Status: %s\n", status);
            return add_r(root, key, val);   
        }
    }

    void add_r(Node<K, V>*& node, const K& key, const V& val)
    {
        if (node == nullptr)
        {
            node = new Node<K, V>(key, val);
            return;
        }

        int c = comparator.compare(key, node->key);

        if (c == 0)
            return;

        if (c < 0)
            return add_r(node->left, key, val);

        return add_r(node->right, key, val);
    }
  
    // returns a reference to the element that is equal 
    // (based on the comparator) to the given object. 
    // Throws an exception if not found.
    const V& find(const K& key)
    {
        return find_r(key, root);
    }

    const V& find_r(const K& key, Node<K, V>*& node)
    {
        if (node == nullptr)
            throw "key not found";

        int c = comparator.compare(key, node->key);

        if (c == 0)
        {
            // puts("the key already exists");
            return node->value;
        }

        if (c < 0)
            return find_r(key, node->left);

        return find_r(key, node->right);
    } 
 
    template <typename Proc>
    void iterate(Proc proc) const
    {

    }
};

void show(const string& s)
{

}

int main()
{
    // usara por defecto LessThan
    BST<int, string> bst;
    bst.add(1, "The fellowship of the ring");
    bst.add(2, "The two towers");
    bst.add(3, "The return of the king");
    bst.add(1, "The silmarillion");
}