/* Check if the compiler thinks you are targeting the wrong operating system */
#if defined(__linux__)
#error "To Compile AtOS, you have to use a cross-compiler"
#endif

/* Can only compile for 32-bit ix86 targets. */
#if !defined(__i386__)
#error "You need an ix86-elf compiler to build AtOS"
#endif

#include "kernel_keyboard.h"
#include "gdt.h"
#include "interrupts.h"
#include "irqs.h"
#include "heap.h"
#include "clock.h"


int kmain(void) {
  
  pd_remove_entry(0); 	// Remove identity mapping

  /* Initialize terminal interface */
  terminal_initialize();

  bitmap_mark_kernel();

  perry(25, 5);

  setup_gdt();
  setup_idt();
  init_irq();
  setup_clock();

  int* hello = malloc(20);
  memset(hello, 69, 20);

  //PRINTNH(hello);
  
  int* hi = malloc(30);
  
  //PRINTNH(hi);

  free(hi);
  free(hello);

  int x = 10 / 0;
  //PRINTN(x);
  /* while (true) {
    cursor_update(0, 0);
    cmos_time time = read_rtc();
    PRINT(ttoa(time));
    sleep(1000);
  } */

  return 0;
}

