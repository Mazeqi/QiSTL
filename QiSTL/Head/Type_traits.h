#pragma once
#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_
/*
	@author: MZQ
	@version:1.0
*/


namespace QTL {

	namespace {

		template<bool, class Ta, class Tb>
		struct IfThenElse;


		template<class Ta, class Tb>
		struct IfThenElse < true, Ta, Tb > {
			using result = Ta;
		};


		template<class Ta, class Tb>
		struct IfThenElse < false, Ta, Tb > {
			using result = Tb;
		};

	}

	struct true_type{};
	struct false_type{};



	template<class type>
	struct type_traits
	{
		/*
		   我们现在看到的这个type_traits是特殊的。这是为了确保万一编译器也
		   使用一个名为_type_triats 而其实于此处无任何关联的template时，所
		   有事情都正常进行
		*/
		typedef true_type this_dummy_member_must_be_first;
		

		/*
			以下条件应该被遵守，因为编译器有可能自动为各型别产生专属的type_triats
			特化版本
		*/
		typedef false_type    has_trivial_default_constructor;
		typedef false_type    has_trivial_copy_constructor;
		typedef false_type    has_trivial_assignment_operator;
		typedef false_type    has_trivial_destructor;
		typedef false_type    is_POD_type;
	};

	/*
		以下针对基本型别提供特化版本，表示这些型别都可以采用最快速方式，如memcpy来进行
		拷贝或赋值操作
	*/
	template<>
	struct type_traits<bool>
	{
		
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<char>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	

	template<>
	struct type_traits<unsigned char>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<signed char>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<wchar_t>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<short>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<unsigned short>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<int>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};



	template<>
	struct type_traits<unsigned int>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<long>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template<>
	struct type_traits<unsigned long>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template<>
	struct type_traits<long long>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<unsigned long long>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template<>
	struct type_traits<float>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<double>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<long double>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	//-------------------------------------------------------------
	template<class T>
	struct type_traits<T*>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<char*>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<signed char*>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template<>
	struct type_traits<unsigned char*>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<const char*>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<const signed char*>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};


	template<>
	struct type_traits<const unsigned char*>
	{

		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};



}
#endif // !_TYPE_TRAITS_H
