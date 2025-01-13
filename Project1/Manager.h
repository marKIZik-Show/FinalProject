#include <iostream>
#include <vector>
#include "Product.h"
#include "Exeptions.h"

namespace Manager {
	class ProductManager {
	private:
		vector<Products::Product*> products;

	public:
		~ProductManager() {
			for (auto product : products) {
				delete product;
			}
		}

		void addProduct(Products::Product* product) {
			products.push_back(product);
			cout << "Product added: " << product->getName() << endl;
		}

		void removeProductById(int id) {
			auto it = find_if(products.begin(), products.end(),
				[id](Products::Product* product) { return product->getId() == id; });

			if (it != products.end()) {
				cout << "Product removed: " << (*it)->getName() << endl;
				delete* it;
				products.erase(it);
			}
		}

		void editProductById(int id, string newName, float newPrice) {
			auto it = find_if(products.begin(), products.end(),
				[id](Products::Product* product) { return product->getId() == id; });

			if (it != products.end()) {
				(*it)->setName(newName);
				(*it)->setPrice(newPrice);
				cout << "Product edited: " << newName << endl;
			}
		}

		void searchByName(const string& name) const {
			auto it = find_if(products.begin(), products.end(),
				[&name](Products::Product* product) { return product->getName() == name; });

			if (it != products.end()) {
				(*it)->show();
			}
			else {
				cout << "No product found with name: " << name << endl;
			}
		}

		void sortByPrice() {
			for (int i = 0; i < products.size(); ++i) {
				for (int j = 0; j < products.size() - i - 1; ++j) {
					if (products[j]->getPrice() > products[j + 1]->getPrice()) {
						Products::Product* temp = products[j];
						products[j] = products[j + 1];
						products[j + 1] = temp;
					}
				}
			}
			cout << "Products sorted by price." << endl;
		}

		void saveToFile(const string& filename) const {
			ofstream out(filename);
			if (!out) throw saveFileExeption("Cannot open file for writing.", filename);

			for (const auto& product : products) {
				product->saveToFile(out);
			}
			out.close();
			cout << "Products saved to file: " << filename << endl;
		}

		void loadFromFile(const string& filename) {
			ifstream in(filename);
			if (!in) throw loadFileExeption("Cannot open file for reading.", filename);

			string line;
			while (getline(in, line)) {
				cout << "Loaded line: " << line << endl;
			}
			in.close();
			cout << "Products loaded from file: " << filename << endl;
		}

		void showAllProducts() const {
			for (const auto& product : products) {
				product->show();
				cout << "--------------------------" << endl;
			}
		}
	};
}