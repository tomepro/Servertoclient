# Aplicació Client-Servidor amb Sòcols TCP en C++

Aquesta aplicació implementa una comunicació client-servidor utilitzant sòcols TCP en C++. El servidor escolta connexions en un port específic, rep missatges del client i li envia una resposta.

## Funcionalitats

- **Servidor:**
  - Escolta connexions al port 8080.
  - Mostra per pantalla els missatges rebuts dels clients.
  - Envia una resposta fixa: *"Hola des del servidor!"*.

- **Client:**
  - Es connecta al servidor (localhost o 127.0.0.1).
  - Envia un missatge al servidor: *"Hola servidor!"*.
  - Mostra per pantalla la resposta del servidor.

## Requisits

- **Entorn Windows**
- Compilador que suporti C++ (ex.: MinGW).
- Llibreria Winsock (`ws2_32.lib`).

## Compilació i Execució

1. **Compilar el servidor:**
   ```bash
   g++ server.cpp -o server -lws2_32
