#pragma once
#ifndef  _ALLOC_H_
#define  _ALLOC_H_
#include<cstdio>

/*
	@author : MZQ
	@version: 1.0
	@deprecated : The class is constructed for applying memory for other block; 
*/

namespace QTL {

	class alloc {
	
	private:
		//С���������Сֵ������������8��
		enum {ALIGN = 8};

		//���ֵ
		enum{MAX_BYTES = 128};

		//free-list�ĸ���
		enum{NFFREELISTS = MAX_BYTES / ALIGN};


	private:

		//��bytes�ϵ���8�������ǰ���8bytesΪ��λ�����
		static size_t ROUND_UP(size_t bytes) {

			//8 = 1000  7 = 0111 , bytes % 8 != 0, β�ͼ���7֮�����ȡ�಻Ϊ0��Ҳ��ԭ���Ĵ�
			return (((bytes)+ALIGN - 1) & ~(ALIGN - 1));
		}

	private:
		//������н��
		union obj {
			union obj* next;
			char client_data;
		};

	private:
		//16��free-lists
		static obj* volatile free_list[NFFREELISTS];

		//���������С������ʹ�õ�n��free-list��n��0��ʼ
		static size_t FREELIST_INDEX(size_t bytes) {
			return ((bytes)+ALIGN - 1) / ALIGN - 1;
		}


		//����һ����СΪn�Ķ��󣬲��ϼ����СΪn���������鵽free-list
		static void* refill(size_t n);

		//����һ���ռ䣬������nobjs����СΪ"size"������
		//�������nobjs�������������㣬nobjs���ܻή��
		static char* chunk_alloc(size_t size, int& nobjs);

		//�ڴ����ʼλ�ã�ֻ��chunk_alloc�б任
		static char* start_free;

		//�ڴ�ؽ���λ�ã�ֻ��chunk_alloc�б任
		static char* end_free;

		static size_t heap_size;

	public:
		static void* allocate(size_t n);

		static void deallocate(void* p, size_t n);

		static void* reallocate(void* p, size_t old_sz, size_t new_sz);
	};

};

#endif // ! _ALLOC_H_
