struct Car
{
    char id[32];
    char desc[32];

    void show() const
    {
        printf("(%s) %s\n", id, desc);
    }
};

struct CarList
{
    Car** cars;
    size_t n;
    // ....
}

struct CarDescData
{
    char desc[32];
    // Por cada descripcion tiene una lista
    CarList cars;
};

void sc(const Car& c)
{
    c.show();
}

struct CarManager
{
    // el arbol esta configurado para almacenar Car y busque por el id.
    BST carByID;
    // este arbol tiene nodos de tipo CarNode y busca por descripcion.
    BST carByDesc;
}

int main()
{
    CarManager r;

    r.add(Car {"123XYZ", "Volkswagen Brasilia"});

    r.add("");

    r.iterate_by_desc("Volkswagen_Brasilia", sc);

    Car c;

    bool p = r_find_car("123XYZ", c);

    if (p)
        sc(c);
}

