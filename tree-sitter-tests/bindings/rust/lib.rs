use tree_sitter::Language;
use tree_sitter_visitor::generate_visitor_trait;

extern "C" {
    fn tree_sitter_dummy() -> Language;
}

pub fn language() -> Language {
    unsafe { tree_sitter_dummy() }
}

pub const NODE_TYPES: &'static str = include_str!("../../src/node-types.json");
generate_visitor_trait!(DummyVisitor, "../../src/node-types.json");

#[cfg(test)]
mod tests {
    use tree_sitter::Node;
    use super::DummyVisitor;

    #[derive(Default)]
    struct SampleVisitor {
        fizz_count: u32,
        buzz_count: u32,
    }
    
    impl DummyVisitor for SampleVisitor {
        type ReturnType = ();

        fn visit_source_file(&mut self, node: &Node) {
            let mut cursor = node.walk();
            for child in node.children(&mut cursor) {
                self.visit(&child);
            }
        }

        fn visit_fizz(&mut self, _: &Node) {
            self.fizz_count += 1;
        }

        fn visit_buzz(&mut self, _: &Node) {
            self.buzz_count += 1;
        }
    }

    #[test]
    fn test_visitor_works() {
        let mut parser = tree_sitter::Parser::new();
        parser.set_language(super::language())
            .expect("Error loading dummy language"); 

        let parsed = parser.parse(r"fizz buzz fizz fizz buzz", None)
            .expect("Could not parse");

        let root_node = parsed.root_node();

        let mut visitor : SampleVisitor = Default::default();
        visitor.visit(&root_node);

        assert_eq!(visitor.fizz_count, 3);
        assert_eq!(visitor.buzz_count, 2);
    }
}
