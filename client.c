#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ошибка создания сокета");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование IP-адреса из текстового в бинарный формат
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Неверный адрес");
        return -1;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Не удалось установить соединение");
        return -1;
    }

    // Формирование данных студента
    char *student_info = "Проказов Никита Юрьевич, Группа: ККСО-26-24, Курс: 1";

    // Отправка данных серверу
    send(sock, student_info, strlen(student_info), 0);
    printf("Данные студента отправлены серверу\n");

    // Чтение ответа от сервера
    read(sock, buffer, BUFFER_SIZE);
    printf("Ответ сервера: %s\n", buffer);

    close(sock);
    return 0;
}
