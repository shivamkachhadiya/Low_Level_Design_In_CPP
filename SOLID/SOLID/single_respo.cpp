#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ---------------- Product ----------------
class Product {
public:
    string name;
    double price;

    Product(string n, double p) : name(n), price(p) {}
};

// ---------------- ShoppingCart ----------------
class ShoppingCart {
    vector<Product> products;

public:
    void addProduct(const Product& p) {
        products.push_back(p);
    }

    const vector<Product>& getProducts() const {
        return products;
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& p : products)
            total += p.price;
        return total;
    }
};

// ---------------- InvoicePrinter ----------------
class InvoicePrinter {
public:
    void print(const ShoppingCart& cart) const {
        cout << "\n--- Invoice ---\n";
        for (const auto& p : cart.getProducts()) {
            cout << p.name << " - " << p.price << '\n';
        }
        cout << "Total: " << cart.calculateTotal() << '\n';
    }
};

// ---------------- CartRepository ----------------
class CartRepository {
public:
    void save(const ShoppingCart& cart) const {
        cout << "\nSaving cart to database...\n";

        for (const auto& p : cart.getProducts()) {
            cout << "Saving: " << p.name << '\n';
        }
    }
};

// ---------------- Main ----------------
int main() {
    ShoppingCart cart;

    cart.addProduct({"Laptop", 50000});
    cart.addProduct({"Mouse", 500});

    InvoicePrinter printer;
    printer.print(cart);

    CartRepository repo;
    repo.save(cart);

    return 0;
}