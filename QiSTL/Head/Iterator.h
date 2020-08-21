#pragma once
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include<cstddef>

/*
	@author : MZQ
	@version: 1.0
	@deprecated : The class is constructed for iterating object for other block;
*/

namespace QTL {

	//*---------------------------------------------------------------------------------------
	//五种迭代器类型


	//只读
	struct input_iterator_tag{};

	//只写
	struct output_iterator_tag{};

	//允许‘写入型’算法，如replace， 在此种迭代器所形成的区间上进行读写操作
	struct forward_iterator_tag:public input_iterator_tag{};

	//可双向移动。某些算法需要逆向走访某个迭代器区间(如逆向拷贝某范围的元素)
	struct bidirectional_iterator_tag:public forward_iterator_tag{};

	//涵盖算术能力 如p+n, p-n, p[n], p1 - p2, p1 < p2
	struct random_access_iterator_tag:public bidirectional_iterator_tag{};



	//这个类用来被继承，是一个模板
	//ptrdiff_t类型变量通常用来保存两个指针减法操作的结果
	template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
		struct iterator {
		/*
			value type 是指迭代器所指对象的类型，任何一个打算与STL算法有完美搭配的class
			都应该定义自己的value type内嵌类型
		*/
		typedef T			  value_type;

		/*
			用来表示两个迭代器之间的距离，因此它也可以用来表示一个容器的最大容量
		*/
		typedef Distance	  difference_type;

		/*
			传回引用，这样才能修改所带的值
		*/
		typedef Reference	  reference;

		/*
			和reference密切关联，传回指针所指向的对象的地址
		*/
		typedef Pointer		  pointer;

		/*
			迭代器的种类
		*/
		typedef Category      iterator_category;

	};


	//榨汁机
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category  iterator_category;
		typedef typename Iterator::value_type		  value_type;
		typedef typename Iterator::difference_type	  difference_type;
		typedef typename Iterator::pointer			  pointer;
		typedef typename Iterator::reference		  reference;
	};


	//针对native pointer的traits偏特化
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};


	//针对pointer-to-const的traits偏特化
	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};


	//决定某个迭代器的类型
	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	//决定某个迭代器的distance type
	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
		distance_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//决定某个迭代器的value_type
	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}


	//---------------------------------------------------------------------------------------
	//distance

	//重载模板，最后一个参数能够确定重载的类型,从而选择某个函数
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first, InputIterator last, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}


	template <class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
		_distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
		return last - first;
	}


	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
		return _distance(first, last, iterator_category(first));
	}




	//------------------------------------------------------------------------------------------------
	//advance

	template<class InputIterator, class Distance>
	inline void _advance(InputIterator& i, Distance n, input_iterator_tag) {
		while (n--) {
			++i;
		} 
	}


	template <class BidirectionalIterator, class Distance>
	inline void _advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
		if (n >= 0) {
			while (n--) {
				++i;
			}
		}
		else {
			while (n++) {
				--i;
			}
		}
	}


	template <class RandomAccessIterator, class Distance>
	inline void _advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
		i += n;
	}



	template <class InputIterator, class Distance>
	inline void advance(InputIterator& i, Distance n) {
		_advance(i, n, iterator_category(i));
	}


	//----------------------------------------------------------------------------------
	//reverse_iterator
	
	template <class Iterator>
	//反向迭代
	class reverse_iterator {

	private:

		//记录对应的正向迭代器
		Iterator current;

	public:
		//反向迭代器的五种类型
		typedef typename iterator_traits<Iterator>::iterator_category  iterator_category;
		typedef typename iterator_traits<Iterator>::value_type		   value_type;
		typedef typename iterator_traits<Iterator>::difference_type	   difference_type;
		typedef typename iterator_traits<Iterator>::pointer			   pointer;
		typedef typename iterator_traits<Iterator>::reference		   reference;

		typedef Iterator											   iterator_type;
		typedef reverse_iterator<Iterator>							   self;

	public:
		//构造函数
		reverse_iterator() {};
		explicit reverse_iterator(iterator_type i) :current(i) {}
		reverse_iterator(const self& rhs):current(rhs.current){}


	public:
		//取出对应的正向迭代器
		iterator_type base()const {
			return current;
		}

		// 实际对应正向迭代器的前一个位置
		reference operator*() const {
			Iterator tmp = current;
			return *--tmp;
		}

		pointer operator->()const {
			return &(operator*());
		}

		//反向后，前进变成后退
		self& operator++() {
			--current;
			return *this;
		}

		self operator++(int) {
			self tmp = *this;
			--current;
			return tmp;
		}

		self& operator--() {
			++current;
			return *this;
		}

		self operator--(int) {
			self tmp = *this;
			++current;
			return tmp;
		}

		self& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		self operator+(difference_type n) const
		{
			return self(current - n);
		}

		self& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		self operator-(difference_type n) const
		{
			return self(current + n);
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

	};


	//----------------------------------------------------------------------------------------------------------
	//重载比较操作符
	template<class Iterator>
	bool operator==(const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y) {
		return x.base() == y.base();
	}

	//x<y
	template<class Iterator>
	bool operator<(const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y) {
		return x.base() < y.base();
	}

	//x!=y
	template<class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y) {
		return !(x == y);
	}

	//x>y
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return y < x;
	}

	//x<=y
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return !(y < x);
	}

	//x>=y
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return !(x < y);
	}

}
#endif // !_ITERATOR_H_
