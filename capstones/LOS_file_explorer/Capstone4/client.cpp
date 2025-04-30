#include <iostream>
#include <fstream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 9002
#define BUFFER_SIZE 1024

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    std::string input;
    std::cout << "Enter command (LIST / DOWNLOAD:<filename> / UPLOAD:<filename>): ";
    getline(std::cin, input);

    send(sock, input.c_str(), input.length(), 0);

    if (input == "LIST") {
        read(sock, buffer, BUFFER_SIZE);
        std::cout << "Files on Server:\n" << buffer << std::endl;
    } else if (input.rfind("DOWNLOAD:", 0) == 0) {
        read(sock, buffer, BUFFER_SIZE);
        std::string filename = input.substr(9);
        std::ofstream file("client_" + filename, std::ios::binary);
        file.write(buffer, strlen(buffer));
        std::cout << "Downloaded: " << filename << std::endl;
    } else if (input.rfind("UPLOAD:", 0) == 0) {
        std::string filename = input.substr(7);
        std::ifstream file(filename, std::ios::binary);
        if (file) {
            file.read(buffer, BUFFER_SIZE);
            send(sock, buffer, file.gcount(), 0);
            std::cout << "Uploaded: " << filename << std::endl;
        } else {
            std::cout << "File not found!" << std::endl;
        }
    }

    close(sock);
    return 0;
}
