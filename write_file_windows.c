#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile = CreateFile(
        "file.txt",            // имя файла
        GENERIC_WRITE,         // доступ на запись
        0,                     // совместный доступ (нет)
        NULL,                  // атрибуты безопасности
        CREATE_ALWAYS,         // создать новый файл или перезаписать
        FILE_ATTRIBUTE_NORMAL, // обычный файл
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Ошибка открытия файла: %lu\n", GetLastError());
        return 1;
    }

    printf("Введите текст (Ctrl+Z и Enter для завершения):\n");
    char buffer[1024];
    DWORD written;
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (!WriteFile(hFile, buffer, (DWORD)strlen(buffer), &written, NULL)) {
            printf("Ошибка записи: %lu\n", GetLastError());
            CloseHandle(hFile);
            return 1;
        }
    }

    CloseHandle(hFile);
    printf("Текст успешно записан.\n");
    return 0;
}
