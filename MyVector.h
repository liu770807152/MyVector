// MyVector.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

using namespace std;
template<class T>
class My_Vector
{
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
	explicit My_Vector() { address = nullptr; num = capacity = 0; }
	My_Vector(My_Vector& other) :address(address), capacity(capacity), num(num)
	{
		for (int i = 0; i < other.num; i++)
			*(address + i) = *(other.address + i);
	}
	~My_Vector()
	{
		_clear();
	}
	struct Iterator//迭代器
	{
		T* pt;//指针
		Iterator()//无参构造
		{
			pt = nullptr;
		}
		Iterator(Iterator& other)//拷贝构造
		{
			this->pt = other.pt;
		}
		~Iterator()//析构
		{
			pt = nullptr;
		}
		void operator = (const T* obj)//赋值运算符重载
		{
			pt = (T*)obj;
		}
		T& operator * ()const//解引用运算符重载
		{
			return (*pt);
		}
		Iterator operator + (const int off)//+运算符重载
		{
			return this->pt + off;
		}
		int operator - (Iterator& other)//-运算符重载
		{
			return (this->pt - other.pt);
		}
		int operator - (T* other)//-运算符重载
		{
			return static_cast<int>(this->pt - other);
		}
		Iterator operator - (const int off)//-运算符重载
		{
			return this->pt - off;
		}
		Iterator& operator ++ (int)//后++运算符重载
		{
			Iterator* temp = new Iterator;//临时变量
			temp->pt = this->pt;
			this->pt++;
			return *temp;
		}
		Iterator& operator ++ ()//前++运算符重载
		{
			return ++this->pt;
		}
		Iterator& operator -- (int)//后--运算符重载
		{
			Iterator* temp = new Iterator;//临时变量
			temp->pt = this->pt;
			this->pt--;
			return *temp;
		}
		Iterator& operator -- ()//前--运算符重载
		{
			return 	--this->pt;
		}
		bool operator != (const Iterator& obj)//!=运算符重载
		{
			return (this->pt != obj);
		}
		bool operator != (const T* obj)//!=运算符重载
		{
			return (this->pt != obj);
		}
		Iterator& operator += (const int off)//+=运算符重载
		{
			return pt + off;
		}
		int operator -= (const int off)//-=运算符重载
		{
			return static_cast<int>(pt - off);
		}
		Iterator& operator -= (const Iterator& other)//-=运算符重载
		{
			this->pt = this->pt - other->pt;
			return this->pt;
		}

	};
	/*---------------------------------------以下为<<重载-------------------------------------------*/
	friend ostream& operator << (ostream& os, const My_Vector<T>* dt);
	/*--------------------------------------以下为成员函数------------------------------------------*/
	T* begin()const//求容器始端地址
	{
		return this->address;
	}
	T* end()const//求容器末端地址
	{
		return this->address + num;
	}
	size_t get_capacity()const//求容量大小
	{
		return this->capacity;
	}
	size_t size()const//求元素数量
	{
		return this->num;
	}
	T at(const size_t pos)const//正迭代器：返回所在位置的元素
	{
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
	T at_back(const int pos)const//逆迭代器：返回倒数第几个元素
	{
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
	void insert(const int pos, My_Vector& other);
	//清空数据
	void clear();
	//交换两个vector
	void swap(My_Vector& other);
	//删除迭代器所在位置元素
	void erase(Iterator& it);
	//删除下标所在位置元素
	void erase(const int pos);
	//删除两个下标之间的所有元素
	void erase(const int pos1, const int pos2);
	//修改迭代器所在位置的元素
	void modify(Iterator& it, T&& data);
	//修改下标所在位置的元素
	void modify(const int pos, T&& data);
	//修改两个下标之间的所有元素
	void modify(const int pos1, const int pos2, const T* data_beg, const T* data_end);
	//修改两个下标之间的所有元素
	void modify(const int pos1, const int pos2, const My_Vector& other);
	//根据sign进行升序/降序排序,默认false降序，true升序(quicksort)
	void sort(bool sign);
};

template<class T>
ostream& operator << (ostream& os, const My_Vector<T>* dt)
{
	return os << *dt;
}

template<class T>
void My_Vector<T>::push_back(const T& data)
{
	if (num == capacity)
	{
		capacity += ((capacity >> 1) > 1) ? (capacity >> 1) : 1;//每次开1.5倍内存
		T* temp = new T[num];
		memcpy(temp, address, num * sizeof(T));//临时保存数据
		address = new T[capacity];//重新分配内存
		memcpy(address, temp, num * sizeof(T));//把临时数据拷贝回来
		delete[] temp;
	}
	address[num++] = data;//添加元素
}

template<class T>
void My_Vector<T>::push_front(const T& data)
{
	if (num == capacity)
		capacity += ((capacity >> 1) > 1) ? (capacity >> 1) : 1;//每次开1.5倍内存
	T* temp = new T[num];
	memcpy(temp, address, num * sizeof(T));//临时保存数据
	address = new T[capacity];//重新分配内存
	memcpy(address + 1, temp, num * sizeof(T));//把临时数据拷贝回来
	delete[] temp;
	address[0] = data;//添加元素
	num++;
}

template<class T>
void My_Vector<T>::pop_back()
{
	if (--num != 0)
	{
		T* temp = new T[num];
		for (int i = 0; i < num; i++)
		{
			temp[i] = address[i];//临时保存数据
		}
		address = new T[num];
		for (int i = 0; i < num; i++)
		{
			address[i] = temp[i];//把临时数据拷贝回来
		}
		delete[] temp;
	}
	else
		_clear();
}

template<class T>
void My_Vector<T>::pop_front()
{
	if (--num != 0)
	{
		T* temp = new T[num];
		for (int i = 1; i <= num; i++)
		{
			temp[i - 1] = address[i];//临时保存数据
		}
		address = new T[num];
		for (int i = 0; i < num; i++)
		{
			address[i] = temp[i];//把临时数据拷贝回来
		}
		delete[] temp;
	}
	else
		_clear();
}

template<class T>
T My_Vector<T>::maximum()const//太简单了没有注释
{
	T* at = this->begin();
	if (at)
	{
		T temp = *at;
		for (; at != this->end(); at++)
			if (temp < *at)
				temp = *at;
		return temp;
	}
	else
	{
		cout << "亲容器里没有元素哪来的最大值哇" << endl;
		return;
	}

}

template<class T>
T My_Vector<T>::maximum(T*& pos)const//太简单了没有注释
{
	T* at = this->begin();
	pos = this->address;
	if (at)
	{
		T temp = *at;
		for (; at != this->end(); at++)
			if (temp < *at)
			{
				temp = *at;
				pos = at;
			}
		return temp;
	}
	else
	{
		cout << "亲容器里没有元素哪来的最大值哇" << endl;
		return;
	}
}

template<class T>
T My_Vector<T>::maximum(int pos1, int pos2)const//太简单了没有注释
{
	T temp = this->at(pos1);
	if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0)
	{
		for (int i = pos1; i != pos2; i++)
			if (temp < this->at(i))
			{
				temp = this->at(i);
			}
		return temp;
	}
	else
	{
		cout << "亲下标是不是传错了" << endl;
		return;
	}
}

template<class T>
T My_Vector<T>::maximum(int pos1, int pos2, T*& pos)const//太简单了没有注释
{
	T temp = this->at(pos1);
	pos = this->address + pos1;
	if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0)
	{
		for (int i = pos1; i != pos2; i++)
			if (temp < this->at(i))
			{
				temp = this->at(i);
				pos = this->address + i;
			}
		return temp;
	}
	else
	{
		cout << "亲下标是不是传错了" << endl;
		return;
	}
}

template<class T>
T My_Vector<T>::minimum()const//太简单了没有注释
{
	T* at = this->begin();
	if (at)
	{
		T temp = *at;
		for (; at != this->end(); at++)
			if (temp > *at)
				temp = *at;
		return temp;
	}
	else
	{
		cout << "亲容器里没有元素哪来的最小值哇" << endl;
		return;
	}
}

template<class T>
T My_Vector<T>::minimum(T*& pos)const//太简单了没有注释
{
	T* at = this->begin();
	pos = this->address;
	if (at)
	{
		T temp = *at;
		for (; at != this->end(); at++)
			if (temp > *at)
			{
				temp = *at;
				pos = at;
			}
		return temp;
	}
	else
	{
		cout << "亲容器里没有元素哪来的最小值哇" << endl;
		return;
	}
}

template<class T>
T My_Vector<T>::minimum(int pos1, int pos2)const//太简单了没有注释
{
	try {
		T temp = this->at(pos1);
		if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0)
		{
			for (int i = pos1; i != pos2; i++)
				if (temp > this->at(i))
				{
					temp = this->at(i);
				}
			return temp;
		}
		else throw pos1;
	}
	catch (int)
	{
		cout << "亲下标是不是传错了" << endl;
		return;
	}
}

template<class T>
T My_Vector<T>::minimum(int pos1, int pos2, T*& pos)const//太简单了没有注释
{
	try {
		T temp = this->at(pos1);
		pos = this->address + pos1;
		if (pos1 < (int)num && pos1 >= 0 && pos2 < (int)num && pos2 >= 0)
		{
			for (int i = pos1; i != pos2; i++)
				if (temp < this->at(i))
				{
					temp = this->at(i);
					pos = this->address + i;
				}
			return temp;
		}
		else throw pos1
	}
	catch (int)
	{
		cout << "亲下标是不是传错了" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::assign(int&& _newsize, int&& val)//重新分配内存并初始化
{
	if (num)
		delete[] address;
	address = new T[_newsize];
	this->num = _newsize;//调整num大小
	for (capacity = 1; capacity < num;)
		capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;//调整capacity大小
	for (auto i = this->begin(); i != this->end(); i++)
		*i = val;//初始化
}


template<class T>
void My_Vector<T>::insert(Iterator& it, T&& data)
{
	try {
		int offset = it - address;//计算插入位置距离容器首地址的距离
		if (offset >= 0 && offset < num)
		{
			int i = 0;//定义临时变量
			int size = num - offset;//计算需要临时存储的数据的大小
			if (num == capacity)
				capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;//调整capacity大小
			T* _new = new T[capacity];//申请新的堆内存存vector
			if (size > 0 && size <= num)//防止size出现异常
			{
				T* at = new T[size];//申请堆内存暂存数据
				for (i = 0; i < (num - offset); i++)
					at[i] = address[offset + i];//暂存需要转移的数据
				for (i = 0; i < (num - offset); i++)
					_new[offset + i + 1] = at[i];//存第二段vector(也就是全部后移)
				i = 0;//初始化临时变量(_new要用)
				delete[] at;
			}
			if (offset != 0)
			{
				for (i = 0; i < offset; i++)
				{
					_new[i] = address[i];//存第一段vector
				}
			}
			_new[i] = data;//存插入的数据
			delete[] address;
			address = _new;
			num++;
		}
		else
			throw offset;
	}
	catch (int)
	{
		cout << "插入位置越界啦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::insert(const int pos, T&& data)
{
	try {
		int offset = pos;//计算插入位置距离容器首地址的距离
		if (offset >= 0 && offset < num)
		{
			int i = 0;//定义临时变量
			int size = num - offset;//计算需要临时存储的数据的大小
			if (num == capacity)
				capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;//调整capacity大小
			T* _new = new T[capacity];//申请新的堆内存存vector
			if (size > 1 && size <= num)//防止size出现异常
			{
				T* at = new T[size];//申请堆内存暂存数据
				for (i = 0; i < (num - offset); i++)
					at[i] = address[offset + i];//暂存需要转移的数据
				for (i = 0; i < (num - offset); i++)
					_new[offset + i + 1] = at[i];//存第二段vector(也就是全部后移)
				i = 0;//初始化临时变量(_new要用)
				delete[] at;
			}
			for (i = 0; i < offset; i++)
			{
				_new[i] = address[i];//存第一段vector
			}
			_new[i] = data;//存插入的数据
			delete[] address;
			address = _new;
			num++;
		}
		else
			throw offset;
	}
	catch (int)
	{
		cout << "插入位置越界啦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::insert(const int pos, const T* data_beg, const T* data_end)
{
	try {
		int offset = data_end - data_beg + 1;//计算插入位置距离容器首地址的距离
		if (offset <= 0)
			throw static_cast<float>(-1);
		if (pos >= 0 && pos <= num)//防止越界
		{
			int i = 0;//定义临时变量
			int size = num - pos;//计算需要临时存储的数据的大小
			num += offset;
			if (num >= capacity)
				while (capacity <= num)
					capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;//调整capacity大小
			T* _new = new T[capacity];//申请新的堆内存存vector
			if (size > 0 && size <= num)//防止size出现异常
			{
				T* at = new T[size];//申请堆内存暂存数据
				for (i = 0; i < (num - offset - pos); i++)
					at[i] = address[pos + i];//暂存需要转移的数据
				for (i = 0; i < (num - offset - pos); i++)
					_new[offset + pos + i] = at[i];//存第二段vector(也就是全部后移)
				delete[] at;
			}
			for (i = 0; i < pos; i++)
				_new[i] = address[i];//存第一段vector

			for (i = 0; i < offset; i++)
				_new[pos + i] = data_beg[i];//存插入的数据

			delete[] address;
			address = _new;
		}
		else
			throw - 1;
	}
	catch (int)
	{
		cout << "插入位置越界啦！" << endl;
		return;
	}
	catch (float)
	{
		cout << "数组的下标传错啦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::insert(const int pos, My_Vector& other)
{
	try {
		int offset = other.num;//计算插入位置距离容器首地址的距离
		if (offset <= 0)
			throw static_cast<float>(-1);
		if (pos >= 0 && pos <= num)//防止越界
		{
			int i = 0;//定义临时变量
			int size = num - pos;//计算需要临时存储的数据的大小
			num += offset;
			if (num >= capacity)
				while (capacity <= num)
					capacity += ((capacity >> 2) > 1) ? (capacity >> 2) : 1;//调整capacity大小
			T* _new = new T[capacity];//申请新的堆内存存vector
			if (size > 0 && size <= num)//防止size出现异常
			{
				T* at = new T[size];//申请堆内存暂存数据
				for (i = 0; i < (num - offset - pos); i++)
					at[i] = address[pos + i];//暂存需要转移的数据
				for (i = 0; i < (num - offset - pos); i++)
					_new[offset + pos + i] = at[i];//存第二段vector(也就是全部后移)
				delete[] at;
			}
			for (i = 0; i < pos; i++)
				_new[i] = address[i];//存第一段vector

			for (i = 0; i < offset; i++)
				_new[pos + i] = other.at(i);//存插入的数据

			delete[] address;
			address = _new;
		}
		else
			throw - 1;
	}
	catch (int)
	{
		cout << "插入位置越界啦！" << endl;
		return;
	}
	catch (float)
	{
		cout << "数组的下标传错啦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::clear()//太简单了没有注释
{
	if (num)
		_clear();
}

template<class T>
void My_Vector<T>::swap(My_Vector& other)//太简单了没有注释
{
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
void My_Vector<T>::erase(Iterator& it)
{
	try
	{
		if (num--)
		{
			if (!num)
				_clear();//如果全部元素都删除了就初始化容器
			else
			{
				int offset = it - address;
				for (int i = 0; i < num; i++)
				{
					address[offset + i] = address[offset + i + 1];//将后一个元素覆盖前一个元素
				}
			}
		}
		else throw - 1;
	}
	catch (int)
	{
		cout << "容器里没有元素怎么删除啊亲！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::erase(const int pos)
{
	try
	{
		if (num-- && pos >= 0 && pos < num)
		{
			if (!num)
				_clear();//如果全部元素都删除了就初始化容器
			else
			{
				int offset = pos;
				for (int i = 0; i < num; i++)
				{
					address[offset + i] = address[offset + i + 1];//将后一个元素覆盖前一个元素
				}
			}
		}
		else throw - 1;
	}
	catch (int)
	{
		cout << "容器里没有元素怎么删除啊亲！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::erase(const int pos1, const int pos2)
{
	try
	{
		if (num)//检测容器是否为空
		{
			if (pos1 >= 0 && pos1 < num && pos2 >= 0 && pos2 < num)//检测是否越界
			{
				int beg = 0;
				int end = 0;
				int offset = 0;
				if (pos1 < pos2)
				{
					offset = pos2 - pos1 + 1;//计算下标之间的距离
					beg = pos1;
					end = pos2;
					num -= offset;//更新num
				}
				else if (pos2 < pos1)
				{
					offset = pos1 - pos2 + 1;//计算下标之间的距离
					beg = pos2;
					end = pos1;
					num -= offset;//更新num
				}
				else throw static_cast<float>(-1.0);//检测下标是否不同

				if (!num)
					_clear();//如果全部元素都删除了就初始化容器
				else
					for (int i = 0; i < num + offset - end - 1; i++)
					{
						address[beg + i] = address[end + i + 1];//将区间后一个元素覆盖区间内一个元素
					}
			}
			else throw static_cast<double>(-1.0);
		}
		else throw - 1;
	}
	catch (int)
	{
		cout << "容器里没有元素怎么删除啊亲！" << endl;
		return;
	}
	catch (double)
	{
		cout << "输入的下标越界啦！" << endl;
		return;
	}
	catch (float)
	{
		cout << "输入的下标不可以一样哦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::modify(const int pos, T&& data)//太简单了没有注释
{
	try
	{
		if (pos >= 0 && pos < num)
			address[pos] = data;
		else
			throw - 1;
	}
	catch (int)
	{
		cout << "输入的下标越界啦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::modify(Iterator& it, T&& data)//太简单了没有注释
{
	try
	{
		int pos = it - address;
		if (pos >= 0 && pos < num)
			address[pos] = data;
		else
			throw - 1;
	}
	catch (int)
	{
		cout << "输入的下标越界啦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::modify(const int pos1, const int pos2, const T* data_beg, const T* data_end)//太简单了没有注释
{
	try
	{
		int beg = 0;
		int end = 0;
		int offset = 0;
		if (pos2 < pos1)
		{
			offset = pos1 - pos2 + 1;
			beg = pos2;
			end = pos1;
		}
		else if (pos1 < pos2)
		{
			offset = pos2 - pos1 + 1;
			beg = pos1;
			end = pos2;
		}
		else
			throw - 1;//检测下标是否不同

		if (offset > this->num)
			throw static_cast<double>(-1);
		if (static_cast<int>(data_end - data_beg) < offset)//数组的长度必须大于等于修改的长度
			throw static_cast<float>(-1);

		for (int i = 0; i < offset && i < static_cast<int>(data_end - data_beg); i++)
		{
			address[beg + i] = data_beg[i];
		}
	}
	catch (int)
	{
		cerr << "输入的下标不可以一样哦！" << endl;
		return;
	}
	catch (double)
	{
		cout << "输入的下标越界了！" << endl;
		return;
	}
	catch (float)
	{
		cout << "数组长度太短了，不足以修改下标之间的数据哦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::modify(const int pos1, const int pos2, const My_Vector& other)//太简单了没有注释
{
	try
	{
		int beg = 0;
		int end = 0;
		int offset = 0;
		if (pos2 < pos1)
		{
			offset = pos1 - pos2 + 1;
			beg = pos2;
			end = pos1;
		}
		else if (pos1 < pos2)
		{
			offset = pos2 - pos1 + 1;
			beg = pos1;
			end = pos2;
		}
		else
			throw - 1;//检测下标是否不同

		if (offset > this->num)
			throw static_cast<double>(-1);
		if (other.num < offset)//数组的长度必须大于等于修改的长度
			throw static_cast<float>(-1);

		for (int i = 0; i < offset && i < num; i++)
		{
			address[beg + i] = other.at(i);
		}
	}
	catch (int)
	{
		cout << "输入的下标不可以一样哦！" << endl;
		return;
	}
	catch (double)
	{
		cout << "输入的下标越界了！" << endl;
		return;
	}
	catch (float)
	{
		cout << "数组长度太短了，不足以修改下标之间的数据哦！" << endl;
		return;
	}
}

template<class T>
void My_Vector<T>::sort(bool sign = false)
{
	try {
		if (num)
		{
			T temp = 0;
			if (sign == true)//升序
				for (int gap = num / 2; gap > 0; gap /= 2)
					for (int i = gap; i < num; ++i)
						for (int j = i - gap; j >= 0 && address[j] > address[j + gap]; j -= gap)
						{
							temp = address[j];
							address[j] = address[j + gap];
							address[j + gap] = temp;
						}
			else  //降序
				for (int gap = num / 2; gap > 0; gap /= 2)
					for (int i = gap; i < num; ++i)
						for (int j = i - gap; j >= 0 && address[j] < address[j + gap]; j -= gap)
						{
							temp = address[j];
							address[j] = address[j + gap];
							address[j + gap] = temp;
						}
		}
		else
			throw - 1;
	}
	catch (int)
	{
		cerr << "没有数据怎么排序啊亲!" << endl;
		return;
	}
}