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
