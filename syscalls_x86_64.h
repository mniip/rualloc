#define syscall2(r, n, a, b) \
	asm volatile("syscall" \
		: "=a"(*(r)) \
		: "0"(n), "D"(a), "S"(b) \
		: "cc", "rcx", "r11", "memory")
#define syscall4(r, n, a, b, c, d) \
	do { \
		register uint64_t syscall4_r10 asm("r10") = d; \
		asm volatile("syscall" \
			: "=a"(*(r)) \
			: "0"(n), "D"(a), "S"(b), "d"(c), "r"(syscall4_r10) \
			: "cc", "rcx", "r11", "memory"); \
	} while(0)
#define syscall6(r, n, a, b, c, d, e, f) \
	do { \
		register uint64_t syscall6_r10 asm("r10") = d; \
		register uint64_t syscall6_r8 asm("r8") = e; \
		register uint64_t syscall6_r9 asm("r9") = f; \
		asm volatile("syscall" \
			: "=a"(*(r)) \
			: "0"(n), "D"(a), "S"(b), "d"(c), "r"(syscall6_r10), "r"(syscall6_r8), "r"(syscall6_r9) \
			: "cc", "rcx", "r11", "memory"); \
	} while(0)
