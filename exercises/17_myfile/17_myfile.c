#include <elf.h>
#include <stdio.h>
#include <stdint.h>

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
  // 模拟两种不同类型的 ELF 文件头
  Elf64_Ehdr ehdr_rel;
  ehdr_rel.e_type = ET_REL;   // Relocatable

  Elf64_Ehdr ehdr_dyn;
  ehdr_dyn.e_type = ET_DYN;   // Shared Object/PIE

  print_elf_type(ehdr_rel.e_type);
  print_elf_type(ehdr_dyn.e_type);

  return 0;
}