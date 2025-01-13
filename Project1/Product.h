#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;



namespace Products {
	class Product
	{
	protected:
		int id;
		int code;
		string name;
		float price;
		string description;
	public:
		Product() : id(0), code(0), name("Unnamed"), price(0.0f), description("No description") {
		}

		Product(int id, int code, string name, float price, string description)
			: id(id), code(code), name(name), price(price), description(description) {}
		virtual ~Product() {}
		int getId() const { return id; }
		int getCode() const { return code; }
		string getName() const { return name; }
		float getPrice() const { return price; }
		string getDesc() const { return description; }

		void setId(int id) { this->id = id; }
		void setCode(int code) { this->code = code; }
		void setName(const string& name) { this->name = name; }
		void setPrice(float price) { this->price = price; }
		void setDesc(const string& description) { this->description = description; }

		virtual void show() const{
			cout << "Id:" << id << endl;
			cout << "Code:" << code << endl;
			cout << "Name:" << name << endl;
			cout << "Price:" << price << endl;
			cout << "Description:" << description << endl;
		}
		virtual void saveToFile(ofstream& out) const {
			out << id << "," << code << "," << name << "," << price << "," << description;
		}
		bool operator<(const Product& other) const {
			return price < other.price; 
		}

		virtual string getType() const { return "Product"; }
	};


	class FragileProduct : public Product {
	private:
		float fragilityCoefficient;

	public:
		FragileProduct(int id, int code, string name, float price, string description, float fragilityCoefficient)
			: Product(id, code, name, price, description), fragilityCoefficient(fragilityCoefficient) {}

		void show() const override {
			Product::show();
			cout << "Fragility Coefficient: " << fragilityCoefficient << endl;
		}

		void saveToFile(ofstream& out) const override {
			Product::saveToFile(out);
			out << "," << fragilityCoefficient << ",Fragile" << endl;
		}

		string getType() const override { return "Fragile"; }
	};

	class largeProduct : public Product {
	private:
		float width;
		float height;
		float length;

	public:
		largeProduct(int id, int code, string name, float price, string description, float width, float height, float length)
			: Product(id, code, name, price, description), width(width), height(height), length(length) {}

		void show() const override {
			Product::show();
			cout << "Size w/h/l: " << width<<", "<< height << ", "<< length << endl;
		}

		void saveToFile(ofstream& out) const override {
			Product::saveToFile(out);
			out << "," << width << "," << height << "," << length << ",Large" << endl;
		}

		string getType() const override { return "Large"; }
	};

	class PerishableProduct : public Product {
	private:
		int maxStorageTime;

	public:
		PerishableProduct(int id, int code, string name, float price, string description, int maxStorageTime)
			: Product(id, code, name, price, description), maxStorageTime(maxStorageTime) {}

		void show() const override {
			Product::show();
			cout << "Max Storage Time: " << maxStorageTime << " hours" << endl;
		}

		void saveToFile(ofstream& out) const override {
			Product::saveToFile(out);
			out << "," << maxStorageTime << ",Perishable" << endl;
		}

		string getType() const override { return "Perishable"; }
	};


}

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
			else {
				throw runtime_error("Product not found.");
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
			else {
				throw runtime_error("Product not found.");
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
			if (!out) throw runtime_error("Cannot open file for writing.");

			for (const auto& product : products) {
				product->saveToFile(out);
			}
			out.close();
			cout << "Products saved to file: " << filename << endl;
		}

		void loadFromFile(const string& filename) {
			ifstream in(filename);
			if (!in) throw runtime_error("Cannot open file for reading.");

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

