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
	//���ֵ���������


	//ֻ��
	struct input_iterator_tag{};

	//ֻд
	struct output_iterator_tag{};

	//����д���͡��㷨����replace�� �ڴ��ֵ��������γɵ������Ͻ��ж�д����
	struct forward_iterator_tag:public input_iterator_tag{};

	//��˫���ƶ���ĳЩ�㷨��Ҫ�����߷�ĳ������������(�����򿽱�ĳ��Χ��Ԫ��)
	struct bidirectional_iterator_tag:public forward_iterator_tag{};

	//������������ ��p+n, p-n, p[n], p1 - p2, p1 < p2
	struct random_access_iterator_tag:public bidirectional_iterator_tag{};



	//������������̳У���һ��ģ��
	//ptrdiff_t���ͱ���ͨ��������������ָ����������Ľ��
	template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
		struct iterator {
		/*
			value type ��ָ��������ָ��������ͣ��κ�һ��������STL�㷨�����������class
			��Ӧ�ö����Լ���value type��Ƕ����
		*/
		typedef T			  value_type;

		/*
			������ʾ����������֮��ľ��룬�����Ҳ����������ʾһ���������������
		*/
		typedef Distance	  difference_type;

		/*
			�������ã����������޸�������ֵ
		*/
		typedef Reference	  reference;

		/*
			��reference���й���������ָ����ָ��Ķ���ĵ�ַ
		*/
		typedef Pointer		  pointer;

		/*
			������������
		*/
		typedef Category      iterator_category;

	};


	//ե֭��
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category  iterator_category;
		typedef typename Iterator::value_type		  value_type;
		typedef typename Iterator::difference_type	  difference_type;
		typedef typename Iterator::pointer			  pointer;
		typedef typename Iterator::reference		  reference;
	};


	//���native pointer��traitsƫ�ػ�
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};


	//���pointer-to-const��traitsƫ�ػ�
	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};


	//����ĳ��������������
	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	//����ĳ����������distance type
	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
		distance_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//����ĳ����������value_type
	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}


	//---------------------------------------------------------------------------------------
	//distance

	//����ģ�壬���һ�������ܹ�ȷ�����ص�����,�Ӷ�ѡ��ĳ������
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
	//�������
	class reverse_iterator {

	private:

		//��¼��Ӧ�����������
		Iterator current;

	public:
		//�������������������
		typedef typename iterator_traits<Iterator>::iterator_category  iterator_category;
		typedef typename iterator_traits<Iterator>::value_type		   value_type;
		typedef typename iterator_traits<Iterator>::difference_type	   difference_type;
		typedef typename iterator_traits<Iterator>::pointer			   pointer;
		typedef typename iterator_traits<Iterator>::reference		   reference;

		typedef Iterator											   iterator_type;
		typedef reverse_iterator<Iterator>							   self;

	public:
		//���캯��
		reverse_iterator() {};
		explicit reverse_iterator(iterator_type i) :current(i) {}
		reverse_iterator(const self& rhs):current(rhs.current){}


	public:
		//ȡ����Ӧ�����������
		iterator_type base()const {
			return current;
		}

		// ʵ�ʶ�Ӧ�����������ǰһ��λ��
		reference operator*() const {
			Iterator tmp = current;
			return *--tmp;
		}

		pointer operator->()const {
			return &(operator*());
		}

		//�����ǰ����ɺ���
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
	//���رȽϲ�����
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
