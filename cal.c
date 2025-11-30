#include <lpc21xx.h>
#include "header.h"
char exp[60];
int idx;
int errorFlag = 0;

int evaluate_expression();
int evaluate_term();
int evaluate_factor();

int get_number()
{
    int num = 0, sign = 1;

    if (exp[idx] == '-') 
    {
        sign = -1;
        idx++;
    }

    if (!(exp[idx] >= '0' && exp[idx] <= '9'))
    {
        errorFlag = 1; // not a valid number
        return 0;
    }

    while (exp[idx] >= '0' && exp[idx] <= '9')
    {
        num = num * 10 + (exp[idx] - '0');
        idx++;
    }
    return num * sign;
}

int evaluate_factor()
{
    int result;

    if (exp[idx] == '(')
    {
        idx++;
        result = evaluate_expression();
        if (exp[idx] == ')')
            idx++;
        else
            errorFlag = 2; // missing closing bracket
        return result;
    }

    return get_number();
}

int evaluate_term()
{
    int result = evaluate_factor();
    while (exp[idx] == '*' || exp[idx] == '/')
    {
        char op = exp[idx++];
        int num = evaluate_factor();
        if (op == '/' && num == 0)
        {
            errorFlag = 3;// division by zero
            return 0;
        }
        if (op == '*') result *= num;
        else result /= num;
    }
    return result;
}

int evaluate_expression()
{
    int result = evaluate_term();

    while (exp[idx] == '+' || exp[idx] == '-')
    {
        char op = exp[idx++];
        int num = evaluate_term();
        if (errorFlag) 
				{
					return 0;
				}
        if (op == '+') 
				{
					result = result+num;
				}
        else 
				{
					result = result-num;
				}
		}
    return result;
}

/* main program*/
int main()
{
    int result;
    uart0_init(9600);
    lcd_init();
    while (1)
    {
        uart0_tx_string("\r\nEnter Expression: ");
        lcd_cmd(0x01);
        lcd_string("Enter Exp");
        uart0_rx_string(exp);
        errorFlag = 0;
        idx = 0;
        if (exp[0] == '\0')
            errorFlag = 4;
        result = evaluate_expression();
        if (exp[idx] != '\0' && errorFlag == 0)
            errorFlag = 1;//extra invalid characters
        /*Error handling*/
        lcd_cmd(0x01);
        if (errorFlag == 4)
        {
            lcd_string("NO INPUT");
            uart0_tx_string("\r\nNO INPUT");
        }
        else if (errorFlag == 1)
        {
            lcd_string("SYNTAX ERROR");
            uart0_tx_string("\r\nSYNTAX ERROR");
        }
        else if (errorFlag == 2)
        {
            lcd_string("BRACKET ERROR");
            uart0_tx_string("\r\nBRACKET ERROR");
        }
        else if (errorFlag == 3)
        {
            lcd_string("DIV BY ZERO");
            uart0_tx_string("\r\nDIV BY ZERO");
        }
        else
        {
            /* Valid Result */
            lcd_string(exp);
            lcd_cmd(0xC0);
            lcd_string("Result=");
            lcd_integer(result);
            uart0_tx_string("\r\nResult = ");
            uart0_tx_integer(result);
        }
    }
}
