#include <stdio.h>
#include <stdint.h>

#ifndef __ELF_H__
#define __ELF_H__

typedef uint16_t Elf64_Half;

#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4

typedef struct {
    Elf64_Half e_type;
} Elf64_Ehdr;

#endif

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    case ET_NONE: type_str = "Unknown"; break;
    case ET_REL:  type_str = "Relocatable"; break;
    case ET_EXEC: type_str = "Executable"; break;
    case ET_DYN:  type_str = "Shared Object/PIE"; break;
    case ET_CORE: type_str = "Core"; break;
    default:      type_str = "Unknown"; break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main() {
  Elf64_Ehdr ehdr_rel;
  ehdr_rel.e_type = ET_REL;

  Elf64_Ehdr ehdr_dyn;
  ehdr_dyn.e_type = ET_DYN;

  print_elf_type(ehdr_rel.e_type);
  print_elf_type(ehdr_dyn.e_type);

  return 0;
}