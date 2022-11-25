#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct _MUTEX_LOCK_STRUCT {

  tcb_t* waiting_list_head;
  tcb_t* waiting_list_tail;

} mutex_t;





#endif
