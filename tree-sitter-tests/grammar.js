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
