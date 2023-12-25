#ifndef MANAGER_H
#define MANAGER_H

struct task_category
{
    char *name;
    int task_count;
    struct task **tasks; // array of pointers to tasks 
};

#endif /* !MANAGER_H */
