#include <yed/plugin.h>

#define MAYBE_CONVERT(rgb) (tc ? (rgb) : rgb_to_256(rgb))

PACKABLE_STYLE(pastel) {
    yed_style s;
    int       tc,
              attr_kind;

    YED_PLUG_VERSION_CHECK();

    tc        = !!yed_get_var("truecolor");
    attr_kind = tc ? ATTR_KIND_RGB : ATTR_KIND_256;

    memset(&s, 0, sizeof(s));
    ATTR_SET_FG_KIND(s.active.flags, attr_kind);
    s.active.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.active.flags, attr_kind);
    s.active.bg     = MAYBE_CONVERT(0x292929);

    ATTR_SET_FG_KIND(s.active_border.flags, attr_kind);
    s.active_border.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.active_border.flags, attr_kind);
    s.active_border.bg     = MAYBE_CONVERT(0x292929);

    ATTR_SET_FG_KIND(s.active_gutter.flags, attr_kind);
    s.active_gutter.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.active_gutter.flags, attr_kind);
    s.active_gutter.bg     = MAYBE_CONVERT(0x292929);

    ATTR_SET_FG_KIND(s.inactive.flags, attr_kind);
    s.inactive.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.inactive.flags, attr_kind);
    s.inactive.bg     = MAYBE_CONVERT(0xa0a0a);

    ATTR_SET_FG_KIND(s.inactive_border.flags, attr_kind);
    s.inactive_border.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.inactive_border.flags, attr_kind);
    s.inactive_border.bg     = MAYBE_CONVERT(0xa0a0a);

    ATTR_SET_FG_KIND(s.inactive_gutter.flags, attr_kind);
    s.inactive_gutter.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.inactive_gutter.flags, attr_kind);
    s.inactive_gutter.bg     = MAYBE_CONVERT(0xa0a0a);

    ATTR_SET_FG_KIND(s.cursor_line.flags, attr_kind);
    s.cursor_line.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.cursor_line.flags, attr_kind);
    s.cursor_line.bg     = MAYBE_CONVERT(0x494646);

    ATTR_SET_FG_KIND(s.selection.flags, attr_kind);
    s.selection.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.selection.flags, attr_kind);
    s.selection.bg     = MAYBE_CONVERT(0x494646);

    ATTR_SET_FG_KIND(s.search.flags, attr_kind);
    s.search.fg     = MAYBE_CONVERT(0xbb77aa);
    ATTR_SET_BG_KIND(s.search.flags, attr_kind);
    s.search.bg     = MAYBE_CONVERT(0x170326);
    s.search.flags |= 0 | ATTR_INVERSE;

    ATTR_SET_FG_KIND(s.search_cursor.flags, attr_kind);
    s.search_cursor.fg     = MAYBE_CONVERT(0x5668d);
    ATTR_SET_BG_KIND(s.search_cursor.flags, attr_kind);
    s.search_cursor.bg     = MAYBE_CONVERT(0x170326);
    s.search_cursor.flags |= 0 | ATTR_INVERSE;

    ATTR_SET_FG_KIND(s.attention.flags, attr_kind);
    s.attention.fg     = MAYBE_CONVERT(0xaf0000);
    s.attention.flags |= 0 | ATTR_BOLD;

    ATTR_SET_FG_KIND(s.associate.flags, attr_kind);
    s.associate.fg     = MAYBE_CONVERT(0xfff3f0);
    ATTR_SET_BG_KIND(s.associate.flags, attr_kind);
    s.associate.bg     = MAYBE_CONVERT(0x885a5a);

    ATTR_SET_FG_KIND(s.status_line.flags, attr_kind);
    s.status_line.fg     = MAYBE_CONVERT(0x252730);
    ATTR_SET_BG_KIND(s.status_line.flags, attr_kind);
    s.status_line.bg     = MAYBE_CONVERT(0xf6bd60);
    s.status_line.flags |= 0 | ATTR_BOLD;

    ATTR_SET_FG_KIND(s.command_line.flags, attr_kind);
    s.command_line.fg     = MAYBE_CONVERT(0xbdbbb0);
    ATTR_SET_BG_KIND(s.command_line.flags, attr_kind);
    s.command_line.bg     = MAYBE_CONVERT(0x151414);

    ATTR_SET_FG_KIND(s.code_comment.flags, attr_kind);
    s.code_comment.fg     = MAYBE_CONVERT(0x7d808c);
    s.code_comment.flags |= 0 | ATTR_BOLD;

    ATTR_SET_FG_KIND(s.code_keyword.flags, attr_kind);
    s.code_keyword.fg     = MAYBE_CONVERT(0x345995);

    ATTR_SET_FG_KIND(s.code_control_flow.flags, attr_kind);
    s.code_control_flow.fg     = MAYBE_CONVERT(0x84a59d);

    ATTR_SET_FG_KIND(s.code_typename.flags, attr_kind);
    s.code_typename.fg     = MAYBE_CONVERT(0xaf4d98);

    ATTR_SET_FG_KIND(s.code_preprocessor.flags, attr_kind);
    s.code_preprocessor.fg     = MAYBE_CONVERT(0xaf4d98);
    s.code_preprocessor.flags |= 0 | ATTR_BOLD;

    ATTR_SET_FG_KIND(s.code_fn_call.flags, attr_kind);
    s.code_fn_call.fg     = MAYBE_CONVERT(0xf28482);

    ATTR_SET_FG_KIND(s.code_number.flags, attr_kind);
    s.code_number.fg     = MAYBE_CONVERT(0xf6bd60);

    ATTR_SET_FG_KIND(s.code_constant.flags, attr_kind);
    s.code_constant.fg     = MAYBE_CONVERT(0xf6bd60);
    s.code_constant.flags |= 0 | ATTR_BOLD;

    ATTR_SET_FG_KIND(s.code_string.flags, attr_kind);
    s.code_string.fg     = MAYBE_CONVERT(0x84a59d);

    ATTR_SET_FG_KIND(s.code_character.flags, attr_kind);
    s.code_character.fg     = MAYBE_CONVERT(0x84a59d);

    yed_plugin_set_style(self, "pastel", &s);
    return 0;
}
