//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef keywords_H
#define keywords_H

#include "Yisp.h"
#include "exception.h"
#include "Type.h"

namespace Yisp::Syntax {

    // Excuse my poor regex-ing...
    static inline const std::string grammar = YispGrammar; /* NOLINT */

    // Delimiter Syntax Classes
    enum class DelimiterKind {
        comment,
        empty [[maybe_unused]],
        list,
        string,
    };

    static std::unordered_map<DelimiterKind, char> delimiters = { /* NOLINT */
            {DelimiterKind::comment, '#'},
            {DelimiterKind::list,    '('},
            {DelimiterKind::string,  '"'}
    };

    // Keyword Syntax
    enum class KeywordKind {
        definition,
        assignment,
        local_assignment,
        function,
        conditional_if,
    };

    static std::unordered_map<KeywordKind, std::string> keywords = { /* NOLINT */
            {KeywordKind::definition,       "define"},
            {KeywordKind::assignment,       "set"},
            {KeywordKind::local_assignment, "let"},
            {KeywordKind::function,         "fun"},
            {KeywordKind::conditional_if,   "if"},
    };

    [[maybe_unused]] bool is_comment_delimited(const std::string &token);

    bool is_list_delimited(const std::string &token);

    bool is_string_delimited(const std::string &token);

    bool out_of_bounds(size_t index, size_t size);

    bool is_definition(const std::string &symbol);

    Type::YispAST definition_name(const Type::YispAST &expression);

    Type::YispAST definition_value(const Type::YispAST &expression);

    bool is_assigment(const std::string &symbol);

    Type::YispAST variable_name(const Type::YispAST &expression);

    Type::YispAST variable_update(const Type::YispAST &expression);

    bool is_local_assignment(const std::string &symbol);

    std::vector<Type::YispAST> local_variables(const Type::YispAST &expression);

    Type::YispAST local_body(const Type::YispAST &expression);

    bool is_function(const std::string &symbol);

    std::vector<Type::YispAST> function_parameters(const Type::YispAST &expression);

    Type::YispAST function_body(const Type::YispAST &expression);

    Type::YispAST apply_function(const Type::YispAST &expression);

    std::vector<Type::YispAST> apply_arguments(const Type::YispAST &expression);

    bool is_if(const std::string &symbol);

    Type::YispAST if_predicate(const Type::YispAST &expression);

    Type::YispAST if_consequent(const Type::YispAST &expression);

    Type::YispAST if_alternative(const Type::YispAST &expression);
}

#endif // Syntax_H
