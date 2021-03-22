//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Yisp.h"
#include "exception.h"
#include "Frame.h"
#include "Syntax.h"
#include "Type.h"

namespace Yisp {
    class Evaluator {
    public:
        static Type::YispAST eval(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST apply(const Type::YispAST &procedure, const std::vector<Type::YispAST> &arguments);

    private:
        static Type::YispAST eval_list(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST eval_symbol(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST eval_ast(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST eval_definition(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST eval_assignment(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST eval_local_assignment(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST eval_if(const Type::YispAST &ast, Frame &frame);

        static Type::YispAST eval_function(const Type::YispAST &ast, Frame &frame);

        static bool is_self_evaluating(const Type::YispAST &ast);
    };
}

#endif // EVALUATOR_H
