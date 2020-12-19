// MyVector.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

using namespace std;
template<class T>
class MyVector {
private:
	T* address;//首地址
	size_t capacity;//容量大小
	size_t num;//元素个数
	void _clear()
	{
		num = capacity = 0;
		delete[] this->address;
		this->address = nullptr;
	}

public:
	explicit MyVector() { 
		address = nullptr; num = capacity = 0; 
	}
	MyVector(MyVector& other) :capacity(other.capacity), num(other.num) {
		address = new T[capacity];
		for (int i = 0; i < other.num; i++) {
			*(address + i) = *(other.address + i);
		}
	}
	~MyVector() {
		_clear();
	}
	struct Iterator {
		//指针
		T* pt;

		//无参构造
		Iterator() {
			pt = nullptr;
		}

		//拷贝构造
		Iterator(Iterator& other) {
			this->pt = other.pt;
		}
		
		//析构
		~Iterator() {
			pt = nullptr;
		}

		//赋值运算符重载
		void operator = (const T* obj) {
			pt = (T*)obj;
		}

		//解引用运算符重载
		T& operator * () const {
			return (*pt);
		}

		//+运算符重载
		Iterator operator + (const int off) {
			return this->pt + off;
		}

		//-运算符重载
		int operator - (Iterator& other) {
			return (this->pt - other.pt);
		}

		//-运算符重载
		int operator - (T* other) {
			return static_cast<int>(this->pt - other);
		}

		//-运算符重载
		Iterator operator - (const int off) {
			return this->pt - off;
		}

		//后++运算符重载
		Iterator& operator ++ (int) {
			//临时变量
			Iterator* temp = new Iterator;
			temp->pt = this->pt;
			this->pt++;
			return *temp;
		}

		//前++运算符重载
		Iterator& operator ++ () {
			return ++this->pt;
		}

		//后--运算符重载
		Iterator& operator -- (int) {
			//临时变量
			Iterator* temp = new Iterator;
			temp->pt = this->pt;
			this->pt--;
			return *temp;
		}

		//前--运算符重载
		Iterator& operator -- () {
			return 	--this->pt;
		}

		//!=运算符重载
		bool operator != (const Iterator& obj) {
			return (this->pt != obj);
		}

		//!=运算符重载
		bool operator != (const T* obj) {
			return (this->pt != obj);
		}

		//+=运算符重载
		Iterator& operator += (const int off) {
			return pt + off;
		}

		//-=运算符重载
		int operator -= (const int off) {
			return static_cast<int>(pt - off);
		}

		//-=运算符重载
		Iterator& operator -= (const Iterator& other) {
			this->pt = this->pt - other->pt;
			return this->pt;
		}

	};

	/*---------------------------------------以下为<<重载-------------------------------------------*/
	friend ostream& operator << (ostream& os, const MyVector<T>* dt);

	/*--------------------------------------以下为成员函数------------------------------------------*/
	//求容器始端地址
	T* begin()const {
		return this->address;
	}

	//求容器末端地址
	T* end()const {
		return this->address + num;
	}

	//求容量大小
	size_t get_capacity()const {
		return this->capacity;
	}

	//求元素数量
	size_t size()const {
		return this->num;
	}

	//正迭代器：返回所在位置的元素
	T at(const size_t pos)const	{
		try {
			if (pos < num && pos >= 0)
				return address[pos];
			else
				throw pos;
		}
		catch (decltype(pos))
		{
			cout << endl << "访问的元素越界" << endl;
			return 0;
		}
	}

	//逆迭代器：返回倒数第几个元素
	T at_back(const int pos)const {
		try {
			if ((-1 * pos) <= num && pos < 0)
				return address[num + pos];
			else
				throw pos;
		}
		catch (decltype(pos))
		{
			cout << endl << "访问的元素越界" << endl;
			return;
		}
	}

	//在末尾添加元素
	void push_back(const T& data);
	//在开头添加元素
	void push_front(const T& data);
	//弹出末尾元素
	void pop_back();
	//弹出第一个元素
	void pop_front();
	//寻找最大值
	T maximum()const;
	//寻找最大值并求得地址
	T maximum(T*& at)const;
	//寻找范围内最大值
	T maximum(int pos1, int pos2)const;
	//寻找范围内最大值并求得地址
	T maximum(int pos1, int pos, T*& at)const;
	//寻找最小值
	T minimum()const;
	//寻找最小值并求得地址
	T minimum(T*& at)const;
	//寻找范围内最小值
	T minimum(int pos1, int pos2)const;
	//寻找范围内最小值并求得地址
	T minimum(int pos1, int pos2, T*& at)const;
	//重新分配内存并初始化(标准vector另还有两个重载函数)
	void assign(int&& _newsize, int&& val);
	//在迭代器所在位置插入数据
	void insert(Iterator& it, T&& data);
	//在下标所在位置插入数据
	void insert(const int pos, T&& data);
	//从下标所在位置开始插入数据
	void insert(const int pos, const T* data_beg, const T* data_end);
	//从下标所在位置开始插入数据
	void insert(const int pos, MyVector& other);
	//清空数据
	void clear();
	//交换两个vector
	void swap(MyVector& other);
	//删除迭代器所在位置元素
	void erase(Iterator& it);
	//删除下标所在位置元素
	void erase(const int pos);
	//删除两个下标之间的所有元素
	void erase(const int pos1, const int pos2);
	//修改迭代器所在位置的元素
	void modify(Iterator& it, T data);
	//修改下标所在位置的元素
	void modify(const int pos, T data);
	//修改两个下标之间的所有元素
	void modify(const int pos1, const int pos2, const T* data_beg, const T* data_end);
	//修改两个下标之间的所有元素
	void modify(const int pos1, const int pos2, const MyVector& other);
	void sort();
};

template<class T>
ostream& operator << (ostream& os, const MyVector<T>* dt) {
	return os << *dt;
}

template<class T>
void MyVector<T>::push_back(const T& data) {
	if (num == capacity) {
		capacity += ((capacity >> 1) > 1) ? (capacity >> 1) : 1;
		T* temp = new T[num];
		//临时保存数据
		memcpy(temp, address, num * sizeof(T));
		//重新分配内存
		this->address = new T[capacity];
		//把临时数据拷贝回来
		memcpy(address, temp, num * sizeof(T));
		delete[] temp;
	}
	address[num++] = data;//添加元素
}

template<class T>
void MyVector<T>::push_front(const T& data) {
	if (num == capacity) {
		//每次开1.5倍内存
		capacity += ((capacity >> 1) > 1) ? (capacity >> 1) : 1;
	}
	T* temp = new T[num];
	//临时保存数据
	memcpy(temp, address, num * sizeof(T));
	//重新分配内存
	this->address = new T[capacity];
	//把临时数据拷贝回来
	memcpy(address + 1, temp, num * sizeof(T));
	delete[] temp;
	//添加元素
	address[0] = data;
	num++;
}

template<class T>
void MyVector<T>::pop_back() {
	if (--num != 0) {
		T* temp = new T[num];
		for (int i = 0; i < num; i++) {
			//临时保存数据
			temp[i] = address[i];
		}
		address = new T[num];
		for (int i = 0; i < num; i++) {
			//把临时数据拷贝回来
			address[i] = temp[i];
		}
		delete[] temp;
	}
	else {
		_clear();
	}
}

template<class T>
void MyVector<T>::pop_front() {
	if (--num != 0) {
		T* temp = new T[num];
		for (int i = 1; i <= num; i++) {
			temp[i - 1] = address[i];
		}
		address = new T[num];
		for (int i = 0; i < num; i++) {
			address[i] = temp[i];
		}
		delete[] temp;
	}
	else {
		_clear();
	}
}

template<class T>
T MyVector<T>::maximum()const {
	T* at = this->begin();
	if (at) {
		T temp = *at;
		for (; at != this->end(); at++) {
			if (temp < *at) {
				temp = *at;
			}
		}
		return temp;
	}
	else {
		cout << "亲容器里没有元素哪来的最大值哇" << endl;
		return -1;
	}
}

template<class T>
T MyVector<T>::maximum(T*& pos)const {
	T* at = this->begin();
	pos = this->address;
	if (at)	{
		T temp = *at;
		for (; at != this->end(); at++) {
			if (temp < *at) {
				temp = *at;
				pos = at;
			}
		}
		return temp;
	}
	else {
		cout << "亲容器里没有元素哪来的最大值哇" << endl;
		return -1;
	}
}

template<class T>
T MyVector<T>::maximum(int pos1, int pos2)const {
	T temp = this->at(pos1);
	if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0) {
		for (int i = pos1; i != pos2; i++)
			if (temp < this->at(i)) {
				temp = this->at(i);
			}
		return temp;
	}
	else {
		cout << "亲下标是不是传错了" << endl;
		return -1;
	}
}

template<class T>
T MyVector<T>::maximum(int pos1, int pos2, T*& pos)const {
	T temp = this->at(pos1);
	pos = this->address + pos1;
	if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0) {
		for (int i = pos1; i != pos2; i++) {
			if (temp < this->at(i)) {
				temp = this->at(i);
				pos = this->address + i;
			}
		}
		return temp;
	}
	else {
		cout << "亲下标是不是传错了" << endl;
		return -1;
	}
}

template<class T>
T MyVector<T>::minimum()const {
	T* at = this->begin();
	if (at)	{
		T temp = *at;
		for (; at != this->end(); at++) {
			if (temp > *at)
				temp = *at;
		}
		return temp;
	}
	else {
		cout << "亲容器里没有元素哪来的最小值哇" << endl;
		return -1;
	}
}

template<class T>
T MyVector<T>::minimum(T*& pos)const {
	T* at = this->begin();
	pos = this->address;
	if (at) {
		T temp = *at;
		for (; at != this->end(); at++) {
			if (temp > *at)	{
				temp = *at;
				pos = at;
			}
		}
		return temp;
	}
	else {
		cout << "亲容器里没有元素哪来的最小值哇" << endl;
		return -1;
	}
}

template<class T>
T MyVector<T>::minimum(int pos1, int pos2)const {
	try {
		T temp = this->at(pos1);
		if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0) {
			for (int i = pos1; i != pos2; i++) {
				if (temp > this->at(i))	{
					temp = this->at(i);
				}
			}
			return temp;
		}
		else throw pos1;
	}
	catch (int)	{
		cout << "亲下标是不是传错了" << endl;
		return;
	}
}

template<class T>
T MyVector<T>::minimum(int pos1, int pos2, T*& pos)const {
	try {
		T temp = this->at(pos1);
		pos = this->address + pos1;
		if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0) {
			for (int i = pos1; i != pos2; i++) {
				if (temp < this->at(i)) {
					temp = this->at(i);
					pos = this->address + i;
				}
			}
			return temp;
		}
		else throw pos1;
	}
	catch (int)	{
		cout << "亲下标是不是传错了" << endl;
		return;
	}
}

template<class T>
//重新分配内存并初始化
void MyVector<T>::assign(int&& _newsize, int&& val) {
	if (num) {
		delete[] address;
	}
	address = new T[_newsize];
	this->num = _newsize;//调整num大小
	for (capacity = 1; capacity < num;) {
		//调整capacity大小
		capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;
	}
	for (auto i = this->begin(); i != this->end(); i++) {
		//初始化
		*i = val;
	}
}


template<class T>
void MyVector<T>::insert(Iterator& it, T&& data) {
	try {
		//计算插入位置距离容器首地址的距离
		int offset = it - address;
		if (offset >= 0 && offset < num) {
			//定义临时变量
			int i = 0;
			//计算需要临时存储的数据的大小
			int size = num - offset;
			if (num == capacity) {
				//调整capacity大小
				capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;
			}
			//申请新的堆内存存vector
			T* _new = new T[capacity];
			//防止size出现异常
			if (size > 0 && size <= num) {
				//申请堆内存暂存数据
				T* at = new T[size];
				for (i = 0; i < (num - offset); i++) {
					//暂存需要转移的数据
					at[i] = address[offset + i];
				}
				for (i = 0; i < (num - offset); i++) {
					//存第二段vector(也就是全部后移)
					_new[offset + i + 1] = at[i];
				}
				//初始化临时变量(_new要用)
				i = 0;
				delete[] at;
			}
			if (offset != 0) {
				for (i = 0; i < offset; i++) {
					_new[i] = address[i];//存第一段vector
				}
			}
			//存插入的数据
			_new[i] = data;
			delete[] address;
			address = _new;
			num++;
		}
		else
			throw offset;
	}
	catch (int) {
		cout << "插入位置越界啦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::insert(const int pos, T&& data) {
	try {
		//计算插入位置距离容器首地址的距离
		int offset = pos;
		if (offset >= 0 && offset < num) {
			int i = 0;
			int size = num - offset;
			if (num == capacity) {
				capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;
			}
			T* _new = new T[capacity];
			if (size > 1 && size <= num) {
				T* at = new T[size];
				for (i = 0; i < (num - offset); i++) {
					at[i] = address[offset + i];
				}
				for (i = 0; i < (num - offset); i++) {
					_new[offset + i + 1] = at[i];
				}
				i = 0;
				delete[] at;
			}
			for (i = 0; i < offset; i++) {
				_new[i] = address[i];
			}
			_new[i] = data;
			delete[] address;
			address = _new;
			num++;
		}
		else
			throw offset;
	}
	catch (int)	{
		cout << "插入位置越界啦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::insert(const int pos, const T* data_beg, const T* data_end) {
	try {
		//计算插入位置距离容器首地址的距离
		int offset = data_end - data_beg + 1;
		if (offset <= 0) {
			throw static_cast<float>(-1);
		}
		//防止越界
		if (pos >= 0 && pos <= num)
		{
			int i = 0;
			int size = num - pos;
			num += offset;
			if (num >= capacity)
				while (capacity <= num)
					capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;
			T* _new = new T[capacity];
			if (size > 0 && size <= num)
			{
				T* at = new T[size];
				for (i = 0; i < (num - offset - pos); i++)
					at[i] = address[pos + i];
				for (i = 0; i < (num - offset - pos); i++)
					_new[offset + pos + i] = at[i];
				delete[] at;
			}
			for (i = 0; i < pos; i++)
				_new[i] = address[i];

			for (i = 0; i < offset; i++)
				_new[pos + i] = data_beg[i];

			delete[] address;
			address = _new;
		}
		else
			throw - 1;
	}
	catch (int)	{
		cout << "插入位置越界啦！" << endl;
		return;
	}
	catch (float) {
		cout << "数组的下标传错啦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::insert(const int pos, MyVector& other) {
	try {
		//计算插入位置距离容器首地址的距离
		int offset = other.num;
		if (offset <= 0) {
			throw static_cast<float>(-1);
		}
		//防止越界
		if (pos >= 0 && pos <= num) {
			int i = 0;
			int size = num - pos;
			num += offset;
			if (num >= capacity) {
				while (capacity <= num) {
					capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;
				}
			}
			T* _new = new T[capacity];
			if (size > 0 && size <= num) {
				T* at = new T[size];
				for (i = 0; i < (num - offset - pos); i++) {
					at[i] = address[pos + i];
				}
				for (i = 0; i < (num - offset - pos); i++) {
					_new[offset + pos + i] = at[i];
				}
				delete[] at;
			}
			for (i = 0; i < pos; i++) {
				_new[i] = address[i];
			}
			for (i = 0; i < offset; i++) {
				//存插入的数据
				_new[pos + i] = other.at(i);
			}
			delete[] address;
			address = _new;
		}
		else
			throw - 1;
	}
	catch (int)	{
		cout << "插入位置越界啦！" << endl;
		return;
	}
	catch (float) {
		cout << "数组的下标传错啦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::clear()
{
	if (num) {
		_clear();
	}
}

template<class T>
void MyVector<T>::swap(MyVector& other) {
	T* temp;
	size_t tmp;

	temp = this->address;
	this->address = other.address;
	other.address = temp;

	tmp = this->num;
	this->num = other.num;
	other.num = tmp;

	tmp = this->capacity;
	this->capacity = other.capacity;
	other.capacity = tmp;
}

template<class T>
void MyVector<T>::erase(Iterator& it) {
	try	{
		if (num--) {
			if (!num) {
				//如果全部元素都删除了就初始化容器
				_clear();
			}
			else {
				int offset = it - address;
				for (int i = 0; i < num; i++) {
					//将后一个元素覆盖前一个元素
					address[offset + i] = address[offset + i + 1];
				}
			}
		}
		else throw - 1;
	}
	catch (int)	{
		cout << "容器里没有元素怎么删除啊亲！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::erase(const int pos) {
	try	{
		if (num-- && pos >= 0 && pos < num)	{
			if (!num) {
				_clear();
			}
			else {
				int offset = pos;
				for (int i = 0; i < num; i++) {
					address[offset + i] = address[offset + i + 1];
				}
			}
		}
		else throw - 1;
	}
	catch (int) {
		cout << "容器里没有元素怎么删除啊亲！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::erase(const int pos1, const int pos2) {
	try	{
		if (num) {
			//检测是否越界
			if (pos1 >= 0 && pos1 < num && pos2 >= 0 && pos2 < num)	{
				int beg = 0;
				int end = 0;
				int offset = 0;
				if (pos1 < pos2) {
					//计算下标之间的距离
					offset = pos2 - pos1 + 1;
					beg = pos1;
					end = pos2;
					//更新num
					num -= offset;
				}
				else if (pos2 < pos1) {
					offset = pos1 - pos2 + 1;
					beg = pos2;
					end = pos1;
					num -= offset;
				}
				//检测下标是否不同
				else throw static_cast<float>(-1.0);

				if (!num) {
					_clear();
				}
				else {
					for (int i = 0; i < num + offset - end - 1; i++) {
						address[beg + i] = address[end + i + 1];
					}
				}
			}
			else throw static_cast<double>(-1.0);
		}
		else throw - 1;
	}
	catch (int) {
		cout << "容器里没有元素怎么删除啊亲！" << endl;
		return;
	}
	catch (double) {
		cout << "输入的下标越界啦！" << endl;
		return;
	}
	catch (float) {
		cout << "输入的下标不可以一样哦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::modify(const int pos, T data) {
	try	{
		if (pos >= 0 && pos < num) {
			address[pos] = data;
		}
		else {
			throw - 1;
		}
	}
	catch (int)	{
		cout << "输入的下标越界啦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::modify(Iterator& it, T data) {
	try	{
		int pos = it - address;
		if (pos >= 0 && pos < num) {
			address[pos] = data;
		}
		else {
			throw - 1;
		}
	}
	catch (int)	{
		cout << "输入的下标越界啦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::modify(const int pos1, const int pos2, const T* data_beg, const T* data_end) {
	try {
		int beg = 0;
		int end = 0;
		int offset = 0;
		if (pos2 < pos1) {
			offset = pos1 - pos2 + 1;
			beg = pos2;
			end = pos1;
		}
		else if (pos1 < pos2) {
			offset = pos2 - pos1 + 1;
			beg = pos1;
			end = pos2;
		}
		else {
			//检测下标是否不同
			throw - 1;
		}

		if (offset > this->num) {
			throw static_cast<double>(-1);
		}
		//数组的长度必须大于等于修改的长度
		if (static_cast<int>(data_end - data_beg) < offset) {
			throw static_cast<float>(-1);
		}
		for (int i = 0; i < offset && i < static_cast<int>(data_end - data_beg); i++) {
			address[beg + i] = data_beg[i];
		}
	}
	catch (int)	{
		cerr << "输入的下标不可以一样哦！" << endl;
		return;
	}
	catch (double) {
		cout << "输入的下标越界了！" << endl;
		return;
	}
	catch (float) {
		cout << "数组长度太短了，不足以修改下标之间的数据哦！" << endl;
		return;
	}
}

template<class T>
void MyVector<T>::modify(const int pos1, const int pos2, const MyVector& other) {
	try	{
		int beg = 0;
		int end = 0;
		int offset = 0;
		if (pos2 < pos1) {
			offset = pos1 - pos2 + 1;
			beg = pos2;
			end = pos1;
		}
		else if (pos1 < pos2) {
			offset = pos2 - pos1 + 1;
			beg = pos1;
			end = pos2;
		}
		else {
			throw - 1;
		}

		if (offset > this->num) {
			throw static_cast<double>(-1);
		}
		if (other.num < offset) {
			throw static_cast<float>(-1);
		}
		for (int i = 0; i < offset && i < num; i++)	{
			address[beg + i] = other.at(i);
		}
	}
	catch (int)	{
		cout << "输入的下标不可以一样哦！" << endl;
		return;
	}
	catch (double) {
		cout << "输入的下标越界了！" << endl;
		return;
	}
	catch (float) {
		cout << "数组长度太短了，不足以修改下标之间的数据哦！" << endl;
		return;
	}
}

template<class T>
// insertion sort
void MyVector<T>::sort() {
	try {
		for (int i = 1; i < this->num; i++) {
			T key = this->at(i);
			int j = i - 1;
			while ((j >= 0) && (key < this->at(j))) {
				this->modify(j+1, this->at(j));
				j--;
			}
			this->modify(j + 1, key);
		}
	}
	catch (int)	{
		cerr << "没有数据怎么排序啊亲!" << endl;
		return;
	}
}