#include <iostream>
#include <winsock2.h> // Llibreria per a sòcols a Windows
#pragma comment(lib, "ws2_32.lib") // Enllaçar amb Winsock

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE] = {0};

    // Inicialitzar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error en inicialitzar Winsock." << std::endl;
        return 1;
    }

    // Crear el sòcol
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socol." << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar l'adreça del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Assignar el sòcol al port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error al bind." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Esperar connexions
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        std::cerr << "Error al listen." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << ">> Esperant connexions..." << std::endl;

    // Acceptar connexions
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al acceptar connexio." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Rebre missatge del client
    int valread = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    std::cout << ">> Missatge rebut del client: " << buffer << std::endl;

    // Enviar resposta al client
    const char* response = "Hola des del servidor!";
    send(clientSocket, response, strlen(response), 0);
    std::cout << ">> Resposta enviada al client." << std::endl;

    // Tancar el sòcol
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
