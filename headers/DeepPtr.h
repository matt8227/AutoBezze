	#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>
class DeepPtr
{
   private:
	   T* p;
   public:
	   DeepPtr(T* a = nullptr);
	   DeepPtr(const DeepPtr& a);
	   ~DeepPtr();

	   void setPointer(T* a);
	   void destroyPointer();

	   T& operator*() const;
	   T* operator->() const;
	   T* getPointer() const;

	   DeepPtr& operator=(const DeepPtr<T>& a);
	   bool operator==(const DeepPtr& a) const;

	   explicit operator bool() const;

};

template<class T>
DeepPtr<T>::DeepPtr(T* a) : p(a)
{

}

template<class T>
DeepPtr<T>::DeepPtr(const DeepPtr& a) : p(a->clone())
{

}

template<class T>
DeepPtr<T>::~DeepPtr()
{

	delete p;
}

template<class T>
void DeepPtr<T>::setPointer(T* a)
{
	delete p;
	p = a;
}

template<class T>
void DeepPtr<T>::destroyPointer()
{
	delete p;
	p = nullptr;
}

template<class T>
T& DeepPtr<T>::operator*()  const
{
	return *p;
}

template<class T>
T* DeepPtr<T>::operator->() const
{
	return p;
}

template<class T>
T* DeepPtr<T>::getPointer() const
{
	return p;
}

template<class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr<T>& a)
{
	if(p != a.p )
	{
		if(p!=nullptr) delete p;
		p = a->clone();
	}

	return *this;
}

template<class T>
bool DeepPtr<T>::operator==(const DeepPtr& a) const
{
	return p == a.p;
}

template<class T>
DeepPtr<T>::operator bool() const
{
	return p!=nullptr;
}

#endif //DEEPPTR
