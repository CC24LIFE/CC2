//https://github.com/ensc/dietlibc/blob/master/ldso.c

#define errno fnord
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
//#include <elf.h>
#include <stdlib.h>
#include <stdint.h>
#undef errno

/* Type for a 16-bit quantity.  */
typedef uint16_t Elf32_Half;
typedef uint16_t Elf64_Half;

/* Types for signed and unsigned 32-bit quantities.  */
typedef uint32_t Elf32_Word;
typedef	int32_t  Elf32_Sword;
typedef uint32_t Elf64_Word;
typedef	int32_t  Elf64_Sword;

/* Types for signed and unsigned 64-bit quantities.  */
typedef uint64_t Elf32_Xword;
typedef	int64_t  Elf32_Sxword;
typedef uint64_t Elf64_Xword;
typedef	int64_t  Elf64_Sxword;

/* Type of addresses.  */
typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;

/* Type of file offsets.  */
typedef uint32_t Elf32_Off;
typedef uint64_t Elf64_Off;

/* Type for section indices, which are 16-bit quantities.  */
typedef uint16_t Elf32_Section;
typedef uint16_t Elf64_Section;

/* Type for version symbol information.  */
typedef Elf32_Half Elf32_Versym;
typedef Elf64_Half Elf64_Versym;


/* The ELF file header.  This appears at the start of every ELF file.  */

#define EI_NIDENT (16)

typedef struct
{
  unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
  Elf32_Half	e_type;			/* Object file type */
  Elf32_Half	e_machine;		/* Architecture */
  Elf32_Word	e_version;		/* Object file version */
  Elf32_Addr	e_entry;		/* Entry point virtual address */
  Elf32_Off	e_phoff;		/* Program header table file offset */
  Elf32_Off	e_shoff;		/* Section header table file offset */
  Elf32_Word	e_flags;		/* Processor-specific flags */
  Elf32_Half	e_ehsize;		/* ELF header size in bytes */
  Elf32_Half	e_phentsize;		/* Program header table entry size */
  Elf32_Half	e_phnum;		/* Program header table entry count */
  Elf32_Half	e_shentsize;		/* Section header table entry size */
  Elf32_Half	e_shnum;		/* Section header table entry count */
  Elf32_Half	e_shstrndx;		/* Section header string table index */
} Elf32_Ehdr;

typedef struct
{
  unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
  Elf64_Half	e_type;			/* Object file type */
  Elf64_Half	e_machine;		/* Architecture */
  Elf64_Word	e_version;		/* Object file version */
  Elf64_Addr	e_entry;		/* Entry point virtual address */
  Elf64_Off	e_phoff;		/* Program header table file offset */
  Elf64_Off	e_shoff;		/* Section header table file offset */
  Elf64_Word	e_flags;		/* Processor-specific flags */
  Elf64_Half	e_ehsize;		/* ELF header size in bytes */
  Elf64_Half	e_phentsize;		/* Program header table entry size */
  Elf64_Half	e_phnum;		/* Program header table entry count */
  Elf64_Half	e_shentsize;		/* Section header table entry size */
  Elf64_Half	e_shnum;		/* Section header table entry count */
  Elf64_Half	e_shstrndx;		/* Section header string table index */
} Elf64_Ehdr;

#if (__WORDSIZE == 64)

#define phdr Elf64_Phdr
#define ehdr Elf64_Ehdr
#define shdr Elf64_Shdr
#define sym Elf64_Sym
#define dyn Elf64_Dyn
#define rela Elf64_Rela
#define R_SYM ELF64_R_SYM
#define R_TYPE ELF64_R_TYPE

#else

#define phdr Elf32_Phdr
#define ehdr Elf32_Ehdr
#define shdr Elf32_Shdr
#define sym Elf32_Sym
#define dyn Elf32_Dyn
#define rela Elf32_Rela
#define R_SYM ELF32_R_SYM
#define R_TYPE ELF32_R_TYPE

#endif

static int errno;

static char path[100];
static char* ldlp;

static struct dll {
  struct dll* next;
  ehdr* e;
  void* code,* data;
  size_t codelen,datalen,codeplus;
  char name[1];		// asciiz of library name
} *dlls, dllroot;


extern int __loadlibrary(const char* fn);
extern ssize_t __write1(const char* s);
extern size_t _strlen(const char* s);
extern int _strcmp(const void* str1,const void* str2);


/* dietlibc */
extern int __mark(int);
static char *stpcpy(char *to, const char *from) {
    while (__mark(0) & (*to++ = *from++))
        ;
    return (to - 1);
}

//CLEVERCLIENTSTART
int loadlibrary(const char* fn) {
  char lp[200];
  int r;
  char* c;
  const char* shortname=fn;
  struct dll* d;

  {
    size_t i;
    for (i=0; fn[i]; ++i)
      if (fn[i]=='/') shortname=fn+i+1;
  }

  if (_strlen(fn)>50) return -1;
  for (d=dlls; d; d=d->next)
    if (!_strcmp(d->name,shortname))
      return 0;

  __write1("loadlibrary(\"");
  __write1(fn);
  __write1("\")\n");
  if (fn[0]=='/') {
    return __loadlibrary(fn);
  }

  c=stpcpy(lp,path);
  *c++='/';
  stpcpy(c,fn);
  r=__loadlibrary(lp);
  if (r==0) return r;
  if (ldlp) {
    size_t i;
    char* d;
    c=ldlp;
    for (i=0; ; ++i) {
again:
      if (c[i]==':' || c[i]==0) {
	if (i<100) {
	  lp[i]='/';
	  stpcpy(lp+i+1,fn);
	  r=__loadlibrary(lp);
	  if (r==0) return 0; //MODIFIED
	}
	if (c[i]==0) break;
	c+=i+1; i=0; goto again;
      } else
	if (i<100) lp[i]=c[i];
    }
  }
  return r;
}
//CLEVERCLIENTEND
