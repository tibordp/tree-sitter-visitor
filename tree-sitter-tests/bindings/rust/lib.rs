use tree_sitter::Language;
use tree_sitter_visitor::visitor_trait;

extern "C" {
    fn tree_sitter_dummy() -> Language;
}

pub fn language() -> Language {
    unsafe { tree_sitter_dummy() }
}

pub const NODE_TYPES: &str = include_str!("../../src/node-types.json");
#[visitor_trait("../../src/node-types.json")]
pub trait CalcVisitor {}

#[cfg(test)]
mod tests {
    use super::CalcVisitor;
    use tree_sitter::Node;

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
            let lhs = self.visit(&node.child_by_field_name("lhs").unwrap());
            let rhs = self.visit(&node.child_by_field_name("rhs").unwrap());

            lhs + rhs
        }

        // other nodes have default implementations which panic on visit,
        // so a visitor can be written incrementally for large grammars
    }

    #[test]
    fn test_visitor_works() {
        let mut parser = tree_sitter::Parser::new();
        parser
            .set_language(super::language())
            .expect("Error loading dummy language");

        let src = "1 + 2";
        let parsed = parser.parse(src, None).expect("Could not parse");

        let root_node = parsed.root_node();

        let mut visitor = Calculator { src };
        let result = visitor.visit(&root_node);

        assert_eq!(result, 3.0);
    }
}
