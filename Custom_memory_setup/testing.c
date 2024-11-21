#include <stdio.h>
#include "common.h"

int bitmap_find_first_bit(unsigned char * bitmap, int size, int val);
int bitmap_clear_bit(unsigned char *bitmap, int size, int target_pos) ;
int bitmap_set_bit(unsigned char *bitmap, int size, int target_pos) ;
//--------------------------------------------------------------------------------
int bitmap_bit_is_set(unsigned char *bitmap, int size, int pos) ;
int bitmap_print_bitmap(unsigned char * bitmap, int size);



int main() {
 /// printf("Hello World!");

    // unsigned char bitmap[] = {0b01010101, 0b10101010};
    unsigned char bitmap[] = {0xF7, 0xFF};
    //bitmap_set_bit(bitmap, sizeof(bitmap), 3);
    int size = sizeof(bitmap);

    int val = 0;
    int target = 3;



    
    // int result = bitmap_find_first_bit(bitmap, size, val);
    // bitmap_set_bit(bitmap, sizeof(bitmap), target);
    // bitmap_print_bitmap(bitmap,  size);
    // bitmap_clear_bit(bitmap,size,target);

   int result =  bitmap_bit_is_set(bitmap, size, target);
   printf("The position of the set bit with value %d\n" , result);

    bitmap_print_bitmap(bitmap,  size);

    //printf("The position of the first bit with value %d is: %d\n", val, result);  //------------------- First function
    //printf("The position of the set bit with value %d" , result1);
  return 0;
}
//-------------------------------------------------------------------------------------------------------------
int bitmap_find_first_bit(unsigned char *bitmap, int size, int val) {

    if (bitmap == NULL || size <= 0) {   // base case 
        return BITMAP_OP_ERROR;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
           
            if (((bitmap[i] >> j) & 1) == val) {   // Check if the j-th bit of bitmap[i] is equal to val
                return i * 8 + j;
            }
        }
    }

    return BITMAP_OP_NOT_FOUND;
}

//---------------------------------------------------------------------------------------------------------------

int bitmap_set_bit(unsigned char *bitmap, int size, int target_pos) {
    if (bitmap == NULL || size <= 0 || target_pos < 0 || target_pos >= size * 8) {
        return BITMAP_OP_ERROR;
    }

    int byte_pos = target_pos / 8;
    int bit_pos = target_pos % 8;

    bitmap[byte_pos] |= (1 << bit_pos);

    return BITMAP_OP_SUCCEED;
}


int bitmap_clear_bit(unsigned char *bitmap, int size, int target_pos) {
    if (bitmap == NULL || size <= 0 || target_pos < 0 || target_pos >= size * 8) {
        return BITMAP_OP_ERROR;
    }

    int byte_pos = target_pos / 8;
    int bit_pos = target_pos % 8;

    bitmap[byte_pos] &= ~(1 << bit_pos);

    return BITMAP_OP_SUCCEED;
}

//------------------------------------------------------------------------------------------------------

int bitmap_bit_is_set(unsigned char *bitmap, int size, int pos) {
  
    if (bitmap == NULL || size <= 0 || pos < 0 || pos >= size * 8) {
        return BITMAP_OP_ERROR; 
    }

    int byte_pos = pos / 8; 
    int bit_pos = pos % 8; 
    

    if (bitmap[byte_pos] & (1 << bit_pos)) {
        return 1; 
    } else {
        return 0; 
    }
}

//------------------------------------------------------------------------------------------------

int bitmap_print_bitmap(unsigned char * bitmap, int size)
{
    int pos = 0;
    int total_bits = size * BIT_PER_BYTE;
    unsigned char current_byte = 0;

    if (NULL == bitmap)
    {
        printf("ERROR: NULL bit map!\n");
        return BITMAP_OP_ERROR;
    }

    printf("bitmap %p size %d bytes: ", bitmap, size);

    while (pos < total_bits)
    {
        int v = 0;
        
        current_byte = *(bitmap + pos/BIT_PER_BYTE);
        v = ((current_byte >> pos % BIT_PER_BYTE) & 0x01);
        printf("%d", v);
        if ((pos + 1) % 4 == 0)
        {
            printf("  ");
        }
        
        pos++;
    }

    printf("\n");

    return BITMAP_OP_SUCCEED;
}


//------------<<<<-------------mem_mngr_intit---------------->>>>------------------------------------
/*
void mem_mngr_init(void)
{
    // Allocate memory for the memory list
    mem_pool = (STRU_MEM_LIST *)malloc(sizeof(STRU_MEM_LIST));
    if (mem_pool == NULL) {
        // Handle allocation failure if necessary
        return;
    }

    // Initialize the memory list
    mem_pool->slot_size = 8; // Slot size is 8 bytes
    mem_pool->batch_count = 1; // One batch of slots
    mem_pool->bitmap_size = MEM_BATCH_SLOT_COUNT; // Bitmap size equals the number of slots in a batch

    // Allocate and initialize the bitmap
    mem_pool->free_slots_bitmap = (unsigned char *)malloc(mem_pool->bitmap_size);
    if (mem_pool->free_slots_bitmap == NULL) {
        // Handle allocation failure if necessary
        // Clean up previously allocated memory
        free(mem_pool);
        mem_pool = NULL;
        return;
    }
    // Initialize the bitmap with all bits set to 1 (all slots are free)
    memset(mem_pool->free_slots_bitmap, 0xFF, mem_pool->bitmap_size);

    // Allocate memory for the first batch
    STRU_MEM_BATCH *first_batch = (STRU_MEM_BATCH *)malloc(sizeof(STRU_MEM_BATCH));
    if (first_batch == NULL) {
        // Handle allocation failure if necessary
        // Clean up previously allocated memory
        free(mem_pool->free_slots_bitmap);
        free(mem_pool);
        mem_pool = NULL;
        return;
    }

    // Allocate memory for the slots in the batch
    first_batch->batch_mem = malloc(mem_pool->slot_size * MEM_BATCH_SLOT_COUNT);
    if (first_batch->batch_mem == NULL) {
        // Handle allocation failure if necessary
        // Clean up previously allocated memory
        free(first_batch);
        free(mem_pool->free_slots_bitmap);
        free(mem_pool);
        mem_pool = NULL;
        return;
    }

    // Initialize the first batch
    first_batch->next_batch = NULL; // This is the only batch, so no next batch

    // Link the first batch to the memory list
    mem_pool->first_batch = first_batch;

    // There is no next list, as we're initializing with a single list
    mem_pool->next_list = NULL;
}

*/
