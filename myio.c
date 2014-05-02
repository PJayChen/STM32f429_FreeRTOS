#include <myio.h>
#include <String.h>

extern char* pUSARTtxData;

void _print(char *str){
    
    pUSARTtxData = str;
    
    //The Interrup will always assert when the TX register is empty(USART_IT_TXE == 1)
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}


//put string into default pipe defined in _print().
void uprintf(const char *format, ...){
    va_list ap;
    va_start(ap, format);
    int curr_ch = 0;
    char out_ch[2] = {'\0', '\0'};
    char newLine[3] = {'\n' , '\r', '\0'};
    char percentage[] = "%";
    char *str;
    char str_num[10];
    char *str_out = NULL;

    while( format[curr_ch] != '\0' ){
        
        if(format[curr_ch] == '%'){

            switch(format[curr_ch + 1]){
                case 's':
                    str = va_arg(ap, char *);
                    str_out = str;
                    break;
                case 'd':
                    itoa(va_arg(ap, int), str_num);
                    str_out = str_num;
                    break;
                case 'c':                  
                    out_ch[0] = (char)va_arg(ap, int);
                    str_out = out_ch;
                    break;
                case 'x':
                    xtoa(va_arg(ap, int), str_num);
                    str_out = str_num;
                    break;
                case '%':
                    str_out = percentage;
                    break;
                default:;
            }//End of switch(format[curr_ch + 1])

            curr_ch++;

        }else if(format[curr_ch] == '\n'){
            
            str_out = newLine;
        
        }else{
            
            out_ch[0] = format[curr_ch];
            str_out = out_ch;
        }
        curr_ch++;
        _print(str_out); //print on screen by syscall write()
    }//End of while( format[curr_ch] != '\0' )
    va_end(ap);
}//End of void printf(const char *format, ...)
