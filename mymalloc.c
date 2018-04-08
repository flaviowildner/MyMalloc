#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>


#define FREE_SIZE sizeof(struct t_BLOCK) //BLOCO LIVRE
#define BLOCK_SIZE sizeof(struct c_BLOCK) //BLOCO OCUPADO
#define SIZE_INIT 2000000000


struct t_BLOCK *base_pointer = NULL;


struct t_BLOCK{ //BLOCO LIVRE
	int size;
	struct t_BLOCK *next;
	struct t_BLOCK *prev;
};

struct c_BLOCK{ //BLOCO OCUPADO
	int size;
};


int MyMallocInit(int size){
	void *retorno = sbrk(0);

	void *request = sbrk(size);
	assert((void*)retorno == request);
	if(request == (void*) -1){
		return 0;
	}
	base_pointer = retorno;
	return 1;
}



struct c_BLOCK *find_free(int size){
	struct t_BLOCK *current = base_pointer;
	struct t_BLOCK *temp = NULL;

	while(current != NULL){
		if(current->size >= size){
			temp = current;

			if(current->size == size){
				if(current == base_pointer){
					base_pointer = temp->next;
					temp->next->prev = NULL;
				}else{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
			}else{
				current = (void*)current + size;
				current->prev = temp->prev;
				current->next = temp->next;
				current->size = temp->size - size;


				if(current->prev != NULL){
					current->prev->next = current;
				}
				if(current->next != NULL){
					temp->next->prev = current;
				}

				if(temp == base_pointer){
					base_pointer = current;
				}
			}

			return (struct c_BLOCK*)temp;
		}
		current = current->next;
	}
	return NULL;
}


void *MyMalloc(int size){
	struct c_BLOCK *retorno;
	struct t_BLOCK *free_block;

	if(size <= 0)
		return NULL;

	size = size + BLOCK_SIZE;

	if(!base_pointer){
		if(MyMallocInit(SIZE_INIT) == 0){
			printf("erro!");
			return NULL;
		}
		retorno = (void*)base_pointer;
		retorno->size = size - BLOCK_SIZE;

		base_pointer = (void*)base_pointer + size;

		free_block = base_pointer;
		free_block->size = SIZE_INIT - size;
		free_block->next = NULL;
		free_block->prev = NULL;
	}else{
		retorno = find_free(size);
		retorno->size = size - BLOCK_SIZE;
		if(retorno == NULL)
			return NULL;

	}
	return retorno + 1;
}

struct c_BLOCK *getBlock(void *ptr){
	return ptr - BLOCK_SIZE;
}


int MyMallocFree(void *ptr){
	struct c_BLOCK *free = getBlock(ptr);
	struct t_BLOCK *free_block = (struct t_BLOCK*)free;
	struct t_BLOCK *current = base_pointer;


	free_block->size = free->size + BLOCK_SIZE;

	while(current->next != NULL && free_block->size < current->size){
		current = current->next;
	}
	if(free_block->size <= current->size){
		free_block->next = current->next;
		free_block->prev = current;
		if(current->next != NULL)
			current->next->prev = free_block;
		current->next = free_block;
	}else if(free_block->size > current->size){
		if(current == base_pointer){
			base_pointer = free_block;
			free_block->prev = NULL;
			free_block->next = current;
			current->prev = free_block;
		}
		else{
			free_block->next = current;
			free_block->prev = current->prev;
			current->prev->next = free_block;
			current->prev = free_block;
		}
	}
	return 1;
}

void mymalloc(void){
	printf("I'm a shared library\n");
}
