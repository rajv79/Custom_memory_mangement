Custom Memory Management
This project implements a custom memory management system in C, designed to enhance memory allocation, deallocation, and tracking for better performance and debugging.

Project Structure
Custom_memory_management/
├── Makefile              # Build configuration for the project
├── README                # Documentation for the project
├── bitmap.c              # Implementation for bitmap-based memory tracking
├── common.h              # Common macros and utility functions
├── interposition.h       # Header for function interpositioning
├── memory_manager.c      # Core memory management implementation
├── memory_manager.h      # Header file for memory management functions
├── outputfile.txt        # Output logs or results from the program
├── test1                 # Binary or test file
├── test_main.c           # Main test file
├── testing.c             # Additional testing functionality

Features
Custom Memory Management: Provides a custom memory allocator that overrides the standard malloc/free functions for better control.
Bitmap-based Tracking: Uses a bitmap to manage memory blocks efficiently.
Interpositioning: Leverages interposition to replace default memory management functions with custom implementations.
Logging and Debugging: Outputs memory usage details to outputfile.txt for debugging purposes.
Test Suite: Includes test cases to validate functionality and performance.

Files Description
bitmap.c: Contains functions for managing memory allocation and deallocation using a bitmap data structure.
memory_manager.c: Implements the core functionality of the custom memory allocator, including malloc, free, and realloc replacements.
interposition.h: Facilitates overriding standard memory allocation functions using linker or runtime interposition techniques.
test_main.c: Includes test cases to validate the functionality of the memory manager.
testing.c: Provides additional tests and utilities for stress-testing the memory manager.
