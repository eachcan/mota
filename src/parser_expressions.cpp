#include "parser.h"
#include <iostream>

namespace mota {
namespace parser {

// ===== 表达式解析 =====

std::shared_ptr<ast::Expr> Parser::expression() {
    // 表达式是字面量和操作符的组合
    return assignment();
}

std::shared_ptr<ast::Expr> Parser::assignment() {
    
    auto expr = logicalOr();
    
    if (consume(lexer::TokenType::Equal)) {
        auto equals = previous_;
        auto value = assignment();
        
        if (auto* identifier = dynamic_cast<ast::Identifier*>(expr.get())) {
            // 我们没有 Assign 类型，所以这里需要创建一个 BinaryOp 来表示赋值
            return makeNode<ast::BinaryOp>(
                ast::BinaryOp::Op::Eq,  // 使用等于操作符表示赋值
                expr,
                value
            );
        } else if (auto* memberAccess = dynamic_cast<ast::MemberAccess*>(expr.get())) {
            // 我们没有 Set 类型，所以这里需要创建一个 BinaryOp 来表示成员赋值
            return makeNode<ast::BinaryOp>(
                ast::BinaryOp::Op::Eq,  // 使用等于操作符表示赋值
                expr,
                value
            );
        }
        
        throw error(equals, "Invalid assignment target");
    }
    
    return expr;
}

std::shared_ptr<ast::Expr> Parser::logicalOr() {
    
    auto expr = logicalAnd();
    
    while (consume(lexer::TokenType::Or)) {
        auto op = previous_;
        auto right = logicalAnd();
        expr = makeNode<ast::BinaryOp>(
            ast::BinaryOp::Op::Or,
            expr,
            right
        );
    }
    
    return expr;
}

std::shared_ptr<ast::Expr> Parser::logicalAnd() {
    
    auto expr = equality();
    
    while (consume(lexer::TokenType::And)) {
        auto op = previous_;
        auto right = equality();
        expr = makeNode<ast::BinaryOp>(
            ast::BinaryOp::Op::And,
            expr,
            right
        );
    }
    
    return expr;
}

std::shared_ptr<ast::Expr> Parser::equality() {
    
    auto expr = comparison();
    
    while (consume(lexer::TokenType::EqualEqual) || consume(lexer::TokenType::BangEqual)) {
        auto op = previous_;
        auto right = comparison();
        
        ast::BinaryOp::Op opType;
        if (op.type == lexer::TokenType::EqualEqual) {
            opType = ast::BinaryOp::Op::Eq;
        } else {
            opType = ast::BinaryOp::Op::Ne;
        }
        
        expr = makeNode<ast::BinaryOp>(
            opType,
            expr,
            right
        );
    }
    
    return expr;
}

std::shared_ptr<ast::Expr> Parser::comparison() {
    auto nowToken = peek();

    
    auto expr = term();
    
    while (consume(lexer::TokenType::Greater) || 
           consume(lexer::TokenType::GreaterEqual) || 
           consume(lexer::TokenType::Less) || 
           consume(lexer::TokenType::LessEqual)) {
        auto op = previous_;
        auto right = term();
        
        ast::BinaryOp::Op opType;
        switch (op.type) {
            case lexer::TokenType::Greater:
                opType = ast::BinaryOp::Op::Gt;
                break;
            case lexer::TokenType::GreaterEqual:
                opType = ast::BinaryOp::Op::Ge;
                break;
            case lexer::TokenType::Less:
                opType = ast::BinaryOp::Op::Lt;
                break;
            case lexer::TokenType::LessEqual:
                opType = ast::BinaryOp::Op::Le;
                break;
            default:
                // 不应该到达这里
                throw error(op, "Invalid comparison operator");
        }
        
        expr = makeNode<ast::BinaryOp>(
            opType,
            expr,
            right
        );
    }
    
    return expr;
}

std::shared_ptr<ast::Expr> Parser::term() {
    
    auto expr = factor();
    
    while (consume(lexer::TokenType::Plus) || consume(lexer::TokenType::Minus)) {
        auto op = previous_;
        auto right = factor();
        
        ast::BinaryOp::Op opType;
        if (op.type == lexer::TokenType::Plus) {
            opType = ast::BinaryOp::Op::Add;
        } else {
            opType = ast::BinaryOp::Op::Sub;
        }
        
        expr = makeNode<ast::BinaryOp>(
            opType,
            expr,
            right
        );
    }
    
    return expr;
}

std::shared_ptr<ast::Expr> Parser::factor() {
    
    auto expr = unary();
    
    while (consume(lexer::TokenType::Star) || 
           consume(lexer::TokenType::Slash) || 
           consume(lexer::TokenType::Percent)) {
        auto op = previous_;
        auto right = unary();
        
        ast::BinaryOp::Op opType;
        switch (op.type) {
            case lexer::TokenType::Star:
                opType = ast::BinaryOp::Op::Mul;
                break;
            case lexer::TokenType::Slash:
                opType = ast::BinaryOp::Op::Div;
                break;
            case lexer::TokenType::Percent:
                opType = ast::BinaryOp::Op::Mod;
                break;
            default:
                // 不应该到达这里
                throw error(op, "Invalid factor operator");
        }
        
        expr = makeNode<ast::BinaryOp>(
            opType,
            expr,
            right
        );
    }
    
    return expr;
}

std::shared_ptr<ast::Expr> Parser::unary() {
    
    if (consume(lexer::TokenType::Bang) || consume(lexer::TokenType::Minus)) {
        auto op = previous_;
        auto right = unary();
        
        ast::UnaryOp::Op opType;
        if (op.type == lexer::TokenType::Bang) {
            opType = ast::UnaryOp::Op::Not;
        } else {
            opType = ast::UnaryOp::Op::Minus;
        }
        
        return makeNode<ast::UnaryOp>(opType, right);
    }
    
    return primary();
}

std::shared_ptr<ast::Expr> Parser::primary() {
    
    if (consume(lexer::TokenType::False)) {
        return makeNode<ast::Literal>(false);
    }
    
    if (consume(lexer::TokenType::True)) {
        return makeNode<ast::Literal>(true);
    }
    
    if (consume(lexer::TokenType::Integer)) {
        try {
            int64_t value = std::stoll(previous_.lexeme);
            return makeNode<ast::Literal>(value);
        } catch (const std::exception& e) {
            throw error(previous_, "Invalid integer literal");
        }
    }
    
    if (consume(lexer::TokenType::Float)) {
        try {
            double value = std::stod(previous_.lexeme);
            return makeNode<ast::Literal>(value);
        } catch (const std::exception& e) {
            throw error(previous_, "Invalid float literal");
        }
    }
    
    if (consume(lexer::TokenType::String)) {
        return makeNode<ast::Literal>(previous_.lexeme);
    }
    
    if (consume(lexer::TokenType::Identifier)) {
        return makeNode<ast::Identifier>(previous_.lexeme);
    }
    
    if (consume(lexer::TokenType::LeftParen)) {
        auto expr = expression();
        consume(lexer::TokenType::RightParen, "Expected ')' after expression");
        // 我们没有 Grouping 类型，所以直接返回表达式
        return expr;
    }
    
    // 解析数组字面量 [expr1, expr2, ...]
    if (consume(lexer::TokenType::LeftBracket)) {
        std::vector<std::shared_ptr<ast::Expr>> elements;
        
        // 处理空数组 []
        if (!check(lexer::TokenType::RightBracket)) {
            do {
                // 支持数组元素为注解
                if (check(lexer::TokenType::At)) {
                    elements.push_back(annotation());
                } else {
                    elements.push_back(expression());
                }
            } while (consume(lexer::TokenType::Comma));
        }
        
        consume(lexer::TokenType::RightBracket, "Expected ']' after array elements");
        return makeNode<ast::ArrayLiteral>(elements);
    }
    
    throw error(peek(), "Expected expression");
}

} // namespace parser
} // namespace mota
