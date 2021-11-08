//! Procedural macro that generates a visitor trait for a given [Tree Sitter](https://github.com/tree-sitter/tree-sitter)
//! language based on `node-types.json` that is part of the generated parser.
//!
//! It generates `visit_<node type>()` methods for each node type in the tree-sitter grammar and a generic `visit(...)`
//! that dispatches to the appropriate typed method. All the trait methods have default implementations that panic, making
//! it easier to implement visitors for large grammars incrementally.
//!
//! # Example:
//!
//! ```rust
//! use tree_sitter_visitor::visitor_trait;
//! 
//! #[visitor_trait("../../tree-sitter-tests/src/node-types.json")]
//! trait CppVisitor { }
//! ```
//!
//! This expands to roughly the following:
//! ```rust
//! trait CppVisitor {
//!     type ReturnType;
//!
//!     fn visit(&mut self, node: &tree_sitter::Node) -> Self::ReturnType {
//!         match node.kind() {
//!             "node1" => self.visit_node1(node),
//!             "node2" => self.visit_node2(node),
//!             /* ... */
//!             _ => unimplemented!(),
//!         }
//!     }
//!
//!     fn visit_node1(&mut self, node: &tree_sitter::Node) -> Self::ReturnType {
//!          unimplemented!()
//!     }
//!
//!     fn visit_node2(&mut self, node: &tree_sitter::Node) -> Self::ReturnType {
//!          unimplemented!()
//!     }
//!     
//!     /* ... */
//! }
//! ```
#![feature(proc_macro_span)]

use proc_macro::Span;
use proc_macro::TokenStream;
use quote::{format_ident, quote, ToTokens};
use serde::Deserialize;
use serde_json::from_reader;
use std::fs::File;
use syn::{parse_macro_input, parse_quote, AttributeArgs, ItemTrait, Lit, NestedMeta, TraitItem};

#[derive(Deserialize)]
struct Node {
    r#type: String,
}

fn sanitize_identifier(name: &str) -> String {
    let mut result = String::with_capacity(name.len());
    for c in name.chars() {
        if ('a'..='z').contains(&c)
            || ('A'..='Z').contains(&c)
            || ('0'..='9').contains(&c)
            || c == '_'
        {
            result.push(c);
        } else {
            let replacement = match c {
                '~' => "TILDE",
                '`' => "BQUOTE",
                '!' => "BANG",
                '@' => "AT",
                '#' => "POUND",
                '$' => "DOLLAR",
                '%' => "PERCENT",
                '^' => "CARET",
                '&' => "AMP",
                '*' => "STAR",
                '(' => "LPAREN",
                ')' => "RPAREN",
                '-' => "DASH",
                '+' => "PLUS",
                '=' => "EQ",
                '{' => "LBRACE",
                '}' => "RBRACE",
                '[' => "LBRACK",
                ']' => "RBRACK",
                '\\' => "BSLASH",
                '|' => "PIPE",
                ':' => "COLON",
                ';' => "SEMI",
                '"' => "DQUOTE",
                '\'' => "SQUOTE",
                '<' => "LT",
                '>' => "GT",
                ',' => "COMMA",
                '.' => "DOT",
                '?' => "QMARK",
                '/' => "SLASH",
                '\n' => "LF",
                '\r' => "CR",
                '\t' => "TAB",
                _ => continue,
            };
            if !result.is_empty() && !result.ends_with('_') {
                result.push('_');
            }
            result += replacement;
        }
    }
    result
}

#[proc_macro_attribute]
pub fn visitor_trait(args: TokenStream, input: TokenStream) -> TokenStream {
    let args = parse_macro_input!(args as AttributeArgs);
    let mut input = parse_macro_input!(input as ItemTrait);

    let path_to_json = match args.into_iter().next() {
        Some(NestedMeta::Lit(Lit::Str(s))) => s.value(),
        _ => panic!("expected a filename"),
    };

    let call_site_file = Span::call_site().source_file().path();
    let cwd = call_site_file.parent().unwrap();
    let filename = cwd.join(&path_to_json);
    let file = File::open(filename).unwrap();
    let parsed: Vec<Node> = from_reader(file).expect("could not parse the node types JSON");

    let (trait_fns, match_arms): (Vec<_>, Vec<_>) = parsed
        .iter()
        .map(|symbol| {
            let raw_name = &symbol.r#type;
            let sanitized_name = sanitize_identifier(&symbol.r#type);
            let method_name = format_ident!("visit_{}", sanitized_name);
            let doc_name = format!("{:?}", raw_name).replace('`', "\\`");
            let doc_string = format!("Visits a node of type `{}`", doc_name);

            let trait_fn: TraitItem = parse_quote! {
                #[doc=#doc_string]
                fn #method_name(&mut self, node: &::tree_sitter::Node) -> Self::ReturnType {
                    unimplemented!(#sanitized_name)
                }
            };

            let match_arm = quote! {
                #raw_name => self.#method_name(node)
            };

            (trait_fn, match_arm)
        })
        .unzip();

    let return_item: TraitItem = parse_quote! {
        type ReturnType;
    };
    let dispatch_visit_fn: TraitItem = parse_quote! {
        #[doc=r"Visits a node of any type."]
        fn visit(&mut self, node: &::tree_sitter::Node) -> Self::ReturnType {
            match node.kind() {
                #(#match_arms,)*
                _ => panic!("unknown node kind: {}", node.kind())
            }
        }
    };

    input.items = [return_item, dispatch_visit_fn]
        .into_iter()
        .chain(trait_fns)
        .chain(input.items)
        .collect();

    TokenStream::from(input.into_token_stream())
}
