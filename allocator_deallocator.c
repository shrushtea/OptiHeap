#include <stdio.h>
#include <stddef.h>

#define MEM_SIZE 1024

typedef struct Chunk {
    size_t size;
    struct Chunk* next;
    int tag;
} Chunk;

#define CHUNK_OVERHEAD sizeof(Chunk)

static char memory[MEM_SIZE];
static Chunk* free_list = NULL;

void setup_memory() {
    free_list = (Chunk*)memory;
    free_list->size = MEM_SIZE - CHUNK_OVERHEAD;
    free_list->next = NULL;
    free_list->tag = 999;
}

void* alloc_mem(size_t requested) {
    Chunk* current = free_list;
    Chunk* previous = NULL;

    while (current) {
        if (current->size >= requested) {
            if (current->size >= requested + CHUNK_OVERHEAD + 4) {
                Chunk* remainder = (Chunk*)((char*)current + CHUNK_OVERHEAD + requested);
                remainder->size = current->size - requested - CHUNK_OVERHEAD;
                remainder->tag = 999;
                remainder->next = current->next;

                current->size = requested;
                current->next = NULL;

                if (previous)
                    previous->next = remainder;
                else
                    free_list = remainder;
            } else {
                if (previous)
                    previous->next = current->next;
                else
                    free_list = current->next;
            }

            return (char*)current + CHUNK_OVERHEAD;
        }

        previous = current;
        current = current->next;
    }

    return NULL;
}

void free_mem(void* ptr) {
    if (!ptr) return;

    Chunk* to_free = (Chunk*)((char*)ptr - CHUNK_OVERHEAD);
    to_free->next = free_list;
    free_list = to_free;
}

int main() {
    setup_memory();

    void* a = alloc_mem(32);
    void* b = alloc_mem(4);

    free_mem(b);

    return 0;
}
