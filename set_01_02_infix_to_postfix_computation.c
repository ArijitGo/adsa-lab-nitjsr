#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void infixToPostfix(char* exp, char* postfix) {

    char stack[100];
    int j = 0;
    int top = -1;

    for (int i = 0; exp[i]!='\0'; i++) {
        char c = exp[i];

        // If the scanned character is an operand, add it to the output string.
        if (isalnum(c))
            postfix[j++] = c;

        // If the scanned character is an '(', push it to the stack.
        else if (c == '(')
            stack[++top] = '(';

        // If the scanned character is an ')', pop and add to the output string from the stack until an '(' is encountered.
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--; 
        }

        // If an operator is scanned
        else {
            while (top != -1 && (prec(c) < prec(stack[top]) || prec(c) == prec(stack[top]))) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    // Pop all the remaining elements from the stack
    while (top != -1) {
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';
    printf("%s\n", postfix);
}

int postfixComputation(char* postfix){
    int stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            // convert char digit to int and push
            stack[++top] = c - '0';
        }else{
            int num1 = stack[top--];
            int num2 = stack[top--];
            int res;
            switch (c)
            {
            case '+':
                res = num1 + num2;
                break;
            case '-':
                res = num1 - num2;
                break;
            case '/':
                res = num1 / num2;
                break;
            case '*':
                res = num1 * num2;
                break;
            case '^':
                res = (int) pow(num1, num2);
                break;
            default:
                break;
            }
            stack[++top] = res;
        }
    }
    return stack[top];
}

int main() {
    char exp[100];
    char postfix[100];
    int res;
    printf("Enter the infix expression: \n");
    scanf("%s", exp);
    infixToPostfix(exp, postfix);
    res = postfixComputation(postfix);
    printf("The result will be: %d", res);
    return 0;
}