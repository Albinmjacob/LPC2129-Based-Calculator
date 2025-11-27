#include <lpc21xx.h>
#include "header.h"

char s[50];

int main()
{
    int i, num, a, b, n, o;
    int N[20];
    char O[20];

    uart0_init(9600);
    lcd_init();

    while (1)
    {
        uart0_tx_string("\r\nEnter Expression: ");

        // ------- LCD Input Section -------
        lcd_cmd(0x01);          // Clear for new input
        lcd_string("Expr:");

        // Read & display characters
        int k = 0;
        while (1)
        {
            char ch = uart0_rx();    // receive char
            uart0_tx(ch);            // echo to terminal

            if (ch == '\r' || ch == '\n')   // Enter pressed
            {
                s[k] = '\0';
                break;
            }
            s[k++] = ch;
            lcd_data(ch);     // show input live on LCD
        }

        // ------- Expression Evaluation -------
        n = o = num = 0;
        for (i = 0; s[i]; i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
                num = num * 10 + (s[i] - '0');

            else
            {
                N[n++] = num;
                num = 0;

                if (o > 0 && (O[o-1] == '*' || O[o-1] == '/'))
                {
                    b = N[--n];
                    a = N[--n];
                    char op = O[--o];
                    N[n++] = (op == '*') ? (a * b) : (a / b);
                }
                O[o++] = s[i];
            }
        }

        N[n++] = num;

        if (o > 0 && (O[o-1] == '*' || O[o-1] == '/'))
        {
            b = N[--n];
            a = N[--n];
            char op = O[--o];
            N[n++] = (op == '*') ? (a * b) : (a / b);
        }

        int result = N[0], p = 1;
        for (i = 0; i < o; i++)
            result = (O[i] == '+') ? (result + N[p++]) : (result - N[p++]);

        // ------- Display Result on UART -------
        uart0_tx_string("\r\nResult = ");
        uart0_tx_integer(result);
        uart0_tx_string("\r\n--------------------");

        // ------- Display Result on LCD (line 2) -------
        lcd_cmd(0xC0);
        lcd_string("Result=");
        lcd_integer(result);
				delay_sec(2);
    }
}
