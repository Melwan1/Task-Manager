#include "task.h"

#include <stdlib.h>

#include "../utils/date/date.h"

struct task *task_create(char *due_date, char *tag, char *title, char *comment)
{
    struct task *new_task = malloc(sizeof(*new_task));
    if (!new_task)
    {
        return NULL;
    }
    new_task->due_date = build_timestamp(due_date);
    new_task->creation_date = get_current_date();
    new_task->tag = tag;
    new_task->title = title;
    new_task->comment = comment;
    return new_task;
}

void task_delete(struct task *task)
{
    free(task->due_date);
    free(task->creation_date);
    free(task);
}

void task_print(struct task *task)
{
    if (!task)
    {
        return;
    }
    printf("Creation: ");
    print_timestamp(task->created_at);
    printf("Deadline: ");
    print_timestamp(task->due_date);
    printf("Tag: %s\n", task->tag);
    printf("Title: %s\n", task->title);
    printf("Comment: %s\n", task->title);
    fflush(stdout);
}
