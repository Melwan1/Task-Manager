#include "task.h"

#include <stdio.h>
#include <stdlib.h>

#include "../utils/date/date.h"

struct task *task_create(char *due_date, char *tag, char *title, char *comment)
{
    if (!title)
    {
        fprintf(stderr, "Task-Manager: task_create: title must not be NULL");
        return NULL;
    }
    struct task *new_task = malloc(sizeof(*new_task));
    if (!new_task)
    {
        return NULL;
    }
    if (!due_date)
    {
        new_task->due_date = NULL;
    }
    else
    {
        new_task->due_date = build_timestamp(due_date);
    }
    new_task->creation_date = get_current_date();
    new_task->tag = tag;
    new_task->title = title;
    new_task->comment = comment;
    new_task->percentage = 0;
    return new_task;
}

void task_delete(struct task *task)
{
    free(task->due_date);
    free(task->creation_date);
    free(task);
}

static void print_line(int width)
{
    putchar(' ');
    for (int bar_index = 0; bar_index < width; bar_index++)
    {
        putchar('-');
    }
}

void task_print_completion(int percentage, int width)
{
    puts("Completion:");
    // the progress bar is, with percentage = 50 and width = 20:
    //
    //      --------------------
    //     |##########          | 50%
    //      --------------------
    print_line(width);
    putchar('|');
    for (int completion_index = 0; completion_index < width; completion_index++)
    {
        if (completion_index < width * percentage / 100)
        {
            putchar('#');
        }
        else
        {
            putchar(' ');
        }
    }
    putchar('|');
    printf(" %d%%\n", percentage);
print_line(width);
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
    task_print_completion(task->percentage, 50);
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
            task->tag = new_field; // the NULL tag is considered valid
            break;
        case TITLE:
            if (!new_field)
            {
                fprintf(stderr, "Task-Manager: task_change_field: a title is required");
                return;
            }
            task->title = new_field;
            break;
        case COMMENT:
            task->comment = new_field;
            break;
        case PERCENTAGE:
            int new_percentage = atoi(new_field);
            if (!verify_within_range(new_percentage, 0, 100))
            {
                fprintf(stderr, "Task-Manager: task_change_field: the new percentage is not between 0 and 100");
                return;
            }
            task->percentage = new_percentage;
            break;
        default:
            fprintf(stderr, "Task-Manager: task_change_field: unrecognized task field");
            break;
    }
}
