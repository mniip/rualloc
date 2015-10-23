#ifndef RAW_SYSCALLS
#define _GNU_SOURCE
#include <sys/mman.h>
#else
#include <syscall.h>
#endif
#include <stdint.h>
#include <stddef.h>

#ifdef RAW_SYSCALLS
static void *mmap(void *addr, size_t length, int prot, int flags, int fd, size_t offset)
{
	void *ret;
#ifdef __NR_mmap2
	int num = __NR_mmap2;
#else
	int num = __NR_mmap;
#endif
	syscall6(&ret, num, addr, length, prot, flags, fd, offset);
	return ret;
}

static int munmap(void *addr, size_t length)
{
	int ret;
	syscall2(&ret, __NR_munmap, addr, length);
	return ret;
}

static void *mremap(void *old_addr, size_t old_length, size_t new_length, int flags)
{
	void *ret;
	syscall4(&ret, __NR_mremap, old_addr, old_length, new_length, flags);
	return ret;
}
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20
#define MREMAP_MAYMOVE 0x1
#endif

#define pure_to_impure(x) ((void *)((unsigned char *)(x) - sizeof(size_t)))
#define impure_to_pure(x) ((void *)((unsigned char *)(x) + sizeof(size_t)))
#define pure_size(x) (((size_t *)x)[-1])
#define impure_size(x) (((size_t *)x)[0])
#define header_length sizeof(size_t)

void *malloc(size_t sz)
{
	if(sz)
	{
		void *addr = mmap(NULL, sz + header_length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if(addr == (void *)-1)
		{
			return NULL;
		}
		else
		{
			impure_size(addr) = sz;
			return impure_to_pure(addr);
		}
	}
	else
		return NULL;
}

void free(void *addr)
{
	if(addr)
		munmap(pure_to_impure(addr), pure_size(addr) + header_length);
}

void *realloc(void *addr, size_t sz)
{
	if(addr)
		if(sz)
		{
			void *newaddr = mremap(pure_to_impure(addr), pure_size(addr) + header_length, sz + header_length, MREMAP_MAYMOVE);
			if(newaddr == (void *)-1)
			{
				return NULL;
			}
			else
			{
				impure_size(newaddr) = sz;
				return impure_to_pure(newaddr);
			}
		}
		else
		{
			free(addr);
			return NULL;
		}
	else
	{
		return malloc(sz);
	}
}

void *calloc(size_t nmemb, size_t sz)
{
	return malloc(nmemb * sz);
}
