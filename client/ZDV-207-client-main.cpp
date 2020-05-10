//
//  main.cpp
//  client
//
//  Created by Daniil Zakharov on 23.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#include <iostream>
#include <thread>
#include "ZDV-207-client.h"
int main() {
    
    for(int  i = 0; i < 4; i++){
        char inbuf [200];
        sprintf(inbuf, "command%d.txt", i);
        FILE * fin = fopen(inbuf, "r"); //Отсюда берём команды
        sprintf(inbuf, "result%d.txt", i);
        FILE * fout = fopen(inbuf, "w"); //Сюда будем писать ответ сервера
        //FILE *client;
        if(!fin || !fout){
            perror("error opening file");
            continue;
        }
        std::thread([=](){
            char cmbuf [4096];
            char rdbuf [4096];
            int cmdno = 0;
            while (fgets(cmbuf, 4095, fin)) {
                cmbuf[strlen(cmbuf)-1]=0; //Уберём символ перехода строки, иначе плохо
                FILE * client = Client::request(cmbuf, "127.0.0.1", 3228); // Получаем ответ сервера
                while (fgets(rdbuf, 4095, client)) {
                    fprintf(fout, "%s", rdbuf); //Печатаем ответ
                }
                printf("Thread:%d command:%d finished\n", i,cmdno++);
                
            }
            fclose(fout);
            printf("process %d finished\n", i);
        }).detach();
        
        
    }
    char rd[10];
    scanf("%s",rd);
    
    

    
    
    return 0;
}
