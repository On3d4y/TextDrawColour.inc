#include <a_samp>
#include <Pawn.Regex>
#include <YSI\y_iterate>
#include <YSI\y_hooks>
#include <YSI\y_malloc>

// [240] = [REPLACEMENT_SPACE_CHAR]
static stock Float:characterWidths[][] = {
	{
		 0.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
		12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
		12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
		12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0,
		12.0, 13.0, 13.0, 28.0, 28.0, 28.0, 28.0,  8.0, // 0    ! " Ј $ % & '
		17.0, 17.0, 30.0, 28.0, 28.0, 12.0, 9.0,  21.0, // 8  ( ) * + , - . /
		28.0, 14.0, 28.0, 28.0, 28.0, 28.0, 28.0, 28.0, // 16 0 1 2 3 4 5 6 7
		28.0, 28.0, 13.0, 13.0, 30.0, 30.0, 30.0, 30.0, // 24 8 9 : ; < = > ?
		10.0, 25.0, 23.0, 21.0, 24.0, 22.0, 20.0, 24.0, // 64 - A B C D E F G
		24.0, 17.0, 20.0, 22.0, 20.0, 30.0, 27.0, 27.0, // 72 H I J K L M N O
		26.0, 26.0, 24.0, 23.0, 24.0, 31.0, 23.0, 31.0, // 80 P Q R S T U V W
		24.0, 23.0, 21.0, 28.0, 33.0, 33.0, 14.0, 28.0, // 88 X Y Z & \   i _
		10.0, 11.0, 12.0,  9.0, 11.0, 10.0, 10.0, 12.0, // 64 ! a b c d e f g
		12.0,  7.0,  7.0, 13.0,  5.0, 18.0, 12.0, 10.0, // 72 h i j k l m n o
		12.0, 11.0, 10.0, 12.0,  8.0, 13.0, 13.0, 18.0, // 80 p q r s t u v w
		17.0, 13.0, 12.0, 30.0, 30.0, 37.0, 35.0, 37.0, // 56 x y z
		25.0, 25.0, 25.0, 25.0, 33.0, 21.0, 24.0, 24.0, // 96 А Б В Г Ж З И Й 
		24.0, 24.0, 17.0, 17.0, 17.0, 17.0, 27.0, 27.0, // 104 К Л М Н О П Т У 
		27.0, 27.0, 31.0, 31.0, 31.0, 31.0, 11.0, 11.0, // 112 Ф Ц Щ Ъ Ы Ь Я а
		11.0, 11.0, 11.0, 20.0,  9.0, 10.0, 10.0, 10.0, // 120 б в г ж з и й к
		10.0,  7.0,  7.0,  7.0,  7.0, 10.0, 10.0, 10.0, // 128 л м н о п т у ф
		10.0, 13.0, 13.0, 13.0, 13.0, 27.0, 12.0, 30.0, // 136 ц щ ъ ы ь N n ?(upsidedown)
		27.0, 16.0, 27.0, 27.0, 27.0, 27.0, 27.0, 27.0, // 144 0 1 2 3 4 5 6 7
		27.0, 27.0, 18.0, 29.0, 26.0, 25.0, 28.0, 26.0, // 152 8 9 : A B C D E
		25.0, 27.0, 28.0, 12.0, 24.0, 25.0, 24.0, 30.0, // 160 F G H I J K L M
		27.0, 29.0, 26.0, 26.0, 25.0, 26.0, 25.0, 26.0, // 168 N O P Q R S T U
		28.0, 32.0, 27.0, 26.0, 26.0, 29.0, 29.0, 29.0, // 176 V W X Y Z А Б В
		29.0, 33.0, 25.0, 26.0, 26.0, 26.0, 26.0, 14.0, // 184 Г Ж З И Й К Л М
		14.0, 14.0, 14.0, 29.0, 29.0, 29.0, 29.0, 26.0, // 192 Н О П Т У Ф Ц Щ
		26.0, 26.0, 26.0, 21.0, 25.0, 30.0, 27.0, 27.0, // 200 Ъ Ы Ь Я С ї
		10.0
	},
	{
		 0.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0,
		15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0,
		15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0,
		15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0,
		15.0,  9.0, 17.0, 27.0, 20.0, 34.0, 23.0, 12.0, // 0    ! " Ј $ % & '
		12.0, 12.0, 21.0, 20.0, 12.0, 14.0, 12.0, 15.0, // 8  ( ) * + , - . /
		23.0, 15.0, 21.0, 21.0, 21.0, 21.0, 21.0, 21.0, // 16 0 1 2 3 4 5 6 7
		20.0, 21.0, 12.0, 12.0, 24.0, 24.0, 24.0, 19.0, // 24 8 9 : ; < = > ?
		10.0, 22.0, 19.0, 19.0, 22.0, 16.0, 19.0, 24.0, // 32 tmA B C D E F G
		22.0, 11.0, 16.0, 21.0, 15.0, 28.0, 24.0, 27.0, // 40 H I J K L M N O
		20.0, 25.0, 19.0, 19.0, 18.0, 23.0, 23.0, 31.0, // 48 P Q R S T U V W
		23.0, 19.0, 21.0, 21.0, 13.0, 35.0, 11.0, 21.0, // 56 X Y Z       ! _
		10.0, 19.0, 20.0, 14.0, 20.0, 19.0, 13.0, 20.0, // 64 ! a b c d e f g
		19.0,  9.0,  9.0, 19.0,  9.0, 29.0, 19.0, 21.0, // 72 h i j k l m n o
		19.0, 19.0, 15.0, 15.0, 14.0, 18.0, 19.0, 27.0, // 80 p q r s t u v w
		20.0, 20.0, 17.0, 21.0, 17.0, 20.0, 15.0, 15.0, // 88 x y z     $ [ ]
		22.0, 22.0, 22.0, 22.0, 29.0, 19.0, 16.0, 16.0, // 96 А Б В Г Ж З И Й
		16.0, 16.0, 11.0, 11.0, 11.0, 11.0, 27.0, 27.0, // 104 К Л М Н О П Т У
		27.0, 27.0, 23.0, 23.0, 23.0, 23.0, 20.0, 19.0, // 112 Ф Ц Щ Ъ Ы Ь Я а
		19.0, 19.0, 19.0, 30.0, 14.0, 19.0, 19.0, 19.0, // 120 б в г ж з и й к
		19.0,  9.0,  9.0,  9.0,  9.0, 21.0, 21.0, 21.0, // 128 л м н о п т у ф
		21.0, 18.0, 18.0, 18.0, 18.0, 24.0, 19.0, 19.0, // 136 ц щ ъ ы ь С с ї
		20.0, 18.0, 19.0, 19.0, 21.0, 19.0, 19.0, 19.0, // 144 0 1 2 3 4 5 6 7
		19.0, 19.0, 16.0, 19.0, 19.0, 19.0, 20.0, 19.0, // 152 8 9 : A B C D E
		16.0, 19.0, 19.0,  9.0, 19.0, 20.0, 14.0, 29.0, // 160 F G H I J K L M
		19.0, 19.0, 19.0, 19.0, 19.0, 19.0, 21.0, 19.0, // 168 N O P Q R S T U
		20.0, 32.0, 21.0, 19.0, 19.0, 19.0, 19.0, 19.0, // 176 V W X Y Z А Б В
		19.0, 29.0, 19.0, 19.0, 19.0, 19.0, 19.0,  9.0, // 184 Г Ж З И Й К Л М
		 9.0,  9.0,  9.0, 19.0, 19.0, 19.0, 19.0, 19.0, // 192 Н О П Т У Ф Ц Щ
		19.0, 19.0, 19.0, 19.0, 21.0, 19.0, 10.0,  9.0, // 200 Ъ Ы Ь Я С ї ' .
		10.0
	},
	{
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0
	},
	{
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		0.0
	}
};

static stock regex:gRegex;

hook OnScriptInit() {
	gRegex = regex_new("\\{([0-9A-Fa-f]{6})\\}");
	for (new font = 2; font < 4; font++) {
		for (new c = 0; c < sizeof (characterWidths[]); c++) {
			new c2 = c;
			//if (font == 2) {
			switch (c) {
				case 0x3A:
					c2 = 0xBA;
				case 0x28, 0x29:
					c2 += 0x56;
				case 0x24:
					c2 = 0x7D;
				case 0x27:
					c2 = 0xEE;
				case 0x2E:
					c2 = 0xEF;
				case 0x21:
					c2 = 0xF0;
				default:
					goto font2_not_done;
			}
			goto font2_done;
			//}
			font2_not_done:
			switch (c) {
				case 0xAF:
					c2 = 0xED;
				case 0x3F:
					c2 = 0x7B;
				case 0x26:
					c2 = 0x2A;
				case 0x5E:
					c2 = 0x40;
				case 0xAD, 0xAE:
					c2 = 0xEC;
				default: {
					if (0x30 <= c <= 0x39) {
						c2 += 0x80;
					} else if (0x41 <= c <= 0x5A) {
						c2 += 0x7A;
					} else if (0x61 <= c <= 0x7A) {
						c2 += 0x5A;
					} else if (0x80 <= c <= 0x96) {
						c2 += 0x55;
					} else if (0x97 <= c <= 0xAC) {
						c2 += 0x3E;
					}
				}
			}
			font2_done:
			new font2 = font - 2;
			characterWidths[font][c] = characterWidths[font2][c2];
		}
	}
}

static stock bool:TDC_GetNextColour(str[], &start, &end) {
	new match_results:m;
	if (regex_search(str, gRegex, m, start, end)) {
		start = start + end;
		end = start + 8;
		return true;
	} else {
		return false;
	}
}

static stock TDC_GetColour(str[]) {
	new colour = 0;
	for (new i = 0; i < 6; i++) {
		colour = colour << 4;
		if ('0' <= str[i] <= '9') {
			colour = colour + str[i] - '0';
		} else if ('A' <= str[i] <= 'F') {
			colour = colour + str[i] - '7';
		} else if ('a' <= str[i] <= 'f') {
			colour = colour + str[i] - 'W';
		}
	}
	return colour * 256 + 0xFF;
}

static stock Text:TDC_ShowGlobal(Float:x, Float:y, text[], font, alignment, Float:width, Float:height, shadow, outline, bool:prop, Float:fontx, Float:fonty, bool:box, colour, bg, bc, modelindex, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom, color1, color2, bool:select) {
	new Text:t = TextDrawCreate(x, y, text);
	TextDrawLetterSize(t, fontx, fonty),
	TextDrawAlignment(t, alignment),
	TextDrawColor(t, colour),
	TextDrawSetShadow(t, shadow),
	TextDrawSetOutline(t, outline),
	TextDrawBackgroundColor(t, bg),
	TextDrawFont(t, font),
	TextDrawSetProportional(t, prop),
	TextDrawUseBox(t, box),
	TextDrawBoxColor(t, bc),
	TextDrawTextSize(t, width, height);
	TextDrawSetSelectable(t, select);
	if (font == 5) {
		TextDrawSetPreviewModel(t, modelindex);
		TextDrawSetPreviewRot(t, fRotX, fRotY, fRotZ, fZoom);
		TextDrawSetPreviewVehCol(t, color1, color2);
	}
	return t;
}

static stock PlayerText:TDC_ShowPlayer(playerid, Float:x, Float:y, text[], font, alignment, Float:width, Float:height, shadow, outline, bool:prop, Float:fontx, Float:fonty, bool:box, colour, bg, bc, modelindex, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom, color1, color2, bool:select) {
	new PlayerText:t = CreatePlayerTextDraw(playerid, x, y, text);
	PlayerTextDrawLetterSize(playerid, t, fontx, fonty),
	PlayerTextDrawAlignment(playerid, t, alignment),
	PlayerTextDrawColor(playerid, t, colour),
	PlayerTextDrawSetShadow(playerid, t, shadow),
	PlayerTextDrawSetOutline(playerid, t, outline),
	PlayerTextDrawBackgroundColor(playerid, t, bg),
	PlayerTextDrawFont(playerid, t, font),
	PlayerTextDrawSetProportional(playerid, t, prop),
	PlayerTextDrawUseBox(playerid, t, box),
	PlayerTextDrawBoxColor(playerid, t, bc),
	PlayerTextDrawTextSize(playerid, t, width, height);
	PlayerTextDrawSetSelectable(playerid, t, select);
	if (playerid, font == 5) {
		PlayerTextDrawSetPreviewModel(playerid, t, modelindex);
		PlayerTextDrawSetPreviewRot(playerid, t, fRotX, fRotY, fRotZ, fZoom);
		PlayerTextDrawSetPreviewVehCol(playerid, t, color1, color2);
	}
	return t;
}

stock Float:TDC_GetCharacterWidth(font, c, bool:prop, Float:outline, Float:fontx) {
	if (font > 3) {
		return 0.0;
	} else if (prop) {
		if (font < 2) {
			if (c == 0xB1) {
				c = 0x60;
			} else if (c > 0xBB) {
				c = 0x20;
			}
		}
		if (0 < c < sizeof (characterWidths[])) {
			return (characterWidths[font][c] + outline) * fontx;
		} else {
			return (characterWidths[font][sizeof (characterWidths[]) - 1] + outline) * fontx;
		}
	} else {
		return ((font & 1 ? 20.0 : 27.0) + outline) * fontx;
	}
}

stock Float:TDC_GetStringWidth(font, string[], bool:prop, Float:outline, Float:fontx) {
	new Float:width = 0.0;
	for (new i = 0; string[i]; i++) {
		width += TDC_GetCharacterWidth(font, string[i], prop, outline, fontx);
	}
	return width;
}

static stock TDC_GetLineEnd(font, text[], pos, Float:max, bool:prop, Float:outline, Float:fontx, &Float:measured) {
	new bool:end = false;
	new last = pos;
	new Float:width = 0.0;
	for ( ; ; ) {
		switch (text[pos]) {
			case '\0': {
				measured = width;
				last = pos;
				break;
			}
			case '{': {
				if (text[pos + 1] && text[pos + 2] && text[pos + 3] && text[pos + 4] && text[pos + 5] && text[pos + 6] && text[pos + 7] == '}') {
					pos += 8;
				} else {
					++pos;
				}
			}
			case '\1' .. ' ': {
				width += TDC_GetCharacterWidth(font, ' ', prop, outline, fontx);
				end = true;
				++pos;
				last = pos;
				measured = width;
				if (width >= max) {
					break;
				}
			}
			default: {
				width += TDC_GetCharacterWidth(font, text[pos], prop, outline, fontx);
				if (end && width >= max) {
					break;
				}
				++pos;
			}
		}
	}
	return last;
}

#if !defined MAX_COLOURED_TEXT_DRAWS
	#define MAX_COLOURED_TEXT_DRAWS MAX_TEXT_DRAWS
#endif

#if !defined MAX_COLOURED_PLAYER_TEXT_DRAWS
	#define MAX_COLOURED_PLAYER_TEXT_DRAWS MAX_COLOURED_TEXT_DRAWS
#endif

enum TDC_ENUM {
	TDC_FLAGS,
	Float:TDC_X,
	Float:TDC_Y,
	Alloc:TDC_TEXT,
	TDC_FONT,
	TDC_ALIGNMENT,
	Float:TDC_WIDTH,
	Float:TDC_HEIGHT,
	TDC_SHADOW,
	TDC_OUTLINE,
	bool:TDC_PROP,
	Float:TDC_FONTX,
	Float:TDC_FONTY,
	bool:TDC_BOX,
	bool:TDC_SELECTABLE,
	TDC_COLOUR,
	TDC_BG,
	TDC_BC,
	Float:TDC_ROT_X,
	Float:TDC_ROT_Y,
	Float:TDC_ROT_Z,
	Float:TDC_ZOOM,
	TDC_MODEL,
	TDC_COLOUR_1,
	TDC_COLOUR_2,
	Text:TDC_BOX_TD
}

static stock Iterator:gPlayerTds[MAX_PLAYERS]<MAX_COLOURED_PLAYER_TEXT_DRAWS, MAX_TEXT_DRAWS>;
static stock Iterator:gPlayers[MAX_COLOURED_TEXT_DRAWS]<MAX_PLAYERS>;
static stock Iterator:gTds<MAX_COLOURED_TEXT_DRAWS, MAX_TEXT_DRAWS>;
static stock gStyle[MAX_COLOURED_TEXT_DRAWS][TDC_ENUM];
static stock gPlayerStyle[MAX_PLAYERS * MAX_COLOURED_PLAYER_TEXT_DRAWS][TDC_ENUM];

hook OnPlayerDisconnect(playerid, reason) {
	for (new Text:id = Text:0; id < Text:MAX_COLOURED_TEXT_DRAWS; id++) {
		TDC_TextDrawHideForPlayer(playerid, id);
	}
	for (new PlayerText:id = PlayerText:0; id < PlayerText:MAX_COLOURED_PLAYER_TEXT_DRAWS; id++) {
		TDC_PlayerTDDestroy(playerid, id);
	}
}

static stock TDC_Render(playerid, id, Float:x, Float:y, text[], font, alignment, Float:width, Float:height, shadow, outline, bool:prop, Float:fontx, Float:fonty, bool:box, colour, bg, bc, modelindex, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom, color1, color2, bool:select) {
	new start = 0, p1 = 0, end = 0;
	new next;
	new Float:x2;
	new Float:measured;
	new Float:space = TDC_GetCharacterWidth(font, ' ', prop, outline, fontx);
	if (font < 4) {
		switch (alignment) {
			case 1, 5:
				width = width - x;
			case 2:
				x2 = width,
				width = height,
				height = x2;
			case 4:
				width = x - width;
			case 3:
				width = x;
		}
		height -= y;
	}
	new line = TDC_GetLineEnd(font, text, 0, width, prop, outline, fontx, measured);
	switch (alignment) {
		case 1, 5:
			x2 = x;
		case 2:
			x2 = x - measured / 2;
		case 3, 4: {
			p1 = line;
			while (p1-- > start && text[p1] <= ' ') {
				measured -= space;
			}
			x2 = x - measured;
		}
	}
	new bool:nl = false;
	while (TDC_GetNextColour(text, p1, end)) {
		if (p1 > line) {
			p1 = line;
			end = line;
			nl = true;
		} else if (p1 == line) {
			nl = true;
			next = TDC_GetColour(text[p1 + 1]);
		} else {
			next = TDC_GetColour(text[p1 + 1]);
		}
		while (start < p1 && text[start] <= ' ') {
			x2 += space;
			++start;
		}
		if (start < p1) {
			new t1 = text[p1], p2 = p1;
			text[p1] = '\0';
			while (p2--) {
				if (text[p2] > ' ') {
					++p2;
					break;
				}
			}
			new t2 = text[p2];
			text[p2] = '\0';
			if (playerid == INVALID_PLAYER_ID) {
				new PlayerText:t = TDC_ShowPlayer(playerid, x2, y, text[start], font, 1, 9999.0, 9999.0, shadow, outline, prop, fontx, fonty, box, colour, bg, bc, modelindex, fRotX, fRotY, fRotZ, fZoom, color1, color2, select);
				Iter_Add(gPlayerTds[playerid]<id>, _:t);
			} else {
				new Text:t = TDC_ShowGlobal(x2, y, text[start], font, 1, 9999.0, 9999.0, shadow, outline, prop, fontx, fonty, box, colour, bg, bc, modelindex, fRotX, fRotY, fRotZ, fZoom, color1, color2, select);
				Iter_Add(gTds<id>, _:t);
			}
			text[p2] = t2;
			x2 += TDC_GetStringWidth(font, text[start], prop, outline, fontx);
			text[p1] = t1;
		}
		if (nl) {
			line = TDC_GetLineEnd(font, text, line, width, prop, outline, fontx, measured);
			switch (alignment) {
				case 1, 5:
					x2 = x;
				case 2:
					x2 = x - measured / 2;
				case 3, 4: {
					p1 = line;
					while (p1-- > start && text[p1] <= ' ') {
						measured -= space;
					}
					x2 = x - measured;
				}
			}
			y += fonty * 9.0;
			nl = false;
		}
		colour = next;
		start = end;
	}
	while ('\0' < text[start] <= ' ') {
		x2 += space;
		++start;
	}
	if (start < line) {
		while (line--) {
			if (text[line] > ' ') {
				++line;
				break;
			}
		}
		text[line] = '\0';
		if (playerid == INVALID_PLAYER_ID) {
			new PlayerText:t = TDC_ShowPlayer(playerid, x2, y, text[start], font, 1, 9999.0, 9999.0, shadow, outline, prop, fontx, fonty, box, colour, bg, bc, modelindex, fRotX, fRotY, fRotZ, fZoom, color1, color2, select);
			Iter_Add(gPlayerTds[playerid]<id>, _:t);
		} else {
			new Text:t = TDC_ShowGlobal(x2, y, text[start], font, 1, 9999.0, 9999.0, shadow, outline, prop, fontx, fonty, box, colour, bg, bc, modelindex, fRotX, fRotY, fRotZ, fZoom, color1, color2, select);
			Iter_Add(gTds<id>, _:t);
		}
	}
	if (box) {
		
	} else {
		
	}
}

static stock bool:TDC_ValidGlobal(Text:id) {
	return (Text:0 <= id < Text:MAX_COLOURED_TEXT_DRAWS && (gStyle[_:id][TDC_FLAGS] & 1));
}

static stock bool:TDC_ValidPlayer(playerid, PlayerText:id) {
	return (PlayerText:0 <= id < PlayerText:MAX_COLOURED_PLAYER_TEXT_DRAWS && (gPlayerStyle[playerid * MAX_PLAYERS + _:id][TDC_FLAGS] & 1));
}

#define Malloc_FastString(%1) Malloc_NextSlot(_:(%1))

static stock TDC_UpdateGlobal(id) {
	if (gStyle[id][TDC_FLAGS] & 4) {
		foreach (new t : gTds<id>) {
			TextDrawDestroy(Text:t);
		}
		Iter_Clear(gTds<id>);
		TDC_Render(INVALID_PLAYER_ID, id,
				gStyle[id][TDC_X],                       gStyle[id][TDC_Y],
				Malloc_FastString(gStyle[id][TDC_TEXT]), gStyle[id][TDC_FONT],
				gStyle[id][TDC_ALIGNMENT],               gStyle[id][TDC_WIDTH],
				gStyle[id][TDC_HEIGHT],                  gStyle[id][TDC_SHADOW],
				gStyle[id][TDC_OUTLINE],                 gStyle[id][TDC_PROP],
				gStyle[id][TDC_FONTX],                   gStyle[id][TDC_FONTY],
				gStyle[id][TDC_BOX],                     gStyle[id][TDC_COLOUR],
				gStyle[id][TDC_BG],                      gStyle[id][TDC_BC],
				gStyle[id][TDC_MODEL],                   gStyle[id][TDC_ROT_X],
				gStyle[id][TDC_ROT_Y],                   gStyle[id][TDC_ROT_Z],
				gStyle[id][TDC_ZOOM],                    gStyle[id][TDC_COLOUR_1],
				gStyle[id][TDC_COLOUR_2],                gStyle[id][TDC_SELECTABLE]);
		foreach (new t : gTds<id>) {
			foreach (new playerid : gPlayers[id]) {
				TextDrawShowForPlayer(playerid, Text:t);
			}
		}
	}
}

static stock TDC_UpdatePlayer(playerid, id) {
	foreach (new t : gPlayerTds[playerid]<id>) {
		PlayerTextDrawDestroy(playerid, PlayerText:t);
	}
	new slot = playerid * MAX_PLAYERS + id;
	Iter_Clear(gPlayerTds[playerid]<id>);
	TDC_Render(playerid, id,
			gPlayerStyle[slot][TDC_X],                      gPlayerStyle[slot][TDC_Y],
			Malloc_FastString(gPlayerStyle[slot][TDC_TEXT]), gPlayerStyle[slot][TDC_FONT],
			gPlayerStyle[slot][TDC_ALIGNMENT],               gPlayerStyle[slot][TDC_WIDTH],
			gPlayerStyle[slot][TDC_HEIGHT],                  gPlayerStyle[slot][TDC_SHADOW],
			gPlayerStyle[slot][TDC_OUTLINE],                 gPlayerStyle[slot][TDC_PROP],
			gPlayerStyle[slot][TDC_FONTX],                   gPlayerStyle[slot][TDC_FONTY],
			gPlayerStyle[slot][TDC_BOX],                     gPlayerStyle[slot][TDC_COLOUR],
			gPlayerStyle[slot][TDC_BG],                      gPlayerStyle[slot][TDC_BC],
			gPlayerStyle[slot][TDC_MODEL],                   gPlayerStyle[slot][TDC_ROT_X],
			gPlayerStyle[slot][TDC_ROT_Y],                   gPlayerStyle[slot][TDC_ROT_Z],
			gPlayerStyle[slot][TDC_ZOOM],                    gPlayerStyle[slot][TDC_COLOUR_1],
			gPlayerStyle[slot][TDC_COLOUR_2],                gPlayerStyle[slot][TDC_SELECTABLE]);
	if (gPlayerStyle[slot][TDC_FLAGS] & 8) {
		foreach (new t : gPlayerTds[playerid]<id>) {
			PlayerTextDrawShow(playerid, PlayerText:t);
		}
	}
}

stock Text:TDC_TextDrawCreate(Float:x, Float:y, text[]) {
	static style[TDC_ENUM] = { 1, 0.0, 0.0, NO_ALLOC, 0, 1, 640.0, 480.0, 2, 0, true, 0.48, 1.15, false, false, 0xE1E1E1FF, 0x000000FF, 0x000000FF, 0.0, 0.0, 0.0, 1.0, 0, -1, -1 };
	for (new id = 0; id < MAX_COLOURED_TEXT_DRAWS; ++id) {
		if (!(gStyle[id][TDC_FLAGS] & 1)) {
			new len = strlen(text);
			new Alloc:mem = malloc(len + 1);
			if (mem == NO_ALLOC) {
				return Text:INVALID_TEXT_DRAW;
			}
			if (text[0] == '\0') {
				Malloc_SetData(mem, 0, ' ');
				Malloc_SetData(mem, 1, '\0');
			} else {
				Malloc_SetData(mem, 0, '\0');
				strcat(Malloc_FastString(mem), text, len + 1);
			}
			gStyle[id] = style;
			gStyle[id][TDC_TEXT] = mem;
			gStyle[id][TDC_X] = x;
			gStyle[id][TDC_Y] = y;
			return Text:id;
		}
	}
	return Text:INVALID_TEXT_DRAW;
}

stock TDC_TextDrawDestroy(Text:text) {
	if (TDC_ValidGlobal(text)) {
		TDC_TextDrawHideForAll(text);
		gStyle[_:text][TDC_FLAGS] = 0;
		free(gStyle[_:text][TDC_TEXT]);
	}
}

stock TDC_TextDrawLetterSize(Text:text, Float:x, Float:y) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_FONTX] = x;
		gStyle[_:text][TDC_FONTY] = y;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawTextSize(Text:text, Float:x, Float:y) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_WIDTH] = x;
		gStyle[_:text][TDC_HEIGHT] = y;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawAlignment(Text:text, alignment) {
	/* 1 = left, 2 = centre, 3 = right, 4 = fixed right, 5 = justify */
	if (TDC_ValidGlobal(text) && 1 <= alignment <= 5) {
		gStyle[_:text][TDC_ALIGNMENT] = alignment;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawColor(Text:text, color) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_COLOUR] = color;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawUseBox(Text:text, use) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_BOX] = !!use;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawBoxColor(Text:text, color) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_BC] = color;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetShadow(Text:text, size) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_SHADOW] = size;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetOutline(Text:text, size) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_OUTLINE] = size;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawBackgroundColor(Text:text, color) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_BG] = color;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawFont(Text:text, font) {
	if (TDC_ValidGlobal(text) && 0 <= font <= 5) {
		gStyle[_:text][TDC_FONT] = font;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetProportional(Text:text, set) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_PROP] = !!set;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetSelectable(Text:text, set) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_SELECTABLE] = !!set;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPos(Text:text, Float:x, Float:y) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_X] = x;
		gStyle[_:text][TDC_Y] = y;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawShowForPlayer(playerid, Text:text) {
	if (TDC_ValidGlobal(text) && Iter_Contains(Player, playerid) && !Iter_Contains(gPlayers[_:text], playerid)) {
		Iter_Add(gPlayers[_:text], playerid);
		if (gStyle[_:text][TDC_FLAGS] & 4) {
			foreach (new t : gTds<(_:text)>) {
				TextDrawShowForPlayer(playerid, Text:t);
			}
		} else {
			gStyle[_:text][TDC_FLAGS] |= 4;
			TDC_UpdateGlobal(_:text);
		}
	}
}

stock TDC_TextDrawHideForPlayer(playerid, Text:text) {
	if (TDC_ValidGlobal(text) && Iter_Contains(gPlayers[_:text], playerid)) {
		Iter_Remove(gPlayers[_:text], playerid);
		if (Iter_Count(gPlayers[_:text] == 0)) {
			gStyle[_:text][TDC_FLAGS] &= ~4;
			foreach (new t : gTds<(_:text)>) {
				TextDrawDestroy(Text:t);
			}
			Iter_Clear(gTds<(_:text)>);
		} else {
			foreach (new t : gTds<(_:text)>) {
				TextDrawHideForPlayer(playerid, Text:t);
			}
		}
	}
}

stock TDC_TextDrawShowForAll(Text:text) {
	if (TDC_ValidGlobal(text) && Iter_Count(Player)) {
		gStyle[_:text][TDC_FLAGS] |= 4;
		Iter_TrueArray(gPlayers[text]) = Iter_TrueArray(Player);
		Iter_TrueCount(gPlayers[text]) = Iter_TrueCount(Player);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawHideForAll(Text:text) {
	if (TDC_ValidGlobal(text)) {
		gStyle[_:text][TDC_FLAGS] &= ~4;
		foreach (new t : gTds<(_:text)>) {
			TextDrawDestroy(Text:t);
		}
		Iter_Clear(gTds<_:text>);
	}
}

stock TDC_TextDrawSetString(Text:text, string[]) {
	if (TDC_ValidGlobal(text)) {
		new len = strlen(string);
		new Alloc:mem = malloc(len + 1);
		if (mem == NO_ALLOC) {
			return;
		}
		if (text[0] == '\0') {
			Malloc_SetData(mem, 0, ' ');
			Malloc_SetData(mem, 1, '\0');
		} else {
			Malloc_SetData(mem, 0, '\0');
			strcat(Malloc_FastString(mem), string, len + 1);
		}
		free(gStyle[_:text][TDC_TEXT]);
		gStyle[_:text][TDC_TEXT] = mem;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPreviewModel(Text:text, modelindex) {
	if (TDC_ValidGlobal(text) && gStyle[_:text][TDC_FONT] == 5) {
		gStyle[_:text][TDC_MODEL] = modelindex;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPreviewRot(Text:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0) {
	if (TDC_ValidGlobal(text) && gStyle[_:text][TDC_FONT] == 5) {
		gStyle[_:text][TDC_ROT_X] = fRotX;
		gStyle[_:text][TDC_ROT_Y] = fRotY;
		gStyle[_:text][TDC_ROT_Z] = fRotZ;
		gStyle[_:text][TDC_ZOOM] = fZoom;
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPreviewVehCol(Text:text, color1, color2) {
	if (TDC_ValidGlobal(text) && gStyle[_:text][TDC_FONT] == 5) {
		gStyle[_:text][TDC_COLOUR_1] = color1;
		gStyle[_:text][TDC_COLOUR_2] = color2;
		TDC_UpdateGlobal(_:text);
	}
}

stock bool:TDC_TextDrawGetLetterSize(Text:text, &Float:x, &Float:y) {
	if (TDC_ValidGlobal(text)) {
		x = gStyle[_:text][TDC_FONTX];
		y = gStyle[_:text][TDC_FONTY];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetTextSize(Text:text, &Float:x, &Float:y) {
	if (TDC_ValidGlobal(text)) {
		x = gStyle[_:text][TDC_WIDTH];
		y = gStyle[_:text][TDC_HEIGHT];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetAlignment(Text:text, &alignment) {
	if (TDC_ValidGlobal(text)) {
		alignment = gStyle[_:text][TDC_ALIGNMENT];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetColor(Text:text, &color) {
	if (TDC_ValidGlobal(text)) {
		color = gStyle[_:text][TDC_COLOUR];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetUseBox(Text:text, &bool:use) {
	if (TDC_ValidGlobal(text)) {
		use = gStyle[_:text][TDC_BOX];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetBoxColor(Text:text, &color) {
	if (TDC_ValidGlobal(text)) {
		color = gStyle[_:text][TDC_BC];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetShadow(Text:text, &size) {
	if (TDC_ValidGlobal(text)) {
		size = gStyle[_:text][TDC_SHADOW];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetOutline(Text:text, &size) {
	if (TDC_ValidGlobal(text)) {
		size = gStyle[_:text][TDC_OUTLINE];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetBackgroundColor(Text:text, &color) {
	if (TDC_ValidGlobal(text)) {
		color = gStyle[_:text][TDC_BG];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetFont(Text:text, &font) {
	if (TDC_ValidGlobal(text)) {
		font = gStyle[_:text][TDC_FONT];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetProportional(Text:text, &bool:set) {
	if (TDC_ValidGlobal(text)) {
		set = gStyle[_:text][TDC_PROP];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetSelectable(Text:text, &bool:set) {
	if (TDC_ValidGlobal(text)) {
		set = gStyle[_:text][TDC_SELECTABLE];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPos(Text:text, &Float:x, &Float:y) {
	if (TDC_ValidGlobal(text)) {
		x = gStyle[_:text][TDC_X];
		y = gStyle[_:text][TDC_Y];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetString(Text:text, string[], size = sizeof (string)) {
	if (TDC_ValidGlobal(text)) {
		string[0] = '\0';
		strcat(string, Malloc_FastString(gStyle[_:text][TDC_TEXT]), size);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPreviewModel(Text:text, &modelindex) {
	if (TDC_ValidGlobal(text) && gStyle[_:text][TDC_FONT] == 5) {
		modelindex = gStyle[_:text][TDC_MODEL];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPreviewRot(Text:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom = 1.0) {
	if (TDC_ValidGlobal(text) && gStyle[_:text][TDC_FONT] == 5) {
		fRotX = gStyle[_:text][TDC_ROT_X];
		fRotY = gStyle[_:text][TDC_ROT_Y];
		fRotZ = gStyle[_:text][TDC_ROT_Z];
		fZoom = gStyle[_:text][TDC_ZOOM];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPreviewVehCol(Text:text, &color1, &color2) {
	if (TDC_ValidGlobal(text) && gStyle[_:text][TDC_FONT] == 5) {
		color1 = gStyle[_:text][TDC_COLOUR_1];
		color2 = gStyle[_:text][TDC_COLOUR_2];
		return true;
	} else {
		return false;
	}
}

stock PlayerText:TDC_PlayerTDCreate(playerid, Float:x, Float:y, text[]) {
	static style[TDC_ENUM] = { 1, 0.0, 0.0, NO_ALLOC, 0, 1, 640.0, 480.0, 2, 0, true, 0.48, 1.15, false, false, 0xE1E1E1FF, 0x000000FF, 0x000000FF, 0.0, 0.0, 0.0, 1.0, 0, -1, -1 };
	for (new id = 0; id < MAX_COLOURED_PLAYER_TEXT_DRAWS; ++id) {
		new slot = playerid * MAX_PLAYERS + id;
		if (!(gPlayerStyle[slot][TDC_FLAGS] & 1)) {
			new len = strlen(text);
			new Alloc:mem = malloc(len + 1);
			if (mem == NO_ALLOC) {
				return PlayerText:INVALID_TEXT_DRAW;
			}
			if (text[0] == '\0') {
				Malloc_SetData(mem, 0, ' ');
				Malloc_SetData(mem, 1, '\0');
			} else {
				Malloc_SetData(mem, 0, '\0');
				strcat(Malloc_FastString(mem), text, len + 1);
			}
			gPlayerStyle[slot] = style;
			gPlayerStyle[slot][TDC_TEXT] = mem;
			gPlayerStyle[slot][TDC_X] = x;
			gPlayerStyle[slot][TDC_Y] = y;
			return PlayerText:id;
		}
	}
	return PlayerText:INVALID_TEXT_DRAW;
}

stock TDC_PlayerTDDestroy(playerid, PlayerText:text) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		TDC_PlayerTDHide(playerid, text);
		gPlayerStyle[slot][TDC_FLAGS] = 0;
		free(gPlayerStyle[slot][TDC_TEXT]);
	}
}

stock TDC_PlayerTDLetterSize(playerid, PlayerText:text, Float:x, Float:y) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[slot][TDC_FONTX] = x;
		gPlayerStyle[slot][TDC_FONTY] = y;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDTextSize(playerid, PlayerText:text, Float:x, Float:y) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[slot][TDC_WIDTH] = x;
		gPlayerStyle[slot][TDC_HEIGHT] = y;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDAlignment(playerid, PlayerText:text, alignment) {
	/* 1 = left, 2 = centre, 3 = right, 4 = fixed right, 5 = justify */
	if (TDC_ValidPlayer(playerid, text) && 1 <= alignment <= 5) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_ALIGNMENT] = alignment;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDColor(playerid, PlayerText:text, color) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_COLOUR] = color;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDUseBox(playerid, PlayerText:text, use) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_BOX] = !!use;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDBoxColor(playerid, PlayerText:text, color) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_BC] = color;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetShadow(playerid, PlayerText:text, size) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_SHADOW] = size;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetOutline(playerid, PlayerText:text, size) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_OUTLINE] = size;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDBackgroundColor(playerid, PlayerText:text, color) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_BG] = color;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDFont(playerid, PlayerText:text, font) {
	if (TDC_ValidPlayer(playerid, text) && 0 <= font <= 5) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_FONT] = font;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetProportional(playerid, PlayerText:text, set) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_PROP] = !!set;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetSelectable(playerid, PlayerText:text, set) {
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_SELECTABLE] = !!set;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPos(playerid, PlayerText:text, Float:x, Float:y) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		gPlayerStyle[slot][TDC_X] = x;
		gPlayerStyle[slot][TDC_Y] = y;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDShow(playerid, PlayerText:text) {
	if (TDC_ValidPlayer(playerid, text) && Iter_Contains(Player, playerid)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_FLAGS] |= 8;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDHide(playerid, PlayerText:text) {
	if (TDC_ValidPlayer(playerid, text) && Iter_Contains(Player, playerid)) {
		gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_FLAGS] &= ~8;
		foreach (new t : gPlayerTds[playerid]<(_:text)>) {
			PlayerTextDrawDestroy(playerid, PlayerText:t);
		}
		Iter_Clear(gPlayerTds[playerid]<_:text>);
	}
}

stock TDC_PlayerTDSetString(playerid, PlayerText:text, string[]) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		new len = strlen(string);
		new Alloc:mem = malloc(len + 1);
		if (mem == NO_ALLOC) {
			return;
		}
		if (text[0] == '\0') {
			Malloc_SetData(mem, 0, ' ');
			Malloc_SetData(mem, 1, '\0');
		} else {
			Malloc_SetData(mem, 0, '\0');
			strcat(Malloc_FastString(mem), string, len + 1);
		}
		free(gPlayerStyle[slot][TDC_TEXT]);
		gPlayerStyle[slot]][TDC_TEXT] = mem;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPreviewModel(playerid, PlayerText:text, modelindex) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text) && gPlayerStyle[slot][TDC_FONT] == 5) {
		gPlayerStyle[slot][TDC_MODEL] = modelindex;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPreviewRot(playerid, PlayerText:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text) && gPlayerStyle[slot][TDC_FONT] == 5) {
		gPlayerStyle[slot][TDC_ROT_X] = fRotX;
		gPlayerStyle[slot][TDC_ROT_Y] = fRotY;
		gPlayerStyle[slot][TDC_ROT_Z] = fRotZ;
		gPlayerStyle[slot][TDC_ZOOM] = fZoom;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPreviewVehCol(playerid, PlayerText:text, color1, color2) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text) && gPlayerStyle[slot][TDC_FONT] == 5) {
		gPlayerStyle[slot][TDC_COLOUR_1] = color1;
		gPlayerStyle[slot][TDC_COLOUR_2] = color2;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock bool:TDC_PlayerTDGetLetterSize(playerid, PlayerText:text, &Float:x, &Float:y) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		x = gPlayerStyle[slot][TDC_FONTX];
		y = gPlayerStyle[slot][TDC_FONTY];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetTextSize(playerid, PlayerText:text, &Float:x, &Float:y) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		x = gPlayerStyle[slot][TDC_WIDTH];
		y = gPlayerStyle[slot][TDC_HEIGHT];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetAlignment(playerid, PlayerText:text, &alignment) {
	if (TDC_ValidPlayer(playerid, text)) {
		alignment = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_ALIGNMENT];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetColor(playerid, PlayerText:text, &color) {
	if (TDC_ValidPlayer(playerid, text)) {
		color = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_COLOUR];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetUseBox(playerid, PlayerText:text, &bool:use) {
	if (TDC_ValidPlayer(playerid, text)) {
		use = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_BOX];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetBoxColor(playerid, PlayerText:text, &color) {
	if (TDC_ValidPlayer(playerid, text)) {
		color = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_BC];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetShadow(playerid, PlayerText:text, &size) {
	if (TDC_ValidPlayer(playerid, text)) {
		size = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_SHADOW];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetOutline(playerid, PlayerText:text, &size) {
	if (TDC_ValidPlayer(playerid, text)) {
		size = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_OUTLINE];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetBackgroundColor(playerid, PlayerText:text, &color) {
	if (TDC_ValidPlayer(playerid, text)) {
		color = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_BG];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetFont(playerid, PlayerText:text, &font) {
	if (TDC_ValidPlayer(playerid, text)) {
		font = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_FONT];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetProportional(playerid, PlayerText:text, &bool:set) {
	if (TDC_ValidPlayer(playerid, text)) {
		set = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_PROP];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetSelectable(playerid, PlayerText:text, &bool:set) {
	if (TDC_ValidPlayer(playerid, text)) {
		set = gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_SELECTABLE];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPos(playerid, PlayerText:text, &Float:x, &Float:y) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text)) {
		x = gPlayerStyle[slot][TDC_X];
		y = gPlayerStyle[slot][TDC_Y];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetString(playerid, PlayerText:text, string[], size = sizeof (string)) {
	if (TDC_ValidPlayer(playerid, text)) {
		string[0] = '\0';
		strcat(string, Malloc_FastString(gPlayerStyle[playerid * MAX_PLAYERS + _:text][TDC_TEXT]), size);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPreviewModel(playerid, PlayerText:text, &modelindex) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text) && gPlayerStyle[slot][TDC_FONT] == 5) {
		modelindex = gPlayerStyle[slot][TDC_MODEL];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPreviewRot(playerid, PlayerText:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom = 1.0) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text) && gPlayerStyle[slot][TDC_FONT] == 5) {
		fRotX = gPlayerStyle[slot][TDC_ROT_X];
		fRotY = gPlayerStyle[slot][TDC_ROT_Y];
		fRotZ = gPlayerStyle[slot][TDC_ROT_Z];
		fZoom = gPlayerStyle[slot][TDC_ZOOM];
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPreviewVehCol(playerid, PlayerText:text, &color1, &color2) {
	new slot = playerid * MAX_PLAYERS + _:text;
	if (TDC_ValidPlayer(playerid, text) && gPlayerStyle[slot][TDC_FONT] == 5) {
		color1 = gPlayerStyle[slot][TDC_COLOUR_1];
		color2 = gPlayerStyle[slot][TDC_COLOUR_2];
		return true;
	} else {
		return false;
	}
}

#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif
#define TextDrawCreate TDC_TextDrawCreate

#if defined _ALS_TextDrawDestroy
	#undef TextDrawDestroy
#else
	#define _ALS_TextDrawDestroy
#endif
#define TextDrawDestroy TDC_TextDrawDestroy

#if defined _ALS_TextDrawLetterSize
	#undef TextDrawLetterSize
#else
	#define _ALS_TextDrawLetterSize
#endif
#define TextDrawLetterSize TDC_TextDrawLetterSize

#if defined _ALS_TextDrawTextSize
	#undef TextDrawTextSize
#else
	#define _ALS_TextDrawTextSize
#endif
#define TextDrawTextSize TDC_TextDrawTextSize

#if defined _ALS_TextDrawAlignment
	#undef TextDrawAlignment
#else
	#define _ALS_TextDrawAlignment
#endif
#define TextDrawAlignment TDC_TextDrawAlignment

#if defined _ALS_TextDrawColor
	#undef TextDrawColor
#else
	#define _ALS_TextDrawColor
#endif
#define TextDrawColor TDC_TextDrawColor

#if defined _ALS_TextDrawUseBox
	#undef TextDrawUseBox
#else
	#define _ALS_TextDrawUseBox
#endif
#define TextDrawUseBox TDC_TextDrawUseBox

#if defined _ALS_TextDrawBoxColor
	#undef TextDrawBoxColor
#else
	#define _ALS_TextDrawBoxColor
#endif
#define TextDrawBoxColor TDC_TextDrawBoxColor

#if defined _ALS_TextDrawSetShadow
	#undef TextDrawSetShadow
#else
	#define _ALS_TextDrawSetShadow
#endif
#define TextDrawSetShadow TDC_TextDrawSetShadow

#if defined _ALS_TextDrawSetOutline
	#undef TextDrawSetOutline
#else
	#define _ALS_TextDrawSetOutline
#endif
#define TextDrawSetOutline TDC_TextDrawSetOutline

#if defined _ALS_TextDrawBackgroundColor
	#undef TextDrawBackgroundColor
#else
	#define _ALS_TextDrawBackgroundColor
#endif
#define TextDrawBackgroundColor TDC_TextDrawBackgroundColor

#if defined _ALS_TextDrawFont
	#undef TextDrawFont
#else
	#define _ALS_TextDrawFont
#endif
#define TextDrawFont TDC_TextDrawFont

#if defined _ALS_TextDrawSetProportional
	#undef TextDrawSetProportional
#else
	#define _ALS_TextDrawSetProportional
#endif
#define TextDrawSetProportional TDC_TextDrawSetProportional

#if defined _ALS_TextDrawSetSelectable
	#undef TextDrawSetSelectable
#else
	#define _ALS_TextDrawSetSelectable
#endif
#define TextDrawSetSelectable TDC_TextDrawSetSelectable

#if defined _ALS_TextDrawSetPos
	#undef TextDrawSetPos
#else
	#define _ALS_TextDrawSetPos
#endif
#define TextDrawSetPos TDC_TextDrawSetPos

#if defined _ALS_TextDrawShowForPlayer
	#undef TextDrawShowForPlayer
#else
	#define _ALS_TextDrawShowForPlayer
#endif
#define TextDrawShowForPlayer TDC_TextDrawShowForPlayer

#if defined _ALS_TextDrawHideForPlayer
	#undef TextDrawHideForPlayer
#else
	#define _ALS_TextDrawHideForPlayer
#endif
#define TextDrawHideForPlayer TDC_TextDrawHideForPlayer

#if defined _ALS_TextDrawShowForAll
	#undef TextDrawShowForAll
#else
	#define _ALS_TextDrawShowForAll
#endif
#define TextDrawShowForAll TDC_TextDrawShowForAll

#if defined _ALS_TextDrawHideForAll
	#undef TextDrawHideForAll
#else
	#define _ALS_TextDrawHideForAll
#endif
#define TextDrawHideForAll TDC_TextDrawHideForAll

#if defined _ALS_TextDrawSetString
	#undef TextDrawSetString
#else
	#define _ALS_TextDrawSetString
#endif
#define TextDrawSetString TDC_TextDrawSetString

#if defined _ALS_TextDrawSetPreviewModel
	#undef TextDrawSetPreviewModel
#else
	#define _ALS_TextDrawSetPreviewModel
#endif
#define TextDrawSetPreviewModel TDC_TextDrawSetPreviewModel

#if defined _ALS_TextDrawSetPreviewRot
	#undef TextDrawSetPreviewRot
#else
	#define _ALS_TextDrawSetPreviewRot
#endif
#define TextDrawSetPreviewRot TDC_TextDrawSetPreviewRot

#if defined _ALS_TextDrawSetPreviewVehCol
	#undef TextDrawSetPreviewVehCol
#else
	#define _ALS_TextDrawSetPreviewVehCol
#endif
#define TextDrawSetPreviewVehCol TDC_TextDrawSetPreviewVehCol

#if defined _ALS_TextDrawGetLetterSize
	#undef TextDrawGetLetterSize
#else
	#define _ALS_TextDrawGetLetterSize
#endif
#define TextDrawGetLetterSize TDC_TextDrawGetLetterSize

#if defined _ALS_TextDrawGetTextSize
	#undef TextDrawGetTextSize
#else
	#define _ALS_TextDrawGetTextSize
#endif
#define TextDrawGetTextSize TDC_TextDrawGetTextSize

#if defined _ALS_TextDrawGetAlignment
	#undef TextDrawGetAlignment
#else
	#define _ALS_TextDrawGetAlignment
#endif
#define TextDrawGetAlignment TDC_TextDrawGetAlignment

#if defined _ALS_TextDrawGetColor
	#undef TextDrawGetColor
#else
	#define _ALS_TextDrawGetColor
#endif
#define TextDrawGetColor TDC_TextDrawGetColor

#if defined _ALS_TextDrawGetUseBox
	#undef TextDrawGetUseBox
#else
	#define _ALS_TextDrawGetUseBox
#endif
#define TextDrawGetUseBox TDC_TextDrawGetUseBox

#if defined _ALS_TextDrawGetBoxColor
	#undef TextDrawGetBoxColor
#else
	#define _ALS_TextDrawGetBoxColor
#endif
#define TextDrawGetBoxColor TDC_TextDrawGetBoxColor

#if defined _ALS_TextDrawGetShadow
	#undef TextDrawGetShadow
#else
	#define _ALS_TextDrawGetShadow
#endif
#define TextDrawGetShadow TDC_TextDrawGetShadow

#if defined _ALS_TextDrawGetOutline
	#undef TextDrawGetOutline
#else
	#define _ALS_TextDrawGetOutline
#endif
#define TextDrawGetOutline TDC_TextDrawGetOutline

#if defined _ALS_TextDrawGetBackgroundColor
	#undef TextDrawGetBackgroundColor
#else
	#define _ALS_TextDrawGetBackgroundColor
#endif
#define TextDrawGetBackgroundColor TDC_TextDrawGetBackgroundColor

#if defined _ALS_TextDrawGetFont
	#undef TextDrawGetFont
#else
	#define _ALS_TextDrawGetFont
#endif
#define TextDrawGetFont TDC_TextDrawGetFont

#if defined _ALS_TextDrawGetProportional
	#undef TextDrawGetProportional
#else
	#define _ALS_TextDrawGetProportional
#endif
#define TextDrawGetProportional TDC_TextDrawGetProportional

#if defined _ALS_TextDrawGetSelectable
	#undef TextDrawGetSelectable
#else
	#define _ALS_TextDrawGetSelectable
#endif
#define TextDrawGetSelectable TDC_TextDrawGetSelectable

#if defined _ALS_TextDrawGetPos
	#undef TextDrawGetPos
#else
	#define _ALS_TextDrawGetPos
#endif
#define TextDrawGetPos TDC_TextDrawGetPos

#if defined _ALS_TextDrawGetString
	#undef TextDrawGetString
#else
	#define _ALS_TextDrawGetString
#endif
#define TextDrawGetString TDC_TextDrawGetString

#if defined _ALS_TextDrawGetPreviewModel
	#undef TextDrawGetPreviewModel
#else
	#define _ALS_TextDrawGetPreviewModel
#endif
#define TextDrawGetPreviewModel TDC_TextDrawGetPreviewModel

#if defined _ALS_TextDrawGetPreviewRot
	#undef TextDrawGetPreviewRot
#else
	#define _ALS_TextDrawGetPreviewRot
#endif
#define TextDrawGetPreviewRot TDC_TextDrawGetPreviewRot

#if defined _ALS_TextDrawGetPreviewVehCol
	#undef TextDrawGetPreviewVehCol
#else
	#define _ALS_TextDrawGetPreviewVehCol
#endif
#define TextDrawGetPreviewVehCol TDC_TextDrawGetPreviewVehCol

