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
		   �������ڿ��������type_traits������ġ�����Ϊ��ȷ����һ������Ҳ
		   ʹ��һ����Ϊ_type_triats ����ʵ�ڴ˴����κι�����templateʱ����
		   �����鶼��������
		*/
		typedef true_type this_dummy_member_must_be_first;
		

		/*
			��������Ӧ�ñ����أ���Ϊ�������п����Զ�Ϊ���ͱ����ר����type_triats
			�ػ��汾
		*/
		typedef false_type    has_trivial_default_constructor;
		typedef false_type    has_trivial_copy_constructor;
		typedef false_type    has_trivial_assignment_operator;
		typedef false_type    has_trivial_destructor;
		typedef false_type    is_POD_type;
	};

	/*
		������Ի����ͱ��ṩ�ػ��汾����ʾ��Щ�ͱ𶼿��Բ�������ٷ�ʽ����memcpy������
		������ֵ����
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
