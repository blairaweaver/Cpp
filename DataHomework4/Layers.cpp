//
// Created by blair on 2/18/2020.
//
#include "stdio.h"
#include "string.h"
#include <iostream>

void presentationLayer(char *buffer, int i);

void sessionLayer(char *buffer, int i);

void transportLayer(char *buffer, int i);

void networkLayer(char *buffer, int i);

void dataLinkLayer(char *buffer, int i);

void physicalLayer(char *buffer, int i);

using namespace std;

void applicationLayer(char *buffer, int msize){
    char* header = "Application_Layer_Header";
    int hsize = strlen(header);
    char* buffer2 = (char*)malloc(msize+hsize);
    memcpy(buffer2, header, hsize);
    memcpy(buffer2 + hsize, buffer, msize);
    cout << buffer2 << endl;
    presentationLayer(buffer2, hsize+msize);
}

void presentationLayer(char *buffer, int msize){
    char* header = "Presentation_Layer_Header";
    int hsize = strlen(header);
    char* buffer2 = (char*)malloc(msize+hsize);
    memcpy(buffer2, header, hsize);
    memcpy(buffer2 + hsize, buffer, msize);
    cout << buffer2 << endl;
    sessionLayer(buffer2, hsize+msize);
}

void sessionLayer(char *buffer, int msize){
    char* header = "Session_Layer_Header";
    int hsize = strlen(header);
    char* buffer2 = (char*)malloc(msize+hsize);
    memcpy(buffer2, header, hsize);
    memcpy(buffer2 + hsize, buffer, msize);
    cout << buffer2 << endl;
    transportLayer(buffer2, hsize+msize);
}

void transportLayer(char *buffer, int msize){
    char* header = "Transport_Layer_Header";
    int hsize = strlen(header);
    char* buffer2 = (char*)malloc(msize+hsize);
    memcpy(buffer2, header, hsize);
    memcpy(buffer2 + hsize, buffer, msize);
    cout << buffer2 << endl;
    networkLayer(buffer2, hsize+msize);
}

void networkLayer(char *buffer, int msize){
    char* header = "Network_Layer_Header";
    int hsize = strlen(header);
    char* buffer2 = (char*)malloc(msize+hsize);
    memcpy(buffer2, header, hsize);
    memcpy(buffer2 + hsize, buffer, msize);
    cout << buffer2 << endl;
    dataLinkLayer(buffer2, hsize+msize);
}

void dataLinkLayer(char *buffer, int msize){
    char* header = "DataLink_Layer_Header";
    int hsize = strlen(header);
    char* buffer2 = (char*)malloc(msize+hsize);
    memcpy(buffer2, header, hsize);
    memcpy(buffer2 + hsize, buffer, msize);
    cout << buffer2 << endl;
    physicalLayer(buffer2, hsize+msize);
}

void physicalLayer(char *buffer, int msize){
    char* header = "Physical_Layer_Header";
    int hsize = strlen(header);
    char* buffer2 = (char*)malloc(msize+hsize);
    memcpy(buffer2, header, hsize);
    memcpy(buffer2 + hsize, buffer, msize);
    cout << buffer2 << endl;
    cout << strlen(buffer2) << endl;
}


int main() {
    char* message = "This is my message, which contains things like the number 25 and symbols like $. You could include an email address like testperson@gmail.com. This is so fun! Actually, his password is "
                    " kinda lame. It is !@#$%^&*(). He just goes over the top row with the shift key. See ya, Person";
    cout << strlen(message) << endl;
    applicationLayer(message, strlen(message));
}