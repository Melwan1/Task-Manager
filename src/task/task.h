#ifndef TASK_H
#define TASK_H

struct timestamp
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct task 
{
    int id;
    struct timestamp due_date;
    struct timestamp creation_date;
    char *tag;
};

#endif /* !TASK_H */
