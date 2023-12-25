#ifndef MANAGER_H
#define MANAGER_H

struct task_category
{
    char *name;
    struct task **tasks; // array of pointers to tasks 
};

#endif /* !MANAGER_H */
