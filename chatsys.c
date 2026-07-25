#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define maxlimit 255
char bitVal[8];

void bin(char c){
    int binVal[8] = {0};
    int x;
    x = (int)c;
    for(int i=7; i>=0; i--){
        binVal[i] = x % 2;
        x = x/2;
    }
    for (int j=0; j<8;j++){
        bitVal[j]=binVal[j];
        
    }
}

int main(){
char l1[maxlimit+1];
int i=0;
    do{
        for(;;){

            l1[i] = getch();
                if(l1[i]=='\r'){
                        l1[i] = '\0';
                        break;    
                    }
                    
                    else{
                        if(i<=maxlimit-1){
                            printf("%c", l1[i]);
                            i++;
                        }else{
                            printf("Word limit exceeded");
                        }
                    }

            
                }
                break;
        
    }while(1);

HANDLE esp = CreateFile(
    "\\\\.\\COM7",
    GENERIC_READ | GENERIC_WRITE,
    0,
    NULL,
    OPEN_EXISTING,
    0,
    NULL
);

if (esp == INVALID_HANDLE_VALUE)
{
    printf("\nFailed to open COM7!\n");
    return 1;
}

/*-----------------------------------------------*/
/*Config Settings*/
DCB dcbSerial = {0};
dcbSerial.DCBlength = sizeof(DCB);
if (!GetCommState(esp, &dcbSerial))
{
    printf("Couldn't read COM settings.\n");
    CloseHandle(esp);
    return 1;
}

GetCommState(esp, &dcbSerial);

dcbSerial.BaudRate = CBR_115200;
dcbSerial.ByteSize = 8;
dcbSerial.StopBits = ONESTOPBIT;
dcbSerial.Parity = NOPARITY;

SetCommState(esp, &dcbSerial);


/*-----------------------------------------------*/


for (int k=0;k<255;k++){
    if(l1[k]=='\0'){
    break;
    }
    else{
        bin(l1[k]);

        for(int j=0;j<8;j++)
{
    DWORD bytesWritten;

    WriteFile(
        esp,
        &bitVal[j],
        1,
        &bytesWritten,
        NULL
    );
}

    }
    Sleep(300); /*I set this to 100 only for testing of an LED, set it to 0 for actual use*/
}


CloseHandle(esp);
return 0;
}