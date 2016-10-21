# ft_nm-otool
Implementations of nm and otool in C.

This repository is an implementation of nm and otool unix executable in C, which are used to decompile and explore
the code through compiled executables. The most interesting part of this project lies in the understanding of
unix executable. We can see through the recreation of these executable "how" those files have been made,
by digging into very old include files, and casting a compiled memory -that seems unreadable- into actual sensible content.
