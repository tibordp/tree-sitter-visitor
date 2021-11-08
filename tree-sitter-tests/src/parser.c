#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 15
#define LARGE_STATE_COUNT 7
#define SYMBOL_COUNT 15
#define ALIAS_COUNT 0
#define TOKEN_COUNT 8
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 3

enum {
  anon_sym_PLUS = 1,
  anon_sym_DASH = 2,
  anon_sym_STAR = 3,
  anon_sym_SLASH = 4,
  anon_sym_LPAREN = 5,
  anon_sym_RPAREN = 6,
  sym_number = 7,
  sym_root = 8,
  sym__expr = 9,
  sym_add_expr = 10,
  sym_sub_expr = 11,
  sym_mul_expr = 12,
  sym_div_expr = 13,
  sym_paren_expr = 14,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_STAR] = "*",
  [anon_sym_SLASH] = "/",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_number] = "number",
  [sym_root] = "root",
  [sym__expr] = "_expr",
  [sym_add_expr] = "add_expr",
  [sym_sub_expr] = "sub_expr",
  [sym_mul_expr] = "mul_expr",
  [sym_div_expr] = "div_expr",
  [sym_paren_expr] = "paren_expr",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_number] = sym_number,
  [sym_root] = sym_root,
  [sym__expr] = sym__expr,
  [sym_add_expr] = sym_add_expr,
  [sym_sub_expr] = sym_sub_expr,
  [sym_mul_expr] = sym_mul_expr,
  [sym_div_expr] = sym_div_expr,
  [sym_paren_expr] = sym_paren_expr,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_root] = {
    .visible = true,
    .named = true,
  },
  [sym__expr] = {
    .visible = false,
    .named = true,
  },
  [sym_add_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_sub_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_mul_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_div_expr] = {
    .visible = true,
    .named = true,
  },
  [sym_paren_expr] = {
    .visible = true,
    .named = true,
  },
};

enum {
  field_body = 1,
  field_lhs = 2,
  field_rhs = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_body] = "body",
  [field_lhs] = "lhs",
  [field_rhs] = "rhs",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_body, 1},
  [1] =
    {field_lhs, 0},
    {field_rhs, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(1);
      if (lookahead == '(') ADVANCE(6);
      if (lookahead == ')') ADVANCE(7);
      if (lookahead == '*') ADVANCE(4);
      if (lookahead == '+') ADVANCE(2);
      if (lookahead == '-') ADVANCE(3);
      if (lookahead == '/') ADVANCE(5);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 1:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 2:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 3:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 4:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
  },
  [1] = {
    [sym_root] = STATE(14),
    [sym__expr] = STATE(12),
    [sym_add_expr] = STATE(12),
    [sym_sub_expr] = STATE(12),
    [sym_mul_expr] = STATE(12),
    [sym_div_expr] = STATE(12),
    [sym_paren_expr] = STATE(12),
    [anon_sym_LPAREN] = ACTIONS(3),
    [sym_number] = ACTIONS(5),
  },
  [2] = {
    [sym__expr] = STATE(13),
    [sym_add_expr] = STATE(13),
    [sym_sub_expr] = STATE(13),
    [sym_mul_expr] = STATE(13),
    [sym_div_expr] = STATE(13),
    [sym_paren_expr] = STATE(13),
    [anon_sym_LPAREN] = ACTIONS(3),
    [sym_number] = ACTIONS(7),
  },
  [3] = {
    [sym__expr] = STATE(8),
    [sym_add_expr] = STATE(8),
    [sym_sub_expr] = STATE(8),
    [sym_mul_expr] = STATE(8),
    [sym_div_expr] = STATE(8),
    [sym_paren_expr] = STATE(8),
    [anon_sym_LPAREN] = ACTIONS(3),
    [sym_number] = ACTIONS(9),
  },
  [4] = {
    [sym__expr] = STATE(9),
    [sym_add_expr] = STATE(9),
    [sym_sub_expr] = STATE(9),
    [sym_mul_expr] = STATE(9),
    [sym_div_expr] = STATE(9),
    [sym_paren_expr] = STATE(9),
    [anon_sym_LPAREN] = ACTIONS(3),
    [sym_number] = ACTIONS(11),
  },
  [5] = {
    [sym__expr] = STATE(10),
    [sym_add_expr] = STATE(10),
    [sym_sub_expr] = STATE(10),
    [sym_mul_expr] = STATE(10),
    [sym_div_expr] = STATE(10),
    [sym_paren_expr] = STATE(10),
    [anon_sym_LPAREN] = ACTIONS(3),
    [sym_number] = ACTIONS(13),
  },
  [6] = {
    [sym__expr] = STATE(11),
    [sym_add_expr] = STATE(11),
    [sym_sub_expr] = STATE(11),
    [sym_mul_expr] = STATE(11),
    [sym_div_expr] = STATE(11),
    [sym_paren_expr] = STATE(11),
    [anon_sym_LPAREN] = ACTIONS(3),
    [sym_number] = ACTIONS(15),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 1,
    ACTIONS(17), 6,
      ts_builtin_sym_end,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_RPAREN,
  [9] = 3,
    ACTIONS(21), 1,
      anon_sym_STAR,
    ACTIONS(23), 1,
      anon_sym_SLASH,
    ACTIONS(19), 4,
      ts_builtin_sym_end,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_RPAREN,
  [22] = 3,
    ACTIONS(21), 1,
      anon_sym_STAR,
    ACTIONS(23), 1,
      anon_sym_SLASH,
    ACTIONS(25), 4,
      ts_builtin_sym_end,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_RPAREN,
  [35] = 1,
    ACTIONS(27), 6,
      ts_builtin_sym_end,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_RPAREN,
  [44] = 1,
    ACTIONS(29), 6,
      ts_builtin_sym_end,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_RPAREN,
  [53] = 5,
    ACTIONS(21), 1,
      anon_sym_STAR,
    ACTIONS(23), 1,
      anon_sym_SLASH,
    ACTIONS(31), 1,
      ts_builtin_sym_end,
    ACTIONS(33), 1,
      anon_sym_PLUS,
    ACTIONS(35), 1,
      anon_sym_DASH,
  [69] = 5,
    ACTIONS(21), 1,
      anon_sym_STAR,
    ACTIONS(23), 1,
      anon_sym_SLASH,
    ACTIONS(33), 1,
      anon_sym_PLUS,
    ACTIONS(35), 1,
      anon_sym_DASH,
    ACTIONS(37), 1,
      anon_sym_RPAREN,
  [85] = 1,
    ACTIONS(39), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(7)] = 0,
  [SMALL_STATE(8)] = 9,
  [SMALL_STATE(9)] = 22,
  [SMALL_STATE(10)] = 35,
  [SMALL_STATE(11)] = 44,
  [SMALL_STATE(12)] = 53,
  [SMALL_STATE(13)] = 69,
  [SMALL_STATE(14)] = 85,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_paren_expr, 3, .production_id = 1),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_add_expr, 3, .production_id = 2),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_sub_expr, 3, .production_id = 2),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_mul_expr, 3, .production_id = 2),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_div_expr, 3, .production_id = 2),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_root, 1),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [39] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_dummy(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
