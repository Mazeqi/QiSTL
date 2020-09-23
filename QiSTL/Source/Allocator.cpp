#include "../Head/Allocator.h"

namespace QTL {

	template <class T>
	T* allocator<T>::allocate() {
		/*
			这里可以有两种方式，直接用new或者调用alloc
		*/

		//return static_cast<T*>(QTL::allocate(sizeof(T)));
		return static_cast<T*>(::operator new(sizeof(T)));
	}

	template <class T>
	T* allocator<T>::allocate(size_type n) {
		if (n == 0) {
			return nullptr;
		}

		//return static_cast<T*>(QTL::allocate(n * sizeof(T)));
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	template <class T>
	void allocator<T>::deallocate(T* ptr) {
		if (ptr == nullptr) {
			return;
		}

		//QTL::deallocate(static_cast<void *>(ptr), sizeof(T));
		::operator delete(ptr);
	}

	template <class T>
	void allocator<T>::deallocate(T* ptr, size_type n) {
		if (ptr == nullptr) {
			return;
		}

		//QTL::deallocate(static_cast<void *>(ptr),n * sizeof(T));
		::operator delete(ptr);
	}
	
	template<class T>
	void allocator<T>::construct(T* ptr){
		QTL::construct(ptr);
	}

	template<class T>
	void allocator<T>::construct(T* ptr, const T& value){
		QTL::construct(ptr, value);
	}

	template<class T>
	void allocator<T>::construct(T* ptr, T&& value){
		QTL::construct(ptr, QTL::move(value));
	}

	template<class T>
	template<class ...Args>
	inline void allocator<T>::construct(T* ptr, Args && ...args) {
		QTL::construct(ptr, QTL::forward(args)...);
	}

	template <class T>
	void allocator<T>::destroy(T* ptr)
	{
		QTL::destroy(ptr);
	}

	template <class T>
	void allocator<T>::destroy(T* first, T* last)
	{
		QTL::destroy(first, last);
	}


}
