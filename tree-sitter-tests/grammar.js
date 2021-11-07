module.exports = grammar({
    name: 'dummy',
  
    rules: {
      // TODO: add the actual grammar rules
      source_file: $ => repeat(choice(
        $.fizz,
        $.buzz,
      )),

      fizz: $ => "fizz",
      buzz: $ => "buzz",
    }
});
