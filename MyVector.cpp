// MyVector.cpp: 定义应用程序的入口点。
//

#include "MyVector.h"
#include <vector>

using namespace std;
int main() {
	vector<int> vec;
	vector<int>::iterator it;

	MyVector<int> myVector;
	MyVector<int>::Iterator it2;

	vec.push_back(1);
	myVector.push_back(1);

	for (it = vec.begin(); it != vec.end(); it++) {
		cout << *it << endl;
	}
	for (it2 = myVector.begin(); it2 != myVector.end(); it2++) {
		cout << *it2 << endl;
	}

	return 0;
}
