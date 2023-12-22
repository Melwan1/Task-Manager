#include "task.h"

#include <stdio.h>
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
    print_timestamp(task->creation_date);
    printf("Deadline: ");
    print_timestamp(task->due_date);
    printf("Tag: %s\n", task->tag);
    printf("Title: %s\n", task->title);
    printf("Comment: %s\n", task->title);
    fflush(stdout);
}

void task_change_field(struct task *task, enum task_field field, char *new_field)
{
    if (!task)
    {
        fprintf(stderr, "Task-Manager: task_change_field: task is NULL");
        return;
    }
    switch(field)
    {
        case CREATION_DATE:
            free(task->creation_date);
            task->creation_date = NULL;
            if (!new_field)
            {
                task->creation_date = get_current_date();
            }
            else
            {
                task->creation_date = build_timestamp(new_field);
            }
            break;
        case DUE_DATE:
            if (!new_field)
            {
                fprintf(stderr, "[INFO] Task-Manager: task_change_field: new field is NULL");
            }
            free(task->due_date);
            task->due_date = NULL;
            struct timestamp *new_timestamp = build_timestamp(new_field);
            if (!new_timestamp)
            {
                fprintf(stderr, "Task-Manager: task_change_field: could not change field");
                return;
            }
            task->due_date = new_timestamp;
            break;
        case TAG:
            free(task->tag);
            task->tag = NULL;
            task->tag = new_field; // the NULL tag is considered valid
            break;
        case TITLE:
            if (!new_field)
            {
                fprintf(stderr, "Task-Manager: task_change_field: a title is required");
                return;
            }
            free(task->title);
            task->title = NULL;
            task->title = new_field;
            break;
        case COMMENT:
            free(task->comment);
            task->comment = NULL;
            task->comment = new_field;
            break;
        default:
            fprintf(stderr, "Task-Manager: task_change_field: unrecognized task field");
            break;
    }
}
