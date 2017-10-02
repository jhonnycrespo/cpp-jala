#include <cstdio>
#include <cstdlib>
#include <cstring>

/**
 * char* strcpy (char* destination, const char* source );
 */

class Data
{
    public:
        char description[32];

        virtual show() = 0;

}

class Car: public Data
{
    public:
        char id[32];

        Car(const char* id, const char* description)
        {
            strcpy(this->id, id);
            strcpy(this->description, description);
        }

        void show() const override
        {
            cout << id << " " << desc << endl;
        }
}

class CarDescData: public Data
{
    public:
        CarList cars;

        CarDescData(char* description, CarList list)
        {
            strcpy(this->description, description);
            cars = list;
        }

        void show() const override
        {
            printf("%s %zu\n", desc, cars.n);
        }
}


class Node
{
    public:
        Data* data;
        Node* left;
        Node* right;

        Node()
        {
            data = nullptr;
            left = nullptr;
            right = nullptr;
        }
}

class CarList
{
    public:
        Car** cars;
        size_t n; 

        CarList()
        {

        }

        CarList(Car** cars, int n)
        {
            this->n = n;
        }
};

int cmp_str(const void* a, const void* b)
{
    return strcmp((char*) a, (char*) b);
}

class ITree
{
public:
    Node* root;

    virtual int add(Car* car) = 0;
    Data* search(const char* s) = 0;
}

class CarTree: public ITree
{
public:
    int add(Car* car) override
    {
        return add_r(car, &root);
    }

    int add_r(Car* car, Node** node)
    {
        if (*node == nullptr)
        {
            *node = new Node();
            (*node)->data = car;

            return 1;
        }
        
        int c = cmp_str(((Car*)((*node)->data))->id, data->id);

        if (c == 0)
            return 0;

        if (c > 0)
            return add_r(data, &((*node)->left), type);

        return add_r(data, &((*node)->right), type);

    }
}

class bst
{
    public:
        Node* root;
        int (*cmp) (const void*, const void*);
        void (*f) (void*);

        // data puede ser Car o CarDescData
        int add(Car* data, const char* type)
        {
            return add_r(data, &root, type);
        }

        int add_r(Car* data, Node** node, const char* type)
        {
            if (type == "Car")
            {
                if (*node == nullptr)
                {
                    *node = new Node();
                    (*node)->data = data;

                    return 1;
                }
                
                int c = cmp_str(((Car*)((*node)->data))->id, data->id);

                if (c == 0)
                    return 0;

                if (c > 0)
                    return add_r(data, &((*node)->left), type);

                return add_r(data, &((*node)->right), type);

            }

            if (type == "CarDescData")
            {
                if (*node == nullptr)
                {
                    puts("creando");
                    CarList list = {&data, 1};
                    CarDescData* carDescData = new CarDescData(data->desc, list);
                    *node = new Node();
                    (*node)->data = carDescData;

                    return 1;
                }

                int c = cmp_str(((CarDescData*)((*node)->data))->desc, data->desc);


                if (c == 0)
                {
                    ((CarDescData*)((*node)->data))->cars.n = ((CarDescData*)((*node)->data))->cars.n + 1;
                    return 0;
                }
                    

                if (c > 0)
                    return add_r(data, &((*node)->left), type);

                return add_r(data, &((*node)->right), type);
            }
    }

    void* search_r(Node* node, const char* s)
    {
        if (node == nullptr)
            return nullptr;

        int c = strcmp(((CarDescData*)(node->data))->desc, s);

        if (c == 0)
        {
            return ((CarDescData*)(node->data));
        }

        if (c > 0)
            return search_r(node->left, s);

        return search_r(node->right, s);
    }

    void* search(const char* s)
    {
        return search_r(root, s);
    }

    void show()
    {
        show_r(root);
    }

    void show_r(Node* node)
    {
        if (node == nullptr)
            return;

        show_r(node->left);
        node->data->show();
        show_r(node->right);
    }
};

struct CarManager
{
    bst carsByID;
    bst carsByDesc;

    void add(Car* car)
    {
        carsByID.add(car, "Car");
        carsByDesc.add(car, "CarDescData");
    } 

    void release()
    {
        release_r(carsByID.root);
        release_r(carsByDesc.root);
    }

    void release_r(Node* n)
    {
        if(n == nullptr)
            return;

        release_r(n->left);
        release_r(n->right);
        // liberar lo de dentro el nodo
        free(n);
        puts("bye");
    }

    CarManager()
    {
        carsByID.root = NULL;
        carsByDesc.root = NULL;
    }

    void iterate_by_desc(const char* desc, void (*sc)(const Car&))
    {
        CarDescData* data = (CarDescData*) carsByDesc.search(desc);

        for (int i = 0; i < data->cars.n; i++)
        {
            puts("hola");
            // (*(data->cars.cars))->show();
            // *(data->cars.cars)++;
        }

        printf("cantidad: %zu\n", data->cars.n);
    }

    bool find_car(const char* id, void (*sc)(const Car& c))
    {

    }
};

void sc(const Car& c)
{
    c.show();
}

int main()
{
    CarManager carManager;

    carManager.add(new Car("123ABC", "Ford"));
    carManager.add(new Car("456DEF", "Audi"));
    carManager.add(new Car("657TUC", "BMW"));
    carManager.add(new Car("156AJI", "Toyota"));
    carManager.add(new Car("357EUF", "Ford"));
    carManager.add(new Car("159SJV", "Audi"));
    carManager.add(new Car("671XMW", "BMW"));
    carManager.add(new Car("379QJS", "Audi"));

    // carManager.carsByID.show();
    // carManager.carsByDesc.show();

    carManager.iterate_by_desc("Audi", sc);


    bool p = carManager.find_car("357EUF", sc);

    carManager.release();


    // pasandole una descripcion, debe imprimir todos los autos con esa descripcion
    // r.iterate_by_desc("Volkswaz", sc);

    // Car c;

    // buscar un auto por su ID.
    // bool p = r_find_car("123XYZ",c);

    // si existe, imprimir mostrar el auto.
    // if (p)
        // sc(c);
}