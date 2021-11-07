#![feature(proc_macro_span)]

use proc_macro::Span;
use quote::{quote, format_ident};
use proc_macro::TokenStream;
use syn::parse::{Parse, ParseStream, Result};
use std::fs::File;
use serde::Deserialize;
use serde_json::from_reader;

#[derive(Deserialize)]
struct Node {
    r#type: String,
}

#[derive(Debug)]
struct Arguments {
    trait_name: syn::Ident,
    filename: String,
}

impl Parse for Arguments {
    fn parse(input: ParseStream) -> Result<Self> {
        let trait_name: syn::Ident = input.parse()?;
        let _: syn::Token![,] = input.parse()?;
        let lit_file: syn::LitStr = input.parse()?;

        Ok(Self { trait_name, filename: lit_file.value() })
    }
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

#[proc_macro]
pub fn generate_visitor_trait(input: TokenStream) -> TokenStream {
    let input = syn::parse_macro_input!(input as Arguments);

    let call_site_file = Span::call_site().source_file().path();
    let cwd = call_site_file.parent().unwrap();
    let filename = cwd.join(&input.filename);

    let file = File::open(filename).unwrap();
    let parsed : Vec<Node> = from_reader(file).unwrap();

    let (trait_fns, match_arms) : (Vec<_>, Vec<_>) = parsed.iter().map(|symbol| {
        let raw_name = &symbol.r#type;
        let sanitized_name = sanitize_identifier(&symbol.r#type);
        let method_name = format_ident!("visit_{}", sanitized_name);
        let doc_name = format!("{:?}", raw_name).replace('`', "\\`");
        let doc_string = format!("Visits a node of type `{}`", doc_name);

        let trait_fn = quote! {
            #[doc=#doc_string]
            fn #method_name(&mut self, node: &::tree_sitter::Node) -> Self::ReturnType {
                unimplemented!(#sanitized_name)
            }
        };

        let match_arm = quote! {
            #raw_name => self.#method_name(node)
        };

        (trait_fn, match_arm)
    }).unzip();

    let trait_name = &input.trait_name;
    let doc_string = format!(
        r"A visitor trait for the language.
This trait is automatically generated.
"); 
    TokenStream::from(quote! {
        #[doc=#doc_string]
        pub trait #trait_name {
            type ReturnType;

            #(#trait_fns)*
            
            #[doc=r"Visits a node of any type."]
            fn visit(&mut self, node: &::tree_sitter::Node) -> Self::ReturnType {
                match node.kind() {
                    #(#match_arms,)*
                    _ => panic!("unknown node kind: {}", node.kind())
                }
            }
        }
    })
}
