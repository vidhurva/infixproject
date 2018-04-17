
#include <cmath>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

void provideHelpIfNecessary(char response);
bool isOperator(char letter);
int precedence(char op);
string infixToPostfix(string expr);
int evalInfix(string expr);
int evalPostfix(string expr);

int main()
{
  string expression;
  char response;

  while(response != 'Y' || 'N')
  {
   cout << " Do You Need help ? (Y/N) [Note: Response must be 'Y' or 'N'] : ";
   cin  >> response;
   if(response == 'Y')
     {
       provideHelpIfNecessary('Y');

       while (cin)
       {
        cout << "Expression?" << " ";
        getline(cin, expression);

        if (expression.size() == 0)
        {
          continue;
        }
        try
        {
          cout << evalInfix(expression) << endl;
        }
        catch (char const* error)
        {
          cerr << error << endl;
        }
        if(expression == "return")
        {
          return 0;
          break;
        }
      }
    }
   else if(response == 'N')
   {
     return 0;
   }
 }

return 0;
}

void provideHelpIfNecessary(char response)
{
  cout << "Enter an infix expression at the prompt." << endl;
  cout << "The program will tell you its value." << endl;
  cout << "To stop the program, just hit 'return' on your keyboard." << endl;
}

int evalInfix(string expr)
{
   return evalPostfix(infixToPostfix(expr));
}

string infixToPostfix(string expr)
{
   string postfix;
   stack<char> stack;
   char previous;
   string:: iterator it;
   int openParens = 0;
   for (it = expr.begin(); it != expr.end(); it++)
   {
      char letter = *it;

      if (isspace(letter))
      {
        continue;
      }
      if (isdigit(letter))
      {
        postfix.append(1, letter);
      } else if (letter == '(') {
        openParens++;
        stack.push(letter);
   }
   else if (isOperator(letter))
   {
      if (stack.empty())
      {
         stack.push(letter);
      }
      else
      {
        char op = stack.top();
        while (precedence(op) > precedence(letter))
        {
           stack.pop();
           postfix.append(1, op);
        }
        stack.push(letter);
      }
   }
   else if (letter == ')')
   {
      openParens--;
      while (!stack.empty() && stack.top() != '(')
      {
         postfix.append(1, stack.top());
         stack.pop();
      }
      if (!stack.empty())
      {
         stack.pop();
      }
   }
   else
   {
      if (isOperator(previous) || previous == '(' || previous == ')')
      {
         throw "missing operand";
      }
      else
      {
         throw "missing operator";
      }
   }
   previous = letter;
  }

  if (openParens > 0)
  {
   throw "missing paranthesis";
  }

  while (!stack.empty())
  {
    postfix.append(1, stack.top());
    stack.pop();
  }
  return postfix;
}

int evalPostfix(string expr)
{
   stack<int> stack;
   for (string::iterator it = expr.begin(); it != expr.end(); it++) {
   char letter = *it;

  if (isdigit(letter))
  {
    stack.push(letter - '0');
  }
  else
  {
    int a = stack.top();
    stack.pop();
    int b = stack.top();
    stack.pop();
    int result;
    switch (letter)
    {
       case '+': result = b + a; break;
       case '-': result = b - a; break;
       case '*': result = b * a; break;
       case '^': result = (int) pow((double) b, a); break;
    }
  stack.push(result);
   }
 }
 return stack.top();
}

bool isOperator(char letter)
{
   return letter == '+' || letter == '-' || letter == '*' || letter == '^';
}

int precedence(char op)
{
   switch (op)
   {
      case '+': return 1;
      case '-': return 2;
      case '*': return 3;
      case '/': return 3;
      case '^': return 4;
   }
   return 0;
}
