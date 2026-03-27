#include <iostream>
#include <vector>

using namespace std;

class Product
{
public:
    string name;
    double price;

    Product(string name, double price)
    {
        this->name = name;
        this->price = price;
    }
};
// violating srp : shopping cart is handling multiple responsiblities.
class ShoppingCart
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *p)
    {
        products.push_back(p);
    }
    const vector<Product *> &getProducts()
    {
        return products;
    }
    // 1 calculate total prices
    double calculateTotal()
    {
        double total = 0;
        for (auto p : products)
        {
            total += p->price;
        }
        return total;
    }
    void printInvoice()
    {
        cout << "shopping cart invoice\n";
        for (auto p : products)
        {
            cout << p->name << " - " << p->price << endl;
        }
        cout << "total: " << calculateTotal() << endl; 
    }
    void saveToDatabase()
    {
        cout << "saving to database\n";
    }
};
int main(){
    ShoppingCart* cart = new ShoppingCart();
    Product* p1 = new Product("Product 1", 100);
    Product* p2 = new Product("Product 2", 200);
    cart->addProduct(p1);
    cart->addProduct(p2);
    cart->printInvoice();
    cart->saveToDatabase();
    return 0;
}