#define syscall2(r, n, a, b) \
	asm volatile("pushl %%ebx; movl %2, %%ebx; int $0x80; popl %%ebx" \
		: "=a"(*(r)) \
		: "0"(n), "m"(a), "c"(b) \
		: "cc", "edi", "esi", "memory")
#define syscall4(r, n, a, b, c, d) \
	asm volatile("pushl %%ebx; movl %2, %%ebx; int $0x80; popl %%ebx" \
		: "=a"(*(r)) \
		: "0"(n), "m"(a), "c"(b), "d"(c), "S"(d) \
		: "cc", "edi", "memory")
#define syscall6(r, n, a, b, c, d, e, f) \
	do { \
		(void) f; \
		asm volatile("pushl %%ebx; movl %2, %%ebx; int $0x80; popl %%ebx" \
			: "=a"(*(r)) \
			: "0"(n), "m"(a), "c"(b), "d"(c), "S"(d), "D"(e) \
			: "cc", "memory"); \
	} while(0)
