#ifndef SYSCALLS_CPU_H
#define SYSCALLS_CPU_H

void dump_memory();
void io();
void process_create();
void thread_create();
void thread_join();
void thread_cancel();
void mutex_create();
void mutex_lock();
void mutex_unlock();
void thread_exit();
void process_exit();

#endif