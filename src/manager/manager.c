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

void destroy_category(struct task_category *category)
{
    if (!category)
    {
        return;
    }
    free(category->tasks);
    free(category);
}

struct task_category *add_task_in_category(struct task_category *category, struct task *task)
{
    if (!category)
    {
        if (!task || !task->tag)
        {
            return NULL;
        }
        category = create_category(task->tag);
        return add_task_in_category(category, task);
    }
    if (!task)
    {
        return category;
    }
    category->tasks = realloc(category->tasks, sizeof(struct task *) * (++category->task_count));
    category->tasks[category->task_count - 1] = task;
    return category;
}
