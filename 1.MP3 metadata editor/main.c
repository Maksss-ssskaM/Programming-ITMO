#include <stdio.h>
#include <locale.h>
struct tag
{
    char id[3];
    char vers;
    char subvers;
    int flag;
    int size;
};

struct frame
{
    char name[4];
    int size;
    char f1, f2;
};

void Copy(FILE *Input, FILE *Output)
{
    int Char;
    while ((Char = getc(Input)) != EOF)
    {
        putc(Char, Output);
    }
}

void enter_tag(FILE *file, struct tag *a)
{
    fscanf(file, "%c%c%c", &(a->id[0]), &(a->id[1]), &(a->id[2]));
    char temp;
    fscanf(file, "%c", &temp);
    a->vers = temp;
    fscanf(file, "%c", &temp);
    a->subvers = temp;
    fscanf(file, "%c", &temp);
    a->flag = (int)temp;
    char t1, t2, t3, t4;
    fscanf(file, "%c%c%c%c", &t1, &t2, &t3, &t4);
    a->size = (int)t4 + 128 * (int)t3 + 128 * 128 * (int)t2 + 128 * 128 * 128 *(int)t1;
}

void enter_frame(FILE *file,struct frame *a)
{
    fscanf(file, "%c%c%c%c", &(a->name[0]), &(a->name[1]), &(a->name[2]), &(a->name[3]));
    char t1, t2, t3, t4;
    fscanf(file, "%c%c%c%c", &t1, &t2, &t3, &t4);
    a->size = (int)t4 + 128 * (int)t3 + 128 * 128 * (int)t2 + 128 * 128 * 128 *(int)t1;
    fscanf(file, "%c%c", &(a->f1), &(a->f2));
}

void show_frame(FILE *file, struct frame *a)
{
    char t;
    for(int i = 0; i < a->size; i++)
    {
        fscanf(file, "%c", &t);
        printf("%c", t);
    }
}

void show_all(FILE *file)
{
    fseek(file, 0, 0);
    struct tag a;
    struct frame b;
    enter_tag(file, &a);
    for(int i = a.size; i > 0 ;)
    {
        enter_frame(file, &b);
        printf("%c%c%c%c ", b.name[0], b.name[1], b.name[2], b.name[3]);
        i = i - b.size - 10;
        show_frame(file, &b);
        printf("\n");
    }
    fseek(file, 0, 0);
}

void show_name(FILE *file, char *name)
{
    fseek(file, 0, 0);
    struct tag a;
    struct frame b;
    enter_tag(file, &a);
    for(int i = a.size; i > 0;)
    {
        enter_frame(file, &b);
        i = i - b.size - 10;
        if(b.name[0] == name[0] && b.name[1] == name[1] && b.name[2] == name[2] && b.name[3] == name[3])
        {
            printf("%c%c%c%c:", name[0], name[1], name[2], name[3]);
            show_frame(file, &b);
            printf("\n");
            return;

        }
        fseek(file, b.size, 1);
    }
    printf("ERROR");
    fseek(file, 0, 0);
}

void new_data(FILE *file, char *name, char *data, int dsize)
{
    fseek(file, 0, 0);
    struct tag a;
    struct frame b;
    enter_tag(file, &a);
    char temp;
    int t = 10;
    for(int i = a.size; i > 0;)
    {
        enter_frame(file, &b);
        if(b.name[0] == name[0] && b.name[1] == name[1] && b.name[2] == name[2] && b.name[3] == name[3])
        {
            break;
        }
        fseek(file, b.size, 1);
        t = t + 10 + b.size;
        i = i - b.size - 10;
    }

    int new_size = a.size - b.size + dsize;
    char t1;
    char t2;
    char t3;
    char t4;
    t4 = (char)(new_size % 128);
    new_size = (new_size - (new_size % 128)) / 128 >> 1;
    t3 = (char)new_size;
    new_size = (new_size - (new_size % 128)) / 128 >> 1;
    t2 = (char)new_size;
    new_size = (new_size - (new_size % 128)) / 128 >> 1;
    t1 = (char)new_size;
    printf("successfully");
    FILE *copy = fopen("unknown.mp3", "wb");
    fprintf(copy, "%c%c%c", 'I', 'D', '3');
    fprintf(copy, "%c%c", a.vers, a.subvers);
    fprintf(copy, "%d", a.flag);
    fprintf(copy, "%c%c%c%c", t1, t2, t3, t4);
    fseek(file, 10, 0);
    for(int i = 0; i < t - 10; i++)
    {
        fscanf(file, "%c", &temp);
        fprintf(copy, "%c", temp);
    }
    for(int i = 0; i < 4; i++)
    {
        fscanf(file, "%c", &temp);
        fprintf(copy, "%c", temp);
    }
    new_size = dsize;
    t4 = (char)new_size;
    new_size = (new_size - (new_size % 128)) / 128 >> 1;
    t3 = (char)new_size;
    new_size = (new_size - (new_size % 128)) / 128 >> 1;
    t2 = (char)new_size;
    new_size = (new_size - (new_size % 128)) / 128 >> 1;
    t1 = (char)new_size;
    fprintf(copy, "%c%c%c%c", t1, t2, t3, t4);
    fprintf(copy, "%c%c", b.f1, b.f2);
    for(int i = 0; i < dsize; i++)
    {
        fprintf(copy, "%c", data[i]);
    }
    fseek(file, t + b.size + 10, 0);
    Copy(file, copy);
    close(copy);

}

void copy_to_normal(FILE *file)
{
    fseek(file, 0, 0);
    FILE *a = fopen("unknown.mp3", "rb");
    Copy(a, file);
    remove("unknown.mp3");
    close(a);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    int size;
    char *FileName = NULL, *FrameName = NULL, *Value = NULL, ShowFlag = 0, SetFlag = 0, GetFlag = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--show") == 0)
        {
            ShowFlag = 1;
            continue;
        }
        if (argv[i][2] == 'f') //filepath
        {
            FileName = strpbrk(argv[i], "=") + 1;
        }
        if (argv[i][2] == 'g') //get
        {
            GetFlag = 1;
            FrameName = strpbrk(argv[i], "=") + 1;
            continue;
        }
        if (argv[i][2] == 's') //set
        {
            SetFlag = 1;
            FrameName = strpbrk(argv[i], "=") + 1;
            continue;
        }
        if (argv[i][2] == 'v') //value
        {
            size = sizeof(argv[i]);
            Value = strpbrk(argv[i], "=") + 1;
            continue;
        }
    }
    FILE *file = fopen(FileName, "rb");
    if (ShowFlag)
    {
        show_all(file);
    }
    if (GetFlag)
    {
        show_name(file, FrameName);
    }
    if (SetFlag)
    {
        new_data(file, FrameName, Value, size);
        file = fopen(FileName, "wb");
        copy_to_normal(file);
    }
    close(file);
    return 0;
}

