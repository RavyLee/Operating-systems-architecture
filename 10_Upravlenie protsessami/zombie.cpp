#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    if (pid > 0) {
        // Родительский процесс
        std::cout << "Родительский процесс. PID дочернего процесса: " << pid << std::endl;
        // Родитель ждет 10 секунд, чтобы увидеть зомби-процесс
        sleep(10);
        // Родительский процесс ожидает завершения дочернего процесса
        wait(nullptr);
    } else {
        // Дочерний процесс
        std::cout << "Дочерний процесс. PID: " << getpid() << std::endl;
        // Завершаем дочерний процесс, чтобы он стал зомби
        _exit(0);
    }

    return 0;
}
