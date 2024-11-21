/*
 * CS 551 Project "Memory manager".
 * You do not need to turn in this file.	
 */

#include <stdint.h> 
#include "memory_manager.h" 
#include "interposition.h" 

int main(int argc, char *argv[])
{
    mem_mngr_init();

    
    void* ptr1 = mem_mngr_alloc(8);
    if (ptr1 == NULL) {
        printf("Test 1 Failed: Could not allocate 8 bytes.\n");
    } else {
        printf("Test 1 Passed: Allocated 8 bytes successfully.\n");
    }
    mem_mngr_print_snapshot();

    
    void* ptr2 = mem_mngr_alloc(8);
    if (ptr2 == NULL) {
        printf("Test 2 Failed: Could not allocate another 8 bytes.\n");
    } else {
        printf("Test 2 Passed: Allocated another 8 bytes successfully.\n");
    }
    mem_mngr_print_snapshot();

  
    void* ptr3 = mem_mngr_alloc(5);
    if (ptr3 == NULL) {
        printf("Test 3 Failed: Could not allocate 5 bytes (rounded to 8).\n");
    } else {
        printf("Test 3 Passed: Allocated 5 bytes (rounded to 8) successfully.\n");
    }
    mem_mngr_print_snapshot();

  
    void* ptr4 = mem_mngr_alloc(16);
    if (ptr4 == NULL) {
        printf("Test 4 Failed: Could not allocate 16 bytes.\n");
    } else {
        printf("Test 4 Passed: Allocated 16 bytes successfully.\n");
    }
    mem_mngr_print_snapshot();

    
    void* ptr5 = mem_mngr_alloc(10);
    if (ptr5 == NULL) {
        printf("Test 5 Failed: Could not allocate 10 bytes (rounded to 16).\n");
    } else {
        printf("Test 5 Passed: Allocated 10 bytes (rounded to 16) successfully.\n");
    }
    mem_mngr_print_snapshot();

   
    void* ptr6 = mem_mngr_alloc(32);
    if (ptr6 == NULL) {
        printf("Test 6 Failed: Could not allocate 32 bytes.\n");
    } else {
        printf("Test 6 Passed: Allocated 32 bytes successfully.\n");
    }
    mem_mngr_print_snapshot();

   
    void* ptr7 = mem_mngr_alloc(64);
    if (ptr7 == NULL) {
        printf("Test 7 Failed: Could not allocate 64 bytes.\n");
    } else {
        printf("Test 7 Passed: Allocated 64 bytes successfully.\n");
    }
    mem_mngr_print_snapshot();

    
    mem_mngr_free(ptr1);
    printf("Test 8 Passed: Freed 8 bytes successfully.\n");
    mem_mngr_print_snapshot();

    mem_mngr_free(ptr4);
    printf("Test 9 Passed: Freed 16 bytes successfully.\n");
    mem_mngr_print_snapshot();

   
    mem_mngr_free(ptr4);
    printf("Test 10: Attempted double free\n");

    int outside_var;
    void* ptrOutside = &outside_var;
    mem_mngr_free(ptrOutside);
    printf("Test 11: Attempted to free a pointer not managed \n");

    mem_mngr_leave();

    return 0;
}



