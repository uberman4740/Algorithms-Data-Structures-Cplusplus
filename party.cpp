#include <iostream>
#include <string>

using namespace std;

class Item{
	public:
		Item(const string& n) : name(n){}
		string getName() const {return name;}
		virtual void print() const {cout << name << endl;}
	private:
		string name;
};

class Drink : public Item{
	public:	
		Drink(const string& name, double l, bool ia) : Item(name), liter(l), isAlco(ia){}
		bool IsAlcohol() const {return isAlco;}
		virtual void print() const {cout << getName() << " / " << liter << " liters" << endl;}
		virtual void print(int dummy) const {cout << "Dummy print." << endl;}
	private:
		bool isAlco;
		double liter;
};

class Snack : public Item{
	public:	
		Snack(const string& name, double p, bool iv) : Item(name), pound(p), isVeg(iv){}
		bool IsVegan()const {return isVeg;}
		virtual void print() const {cout << getName() << " / " << pound << " pounds" << endl;}
	private:
		bool isVeg;
		double pound;
};

int main(){
	
	
	Drink d1("beer", 5, true);
	Snack s1("pop corn", 1, true);
	Drink d2("coke", 5, false);
	
	Item* i[3];
	i[0] = &d1;
	i[1] = &s1;
	i[2] = &d2;

	//what happens if the "virtual" before all the print's are taken out
	for(int j = 0; j < 3; j++)
		i[j] -> print();

	for(int j = 0; j < 3; j++)
		i[j] -> Item::print();

	//can't use cout << i[0] -> IsAlcohol() << endl;
	cout << dynamic_cast<Drink*>(i[0]) -> IsAlcohol() << endl;

	//can't do cout i[0] -> print(1);
	dynamic_cast<Drink*>(i[0]) -> print(1);

	return 0;
}
