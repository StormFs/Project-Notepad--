# Notepad--

Overview:
This application is a lightweight, console-based text editor that mimics the functionality of advanced text-editing software. It is built using C++ and offers core features such as real-time text editing, cursor navigation, text manipulation, and file operations. The program leverages a doubly linked list for efficient character management, ensuring a seamless user experience for editing text files.

Features:

Dynamic Text Editing:

Add, remove, and navigate characters efficiently.
Multi-character delete options through Backspace (VK_BACK) or Delete (VK_DELETE) keys.
Cursor Movement:

Move the cursor left, right, up, and down across lines.
Jump words using Ctrl + Left or Ctrl + Right.
Selection & Clipboard Support:

Select text using Shift + Arrow Keys.
Copy selected text to the clipboard (Ctrl + C) and paste it into the editor (Ctrl + V).
File Operations:

Load previously saved files for editing.
Save text to files, with overwrite confirmation to avoid accidental data loss.
Custom Functionalities:

Support for multi-line navigation using Up and Down arrow keys.
Clear all content with a single command.
Provides warnings for unsaved changes before exiting.
User-Friendly Interface:

Intuitive keybindings for common text editing actions.
Clean command-line interface that displays the current text, cursor position, and file size in real time.
System Requirements:

Operating System: Windows
Compiler: Built using C++ (requires <conio.h>, <windows.h>, and standard libraries).
How to Run:

Compile the source code using a C++ compiler or use the pre-built Program.exe file.
Execute the program from the console.
Follow the on-screen instructions to load, edit, or save text files.
Usage Tips:

Press Ctrl + S to save your file at any time.
Use Ctrl + Left and Ctrl + Right for word navigation.
Press Esc to exit the editor (you’ll be prompted to save unsaved changes).
Limitations:

Currently supports single-instance editing (no tabbed files).
Designed for basic text operations; does not support syntax highlighting or advanced formatting.
Future Enhancements:

Add support for syntax highlighting for programming files.
Enable mouse support for navigation.
Incorporate find-and-replace functionality.
Enjoy the simplicity and speed of Program.exe, your lightweight companion for on-the-go text editing!
