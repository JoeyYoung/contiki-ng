#include "contiki.h"
#include "ext-flash.h"
#include <stdio.h> /* For printf() */

#define EXT_ERASE_UNIT_SIZE			4096UL

void
xmem_init(void)
{
  ext_flash_open();
}


int
xmem_pread(void *_p, int size, unsigned long offset)
{
	int rv;
  uint8_t x;
  int i;

  rv = ext_flash_open();

  if(!rv) {
    printf("Could not open flash to save config\n");
    ext_flash_close();
    return -1;
  }

  rv = ext_flash_read(offset, size, _p);
  for (i = 0; i < size; i++){
    x = ~*((uint8_t *)_p + i);
    *((uint8_t *)_p+i) = x;
  }

  ext_flash_close();

  if(rv)
  	return size;

  printf("Could not read flash memory!\n");
  return -1;
} 


int
xmem_pwrite(const void *_buf, int size, unsigned long addr)
{
	int rv;
  int i;
  uint8_t x;

  rv = ext_flash_open();

  if(!rv) {
    printf("Could not open flash to save config!\n");
    ext_flash_close();
    return -1;
  }

  for (i = 0; i < size; i++){
    x = ~*((uint8_t *)_buf + i);
    *((uint8_t *)_buf+i) = x;
  }

  rv = ext_flash_write(addr, size, _buf);

  ext_flash_close();

  if(rv)
  	return size;

  printf("Could not write flash memory!\n");
  return -1;
}


int
xmem_erase(long size, unsigned long addr)
{
	int rv;

  rv = ext_flash_open();


  if(!rv) {
    printf("Could not open flash to save config\n");
    ext_flash_close();
    return -1;
  }

  if(size % EXT_ERASE_UNIT_SIZE != 0) {
    printf("xmem_erase: bad size\n");
    return -1;
  }

  if(addr % EXT_ERASE_UNIT_SIZE != 0) {
    printf("xmem_erase: bad offset\n");
    return -1;
  }

  rv = ext_flash_erase(addr, size);



  ext_flash_close();

  if(rv)
  	return size;

  printf("Could not erase flash memory\n");
  return -1;
}