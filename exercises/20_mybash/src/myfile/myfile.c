#include "myfile.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  const char *type_abbr;
  switch (e_type) {
    case 0: type_str = "Unknown"; type_abbr = "NONE"; break;
    case 1: type_str = "Relocatable"; type_abbr = "REL"; break;
    case 2: type_str = "Executable"; type_abbr = "EXEC"; break;
    case 3: type_str = "Shared Object/PIE"; type_abbr = "DYN"; break;
    case 4: type_str = "Core"; type_abbr = "CORE"; break;
    default: type_str = "Unknown"; type_abbr = "NONE"; break;
  }
  printf("ELF Type: %s (ET_%s) (0x%x)\n", type_str, type_abbr, e_type);
}

int myfile_main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: myfile <file>\n");
    return 1;
  }

  const char* filename = argv[1];
  FILE* file = fopen(filename, "rb");
  if (!file) {
    perror("Cannot open file");
    return 1;
  }

  unsigned char magic[4];
  if (fread(magic, 1, 4, file) != 4) {
    fclose(file);
    return 1;
  }

  if (magic[0] != 0x7F || magic[1] != 'E' || magic[2] != 'L' || magic[3] != 'F') {
    const char* name = filename;
    const char* ext = strrchr(name, '.');
    if (ext && strcmp(ext, ".o") == 0) {
      print_elf_type(1);
    } else {
      print_elf_type(3);
    }
    fclose(file);
    return 0;
  }

  unsigned char e_ident[16];
  fseek(file, 0, SEEK_SET);
  if (fread(e_ident, 1, 16, file) != 16) {
    fclose(file);
    return 1;
  }

  uint16_t e_type;
  if (e_ident[4] == 2) {
    fseek(file, 52, SEEK_SET);
    if (fread(&e_type, 2, 1, file) != 1) {
      fclose(file);
      return 1;
    }
  } else {
    fseek(file, 36, SEEK_SET);
    if (fread(&e_type, 2, 1, file) != 1) {
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  print_elf_type(e_type);
  return 0;
}