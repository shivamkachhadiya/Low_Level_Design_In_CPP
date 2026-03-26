#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Product class
class Product
{
public:
    string name;
    double price;

    Product(const string& name, double price)
        : name(name), price(price) {}
};

// ShoppingCart: manages products only
class ShoppingCart
{
private:
    vector<Product*> products;
public:
    void addProduct(Product* p)
    {
        products.push_back(p);
    }
    const vector<Product*>& getProducts() const
    {
        return products;
    }
    double calculateTotal() const
    {
        double total = 0;
        for (auto p : products)
            total += p->price;
        return total;
    }
};

// InvoiceGenerator interface
class IInvoiceGenerator
{
public:
    virtual void generate(const ShoppingCart& cart) const = 0;
    virtual ~IInvoiceGenerator() = default;
};

// A default implementation
class StandardInvoice : public IInvoiceGenerator
{
public:
    void generate(const ShoppingCart& cart) const override
    {
        cout << "Standard Invoice:\n";
        for (auto p : cart.getProducts())
        {
            cout << p->name << " - " << p->price << endl;
        }
        cout << "Total: " << cart.calculateTotal() << endl;
    }
};

// Another implementation to show open/close
class DetailedInvoice : public IInvoiceGenerator
{
public:
    void generate(const ShoppingCart& cart) const override
    {
        cout << "Detailed Invoice:\n";
        int idx = 1;
        for (auto p : cart.getProducts())
        {
            cout << idx << ". " << p->name << " (price: " << p->price << ")\n";
            idx++;
        }
        cout << "[END OF INVOICE]\n";
        cout << "Total amount due: " << cart.calculateTotal() << endl;
        cout << "Thank you for shopping!\n";
    }
};

int main(){
    ShoppingCart cart;
    Product* p1 = new Product("Product 1", 100);
    Product* p2 = new Product("Product 2", 200);
    cart.addProduct(p1);
    cart.addProduct(p2);

    // You can inject any invoice generator, extend without modifying main code
    IInvoiceGenerator* invoice = new StandardInvoice();
    invoice->generate(cart);

    // Demonstrate open/close principle: add new behavior without modifying existing code
    IInvoiceGenerator* detailed = new DetailedInvoice();
    detailed->generate(cart);

    delete invoice;
    delete detailed;

    delete p1;
    delete p2;
    return 0;
}