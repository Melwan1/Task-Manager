#ifndef TASK_H
#define TASK_H

enum task_field
{
    CREATION_DATE = 0,
    DUE_DATE,
    TAG,
    TITLE,
    COMMENT,
    PERCENTAGE,
    ERROR
};

struct task 
{
    struct timestamp *due_date;
    struct timestamp *creation_date;
    char *tag;
    char *title;
    char *comment;
    int percentage; // between 0 and 100
};

/* task_create
** Creates a task and returns it.
** params: 
**
** - due_date: string, represents the due_date. The format of the string is "YYYY-MM-DD HH:MM:SS".
** - tag: string, the tag of the task. Looks like "CPXA", "STA", "NET1", ...
** - title: string, the title of the task, essentially what to do.
** - comment: string or NULL, an optional comment of the task.
** 
** return: a pointer to the created task.
*/ 

struct task *task_create(char *due_date, char *tag, char *title, char *comment);

/* task_delete
** Deletes a task.
** params:
**
** - task: the task to delete.
**
** return: void
*/

void task_delete(struct task *task);

/* task_print_completion
** Prints the percentage of the task in a pretty way.
**
** params:
**
** - percentage: the percentage of completion of the task
** - width: the width of the progress bar, excluding the pipes at both ends and the percentage at the right.
**
** return: void
*/

void task_print_completion(int percentage, int width);

void task_print(struct task *task);

void task_change_field(struct task *task, enum task_field field, char *new_field);

#endif /* !TASK_H */
