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

	void* alloc::refill(size_t bytes) {
		size_t nobjs = NOBJS;

		//���ڴ����ȡ������chunk_alloc�����Ի��nobjs��������Ϊfree-list���½��
		char* chunk = chunk_alloc(bytes, nobjs);

		obj* volatile* my_free_list;
		obj* result;
		obj* current_obj, * next_obj;

		//���ֻ���һ�����飬�������ͷ�����������ã�free-list���½ڵ�
		if (nobjs == 1) {
			return (chunk);
		}

		//�������free-list�� �����½ڵ�
		my_free_list = free_list + FREELIST_INDEX(bytes);


		/*
			��������һ����chunk�ռ��ڽ���free-list
		*/

		//��һ��׼�����ظ��ͻ���
		result = (obj*)chunk;

		//���µ���free-listָ�������õĿռ䣨ȡ���ڴ�أ�
		*my_free_list = next_obj = (obj*)(chunk + bytes);

		//���½�free-list �ĸ��ڵ㴮������
		//�ӵ�һ����ʼ����Ϊ��0�����ظ��ͻ�����
		for (int i = 1;; i++) {
			current_obj = next_obj;
			//��ַ��ת��Ϊchar*֮����pointer++�������ƶ�һ��char����һ���ֽ�
			next_obj = (obj*)((char*)next_obj + bytes);
			if (nobjs - 1 == i) {
				current_obj->next = 0;
				break;
			}
			else {
				current_obj->next = next_obj;
			}

		}
		return result;
	}

	//�ڴ��
	char* alloc::chunk_alloc(size_t bytes, size_t& nobjs) {
		char* result;

		//һ��list��Ҫ��������ֽ���
		size_t list_total_bytes = bytes * nobjs;

		//ָ�������õ����ٸ�Ԫ�صĲ��
		size_t bytes_left = end_free - start_free;

		if (bytes_left >= list_total_bytes) {
			//�ڴ��ʣ��ռ���ȫ������Ҫ
			result = start_free;
			start_free += list_total_bytes;

			return(result);
		}
		else if(bytes_left >= bytes){
			//�ڴ��ʣ��ռ䲻����ȫ���������������㹻��Ӧһ�����������ϵ�����
			nobjs = bytes_left / bytes;
			list_total_bytes = bytes * nobjs;
			result = start_free;

			start_free += list_total_bytes;
			return result;
		}
		else {
			//�ڴ��ʣ��Ŀռ���һ������Ĵ�С���޷�����
			//��Ҫ��λ������>>��λ�Ĵ���n
			size_t bytes_to_get = 2 * list_total_bytes + ROUND_UP(heap_size >> 4);

			if (bytes_left > 0) {
				//�ڴ�ػ���һЩ��ͷ��������ʵ���free-list
				//����Ѱ���ʵ���free-list
				obj* volatile* my_free_list = free_list + FREELIST_INDEX(bytes_left);

				//����free-list�����ڴ���еĲ���ռ����
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}

			//����heap�ռ䣬�����ڴ��
			start_free = (char*)malloc(bytes_to_get);

			//�ڴ�ռ䲻��
			if (!start_free) {
				//heap�ռ䲻�㣬 mallocʧ��
				obj* volatile* my_free_list, * p;

				//���ż����������ӵ�еĶ������ⲻ������˺��������ﲢ�����㳢������
				for (int i = bytes; i <= MAX_BYTES; i += ALIGN) {
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;

					//free-list�ڻ���δ�õ�����
					//����free-list�ͷų�δ������
					if (p != 0) {
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						
						//�ݹ���ã�����nobjs
						return(chunk_alloc(bytes, nobjs));
					}
				}
				end_free = 0;
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(bytes, nobjs);
		}

	}
}