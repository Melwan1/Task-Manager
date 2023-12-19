#include "task.h"

struct task *task_create(char *due_date, char *tag, char *title, char *comment)
{
    struct task *new_task = malloc(sizeof(*new_task));
    if (!new_task)
    {
        return NULL;
    }
    new_task->due_date = get_current_date(due_date);
    new_task->tag = tag;
    new_task->title = title;
    new_task->comment = comment;
    return new_task;
}
