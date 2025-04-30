#include <iostream>
#include <fstream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>
#define PORT 9002
#define BUFFER_SIZE 1024

void listFiles(int clientSocket) {
    DIR* dir = opendir("./server_files");
    struct dirent* ent;
    std::string fileList = "";
    if (dir) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG)
                fileList += ent->d_name + std::string("\n");
        }
        closedir(dir);
    }
    send(clientSocket, fileList.c_str(), fileList.size(), 0);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    std::cout << "Server is listening on port " << PORT << std::endl;

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addr_size);
    std::cout << "Client connected!" << std::endl;

    read(clientSocket, buffer, BUFFER_SIZE);
    std::string command(buffer);

    if (command == "LIST") {
        listFiles(clientSocket);
    } else if (command.rfind("DOWNLOAD:", 0) == 0) {
        std::string filename = command.substr(9);
        std::ifstream file("server_files/" + filename, std::ios::binary);
        if (file) {
            file.read(buffer, BUFFER_SIZE);
            send(clientSocket, buffer, file.gcount(), 0);
        }
    } else if (command.rfind("UPLOAD:", 0) == 0) {
        std::string filename = command.substr(7);
        read(clientSocket, buffer, BUFFER_SIZE);
        std::ofstream file("server_files/" + filename, std::ios::binary);
        file.write(buffer, strlen(buffer));
    }

    close(clientSocket);
    close(serverSocket);
    return 0;
}
