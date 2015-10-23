# Retarded Useless Allocator

While useless in practice, this allocator might come handy if you're trying to compile a program that doesn't include bloat like crt0.o, libc, and a sane virtual space layout.

The allocator doesn't touch the heap, and has no state. All allocation is done by calls to mmap, munmap, and mremap.

If you compile it with `make`, the library will use glibc wrappers for the system calls. You probably don't want that, you should compile with `make raw PLATFORM=x86_64` (or some other `PLATFORM`) instead.
