# tree-sitter-visitor

Procedural macro that generates a visitor trait for a given [Tree Sitter](https://github.com/tree-sitter/tree-sitter)
language based on `node-types.json` that is part of the generated parser.

It generates `visit_<node type>()` methods for each node type in the tree-sitter grammar and a generic `visit(...)`
that dispatches to the appropriate typed method. All the trait methods have default implementations that panic, making
it easier to implement visitors for large grammars incrementally.

## Example

Let's take a simple Tree Sitter arithmetic expression grammar:

```js
module.exports = grammar({
  name: 'dummy',

  rules: {
    root: $ => $._expr,
    _expr: $ => choice(
      $.add_expr,
      $.sub_expr,
      $.mul_expr,
      $.div_expr,
      $.paren_expr,
      $.number
    ),

    add_expr: $ => prec.left(1, seq(field("lhs", $._expr), '+', field("rhs", $._expr))),
    sub_expr: $ => prec.left(1, seq(field("lhs", $._expr), '-', field("rhs", $._expr))),
    mul_expr: $ => prec.left(2, seq(field("lhs", $._expr), '*', field("rhs", $._expr))),
    div_expr: $ => prec.left(2, seq(field("lhs", $._expr), '/', field("rhs", $._expr))),
    paren_expr: $ => seq('(', field("body", $._expr), ')'),

    number: $ => /\d+(\.\d*)?/
  }
});
```

Now we can implement a visitor using the auto generated trait

```rust
use tree_sitter_visitor::generate_visitor_trait;
use tree_sitter::Node;

#[visitor_trait("path/to/grammar/src/node-types.json")]
pub trait CalcVisitor { /* will be auto-generated */ }

#[derive(Default)]
struct Calculator<'t> {
    src: &'t str,
}

impl<'t> CalcVisitor for Calculator<'t> {
    type ReturnType = f64;

    fn visit_root(&mut self, node: &Node) -> f64 {
        self.visit(&node.child(0).unwrap())
    }

    fn visit_number(&mut self, node: &Node) -> f64 {
        self.src[node.byte_range()].parse().unwrap()
    }

    fn visit_add_expr(&mut self, node: &Node) -> f64 {
        let lhs = self
            .visit(&node.child_by_field_name("lhs").unwrap());
        let rhs = self
            .visit(&node.child_by_field_name("rhs").unwrap());

        lhs + rhs
    }

    // we don't have to override all the methods, the 
    // unimplemented ones will just panic if visited
}

fn main() {
    let mut parser = tree_sitter::Parser::new();
    parser
        .set_language(<language>)
        .unwrap();

    let src = "1 + 2";
    let parsed = parser.parse(src, None).expect("Could not parse");

    let root_node = parsed.root_node();

    let mut visitor = Calculator { src };
    let result = visitor.visit(&root_node);

    assert_eq!(result, 3.0);
}
```
