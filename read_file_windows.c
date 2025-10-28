#include <windows.h>
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(0, "Russian");
    HANDLE hFile = CreateFile(
        "file.txt",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("ошибочка открытия файла: %lu\n", GetLastError());
        return 1;
    }

    printf("введите текст:\n");
    char buffer[1024];
    DWORD written;
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (!WriteFile(hFile, buffer, (DWORD)strlen(buffer), &written, NULL)) {
            printf("ошибка записи: %lu\n", GetLastError());
            CloseHandle(hFile);
            return 1;
        }
    }

    CloseHandle(hFile);
    printf("ТЕКСТ УСПЕШНО ЗАПИСАН!\n");
    return 0;
}
