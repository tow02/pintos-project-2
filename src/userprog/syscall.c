#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "devices/shutdown.h"
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED)
{
  switch (* (int *) f->esp)
  {
    case SYS_HALT:
      halt();
      break;
  }
  printf ("system call!\n");
  thread_exit ();
}

void
halt(void)
{
  shutdown_power_off();
}
