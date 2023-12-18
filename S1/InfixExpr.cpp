#include "InfixExpr.h"
#include <string>
#include "CalculatedExpr.h"

namespace golchanskiy {
    InfixExpr::InfixExpr(const std::string &data) :
            impl_infx_expr(Queue<char>()) {
        size_t nOperands = 0;
        size_t nOperators = 0;
        size_t nOpBrackets = 0;
        size_t nClBrackets = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            if (golchanskiy::InfixExpr::isOperation(data[i]) && (nOperands - nOperators == 1)) {
                impl_infx_expr.push(data[i]);
                ++nOperators;
            } else if (std::isdigit(data[i]) && !(nOperands - nOperators)) {
                while (std::isdigit(data[i])) {
                    impl_infx_expr.push(data[i++]);
                }
                impl_infx_expr.push(' ');
                ++nOperands;
            } else if (data[i] == '(') {
                impl_infx_expr.push(data[i]);
                ++nOpBrackets;
            } else if (data[i] == ')') {
                impl_infx_expr.push(data[i]);
                ++nClBrackets;
            } else if (std::isspace(data[i])) {
                impl_infx_expr.push(data[i]);
            } else {
                throw std::logic_error("Incorrect Expression");
            }
        }
        if (nOpBrackets != nClBrackets || (nOperands - nOperators != 1)) {
            throw std::logic_error("Incorrect Expression");
        }
    }

    void golchanskiy::InfixExpr::pop() {
        impl_infx_expr.pop();
    }

    bool golchanskiy::InfixExpr::isEmpty() const {
        return impl_infx_expr.isEmpty();
    }

    char golchanskiy::InfixExpr::front() const {
        return impl_infx_expr.front();
    }
    bool golchanskiy::InfixExpr::isOperation(char c)
    {
        return golchanskiy::is_High_operator(c) || golchanskiy::is_Low_operator(c);
    }
}

