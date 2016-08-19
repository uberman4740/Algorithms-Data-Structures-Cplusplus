#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#ifndef ANIMAL_H
#define ANIMAL_H

class Animal
{
	public:
		Animal(string name) : m_name(name) {}
		virtual ~Animal() {}
		virtual string speak() const = 0;
		virtual string move() const { return "walk"; }
		virtual string name() const { return m_name;}
	private:
		string m_name;
};

class Pig : public Animal
{
	public:
		virtual string speak() const;
		Pig(string name, int weight);
		~Pig(){ cout << "Destroying " << name() << " the pig" << endl; }
	private:
		int m_weight;
};

class Cat : public Animal
{
	public:
		Cat(string name) : Animal(name){}
		virtual string speak() const { return "Meow";}
		~Cat(){ cout << "Destroying " << name() << " the cat" << endl; }
};

class Duck : public Animal
{
	public:
		virtual string speak() const { return "Quack";}
		Duck(string name) : Animal(name) {}
		~Duck(){ cout << "Destroying " << name() << " the duck" << endl; }
		string move() const { return "swim"; }
};

#endif

Pig::Pig(string name, int weight) : Animal(name)
{
	if(weight < 0)
		exit(1);
	else
		m_weight = weight;
}

string Pig::speak() const
{
	if(m_weight < 180)
		return "Oink";
	else
		return "Grunt";
}

void animate(const Animal* a)
{
    cout << a->speak() << "!  My name is " << a->name()
         << ".  Watch me " << a->move() << "!\n";
}

int main()
{
    Animal* animals[4];
    animals[0] = new Cat("Fluffy");
      // Pigs have a name and a weight in pounds.  Pigs under 180
      // pounds oink; pigs weighing at least 180 pounds grunt.
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");

    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);

      // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
}