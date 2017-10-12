#include <cstdio>

template <class T>
struct Node
{
    T data;
    Node* left;
    Node* right;

    Node(T d): left {nullptr}, right {nullptr}, data {d}
    {

    }
};

template <class T>
class Tree
{
    Node<T>* root;
    int (*compare) (const T, const T);

public:
    Tree(int (*cmp)(const T, const T))
    {
        root = nullptr;
        compare = cmp;
    }

    int add(T data)
    {
        return add_r(data, root);
    }

    void iterate(void (*f)(T))
    {
        iterate_r(root, f);
    }

    void iterate_r(Node<T>*& node, void (*f)(T))
    {
        if (node == nullptr)
            return;

        iterate_r(node->left, f);
        f(node->data);
        iterate_r(node->right, f);        
    }   

    ~Tree()
    {
        release(root);
    }

private:
    int add_r(T data, Node<T>*& node)
    {
        if (node == nullptr)   
        {
            puts("estoy aqui");
            node = new Node<T>(data);
            return 1;
        }

        int r = compare(node->data, data);

        if (r == 0)
            return 0;

        if (r > 0);
            return add_r(data, node->left);

        return add_r(data, node->right);
    }

    void release(Node<T>*& node)
    {
        if (node == nullptr)
            return;

        release(node->left);
        release(node->right);
        puts("releasing");
    }
};

int cmp_int(const int a, const int b)
{
    return a - b;
}

void print_int(int p)
{
    printf("%d\n", p);
}

int main()
{
    Tree<int> tree {cmp_int};

    tree.add(5);
    tree.add(12);
    tree.add(34);
    tree.add(3);
    tree.add(15);

    tree.iterate(print_int);
}