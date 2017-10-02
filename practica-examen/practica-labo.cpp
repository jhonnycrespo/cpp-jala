#include <cstdio>
#include <cstdlib>
#include <cstring>

/**
 * char* strcpy (char* destination, const char* source );
 */

struct Node
{
    void* data;
    Node* left;
    Node* right;

    Node(): data {nullptr}, left {nullptr}, right {nullptr}
    {

    }
};

struct Car
{
    char id[32];
    char desc[32];

    Car()
    {

    }

    Car(const char* id, const char* desc)
    {
        strcpy(this->id, id);
        strcpy(this->desc, desc);
    }

    void show() const
    {
        printf("%s - %s\n", id, desc);
    }
};

struct CarList
{
    Car** cars;
    size_t n; 

    CarList()
    {
        cars = (Car**) malloc(0);
        n = 0;
    }

    void add(Car* car)
    {
        puts("agregando a la lista");
        cars = (Car**) realloc(cars, (n+1)*sizeof(Car*));
        cars[n++] = car;
    }

    void release()
    {
        for (int i = 0; i < n; i++)
        {
            puts("releasing car");
            free(cars[i]);
        }
        // puts("list");
        // free(cars);
    }
};

struct CarDescData
{
    char desc[32];
    CarList cars;

    CarDescData(const char* desc, CarList cars)
    {
        strcpy(this->desc, desc);
        this->cars = cars;
    }
};

struct bst
{
    Node* root;
    int (*cmp) (const void*, const void*);
    void (*f) (void*);

    bst()
    {

    }

    bst(Node* root, int (*cmp)(const void*, const void*), void (*f)(void*))
    {
        this->root = root;
        this->cmp = cmp;
        this->f = f;
    }

    int add(Car* data)
    {
        return add_r(data, &root);
    }

    int add_desc(Car* data)
    {
        return add_desc_r(data, &root);
    }

    int add_desc_r(Car* data, Node** node)
    {
        if (*node == nullptr)
        {
            printf("agregando marca - %s\n", data->desc);


            CarList list;
            list.add(data);

            CarDescData* carDescData = new CarDescData(data->desc, list);

            *node = new Node();
            (*node)->data = carDescData;

            return 1;
        }

        int c = cmp(((CarDescData*)((*node)->data))->desc, data->desc);

        if (c == 0)
        {
            ((CarDescData*)((*node)->data))->cars.add(data);
            return 0;
        }
            
        if (c > 0)
            return add_desc_r(data, &((*node)->left));

        return add_desc_r(data, &((*node)->right));
    }

    int add_r(Car* data, Node** node)
    {
        if (*node == nullptr)
        {
            *node = new Node();
            (*node)->data = data;

            return 1;
        }
        
        int c = cmp(((Car*)((*node)->data))->id, data->id);

        if (c == 0)
            return 0;

        if (c > 0)
            return add_r(data, &((*node)->left));

        return add_r(data, &((*node)->right));
    }

    void* search_r(Node* node, const char* s)
    {
        if (node == nullptr)
            return nullptr;

        int c = strcmp(((CarDescData*)(node->data))->desc, s);

        if (c == 0)
        {
            puts("Encontrado!!");
            return ((CarDescData*)(node->data));
        }

        if (c > 0)
            return search_r(node->left, s);

        return search_r(node->right, s);
    }

    void* search_car_r(Node* node, const char* s)
    {
        if (node == nullptr)
            return nullptr;

        int c = strcmp(((Car*)(node->data))->id, s);

        if (c == 0)
        {
            puts("Encontrado!!");
            return ((Car*)(node->data));
        }

        if (c > 0)
            return search_r(node->left, s);

        return search_r(node->right, s);
    }

    void* search(const char* s)
    {
        return search_r(root, s);
    }

    void* search_car(const char* s)
    {
        return search_car_r(root, s);
    }

    void show_r(Node* node)
    {
        if (node == nullptr)
            return;

        show_r(node->left);
        ((Car*)(node->data))->show();
        show_r(node->right);
    }

    void show()
    {
        show_r(root);
    }

    void release_car()
    {
        release_car_r(root);
    }

    void release_car_desc()
    {
        release_car_desc_r(root);
    }

    void release_car_desc_r(Node* node)
    {
        if (node == nullptr)
            return;

        release_car_desc_r(node->left);
        release_car_desc_r(node->right);

        ((CarDescData*)(node->data))->cars.release();

        f(node->data);
        free(node);
        puts("bye");
    }

    void release_car_r(Node* node)
    {
        if (node == nullptr)
            return;

        release_car_r(node->left);
        release_car_r(node->right);
        f(node->data);
        free(node);
        puts("bye");
    }
};

int cmp_str(const void* a, const void* b)
{
    return strcmp((char*) a, (char*) b);
}

struct CarManager
{
    bst carsByID;
    bst carsByDesc;

    CarManager()
    {
        carsByID = {nullptr, cmp_str, free};
        carsByDesc = {nullptr, cmp_str, free};
    }

    void add(Car* car)
    {
        carsByID.add(car);
        carsByDesc.add_desc(car);
    }

    void iterate_by_desc(const char* desc, void (*sc)(const Car& c))
    {
        printf("Buscando marca - %s\n", desc);

        CarDescData* carDesc = (CarDescData*) carsByDesc.search(desc);

        printf("===== Cars disponibles : %zu =====\n", carDesc->cars.n);

        for (int i = 0; i < carDesc->cars.n; i++)
        {
            // carDesc->cars.cars[i]->show();
            sc(*(carDesc->cars.cars[i]));
        }

    }

    bool find_car(const char* id, Car& car)
    {
        Car* foundCar = (Car*) carsByID.search_car(id);

        if (foundCar == nullptr)
        {
            return false;
        }
        else
        {
            strcpy(car.id, foundCar->id);
            strcpy(car.desc, foundCar->desc);

            return true;
        }
    }

    void release()
    {
        carsByID.release_car();
        carsByDesc.release_car_desc();
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
    carManager.add(new Car("123ABC", "Ford"));
    carManager.add(new Car("456DEF", "Audi"));
    carManager.add(new Car("657TUC", "BMW"));
    carManager.add(new Car("156AJI", "Toyota"));
    carManager.add(new Car("357EUF", "Ford"));
    carManager.add(new Car("159SJV", "Audi"));
    carManager.add(new Car("671XMW", "BMW"));
    carManager.add(new Car("379QJS", "Audi"));

    carManager.iterate_by_desc("Audi", sc);

    Car c;

    bool p = carManager.find_car("671XMW", c);

    if(p)
        sc(c);

    carManager.release();
}