// MyVector.cpp: 定义应用程序的入口点。

#include "MyVector.h"
#include <vector>
#include <random>

using namespace std;

template <class T>
void print(MyVector<T>& myVector) {
	MyVector<T>::Iterator it;
	for (it = myVector.begin(); it != myVector.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

template <class T>
void print(vector<T>& vec) {
	vector<T>::iterator it;
	for (it = vec.begin(); it != vec.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

int main() {
	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(25, 63); // define the range

	vector<int> vec;
	vector<int>::iterator it;

	MyVector<int> myVector;
	MyVector<int>::Iterator it2;

	for (int i = 0; i < 10; i++) {
		vec.push_back(distr(gen));
	}
	for (size_t i = 0; i < 10; i++)	{
		myVector.push_back(distr(gen));
	}
	print(vec);
	print(myVector);
	cout << "==========================================================" << endl;

	myVector.sort();
	print(myVector);
	cout << myVector.minimum() << " " << myVector.maximum() << endl;
	myVector.modify(0, 100);
	print(myVector);
	myVector.erase(0);
	print(myVector);

	return 0;
}
