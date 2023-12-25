#include "manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../task/task.h"

struct task_category *create_category(char *name)
{
    if (!name)
    {
        fprintf("Task-Manager: create_category: could not create, name is NULL\n");
        return NULL;
    }
    struct task_category *new_category = malloc(sizeof(*new_category));
    if (!new_category)
    {
        fprintf("Task-Manager: create_category: malloc failed\n");
        return NULL;
    }
    new_category->name = name;
    new_category->task_count = 0;
    new_category->tasks = malloc(sizeof(struct task));
    if (!new_category->tasks)
    {
        free(new_category);
        fprintf("Task-Manager: create_category: malloc failed\n");
        return NULL;
    }
    new_category->tasks[0] = NULL;
    return new_category;
}

void category_destroy(struct task_category *category)
{
    if (!category)
    {
        return;
    }
    free(category->tasks);
    free(category);
}
