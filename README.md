# Class Sort Program

### Overview
An efficient C++ program for sorting and organizing course information using optimized data structures. This program demonstrates proficiency in algorithm optimization and advanced data structure implementation by efficiently managing course data including course numbers, titles, and prerequisites.

### Features
- **Binary Search Tree (BST)**: Maintains courses in sorted order for efficient retrieval
- **Hash Table**: Provides O(1) constant-time lookups for prerequisite validation
- **Course Management**: Display comprehensive course details including prerequisites
- **Efficient Sorting**: Optimized for performance with large datasets
- **Menu-Driven Interface**: User-friendly command-line interface for course operations

### Technologies Used
- **Language**: C++
- **Data Structures**: Binary Search Tree, Hash Table
- **Algorithms**: Tree traversal, hashing, sorting
- **Concepts**: Object-oriented programming, memory management

### Project Structure
- `Class Sort (Original).zip` - Initial version with linear search implementation
- `Class Sort (Revised).zip` - Optimized version with BST and hash table

### Key Enhancements
The enhanced version improves upon the original by:
- **Binary Search Tree Implementation**: Upgraded from O(n) linear search to O(log n) tree-based search
- **Hash Table Integration**: Added constant-time O(1) prerequisite validation
- **Improved Memory Management**: Better resource allocation and deallocation
- **Code Modularity**: Enhanced organization with separate classes and functions
- **Error Handling**: Robust input validation and error messages
- **Performance Optimization**: Significantly faster operations on large course datasets


### Algorithm Details

#### Binary Search Tree
- **Purpose**: Maintain courses in alphabetically sorted order
- **Advantage**: Logarithmic search time vs linear scanning
- **Implementation**: In-order traversal for sorted output

#### Hash Table
- **Purpose**: Quick prerequisite lookups and validation
- **Advantage**: Constant-time access to course information
- **Implementation**: Separate chaining for collision resolution

### Sample Input/Output
<img width="1440" height="900" alt="Screenshot 2025-12-14 at 6 51 02 PM" src="https://github.com/user-attachments/assets/03f5bda4-34df-49fc-abc7-a15dd08957f0" />
<img width="1440" height="900" alt="Screenshot 2025-12-14 at 6 50 48 PM" src="https://github.com/user-attachments/assets/165c2f39-65fa-4014-a78a-38b9719c7b46" />
<img width="1440" height="900" alt="Screenshot 2025-12-14 at 6 43 47 PM" src="https://github.com/user-attachments/assets/352362c6-bd6a-4763-ab49-8565ae109fc1" />




### Compilation and Execution

#### Compile
g++ -std=c++11 ProjectModule7.cpp -o class_sort

#### Run
./class_sort


### Usage
1. Load course data from CSV file
2. Choose from menu options:
   - Display all courses in sorted order
   - Search for specific course
   - Display prerequisites for a course
   - Exit program


### Author
Christina Jimenez

