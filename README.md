# Task Management System (BST Implementation in C)

Author: Omar Shoubaki  
Birzeit University  
Electrical and Computer Engineering Department


## Project Overview
This project is an advanced version of the Task Management System implemented in C.  
It uses a Binary Search Tree (BST) to store, organize, and manipulate tasks efficiently.

Each task has an ID, name, date, duration, and a performed flag that indicates whether the task has been completed.  
The system allows the user to load tasks from a file, add or delete tasks, perform searches, mark tasks as done, and restructure the BST based on different criteria.

## How It Works
When the program starts, it displays a main menu that allows the user to select one of several operations.  
Each operation corresponds to a specific functionality such as loading tasks, searching, or restructuring the BST.

Tasks are stored as nodes in a BST, and the ordering of the tree depends on the current structure (by ID, name, date, or duration).  
When the tree is restructured, the program rebuilds it according to the user’s selected sorting criterion.

## Features
1. Load tasks from file  
   Reads tasks from tasks.txt and inserts them into the BST ordered by task ID.
2. Add a new task  
   Prompts the user to enter the task details and inserts it into the BST.
3. Delete a task  
   Removes a task by its ID from the BST while maintaining proper structure.
4. Search for a task  
   Searches for a task by name using a case-insensitive match.
5. Perform a task  
   Marks a task as performed based on its ID.
6. View unperformed tasks  
   Displays all tasks that have not been performed, sorted alphabetically by their name.
7. View performed tasks  
   Displays all tasks marked as performed.
8. Restructure the BST  
   Allows restructuring the BST based on one of the following:
   - Task name  
   - Task date  
   - Task duration  
9. View BST information  
   Displays statistics about the tree including:
   - Height of the tree  
   - Number of nodes  
   - Number of leaf nodes  
   - Number of internal nodes  
10. Exit program

## Data Structures Used
Binary Search Tree (BST)  
Used to store and manage tasks efficiently. Each node represents a task.  
The BST supports insertion, deletion, traversal, and restructuring.

## File Format
Input File (tasks.txt)  
Each task is stored in one line using the following format:
id#name#date#duration
Example:
1#Complete report#2025-04-01#2.5
2#Project meeting#2025-04-03#1.5
3#Design presentation#2025-04-05#3.0

## How to Run
1. Make sure tasks.txt is in the same directory as the source file.  
2. Compile the program using any C compiler
3. Run the program:
4. Follow the on-screen menu to perform operations.

## Example Menu
Select an operation 1-10
1- Load tasks from file
2- Add a new task
3- Delete a task
4- Search for a task
5- Perform a task
6- View unperformed tasks
7- View performed tasks
8- Restructure the Tasks BST
9- View the tasks BST info
10- Exit program

## BST Statistics Displayed
- Tree height  
- Tree size  
- Number of leaves  
- Number of internal nodes  

## Concepts Demonstrated
- Binary Search Tree traversal and manipulation  
- Recursive functions for insertion, deletion, and restructuring  
- Case-insensitive string comparison  
- Dynamic memory allocation and pointer handling  
- File reading and token parsing using strtok  

## Purpose
This project was developed as part of the COMP2421 – Data Structures course to demonstrate practical use of Binary Search Trees in managing tasks efficiently.
