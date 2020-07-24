#include "../Head/Alloc.h"

namespace QTL {
	char* alloc::start_free = 0;
	char* alloc::end_free = 0;
	size_t alloc::heap_size = 0;

	alloc::obj* volatile alloc::free_list[alloc::NFFREELISTS] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};


	void *alloc::allocate(size_t bytes) {

		//二级指针
		obj* volatile*  my_free_list;
		obj* result;


		//大于128就调用一级置配器
		if (bytes > (size_t)MAX_BYTES) {
			return malloc(bytes);
		}

		//寻找16个free-lists中适当的一个
		my_free_list = free_list + FREELIST_INDEX(bytes);
		result = *my_free_list;

		if (my_free_list) {
			*my_free_list = result->next;
			return result;
		}
		else {
			//从内存池取出
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

			//隐式类型转化
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

		//从内存池里取，调用chunk_alloc，尝试获得nobjs个区块作为free-list的新结点
		char* chunk = chunk_alloc(bytes, nobjs);

		obj* volatile* my_free_list;
		obj* result;
		obj* current_obj, * next_obj;

		//如果只获得一个区块，这个区块就分配给调用者用，free-list无新节点
		if (nobjs == 1) {
			return (chunk);
		}

		//否则调整free-list， 纳入新节点
		my_free_list = free_list + FREELIST_INDEX(bytes);


		/*
			接下来这一区在chunk空间内建立free-list
		*/

		//这一块准备返回给客户端
		result = (obj*)chunk;

		//以下导引free-list指向新配置的空间（取自内存池）
		*my_free_list = next_obj = (obj*)(chunk + bytes);

		//以下将free-list 的各节点串接起来
		//从第一个开始，因为第0个返回给客户端了
		for (int i = 1;; i++) {
			current_obj = next_obj;
			//地址被转化为char*之后，若pointer++就这是移动一个char，即一个字节
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

	//内存池
	char* alloc::chunk_alloc(size_t bytes, size_t& nobjs) {
		char* result;

		//一个list需要分配的总字节数
		size_t list_total_bytes = bytes * nobjs;

		//指针相减会得到多少个元素的差距
		size_t bytes_left = end_free - start_free;

		if (bytes_left >= list_total_bytes) {
			//内存池剩余空间完全满足需要
			result = start_free;
			start_free += list_total_bytes;

			return(result);
		}
		else if(bytes_left >= bytes){
			//内存池剩余空间不能完全满足需求量，但足够供应一个（含）以上的区块
			nobjs = bytes_left / bytes;
			list_total_bytes = bytes * nobjs;
			result = start_free;

			start_free += list_total_bytes;
			return result;
		}
		else {
			//内存池剩余的空间连一个区块的大小都无法满足
			//需要移位的数字>>移位的次数n
			size_t bytes_to_get = 2 * list_total_bytes + ROUND_UP(heap_size >> 4);

			if (bytes_left > 0) {
				//内存池还有一些零头，先配给适当的free-list
				//首先寻找适当的free-list
				obj* volatile* my_free_list = free_list + FREELIST_INDEX(bytes_left);

				//调整free-list，将内存池中的残余空间编入
				((obj*)start_free)->next = *my_free_list;
				*my_free_list = (obj*)start_free;
			}

			//配置heap空间，补充内存池
			start_free = (char*)malloc(bytes_to_get);

			//内存空间不足
			if (!start_free) {
				//heap空间不足， malloc失败
				obj* volatile* my_free_list, * p;

				//试着检查我们手上拥有的东西，这不会造成伤害，在这里并不打算尝试配置
				for (int i = bytes; i <= MAX_BYTES; i += ALIGN) {
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;

					//free-list内还有未用的区块
					//调整free-list释放出未用区块
					if (p != 0) {
						*my_free_list = p->next;
						start_free = (char*)p;
						end_free = start_free + i;
						
						//递归调用，修正nobjs
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