A simplified, educational file system implemented in C++ that simulates core operating system file operations using internal structures such as SuperBlock, Inode Table, UFDT, and FileTable. This project replicates the behavior of real file systems and provides hands-on understanding of system calls and file management.

📌 Features

Custom shell interface with command parsing

Supports OS-like system calls:

creat – Create a new file

write – Write data into a file

read – Read data from a file

unlink – Delete a file

stat – Show file information

ls – List all files

man – Show manual pages

clear – Clear screen

exit – Close the CVFS shell

Internal file system components:

SuperBlock

Inode Table (DILB)

User File Descriptor Table (UFDT)

FileTable

Supports file permissions and error handling.

📁 Internal Architecture

The CVFS is built using the following modules:

BootBlock: Holds boot information

SuperBlock: Tracks total and free inodes

Inode Table (DILB): Linked list representing inodes

UAREA: Contains User File Descriptor Table

FileTable: Stores details of each opened file

This structure closely mimics real OS file systems like UNIX VFS.

🛠 Technologies Used

C++ (Core logic)

Pointers & Dynamic Memory Allocation

Linked Lists (Inode Table Management)

Custom Command-Line Interface
