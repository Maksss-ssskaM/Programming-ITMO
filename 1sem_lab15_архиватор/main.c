#include <stdio.h>
#include <locale.h>

FILE* createArchive(char* archiveName, int fileCount) //Создание архива
{
    FILE* archive = fopen(archiveName, "wb");
    fwrite("arh", sizeof(char), 3, archive); //Отличать свой архив от других
    fwrite(&fileCount, sizeof(int), 1, archive); //Размер элемента//Кол-во элементов.
    return archive;
}

int addFileToArchive(FILE* archive, char* fileName) //Добавляю файлы в архив
{
    FILE* inputFile = fopen(fileName, "rb");
    if (inputFile == NULL)
    {
        printf("Таких файлов нет %s\n", fileName);
        return 1;
    }

    // Запись имени файла
    for (unsigned long i = 0; i < strlen(fileName); ++i)
    {
        char buffer = *(fileName + i);
        fwrite(&buffer, sizeof(char), 1, archive);
    }

    // Отделяет название файла
    unsigned char flagByte = 0xFF;
    fwrite(&flagByte, sizeof(char), 1, archive);

    // Место под длину файла
    char zeroByte = 0x0;                                                                                // Нулевой байт
    long pointerOnPlaceForSize = ftell(archive);                                                        // Создаю позицию на место, куда потом
    fwrite(&zeroByte, sizeof(unsigned long long), 1, archive);                                          // запишу размер, пока что заполняю нулями.
    //Данные файла в байт
    unsigned long long bytesWritten = 0; //Это длина
    char buffer;
    while (fread(&buffer, sizeof(char), 1, inputFile) != 0)                                              //Нахожу в цикле длину
    {
        fwrite(&buffer, sizeof(char), 1, archive);
        bytesWritten += 1;
    }
    //Конец файла
    long fileEnd = ftell(archive);
    fseek(archive, pointerOnPlaceForSize, SEEK_SET);                                                     //Возвращаюсь к буферу
    fwrite(&bytesWritten, sizeof(unsigned long long), 1, archive);                                       //Записываю в уже зараннеее выделенные байты размер.
    fseek(archive, fileEnd, SEEK_SET);
    return 0;
}

void extractArchive(char* archiveName) //извлечение архива
{
    FILE* archive = fopen(archiveName, "rb");
    char* buffer = calloc(1, sizeof(char) * 3);
    fread(buffer, sizeof(char), 3, archive);
    if (strcmp(buffer, "arh") != 0)
    {
        printf("Архив повреждён\n");
        return;
    }

    int fileCount = 0;
    fread(&fileCount, sizeof(int), 1, archive);

    unsigned long long offset;
    char* bufferName;
    unsigned char bufferByte;

    FILE* outputFile;
    unsigned long long fileSize;
    for (int i = 0; i < fileCount; ++i)
    {
        bufferName = calloc(1, sizeof(char));
        *bufferName = '\0';
        bufferByte = 0;

        fread(&bufferByte, sizeof(char), 1, archive);
        offset = 1;
        while (bufferByte != 0xFF)
        {
            realloc(bufferName, offset);
            *(bufferName + offset - 1) = bufferByte;
            fread(&bufferByte, sizeof(char), 1, archive);
            offset++;
        }
        *(bufferName + offset - 1) = '\0';

        outputFile = fopen((const char*)bufferName, "wb");
        free(bufferName);
        fileSize = 0;
        fread(&fileSize, sizeof(unsigned long long), 1, archive);
        for (unsigned long long j = 0; j < fileSize; ++j)
        {
            fread(&bufferByte, sizeof(char), 1, archive);
            fwrite(&bufferByte, sizeof(char), 1, outputFile);
        }
        fclose(outputFile);
    }
}

void printList(char* archiveName) //содержимое архива
{
    FILE* archive = fopen(archiveName, "rb");
    char* buffer = calloc(1, sizeof(char) * 3);
    fread(buffer, sizeof(char), 3, archive);
    if (strcmp(buffer, "arh") != 0)
    {
        printf("Архив повреждён\n");
        return;
    }
    printf("Список файлов:\n");
    int number_of_files = 0;
    fread(&number_of_files, sizeof(int), 1, archive);

    unsigned long long offset;
    char* bufferName;
    unsigned char bufferByte;

    for (int i = 0; i < number_of_files; ++i)
    {
        bufferName = calloc(1, sizeof(char));
        *bufferName = '\0';
        bufferByte = 0;

        fread(&bufferByte, sizeof(char), 1, archive);
        offset = 1;
        while (bufferByte != 0xFF)
        {
            realloc(bufferName, offset);
            *(bufferName + offset - 1) = bufferByte;
            fread(&bufferByte, sizeof(char), 1, archive);
            offset++;
        }
        *(bufferName + offset - 1) = '\0';

        printf("%s\n", bufferName);
        free(bufferName);

        // Пропуск данных
        unsigned long long fileSize = 0;
        fread(&fileSize, sizeof(unsigned long long), 1, archive);
        fseek(archive, fileSize, SEEK_CUR);
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    if (argc < 4)
    {
        printf("Ложные аргументы!\nПопробуйте одну из команд:\n1) --file <archive name> --create <list_of_files>\n2)  --file <archive name> --list\n3) --file <archive name> --extract\n");
    }
    char* archiveName;
    if (strcmp(argv[1], "--file") == 0)
    {
        archiveName = malloc(sizeof(argv[2]));
        strcpy(archiveName, argv[2]);
    }
    else
    {
        printf("Ложные аргументы!\nПопробуйте одну из команд:\n1) --file <archive name> --create <list_of_files>\n2)  --file <archive name> --list\n3) --file <archive name> --extract\n");
        return 1;
    }
    if (strcmp(argv[3], "--extract") == 0)
    {
        extractArchive(archiveName);
        printf("Архив %s успешно извлечён\n", archiveName);
    }
    else if (strcmp(argv[3], "--list") == 0)
    {
        printList(archiveName);
    }
    else if (strcmp(argv[3], "--create") == 0)
    {
        FILE* archive = createArchive(archiveName, argc - 4);
        for (int i = 4; i < argc; ++i)
        {
            addFileToArchive(archive, argv[i]);
        }
        fclose(archive);
        printf("Архив %s успешно создан\n", archiveName);
    }
    else
    {
        printf("Ложные аргументы!\nПопробуйте одну из команд:\n1) --file <archive name> --create <list_of_files>\n2)  --file <archive name> --list\n3) --file <archive name> --extract\n");
        return 1;
    }
    return 0;
}
