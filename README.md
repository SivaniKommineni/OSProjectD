# ProjectD
In this project, we developed a single-process operating system with functionalities similar to CP/M. The implemented functions:
Listing directory contents: The dir command displays extant files, optionally including their sizes.

Deleting files: The del command marks a file as deleted in both the directory and disk map, making its space available for reuse.

Writing files: The write command creates a file entry, locates free disk sectors, and writes the file's data to them.


Copying files: The copy command utilizes existing read and write system calls to duplicate the contents of one file to another.

Creating text files: The create textfl command allows users to interactively enter lines of text, which are then stored in a buffer and written to a new file.

compileOS.sh file consists of several commands. By complying compileOS.sh, it will handle the compiling and assembling of the OS into a disc image. Upon which you can use the diskc.img to run it in a simulator

