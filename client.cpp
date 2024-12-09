#include <iostream>
#include <winsock2.h> // Llibreria per a sòcols a Windows
#pragma comment(lib, "ws2_32.lib") // Enllaçar amb Winsock

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE] = {0};

    // Inicialitzar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error en inicialitzar Winsock." << std::endl;
        return 1;
    }

    // Crear el sòcol
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socol." << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar l'adreça del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connectar al servidor
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error al connectar amb el servidor." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << ">> Connexio establerta amb el servidor." << std::endl;

    // Enviar missatge al servidor
    const char* message = "Hola servidor!";
    send(clientSocket, message, strlen(message), 0);
    std::cout << ">> Enviant missatge: " << message << std::endl;

    // Rebre resposta del servidor
    int valread = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    std::cout << ">> Resposta del servidor: " << buffer << std::endl;

    // Tancar el sòcol
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
