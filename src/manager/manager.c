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
    new_category->tasks = NULL;
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

int find_index_of_element(void **array, void *element, int size)
{
    for (int array_index = 0; array_index < size; array_index++)
    {
        if (array[array_index] == element)
        {
            return array_index;
        }
    }
    return -1; // element has not been found in the array
}

void remove_at_in_array(void **array, int size, int index)
{
    for (int other_index = 0; other_index < size - 1; other_index++)
    {
        array[other_index] = array[other_index + 1];
    }
}

struct task_category *remove_task_from_category(struct task_category *category, struct task *task)
{
    if (!category)
    {
        fprintf("Task-Manager: remove_task_from_category: category is NULL, could not remove from it\n");
        return NULL;
    }
    if (!task)
    {
        fprintf("[INFO] Task-Manager: remove_task_from_category: task is NULL, nothing has been removed\n");
        return category;
    }
    int task_index = find_index_of_element(category->tasks, task, category->task_count);
    if (task_index == -1)
    {
        fprintf("Task-Manager: remove_task_from_category: task has not been found, remove failed\n");
        return category;
    }
    remove_at_in_array(category->tasks, category->task_count, task_index);
    category->tasks = realloc(category->tasks, sizeof(struct task *) * (--category->task_count));
    return category;
}
