#ifndef VETT_H
#define VETT_H

#include <stdexcept>
typedef unsigned int u_int;

template <class T>
class vett
{
	private:
		T* arr;
		u_int size;
		u_int capacity;
	public:
		class iterator;
		class const_iterator;

		class iterator
		{
			protected:
				T* p;

			public:
				iterator(T* a = nullptr): p(a){}

				iterator(const iterator& a) : p(a.p) {}

				T& operator[](int a) const { return p[a]; }

				T& operator*() const { return *p; }

				T* operator->() const { return p; }

				iterator& operator++()
				{
					p = p + 1;
					return *this;
				}

				iterator operator++(int)
				{
					iterator tmp(*this);
					operator++();
					return tmp;
				}

				iterator& operator--()
				{
					p = p - 1;
					return *this;
				}

				iterator operator--(int)
				{
					iterator tmp(*this);
					operator--();
					return tmp;
				}

				iterator operator+(int a) const { return iterator(p + a ); }

				iterator operator-(int a) const { return iterator(p - a ); }

				iterator& operator+=(int a)
				{
					p += a;
					return *this;
				}

				iterator& operator-=(int a)
				{
					p -= a;
					return *this;
				}

				bool operator==(const iterator& a) const { return p == a.p; }

				bool operator!=(const iterator& a) const { return p != a.p; }

				bool operator>(const iterator& a) const { return p > a.p; }

				bool operator>=(const iterator& a) const { return p >= a.p; }

				bool operator<(const iterator& a) const { return p < a.p; }

				bool operator<=(const iterator& a) const { return p <= a.p; }

				operator const_iterator()
				{
					return const_iterator(p);
				}

		};

		class const_iterator
		{
			protected:
				T* p;
			public:
				const_iterator(T* a = nullptr) : p(a){}

				const_iterator(const const_iterator& a) : p(a.p){}

				const T* operator ->() const { return p; }

				const T& operator[](int a) const { return p[a]; }

				const T& operator*() const { return *p; }

				const_iterator& operator++()
				{
					p = p + 1;
					return *this;
				}

				const_iterator operator++(int)
				{
					const_iterator tmp(*this);
					operator++();
					return tmp;
				}

				const_iterator& operator--()
				{
					p = p - 1;
					return *this;
				}

				const_iterator operator--(int)
				{
					const_iterator tmp(*this);
					operator--();
					return tmp;
				}

				const_iterator operator+(int a) const { return const_iterator(p + a ); }

				const_iterator operator-(int a) const {	return const_iterator(p - a ); }

				const_iterator& operator+=(int a)
				{
					p += a;
					return *this;
				}

				const_iterator& operator-=(int a)
				{
					p -= a;
					return *this;
				}

				bool operator==(const const_iterator& a) const { return p == a.p; }

				bool operator!=(const const_iterator& a) const { return p != a.p; }

				bool operator>(const const_iterator& a) const { return p > a.p; }

				bool operator>=(const const_iterator& a) const { return p >= a.p; }

				bool operator<(const const_iterator& a) const { return p < a.p; }

				bool operator<=(const const_iterator& a) const { return p <= a.p; }

				operator iterator()
				{
					return iterator(p);
				}

		};

		vett(u_int s = 0);

		vett(T init, u_int s = 0);

		vett(const vett& v);

		~vett();

		vett& operator=(const vett &v);


		u_int getSize() const;

		u_int getCapacity() const;

		bool empty() const;

		void resize(int requested_size);

		T& at(u_int a);

		void reserve(u_int n);

		T& operator[] (u_int n);

		const T& operator[] (u_int n) const;

		T& getFirst();

		const T& getFirst() const;

		T& getLast();

		const T& getLast() const;

		void assign(u_int s, const T& val);

		void shrink_to_fit();

		void push_back(const T& a);

		void pop_back();

		void insert(iterator pos, const T& val);

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		iterator erase(const_iterator pos);

		void swap(vett& a);

		void clear();

		u_int distanza_da_begin(iterator i) const;


};





template<class T>
vett<T>::vett(u_int s) : arr(new T[s==0 ? 1: s]), size(0), capacity(s == 0 ? 1 : s) //Per convenienza, conviene avere sempre capacity diversa da zero, cosÃ¬ quando serve la raddoppio semplicemente
{
}

template<class T>
vett<T>::vett(T init, u_int s) : arr(new T[s==0 ? 1: s]), size(s), capacity(s == 0 ? 1 : s)
{
	for(u_int i = 0; i<s; i++)
	{
		arr [i] = init;
	}
}

template<class T>
vett<T>::vett(const vett& v): arr(new T[v.size]), size(v.size), capacity(v.capacity)
{
	for(u_int i = 0; i<v.size; i++)
	{
		arr[i] = v.arr[i];
	}
}

template<class T>
vett<T>::~vett()
{

	delete[] arr;
}

template<class T>
vett<T>& vett<T>::operator=(const vett& v)
{
	if(this == &v)
		return *this;

	delete[] arr;
	capacity = v.capacity;
	size = v.size;
	arr = new T[capacity]; //NON size
	for(u_int i=0; i<size; i++)
	{
		arr[i] = v.arr[i];
	}

	return *this;
}

template<class T>
u_int vett<T>::getSize() const
{
	return size;
}

template<class T>
u_int vett<T>::getCapacity() const
{
	return capacity;
}

template<class T>
bool vett<T>::empty() const //ritorna true sse size = 0;
{
	return !size;
}

template<class T>
void vett<T>::resize(int requested_size)
{
	if(requested_size > capacity)
		reserve(requested_size);

	size = requested_size;
}

template<class T>
T& vett<T>::at(u_int a)
{
	return arr[a];
}

template<class T>
void vett<T>::reserve(u_int n)
{
	if(capacity<n)
	{
		T* tmp = new T[n];
		for(u_int i=0; i<size; i++)
			tmp[i] = arr[i];
		delete[] arr;
		arr = tmp;
		capacity = n;
	}
}

template<class T>
T& vett<T>::operator[](u_int n)
{
	if(n<size)
	{
		return arr[n];
	}
	else
		throw std::out_of_range("Index larger than vector size");
}

template<class T>
const T& vett<T>::operator[](u_int n) const
{
	if(n<size)
	{
		return arr[n];
	}
	else
		throw std::out_of_range("Index larger than vector size");
}

template<class T>
T& vett<T>::getFirst()
{
	if(size != 0)
		return arr[0];
}

template<class T>
const T& vett<T>::getFirst() const
{
	if(size != 0)
		return arr[0];
}

template<class T>
T& vett<T>::getLast()
{
	if(size != 0)
		return arr[size-1];
}

template<class T>
const T& vett<T>::getLast() const
{
	if(size != 0)
		return arr[size-1];
}

template<class T>
void vett<T>::assign(u_int s, const T& val)
{
	if(capacity < s)
	{
		delete[] arr;
		arr = new T[s];
		capacity = s;
	}

	for(int i = 0; i < s; i++)
		arr [i] = val;

	size = s;
}

template<class T>
void vett<T>::shrink_to_fit()
{
	if(capacity>size)
	{
		T* tmp = new T[size];
		for(u_int i = 0; i<size; i++)
			tmp [i] = arr [i];
		delete[] arr;
		arr = tmp;
	}
}

template<class T>
void vett<T>::push_back(const T& a)
{
	if(size<capacity)
	{
		arr[size] = a;
		size++;
	}
	else
	{
		T* tmp = new T[capacity*2];
		for(u_int i = 0; i<size; i++)
			tmp [i] = arr [i];
		tmp[size] = a;
		delete[] arr;
		arr = tmp;
		size++;
		capacity = capacity*2;
	}
}

template<class T>
void vett<T>::pop_back() //EXCEPTION HANDLING: A FALSE SENSE OF SECURITY by Tom Cargill
{
	if(size != 0)
	{
		delete arr[size-1];
		size--;
	}
}

template<class T>
void vett<T>::insert(vett::iterator pos, const T& val)
{
	int a = distanza_da_begin(pos);
	if(a<0)
		throw std::out_of_range("Iterator position cannot be less than begin()");
	if(a>=capacity)
		throw std::out_of_range("Iterator position cannot be equal or greater than capacity");
	if(a >= size)
	{
		size = a+1;
		arr[a] = val;
		return;
	}


	T* tmp;
	if(capacity == size)
	{
		tmp = new T[capacity+1];
		capacity++;
	}
	else
	{
		tmp = new T[capacity];
	}

	size++;

	for(u_int i = 0; i<a; i++)
		tmp [i] = arr[i];

	tmp[a] = val;

	for(u_int i = a+1; i<size; i++)
		tmp [i] = arr[i-1];

	delete[] arr;
	arr = tmp;
}

template<class T>
typename vett<T>::iterator vett<T>::begin()
{
	return iterator(arr);
}

template<class T>
typename vett<T>::const_iterator vett<T>::begin() const
{
	return const_iterator(arr);
}

template<class T>
typename vett<T>::iterator vett<T>::end()
{
	return iterator(arr+size);
}

template<class T>
typename vett<T>::const_iterator vett<T>::end() const
{
	return const_iterator(arr+size);
}

template<class T>
typename vett<T>::iterator vett<T>::erase(vett::const_iterator pos)
{
	iterator tmp = pos;
	u_int d = distanza_da_begin(pos);

	for(u_int i = d; i<size-1; i++)
	{
		arr[i] = arr[i+1];
	}

	size = size - 1;
	return tmp;
}

template<class T>
void vett<T>::swap(vett& a)
{
	if(this != &a)
	{
		T* tmp = a.arr;
		a.arr = arr;
		arr = tmp;

		std::swap(size,a.size);
		std::swap(capacity,a.capacity);
	}
}

template<class T>
void vett<T>::clear()
{
	delete[] arr;
	arr = new T[1];
	size = 0;
	capacity = 1;

}

template<class T>
u_int vett<T>::distanza_da_begin(vett::iterator i) const
{
	int a = 0;
	while(i != begin())
	{
		i--;
		a++;
	}
	return a;
}
#endif // VETT_H
