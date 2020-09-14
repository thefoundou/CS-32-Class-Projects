/*#include <iostream>
#include <string>
using namespace std;*/

//Your declarationsand implementations would go here

class Animal
{
public:
	Animal(string name) : m_name(name) {};
	string name() const { return m_name;} 
	virtual string moveAction() const { return "walk"; }
	virtual void speak() const = 0; 
	virtual ~Animal() {};

private:
	string m_name;
};

class Cat : public Animal
{
public:
	Cat(string name) : Animal(name) {};
	virtual void speak() const { cout << "Meow"; }
	~Cat() { cout << "Destroying " << name() << " the cat" << endl; }
private:

};


class Duck : public Animal
{
public:
	Duck(string name) : Animal(name) {};
	virtual void speak() const { cout << "Quack"; }
	virtual string moveAction() const { return "swim"; }

	~Duck() { cout << "Destroying " << name() << " the duck" << endl; }
private:

};


class Pig : public Animal
{
public:
	Pig(string name, int weight) : Animal(name), m_weight(weight) {};
	virtual void speak() const
	{ 
		if (m_weight < 160)
			cout << "Oink";
		else
			cout << "Grunt";
	}
	~Pig() { cout << "Destroying " << name() << " the pig" << endl; }
private:
	int m_weight;
};

/*
void animate(const Animal* a)
{
	a->speak();
	cout << "!  My name is " << a->name()
		<< ".  Watch me " << a->moveAction() << "!\n";
}

int main()
{
	Animal* animals[4];

	animals[0] = new Cat("Fluffy");
	// Pigs have a name and a weight in pounds.  Pigs under 160
	// pounds oink; pigs weighing at least 160 pounds grunt.
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
}*/