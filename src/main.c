#include "../lib/console.h"

int main(){
    __putc('O');
    __putc('S');
    __putc('1');
    __putc('\n');

    while(1){
        char c = __getc();
        __putc(c + 30);
    }
    
    return 0;
}