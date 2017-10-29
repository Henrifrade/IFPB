#define BUFFSIZE 64
#define MESSAGESIZE 70
#define FILENAMESIZE 70

#include <sys/types.h>  // data types
#include <sys/stat.h>   // large file support
#include <stdio.h>      // sizeof, do while, if else, return
#include <stdlib.h>     // alocação de memória, controle de processos, conversões e outras.
#include <fcntl.h>      // argumentos de open O_CREAT, O_EXCL, O_RDWR, etc
#include <unistd.h>     // read, write, close

int main() {
  int filedestination, filesource;                          // guarda oq do arq origem e destino?
  int size;                                                 // tamanho do arquivo
  char source_filename[FILENAMESIZE] = "";                  // nome do arquivo de origem
  char copy_filename[FILENAMESIZE] = "";                    // nome do arquivo de destino
  char buffer[BUFFSIZE] = "";                               // tamanho do buffer (64 pelo define)
  char notify_message[MESSAGESIZE]  = "\nDigite o nome do arquivo de origem a ser copiado: ";
  char notify_message2[MESSAGESIZE] = "\nNome do arquivo de destino ou a ser criado: ";
  char notify_message3[MESSAGESIZE] = "\nArquivo de origem copiado com sucesso!\n";
  char failed_message[MESSAGESIZE]  = "\nEste arquivo ja existe\n";
  char failed_message2[MESSAGESIZE] = "\nFalha, nao foi encontrado arquivo com esse nome\n";

/// Origem
  write(1, notify_message, sizeof(notify_message));         // escreve a mensagem (standard output, texto, tamanho do char notify_message)
  size = read(0, source_filename, sizeof(source_filename)); // tamanho recebe (standard input, nome do arquivo de origem, tamanho do arquivo de origem)
  source_filename[size-1] = source_filename[size];          // guarda o nome do arquivo de origem sem o \0

/// Destino
  write(1, notify_message2, sizeof(notify_message2));       // escreve a mensagem (standard output, texto, tamanho do char notify_message2)
  size = read(0, copy_filename, sizeof(copy_filename));     // tamanho recebe (standard input, nome do arquivo de origem, tamanho do arquivo de origem)
  copy_filename[size-1] = copy_filename[size];              // guarda o nome do arquivo de destino sem o \0

/// Abrir o arquivo Origem
  filesource = open(source_filename, O_RDWR);               // recebe o valor da funcao open apos a leitura do arquivo com o argumento read/write

/// Erro por nome invalido

  if (filesource == -1) {                                   // se for -1 exibe a msg de failed_message2
    write(1, failed_message2, sizeof(failed_message));      // ---
    exit(1);                                                // encerra (standard output)
  }else{                                                   // se nao o arquivo de copia é criado (nome do arquivo de copia, cria se o arquivo nao existir, testa se tem algum arquivo com esse nome(se tiver o open() da erro), permissao de ler e escrever, permite acesso total ao arquivo a todos os usuarios(valor octal))

/// Criar novo arquivo

    filedestination = open(copy_filename, O_CREAT | O_EXCL | O_RDWR, 0777);

/// Erro arquivo já existe

    if (filedestination == -1){                             // se for -1 exibe a msg de failed_message
      write(1, failed_message, sizeof(failed_message));     // ---
      exit(1);                                              // encerra (standard output)
    }else {                                                 // se nao faça tamanho recebe o arquivo de origem, do buffer, de 64 em 64)

/// Caso não de erro escreve o arquivo

      do {
        size = read(filesource, buffer, BUFFSIZE);          // ---
        write(filedestination, buffer, size);               // e escreve o dado de arquivo de destino, buffer, com o tamanho de size
      } while (size > 0);                                   // enquanto ainda tiver buffer em size
    }

/// Notificacao de arquivo criado

        write(1, notify_message3, sizeof(notify_message));         // escreve a mensagem (standard output, texto, tamanho do char notify_message3)
  }

/// Encerra os arquivos abertos

  close(filesource);                                        // fecha o open de filesource
  close(filedestination);                                   // fecha o open de filedestination

  return 0;
}
