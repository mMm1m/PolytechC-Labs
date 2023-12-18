#include "PostfixExpr.h"
#include "Stack.h"
#include "CalculatedExpr.h"

namespace golchanskiy
{
    PostfixExpr::PostfixExpr(const InfixExpr &data) :
            impl_pstfx_expr(Queue<char>()) {
        golchanskiy::Stack<char> stack;
        InfixExpr infixExpr(data);
        while (!infixExpr.isEmpty()) {
            if (infixExpr.front() == ' ') {
                infixExpr.pop();
            } else if (infixExpr.front() == '(') {
                stack.push('(');
                infixExpr.pop();
            } else if (infixExpr.front() == ')') {
                while (stack.top() != '(') {
                    impl_pstfx_expr.push(stack.top());
                    stack.pop();
                }
                stack.pop();
                infixExpr.pop();
            } else if (std::isdigit(infixExpr.front())) {
                while (!infixExpr.isEmpty() && infixExpr.front() != ' ') {
                    impl_pstfx_expr.push(infixExpr.front());
                    infixExpr.pop();
                }
                impl_pstfx_expr.push(' ');
                if (infixExpr.isEmpty()) {
                    break;
                } else {
                    infixExpr.pop();
                }
            } else if (golchanskiy::is_High_operator(infixExpr.front())) {
                while (!stack.isEmpty() && stack.top() != '(' && golchanskiy::is_High_operator(stack.top())) {
                    impl_pstfx_expr.push(stack.top());
                    stack.pop();
                }
                stack.push(infixExpr.front());
                infixExpr.pop();
            } else {
                while (!stack.isEmpty() && stack.top() != '(') {
                    impl_pstfx_expr.push(stack.top());
                    stack.pop();
                }
                stack.push(infixExpr.front());
                infixExpr.pop();
            }
        }
        while (!stack.isEmpty()) {
            impl_pstfx_expr.push(stack.top());
            stack.pop();
        }
    }

    long long PostfixExpr::result() {
        PostfixExpr expr(*this);
        golchanskiy::Stack<long long> stack;
        while (!expr.isEmpty()) {
            if (std::isdigit(expr.front())) {
                std::string operand;
                while (expr.front() != ' ') {
                    operand += expr.front();
                    expr.pop();
                }
                stack.push(std::stoll(operand));
                expr.pop();
            } else {
                long long operand = stack.top();
                stack.pop();
                long long operand_ = stack.top();
                stack.pop();
                switch (expr.front()) {
                    case '+':
                        stack.push(golchanskiy::add(operand_, operand));
                        break;
                    case '-':
                        stack.push(golchanskiy::substraction(operand_, operand));
                        break;
                    case '*':
                        stack.push(golchanskiy::multiplicate(operand_, operand));
                        break;
                    case '/':
                        stack.push(golchanskiy::divide(operand_, operand));
                        break;
                    case '%':
                        stack.push(golchanskiy::DivisionWithRemainder(operand_, operand));
                        break;
                }
                expr.pop();
            }
        }
        return stack.top();
    }

    char golchanskiy::PostfixExpr::front() const {
        return impl_pstfx_expr.front();
    }

    void golchanskiy::PostfixExpr::pop() {
        impl_pstfx_expr.pop();
    }

    bool golchanskiy::PostfixExpr::isEmpty() const {
        return impl_pstfx_expr.isEmpty();
    }
}

