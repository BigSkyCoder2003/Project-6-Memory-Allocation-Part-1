#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "myalloc.h"
//Daniel Lounsbury
#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

struct block *head = NULL;

void *myalloc(int size){
  if (head == NULL){
void *heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
                  MAP_ANON|MAP_PRIVATE, -1, 0);
    head = (struct block *)heap;
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
    head->next = NULL;
}

struct block *current = head;
while(current != NULL){
if(!current->in_use && current->size >= size){
  current->in_use = 1;
  return PTR_OFFSET(current, PADDED_SIZE(sizeof(struct block)));
}
  current = current->next;
}
return NULL;


}

void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

int main(){

void *p;
void *n;

print_data();
p = myalloc(16);
print_data();

}