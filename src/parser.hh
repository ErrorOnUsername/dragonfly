#pragma once
#include <vector>

#include "arena.hh"
#include "ast.hh"
#include "token.hh"

class Parser {
public:
	Parser(std::vector<Token>& token_stream);

	void parse_module();

	Stmnt* parse_statement();
	void parse_decl_stmnt();
	void parse_let_stmnt();
	Stmnt* parse_if_stmnt();
	Stmnt* parse_for_stmnt();
	Stmnt* parse_while_stmnt();
	Stmnt* parse_loop_stmnt();
	Stmnt* parse_continue_stmnt();
	Stmnt* parse_break_stmnt();
	Stmnt* parse_return_stmnt();
	Stmnt* parse_expr_stmnt();

	Expr* parse_expr(bool can_assign, bool allow_newlines);
	Expr* parse_operand();
	Type parse_raw_type();
	TypeID register_type(Type& type);

	std::vector<StructMember> parse_struct_members();
	std::vector<ProcParameter> parse_proc_decl_param_list();
	Block parse_stmnt_block();

	bool is_ident_defined(std::string const& name) const;
	VarID get_ident_var_id(std::string const& name) const;

	Token current();
	Token next();
	void eat_next_specific(TokenKind kind);
	void eat_current_specific(TokenKind kind);
	void eat_whitespace();

	Token peek(int64_t offset = 1);

private:
	std::vector<Token>& m_token_stream;
	size_t m_idx;
	size_t m_current_scope;

	Module m_root_module;
	Arena m_stmnt_arena;
	Arena m_expr_arena;
};
