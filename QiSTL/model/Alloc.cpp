#include "../Head/Alloc.h"

namespace QTL {
	char* alloc::start_free = 0;
	char* alloc::end_free = 0;
	size_t alloc::heap_size = 0;

	alloc::obj* volatile alloc::free_list[alloc::NFFREELISTS] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};


	void *alloc::allocate(size_t bytes) {

		//����ָ��
		obj* volatile*  my_free_list;
		obj* result;


		//����128�͵���һ��������
		if (bytes > (size_t)MAX_BYTES) {
			return malloc(bytes);
		}

		//Ѱ��16��free-lists���ʵ���һ��
		my_free_list = free_list + FREELIST_INDEX(bytes);
		result = *my_free_list;

		if (my_free_list) {
			*my_free_list = result->next;
			return result;
		}
		else {
			//���ڴ��ȡ��
			return refill(ROUND_UP(bytes));
		}
	}

	void alloc::deallocate(void *ptr, size_t bytes) {

		if (bytes > (size_t)MAX_BYTES) {
			free(ptr);
			return;
		}
		else {
			size_t index = FREELIST_INDEX(bytes);

			//��ʽ����ת��
			obj* node = static_cast<obj*>(ptr);
			node->next = free_list[index];
			free_list[index] = node;
		}
	}

	void* alloc::reallocate(void* ptr, size_t old_sz, size_t new_sz) {
		deallocate(ptr, old_sz);
		ptr = allocate(new_sz);

		return ptr;
	}
}