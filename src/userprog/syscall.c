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
  int *esp = f->esp;
  int syscall_status = *esp;
  if (syscall_status == SYS_HALT)
  {
    halt();
  } else if (syscall_status == SYS_EXIT)
  {
    thread_current()->exit_status = true;
    thread_exit();
  }
  printf ("system call!\n");
  thread_exit ();
}

void
halt(void)
{
  shutdown_power_off();
}
