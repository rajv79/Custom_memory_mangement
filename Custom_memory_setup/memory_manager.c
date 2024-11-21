/*
 * CS 551 Project "Memory manager".
 * This file needs to be turned in.	
 */


#include "memory_manager.h"

static STRU_MEM_LIST * mem_pool = NULL;

/*
 * Print out the current status of the memory manager.
 * Reading this function may help you understand how the memory manager organizes the memory.
 * Do not change the implementation of this function. It will be used to help the grading.
 */
void mem_mngr_print_snapshot(void)
{
    STRU_MEM_LIST * mem_list = NULL;

    printf("============== Memory snapshot ===============\n");

    mem_list = mem_pool; // Get the first memory list
    while(NULL != mem_list)
    {
        STRU_MEM_BATCH * mem_batch = mem_list->first_batch; // Get the first mem batch from the list 

        printf("mem_list %p slot_size %d batch_count %d free_slot_bitmap %p\n", 
                   mem_list, mem_list->slot_size, mem_list->batch_count, mem_list->free_slots_bitmap);
        bitmap_print_bitmap(mem_list->free_slots_bitmap, mem_list->bitmap_size);

        while (NULL != mem_batch)
        {
            printf("\t mem_batch %p batch_mem %p\n", mem_batch, mem_batch->batch_mem);
            mem_batch = mem_batch->next_batch; // get next mem batch
        }

        mem_list = mem_list->next_list;
    }

    printf("==============================================\n");
}

/*
 * Initialize the memory manager with 8 bytes slot size mem_list.
 * Initialiaze this list with 1 batch of slots
 * @return: 0 if memory manager initialization succeed
 *          -1 if failed on any errors
 */
void mem_mngr_init(void)
{

    mem_pool = (STRU_MEM_LIST *)malloc(sizeof(STRU_MEM_LIST));

 
    if (mem_pool == NULL) {    //------------------------ base case -------------------------
        return;
    }

   // setting the value for slot size to be  8 bytes and only 1 batch size
    mem_pool->slot_size = 8; 
    mem_pool->batch_count = 1; 
    mem_pool->bitmap_size = MEM_BATCH_SLOT_COUNT/8;   // this line of code will take 1 byte for each slot 
    mem_pool->free_slots_bitmap = (unsigned char *)malloc(mem_pool->bitmap_size);
    

    if (mem_pool->free_slots_bitmap == NULL) {
        free(mem_pool);   // this  will free up the  memory if there is no mem_pool allocate 
        mem_pool = NULL;
        return;
    }

    memset(mem_pool->free_slots_bitmap, 0xFF, mem_pool->bitmap_size);  // set all slot===1 are free

    STRU_MEM_BATCH *first_batch = (STRU_MEM_BATCH *)malloc(sizeof(STRU_MEM_BATCH));
    first_batch->batch_mem = malloc(mem_pool->slot_size * MEM_BATCH_SLOT_COUNT);

    first_batch->next_batch = NULL; // one batch and then it willl go ti 
    mem_pool->first_batch = first_batch;
    mem_pool->next_list = NULL;

}


/*
 * Clean up the memory manager (e.g., release all the memory allocated)
 */
void mem_mngr_leave(void)
{
	/* Your code here */
     STRU_MEM_LIST *cur_list = mem_pool;
    STRU_MEM_LIST *next_list_in_batch = NULL;

    while (cur_list != NULL) {   // -----------------------------------------clearing all the list in each batch from the memory for different bytes
        next_list_in_batch = cur_list->next_list;
        STRU_MEM_BATCH *current_batch = cur_list->first_batch;
        STRU_MEM_BATCH *next_batch = NULL;

       
        while (current_batch != NULL) {   // -----------------------------------------clearing all the batches from the memory for different bytes

            next_batch = current_batch->next_batch;
            free(current_batch->batch_mem);
            free(current_batch);
            current_batch = next_batch;
        }

        free(cur_list->free_slots_bitmap);
        free(cur_list);
        cur_list = next_list_in_batch;
    }
    mem_pool = NULL; 


}
//---<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<------------------------------BOUNS- PART ------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

size_t next_highest_power_of_two(size_t size) {   // code to get next higestest power of 2 for allocating best fit
    if (size == 0) {
        return 1; 
    }
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size |= size >> 32;
    return size + 1;
}

STRU_MEM_LIST* create_new_mem_list(size_t slot_size) {    // -------------- this method will create a new list each time for 8, 16 32 and 64 bytes


    
    STRU_MEM_LIST *modified_list = (STRU_MEM_LIST *)malloc(sizeof(STRU_MEM_LIST));

    if (modified_list == NULL) {
        return NULL; 
    }


    modified_list->slot_size = slot_size; 
    modified_list->batch_count = 1; 
    modified_list->bitmap_size = MEM_BATCH_SLOT_COUNT/8; 
    modified_list->free_slots_bitmap = (unsigned char *)malloc(modified_list->bitmap_size);

    if (modified_list->free_slots_bitmap == NULL) {
        free(modified_list);
        return NULL;
    }
    memset(modified_list->free_slots_bitmap, 0xFF, modified_list->bitmap_size); 

    
    STRU_MEM_BATCH *first_batch = (STRU_MEM_BATCH *)malloc(sizeof(STRU_MEM_BATCH));


    if (first_batch == NULL) {  // if the batch is null
        free(modified_list->free_slots_bitmap);
        free(modified_list);
        return NULL;
    }
    first_batch->batch_mem = malloc(slot_size * MEM_BATCH_SLOT_COUNT);
    if (first_batch->batch_mem == NULL) {
        free(first_batch);
        free(modified_list->free_slots_bitmap);
        free(modified_list);
        return NULL;
    }
    first_batch->next_batch = NULL;

    modified_list->first_batch = first_batch;
    modified_list->next_list = NULL;

    return modified_list;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * Allocate a chunk of memory 	
 * @param size: size in bytes to be allocated
 * @return: the pointer to the allocated memory slot
 */
void *mem_mngr_alloc(size_t size) {
    if (size == 0) {
        return NULL;
    }


size_t adjusted_size = next_highest_power_of_two(size);  // this method will call from the above adjusted_size to to allocated the size to nearest 8,16,32 64


    
    STRU_MEM_LIST *list_tag = mem_pool;   //-------------------------------- Search for a memory list that can handle the requested size
    // while (list != NULL && list->slot_size < size) {
    //     list = list->next_list;
    // }

    // // If no such list exists, create a new one
    // if (list == NULL || list->slot_size != size) {
    //     STRU_MEM_LIST *new_list = create_new_mem_list(size);
    //     if (new_list == NULL) {
    //         return NULL; 
    //     }
    
    //     new_list->next_list = mem_pool;
    //     mem_pool = new_list;
    //     list = new_list;
    // }

    while (list_tag != NULL && list_tag->slot_size < adjusted_size) {
        list_tag = list_tag->next_list;
    }

    
    if (list_tag == NULL || list_tag->slot_size != adjusted_size) {

        STRU_MEM_LIST *new_list = create_new_mem_list(adjusted_size);
        if (new_list == NULL) {
            return NULL;
        }
       
        new_list->next_list = mem_pool;
        mem_pool = new_list;
        list_tag = new_list;
    }

   
    for (int i = 0; i < list_tag->bitmap_size * 8; i++) {

        int byteI = i / 8;
        int bitI = i % 8;
        unsigned char mask = 1 << bitI;
        if (list_tag->free_slots_bitmap[byteI] & mask) {
            
            list_tag->free_slots_bitmap[byteI] &= ~mask; // Mark the slot as used
            
            int batchIndex = i / MEM_BATCH_SLOT_COUNT;
            int slotIndex = i % MEM_BATCH_SLOT_COUNT;

            STRU_MEM_BATCH *batch = list_tag->first_batch;

            while (batchIndex > 0) {
                batch = batch->next_batch;
                batchIndex--;
            }
            return (void *)((char *)batch->batch_mem + (slotIndex * list_tag->slot_size));
        }
    }


    // ----------------<<<<<<<<<<<<<<<<--------------------------------This case will create  new batch if the first batch is full with slot ------------------------>>>>>>>>>>>>>>>>>>
    STRU_MEM_BATCH *new_Batch = (STRU_MEM_BATCH *)malloc(sizeof(STRU_MEM_BATCH));

    // if (new_Batch == NULL) {
    //     return NULL;
    // }

    new_Batch->batch_mem = malloc(list_tag->slot_size * MEM_BATCH_SLOT_COUNT); 


    // if (new_Batch->batch_mem == NULL) {
    //     free(new_Batch);
    //     return NULL;
    // }
    new_Batch->next_batch = list_tag->first_batch;
    list_tag->first_batch = new_Batch;
    list_tag->batch_count += 1;

    int newBitmapSize = ((list_tag->batch_count * MEM_BATCH_SLOT_COUNT) + 7) / 8; 

    list_tag->free_slots_bitmap = (unsigned char *)realloc(list_tag->free_slots_bitmap, newBitmapSize);

    // if (list_tag->free_slots_bitmap == NULL) {
       

    //     free(new_Batch->batch_mem);
    //     free(new_Batch);
    //     return NULL;
    // }
    memset(&list_tag->free_slots_bitmap[list_tag->bitmap_size], 0xFF, newBitmapSize - list_tag->bitmap_size); 
    list_tag->bitmap_size = newBitmapSize;

   
    list_tag->free_slots_bitmap[list_tag->bitmap_size - 1] &= ~(1 << 0); 
    return new_Batch->batch_mem; 



}





/*
 * Free a chunk of memory pointed by ptr
 * Print out any error messages
 * @param: the pointer to the allocated memory slot
 */
void mem_mngr_free(void *ptr) {
    if (mem_pool == NULL || ptr == NULL) {
        printf("Error: Memory manager is not initialized or NULL pointer.\n");
        return;
    }

    STRU_MEM_LIST *current_list = mem_pool;

    while (current_list != NULL) {

        STRU_MEM_BATCH *current_batch = current_list->first_batch;

        while (current_batch != NULL) {
            void *batch_start = current_batch->batch_mem;
            void *batch_end = batch_start + (current_list->slot_size * MEM_BATCH_SLOT_COUNT);

            if (ptr >= batch_start && ptr < batch_end) {
                size_t slot_index = ((size_t)ptr - (size_t)batch_start) / current_list->slot_size;

                if (ptr == batch_start + (slot_index * current_list->slot_size)) {
    
                    if (current_list->free_slots_bitmap[slot_index / 8] & (1 << (slot_index % 8))) {  // case1 : -------------------------------- double free errror
                        printf("Error: Double free attempt.\n");
                    } else {
                       
                        current_list->free_slots_bitmap[slot_index / 8] |= (1 << (slot_index % 8));  
                        return; 
                    }
                } else {
                    printf("Error: Pointer is not the starting address of any slot.\n");  // case 2: -------------------------------------------- pointer not allocating to start of list
                    return; 
                }
            }

            current_batch = current_batch->next_batch;
        }

        current_list = current_list->next_list;
    }

    
    printf("Error:ptr is outside of memory managed by the manager\n");   // case 3 : ------------- the pointer was not found in any list or batch
}

