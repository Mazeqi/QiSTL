#pragma once
#ifndef  _ALLOC_H_
#define  _ALLOC_H_
#include<cstdio>
#include<cstdlib>
/*
	@author : MZQ
	@version: 1.0
	@deprecated : The class is constructed for applying memory for other block; 
*/

namespace QTL {

	class alloc {
	
	private:
		//小型区块的最小值，都是能整除8的
		enum {ALIGN = 8};

		//最大值
		enum{MAX_BYTES = 128};

		//free-list的个数
		enum{NFFREELISTS = MAX_BYTES / ALIGN};

		enum{NOBJS = 20};


	private:

		//将bytes上调到8，区块是按照8bytes为单位分配的
		static size_t ROUND_UP(size_t bytes) {

			//8 = 1000  7 = 0111 , bytes % 8 != 0, 尾巴加上7之后就算取余不为0，也比原来的大。
			return (((bytes)+ALIGN - 1) & ~(ALIGN - 1));
		}

	private:
		//构造空闲结点
		union obj {
			union obj* next;
			char client_data;
		};

	private:
		//16个free-lists,存放的是指向各处的指针
		static obj* volatile free_list[NFFREELISTS];

		//根据区块大小，决定使用第n号free-list
		//n从0开始， 申请空间最大是128 超过128启动一级配置，二级配置最大 128/8 = 16
		static size_t FREELIST_INDEX(size_t bytes) {
			return ((bytes)+ALIGN - 1) / ALIGN - 1;
		}


		//返回一个大小为n的对象，并肯加入大小为n的其他区块到free-list
		static void* refill(size_t n);

		//配置一大块空间，可容纳nobjs个大小为"size"的区块
		//如果配置nobjs个区块有所不便，nobjs可能会降低
		static char* chunk_alloc(size_t size, size_t& nobjs);

		//内存池起始位置，只在chunk_alloc中变换
		static char* start_free;

		//内存池结束位置，只在chunk_alloc中变换
		static char* end_free;

		static size_t heap_size;

	public:
		static void* allocate(size_t n);

		static void deallocate(void* p, size_t n);

		static void* reallocate(void* p, size_t old_sz, size_t new_sz);
	};

};

#endif // ! _ALLOC_H_
