#include <iostream>
#include <list>

using namespace std;

class Item{
	public:
		Item(const string& n) : name(n){};
		string getName() const {return name;}
		void printName() const {cout << name << endl;}
		virtual void printQuant() const = 0;
		virtual ~Item(){};
	private:
		string name;
};

class Drink : public Item{
	public:	
		Drink(const string& name, double l, bool ia) : Item(name), liter(l), isAlco(ia), ingred(NULL){}
		bool IsAlcohol() const {return isAlco;}
		virtual void printQuant() const {cout << liter << " liters" << endl;}
		void AddIngredient(const string& s){
			if(ingred == NULL)
				ingred = new list<string>;
			ingred -> push_back(s);
		}
		virtual ~Drink(){delete ingred; cout << "In Drink " << getName() << "'s Destructor." << endl;};
	private:
		bool isAlco;
		double liter;
		list<string>* ingred;
};

class Snack : public Item{
	public:	
		Snack(const string& name, double p, bool iv) : Item(name), pound(p), isVeg(iv){}
		bool IsVegan() const {return isVeg;}
		virtual void printQuant() const {cout << pound << " pounds" << endl;}
		virtual ~Snack(){};
	private:
		bool isVeg;
		double pound;
};

int main(){


	Drink d1("beer", 5, true);
	Snack s1("pop corn", 1, true);


	//can't have an item object because it is an abstract base class

	Item* i[3];
	i[0] = &d1;
	i[1] = &s1;
	i[2] = new Drink("coke", 5, false);
	
	for(int j = 0; j < 3; j++){
		i[j] -> printName();
		i[j] -> printQuant();
	}

	
	//dynamic_cast<Drink*>(i[0]) -> AddIngredient("Vodka");
	d1.AddIngredient("Vodka");

	delete i[2];


	//if the "virtual" in front of the destructor's are deleted
	//print beer's destructor
	//with the "virtual"
	//first coke's destructor and then beer's

	return 0;
}
