#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "cabecera.h"

using namespace std;

class Server {
public:
    int server, client;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];

    Server() {
        server = socket(AF_INET, SOCK_STREAM, 0);
        if (server < 0) {
            perror("Error al crear el socket");
            exit(EXIT_FAILURE);
        }

        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(5555);

        if (bind(server, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("Error al hacer bind");
            close(server);
            exit(EXIT_FAILURE);
        }

        if (listen(server, 0) < 0) {
            perror("Error al hacer listen");
            close(server);
            exit(EXIT_FAILURE);
        }

        cout << "Escuchando para conexiones entrantes." << endl;
        socklen_t clientAddrSize = sizeof(clientAddr);
        client = accept(server, (struct sockaddr *)&clientAddr, &clientAddrSize);
        if (client < 0) {
            perror("Error al aceptar conexión");
            close(server);
            exit(EXIT_FAILURE);
        }

        cout << "Cliente conectado!" << endl;
    }

    void Recibir() {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesReceived = recv(client, buffer, sizeof(buffer), 0);
        if (bytesReceived < 0) {
            perror("Error al recibir datos");
            close(client);
            exit(EXIT_FAILURE);
        } else if (bytesReceived == 0) {
            cout << "Cliente desconectado" << endl;
            close(client);
            exit(EXIT_SUCCESS);
        }
        cout << "El cliente dice: " << buffer << endl;
    }

    //void Enviar() {
     //   ssize_t bytesSent = send(client, buffer, sizeof(buffer), 0);
     //   if (bytesSent < 0) {
      ////      perror("Error al enviar datos");
       //     close(client);
      //      exit(EXIT_FAILURE);
      //  }
        //memset(buffer, 0, sizeof(buffer));
      //  cout << "Mensaje enviado!" << endl;
   // }

    void CerrarSocket() {
        close(client);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }
};

int main() {
    Server *Servidor = new Server();
    while (true) {
        main2();
        //Servidor->Recibir();

        //const char *mensaje ="\nBIENVENIDO A HOTEL 33""\n1. Iniciar Sesion\n2. Registrar Usuario\n3. Salir del programa\nIntroduzca la opcion deseada:"; 
        //Servidor->Enviar(mensaje);
    }
}