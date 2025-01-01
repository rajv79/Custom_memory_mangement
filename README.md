# Custom Memory Management

This project implements a custom memory management system in C, designed to improve memory allocation, deallocation, and tracking for enhanced performance and debugging capabilities.

## Project Structure
```
├── Makefile              # Build configuration for the project
├── README.md             # Documentation for the project
├── bitmap.c              # Implementation for bitmap-based memory tracking
├── common.h              # Common macros and utility functions
├── interposition.h       # Header for function interpositioning
├── memory_manager.c      # Core memory management implementation
├── memory_manager.h      # Header file for memory management functions
├── outputfile.txt        # Output logs or results from the program
├── test1                 # Binary or test file
├── test_main.c           # Main test file
├── testing.c             # Additional testing functionality
```



## Features

- **Custom Memory Management**: Provides a custom memory allocator that overrides standard `malloc` and `free` functions for better control.
- **Bitmap-based Tracking**: Utilizes a bitmap to efficiently manage memory blocks.
- **Interpositioning**: Replaces default memory management functions using function interposition techniques.
- **Logging and Debugging**: Outputs memory usage details to `outputfile.txt` for debugging purposes.
- **Test Suite**: Includes test cases to validate functionality and performance.

## File Descriptions

- **`bitmap.c`**: Contains functions for managing memory allocation and deallocation using a bitmap data structure.
- **`memory_manager.c`**: Implements the core functionality of the custom memory allocator, including replacements for `malloc`, `free`, and `realloc`.
- **`interposition.h`**: Facilitates overriding standard memory allocation functions using linker or runtime interposition techniques.
- **`test_main.c`**: Includes test cases to validate the functionality of the memory manager.
- **`testing.c`**: Provides additional tests and utilities for stress-testing the memory manager.

## Usage

1. Build the project using the provided `Makefile`:
