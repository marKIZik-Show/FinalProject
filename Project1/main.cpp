//•	Створено ієрархію класів.
//•	Реалізовано конструктори, деструктори, аксесори.
//•	Використано принципи Інкапсуляції, Спадкування та Поліморфізму.
//•	Розбиття класів на необхідні простори імен
//•	Наявність перевантаження операторів
//•	Використано статичні дані та\або методи
//•	Реалізовано клас контейнер на основі STL.
//•	Реалізовано додавання, видалення, редагування та пошук за критеріями.
//•	Додано обробку виняткових ситуацій.
//•	Організовано збереження і вивантаження з файлу.
//•	Використання сортування


#include "Product.h"
using namespace Products;
using namespace Manager;

int main() {
    ProductManager manager;

    manager.addProduct(new Product(1, 1001, "RTX5070", 599.99f, "Fast video card"));
    manager.addProduct(new FragileProduct(2, 1002, "Laptop", 1299.99f, "Gaming laptop", 45));
    manager.addProduct(new PerishableProduct(3, 1003, "Socks", 2.99f, "Natural socks", 48));
    manager.addProduct(new largeProduct(4, 1004, "Fridge", 899.99f, "Big fridge", 200.0f, 50.0f, 300.0f));

    cout << "\nAll Products:\n";
    manager.showAllProducts();

    try {
        manager.editProductById(1, "RTX5090", 2999.99f);
        cout << "\nAfter Editing Product with ID 1:\n";
        manager.showAllProducts();
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    cout << "\nSearching Laptop:\n";
    manager.searchByName("Laptop");

    manager.sortByPrice();
    cout << "\nProducts Sorted by Price:\n";
    manager.showAllProducts();

    try {
        manager.removeProductById(3);
        cout << "\nAfter removing product with ID 3:\n";
        manager.showAllProducts();
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
    try {
        manager.saveToFile("products.txt");
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    try {
        manager.loadFromFile("products.txt");
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}
