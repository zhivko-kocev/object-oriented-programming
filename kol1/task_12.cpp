#include <iostream>
#include <cstring>

using namespace std;
/*
Да се дефинира класа Пица за која ќе се чуваат податоци за:

име на пицата (низа од 15 знаци)
цена (цел број)
состојки (динамички алоцирана низа од знаци)
намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето
има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор.
Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
istiSe(Pica p) - функција за споредба на две пици според состојките :
Да се дефинира класа Picerija во која се чуваат:

име (низа од максимум 15 знаци)
динмички алоцирана низа од објекти од класата Pica
број на пици (цел број)
За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

dodadi(Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.

*/
class Pizza
{
private:
    char name[15]{};
    int price;
    char *ingredients;
    int discount;

public:
    Pizza(char *name = "", int price = 0, char *ingredients = "", int discount = 0)
    {
        this->ingredients = new char[strlen(ingredients) + 1];
        strcpy(this->name, name);
        this->price = price;
        strcpy(this->ingredients, ingredients);
        this->discount = discount;
    }

    Pizza(const Pizza &p)
    {
        strcpy(name, p.name);
        price = p.price;
        ingredients = new char[strlen(p.ingredients) + 1];
        strcpy(ingredients, p.ingredients);
        discount = p.discount;
    }

    ~Pizza()
    {
        delete[] ingredients;
    }

    Pizza &operator=(const Pizza &p)
    {
        if (this != &p)
        {
            strcpy(name, p.name);
            price = p.price;
            delete[] ingredients;
            ingredients = new char[strlen(p.ingredients) + 1];
            strcpy(ingredients, p.ingredients);
            discount = p.discount;
        }
        return *this;
    }

    int compareTo(Pizza &p)
    {
        if (!strcmp(ingredients, p.ingredients))
        {
            return 1;
        }
        return 0;
    }

    void print()
    {
        cout << name << " - " << ingredients << ", " << price;
    }

    int getPrice()
    {
        return price;
    }

    char *getName()
    {
        return name;
    };

    int getDiscountPrice()
    {
        return price - (price * (discount / 100.0));
    }

    char *getIngredients()
    {
        return ingredients;
    }

    int getDiscount()
    {
        return discount;
    }
};

class PizzaShop
{
private:
    char name[15]{};
    Pizza *pizzas;
    int numPizza;

public:
    PizzaShop(char *name)
    {
        strcpy(this->name, name);
        numPizza = 0;
        pizzas = nullptr;
    }

    PizzaShop(const PizzaShop &p)
    {
        strcpy(name, p.name);
        numPizza = p.numPizza;
        pizzas = new Pizza[numPizza];
        for (int i = 0; i < numPizza; ++i)
        {
            pizzas[i] = p.pizzas[i];
        }
    }

    ~PizzaShop()
    {
        delete[] pizzas;
    }

    void addPizza(Pizza &p)
    {
        for (int i = 0; i < numPizza; ++i)
        {
            if (pizzas[i].compareTo(p))
            {
                return;
            }
        }
        auto *temp = new Pizza[numPizza + 1];
        for (int i = 0; i < numPizza; ++i)
        {
            temp[i] = pizzas[i];
        }
        temp[numPizza] = p;
        numPizza++;
        delete[] pizzas;
        pizzas = temp;
    }

    void pizzasOnPromotion()
    {
        for (int i = 0; i < numPizza; ++i)
        {
            if (pizzas[i].getDiscount())
            {
                pizzas[i].print();
                cout << " " << pizzas[i].getDiscountPrice() << endl;
            }
        }
    }
    void setName(char *_name)
    {
        strcpy(this->name, _name);
    }
    char *getName()
    {
        return name;
    }
};
int main()
{

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    PizzaShop p1(ime);
    for (int i = 0; i < n; i++)
    {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pizza p(imp, cena, sostojki, popust);
        p1.addPizza(p);
    }

    PizzaShop p2 = p1;
    cin >> ime;
    p2.setName(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pizza p(imp, cena, sostojki, popust);
    p2.addPizza(p);

    cout << p1.getName() << endl;
    cout << "Pici na promocija:" << endl;
    p1.pizzasOnPromotion();

    cout << p2.getName() << endl;
    cout << "Pici na promocija:" << endl;
    p2.pizzasOnPromotion();

    return 0;
}
