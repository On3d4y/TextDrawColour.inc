#include <a_samp>
#include <Pawn.Regex>
#include <memory>
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

enum e_TDC_ENUM {
	e_TDC_FLAGS,
	Float:e_TDC_X,
	Float:e_TDC_Y,
	UnmanagedPointer:e_TDC_TEXT,
	e_TDC_TEXT_LEN,
	e_TDC_FONT,
	e_TDC_ALIGNMENT,
	Float:e_TDC_WIDTH,
	Float:e_TDC_HEIGHT,
	e_TDC_SHADOW,
	e_TDC_OUTLINE,
	bool:e_TDC_PROP,
	Float:e_TDC_FONTX,
	Float:e_TDC_FONTY,
	bool:e_TDC_BOX,
	bool:e_TDC_SELECTABLE,
	e_TDC_COLOUR,
	e_TDC_BG,
	e_TDC_BC,
	Float:e_TDC_ROT_X,
	Float:e_TDC_ROT_Y,
	Float:e_TDC_ROT_Z,
	Float:e_TDC_ZOOM,
	e_TDC_MODEL,
	e_TDC_COLOUR_1,
	e_TDC_COLOUR_2,
	Text:e_TDC_BOX_TD
	UnmanagedPointer:e_TDC_TDS,
	e_TDC_TDS_COUNT,
}

static stock UnmanagedPointer:gPlayerTDs[MAX_PLAYERS][PlayerText:MAX_TEXT_DRAWS];
static stock BitArray:gPlayers[MAX_TEXT_DRAWS]<MAX_PLAYERS>;
static stock UnmanagedPointer:gTDs[Text:MAX_TEXT_DRAWS];
//static stock MEM_UM_get_val(gPlayerTDs[MAX_PLAYERS * MAX_TEXT_DRAWS], e_TDC_ENUM);

hook OnPlayerDisconnect(playerid, reason) {
	for (new Text:id = Text:0; id < Text:MAX_TEXT_DRAWS; id++) {
		TDC_TextDrawHideForPlayer(playerid, id);
	}
	for (new PlayerText:id = PlayerText:0; id < PlayerText:MAX_TEXT_DRAWS; id++) {
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
				Iter_Add(gPlayerTDs[playerid]<id>, _:t);
			} else {
				new Text:t = TDC_ShowGlobal(x2, y, text[start], font, 1, 9999.0, 9999.0, shadow, outline, prop, fontx, fonty, box, colour, bg, bc, modelindex, fRotX, fRotY, fRotZ, fZoom, color1, color2, select);
				Iter_Add(gTDs<id>, _:t);
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
			Iter_Add(gPlayerTDs[playerid]<id>, _:t);
		} else {
			new Text:t = TDC_ShowGlobal(x2, y, text[start], font, 1, 9999.0, 9999.0, shadow, outline, prop, fontx, fonty, box, colour, bg, bc, modelindex, fRotX, fRotY, fRotZ, fZoom, color1, color2, select);
			Iter_Add(gTDs<id>, _:t);
		}
	}
	if (box) {
		
	} else {
		
	}
}

static stock bool:TDC_ValidGlobal(Text:id) {
	return (Text:0 <= id < Text:MAX_TEXT_DRAWS && gTDs[id]);
}

static stock bool:TDC_ValidPlayer(playerid, PlayerText:id) {
	return (PlayerText:0 <= id < PlayerText:MAX_TEXT_DRAWS && gPlayerTDs[playerid][id]);
}

static stock gTempString[8192];

static stock TDC_UpdateGlobal(id) {
	static style[e_TDC_ENUM];
	MEM_UM_get_arr(gTDs[id], 0, style, e_TDC_ENUM);
	if (style[e_TDC_FLAGS] & 4) {
		foreach (new t : gTDs<id>) {
			TextDrawDestroy(Text:t);
		}
		Iter_Clear(gTDs<id>);
		TDC_Render(INVALID_PLAYER_ID, id,
				style[e_TDC_X],         style[e_TDC_Y],        gTempString,            style[e_TDC_FONT],
				style[e_TDC_ALIGNMENT], style[e_TDC_WIDTH],    style[e_TDC_HEIGHT],    style[e_TDC_SHADOW],
				style[e_TDC_OUTLINE],   style[e_TDC_PROP],     style[e_TDC_FONTX],     style[e_TDC_FONTY],
				style[e_TDC_BOX],       style[e_TDC_COLOUR],   style[e_TDC_BG],        style[e_TDC_BC],
				style[e_TDC_MODEL],     style[e_TDC_ROT_X],    style[e_TDC_ROT_Y],     style[e_TDC_ROT_Z],
				style[e_TDC_ZOOM],      style[e_TDC_COLOUR_1], style[e_TDC_COLOUR_2],  style[e_TDC_SELECTABLE]);
		foreach (new t : gTDs<id>) {
			foreach (new playerid : Bits(gPlayers[id])) {
				TextDrawShowForPlayer(playerid, Text:t);
			}
		}
	}
}

static stock TDC_UpdatePlayer(playerid, id) {
	static style[e_TDC_ENUM];
	MEM_UM_get_arr(gPlayerTDs[playerid][id], 0, style, e_TDC_ENUM);
	if (!(style[e_TDC_FLAGS] & 8)) {
		return;
	}
	new UnmanagedPointer:p = style[e_TDC_TDS];
	for (new i = 0, j = style[e_TDC_TDS_COUNT]; i != j; ++i) {
		PlayerTextDrawDestroy(playerid, PlayerText:MEM_UM_get_val(p, i));
	}
	MEM_UM_delete(p);
	new len = min(style[e_TDC_TEXT_LEN], sizeof (gTempString) - 1);
	MEM_UM_get_arr(style[e_TDC_TEXT], 0, gTempString, len);
	gTempString[len] = '\0';
	MEM_UM_delete(style[e_TDC_TDS]);
	TDC_Render(playerid, id,
			style[e_TDC_X],         style[e_TDC_Y],        gTempString,            style[e_TDC_FONT],
			style[e_TDC_ALIGNMENT], style[e_TDC_WIDTH],    style[e_TDC_HEIGHT],    style[e_TDC_SHADOW],
			style[e_TDC_OUTLINE],   style[e_TDC_PROP],     style[e_TDC_FONTX],     style[e_TDC_FONTY],
			style[e_TDC_BOX],       style[e_TDC_COLOUR],   style[e_TDC_BG],        style[e_TDC_BC],
			style[e_TDC_MODEL],     style[e_TDC_ROT_X],    style[e_TDC_ROT_Y],     style[e_TDC_ROT_Z],
			style[e_TDC_ZOOM],      style[e_TDC_COLOUR_1], style[e_TDC_COLOUR_2],  style[e_TDC_SELECTABLE]);
	//for (new i = 0, j = MEM_UM_get_val(gPlayerTDs[playerid][id], e_TDC_TDS_COUNT), p = MEM_UM_get_val(gPlayerTDs[playerid][id], e_TDC_TDS); i != j; ++i) {
	//	PlayerTextDrawShow(playerid, PlayerText:MEM_UM_get_val(UnmanagedPointer:p, i));
	//}
}

stock Text:TDC_TextDrawCreate(Float:x, Float:y, text[]) {
	static style[e_TDC_ENUM] = { 1, 0.0, 0.0, MEM_NULLUMPTR, 0, 0, 1, 640.0, 480.0, 2, 0, true, 0.48, 1.15, false, false, 0xE1E1E1FF, 0x000000FF, 0x000000FF, 0.0, 0.0, 0.0, 1.0, 0, -1, -1, MEM_NULLUMPTR, 0 };
	for (new id = 0; id < MAX_TEXT_DRAWS; ++id) {
		if (!(MEM_UM_get_val(gTDs[id], e_TDC_FLAGS) & 1)) {
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
			MEM_UM_set_val(gTDs[id], e_TDC_TEXT, mem);
			MEM_UM_set_val(gTDs[id], e_TDC_TEXT_LEN, len);
			MEM_UM_set_val(gTDs[id], e_TDC_X, x);
			MEM_UM_set_val(gTDs[id], e_TDC_Y, y);
			return Text:id;
		}
	}
	return Text:INVALID_TEXT_DRAW;
}

stock TDC_TextDrawDestroy(Text:text) {
	if (TDC_ValidGlobal(text)) {
		TDC_TextDrawHideForAll(text);
		MEM_UM_set_val(gTDs[_:text], e_TDC_FLAGS, 0);
		free(MEM_UM_get_val(gTDs[_:text], e_TDC_TEXT));
	}
}

stock TDC_TextDrawLetterSize(Text:text, Float:x, Float:y) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_FONTX, x);
		MEM_UM_set_val(gTDs[_:text], e_TDC_FONTY, y);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawTextSize(Text:text, Float:x, Float:y) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_WIDTH, x);
		MEM_UM_set_val(gTDs[_:text], e_TDC_HEIGHT, y);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawAlignment(Text:text, alignment) {
	/* 1 = left, 2 = centre, 3 = right, 4 = fixed right, 5 = justify */
	if (TDC_ValidGlobal(text) && 1 <= alignment <= 5) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_ALIGNMENT, alignment);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawColor(Text:text, color) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_COLOUR, color);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawUseBox(Text:text, use) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_BOX, !!use);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawBoxColor(Text:text, color) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_BC, color);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetShadow(Text:text, size) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_SHADOW, size);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetOutline(Text:text, size) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_OUTLINE, size);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawBackgroundColor(Text:text, color) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_BG, color);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawFont(Text:text, font) {
	if (TDC_ValidGlobal(text) && 0 <= font <= 5) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_FONT, font);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetProportional(Text:text, set) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_PROP, !!set);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetSelectable(Text:text, set) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_SELECTABLE, !!set);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPos(Text:text, Float:x, Float:y) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_X, x);
		MEM_UM_set_val(gTDs[_:text], e_TDC_Y, y);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawShowForPlayer(playerid, Text:text) {
	if (TDC_ValidGlobal(text) && IsPlayerConnected(playerid) && !Bit_Get(gPlayers[_:text], playerid)) {
		Bit_Let(gPlayers[_:text], playerid);
		if (MEM_UM_get_val(gTDs[_:text], e_TDC_FLAGS) & 4) {
			foreach (new t : gTDs<(_:text)>) {
				TextDrawShowForPlayer(playerid, Text:t);
			}
		} else {
			MEM_UM_get_val(gTDs[_:text], e_TDC_FLAGS) |= 4;
			TDC_UpdateGlobal(_:text);
		}
	}
}

stock TDC_TextDrawHideForPlayer(playerid, Text:text) {
	if (TDC_ValidGlobal(text) && Bit_Get(gPlayers[_:text], playerid)) {
		Bit_Vet(gPlayers[_:text], playerid);
		if (Bit_GetCount(gPlayers[_:text] == 0)) {
			MEM_UM_get_val(gTDs[_:text], e_TDC_FLAGS) &= ~4;
			foreach (new t : gTDs<(_:text)>) {
				TextDrawDestroy(Text:t);
			}
			Iter_Clear(gTDs<(_:text)>);
		} else {
			foreach (new t : gTDs<(_:text)>) {
				TextDrawHideForPlayer(playerid, Text:t);
			}
		}
	}
}

stock TDC_TextDrawShowForAll(Text:text) {
	if (TDC_ValidGlobal(text) && Iter_Count(Player)) {
		MEM_UM_get_val(gTDs[_:text], e_TDC_FLAGS) |= 4;
		Bit_SetAll(gPlayers[text], true);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawHideForAll(Text:text) {
	if (TDC_ValidGlobal(text)) {
		MEM_UM_get_val(gTDs[_:text], e_TDC_FLAGS) &= ~4;
		foreach (new t : gTDs<(_:text)>) {
			TextDrawDestroy(Text:t);
		}
		Bit_SetAll(gPlayers[text], false);
		Iter_Clear(gTDs<_:text>);
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
		free(MEM_UM_get_val(gTDs[_:text], e_TDC_TEXT));
		MEM_UM_set_val(gTDs[_:text], e_TDC_TEXT, mem);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPreviewModel(Text:text, modelindex) {
	if (TDC_ValidGlobal(text) && MEM_UM_get_val(gTDs[_:text], e_TDC_FONT) == 5) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_MODEL, modelindex);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPreviewRot(Text:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0) {
	if (TDC_ValidGlobal(text) && MEM_UM_get_val(gTDs[_:text], e_TDC_FONT) == 5) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_ROT_X, fRotX);
		MEM_UM_set_val(gTDs[_:text], e_TDC_ROT_Y, fRotY);
		MEM_UM_set_val(gTDs[_:text], e_TDC_ROT_Z, fRotZ);
		MEM_UM_set_val(gTDs[_:text], e_TDC_ZOOM, fZoom);
		TDC_UpdateGlobal(_:text);
	}
}

stock TDC_TextDrawSetPreviewVehCol(Text:text, color1, color2) {
	if (TDC_ValidGlobal(text) && MEM_UM_get_val(gTDs[_:text], e_TDC_FONT) == 5) {
		MEM_UM_set_val(gTDs[_:text], e_TDC_COLOUR_1, color1);
		MEM_UM_set_val(gTDs[_:text], e_TDC_COLOUR_2, color2);
		TDC_UpdateGlobal(_:text);
	}
}

stock bool:TDC_TextDrawGetLetterSize(Text:text, &Float:x, &Float:y) {
	if (TDC_ValidGlobal(text)) {
		x = MEM_UM_get_val(gTDs[_:text], e_TDC_FONTX);
		y = MEM_UM_get_val(gTDs[_:text], e_TDC_FONTY);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetTextSize(Text:text, &Float:x, &Float:y) {
	if (TDC_ValidGlobal(text)) {
		x = MEM_UM_get_val(gTDs[_:text], e_TDC_WIDTH);
		y = MEM_UM_get_val(gTDs[_:text], e_TDC_HEIGHT);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetAlignment(Text:text, &alignment) {
	if (TDC_ValidGlobal(text)) {
		alignment = MEM_UM_get_val(gTDs[_:text], e_TDC_ALIGNMENT);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetColor(Text:text, &color) {
	if (TDC_ValidGlobal(text)) {
		color = MEM_UM_get_val(gTDs[_:text], e_TDC_COLOUR);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetUseBox(Text:text, &bool:use) {
	if (TDC_ValidGlobal(text)) {
		use = MEM_UM_get_val(gTDs[_:text], e_TDC_BOX);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetBoxColor(Text:text, &color) {
	if (TDC_ValidGlobal(text)) {
		color = MEM_UM_get_val(gTDs[_:text], e_TDC_BC);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetShadow(Text:text, &size) {
	if (TDC_ValidGlobal(text)) {
		size = MEM_UM_get_val(gTDs[_:text], e_TDC_SHADOW);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetOutline(Text:text, &size) {
	if (TDC_ValidGlobal(text)) {
		size = MEM_UM_get_val(gTDs[_:text], e_TDC_OUTLINE);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetBackgroundColor(Text:text, &color) {
	if (TDC_ValidGlobal(text)) {
		color = MEM_UM_get_val(gTDs[_:text], e_TDC_BG);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetFont(Text:text, &font) {
	if (TDC_ValidGlobal(text)) {
		font = MEM_UM_get_val(gTDs[_:text], e_TDC_FONT);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetProportional(Text:text, &bool:set) {
	if (TDC_ValidGlobal(text)) {
		set = MEM_UM_get_val(gTDs[_:text], e_TDC_PROP);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetSelectable(Text:text, &bool:set) {
	if (TDC_ValidGlobal(text)) {
		set = MEM_UM_get_val(gTDs[_:text], e_TDC_SELECTABLE);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPos(Text:text, &Float:x, &Float:y) {
	if (TDC_ValidGlobal(text)) {
		x = MEM_UM_get_val(gTDs[_:text], e_TDC_X);
		y = MEM_UM_get_val(gTDs[_:text], e_TDC_Y);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetString(Text:text, string[], size = sizeof (string)) {
	if (TDC_ValidGlobal(text)) {
		string[0] = '\0';
		strcat(string, Malloc_FastString(MEM_UM_get_val(gTDs[_:text], e_TDC_TEXT)), size);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPreviewModel(Text:text, &modelindex) {
	if (TDC_ValidGlobal(text) && MEM_UM_get_val(gTDs[_:text], e_TDC_FONT) == 5) {
		modelindex = MEM_UM_get_val(gTDs[_:text], e_TDC_MODEL);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPreviewRot(Text:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom = 1.0) {
	if (TDC_ValidGlobal(text) && MEM_UM_get_val(gTDs[_:text], e_TDC_FONT) == 5) {
		fRotX = MEM_UM_get_val(gTDs[_:text], e_TDC_ROT_X);
		fRotY = MEM_UM_get_val(gTDs[_:text], e_TDC_ROT_Y);
		fRotZ = MEM_UM_get_val(gTDs[_:text], e_TDC_ROT_Z);
		fZoom = MEM_UM_get_val(gTDs[_:text], e_TDC_ZOOM);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_TextDrawGetPreviewVehCol(Text:text, &color1, &color2) {
	if (TDC_ValidGlobal(text) && MEM_UM_get_val(gTDs[_:text], e_TDC_FONT) == 5) {
		color1 = MEM_UM_get_val(gTDs[_:text], e_TDC_COLOUR_1);
		color2 = MEM_UM_get_val(gTDs[_:text], e_TDC_COLOUR_2);
		return true;
	} else {
		return false;
	}
}

stock PlayerText:TDC_PlayerTDCreate(playerid, Float:x, Float:y, text[]) {
	static style[e_TDC_ENUM] = { 1, 0.0, 0.0, MEM_NULLUMPTR, 0, 0, 1, 640.0, 480.0, 2, 0, true, 0.48, 1.15, false, false, 0xE1E1E1FF, 0x000000FF, 0x000000FF, 0.0, 0.0, 0.0, 1.0, 0, -1, -1, MEM_NULLUMPTR, 0 };
	for (new id = 0; id < MAX_TEXT_DRAWS; ++id) {
		//new slot = playerid * MAX_PLAYERS + id;
		if (!gPlayerTDs[playerid][id]) {
			new len = strlen(text);
			new slot = MEM_UM_new(e_TDC_ENUM);
			if (!slot) {
				return PlayerText:INVALID_TEXT_DRAW;
			}
			gPlayerTDs[playerid][id] = slot;
			new UnmanagedPointer:mem = MEM_UM_new(len + 1);
			if (mem == MEM_NULLUMPTR) {
				return;
			}
			if (len) {
				MEM_UM_set_arr(mem, e_TDC_ENUM, text, len + 1);
			} else {
				MEM_UM_set_arr(mem, e_TDC_ENUM, " ", 2);
			}
			MEM_UM_set_arr(slot, 0, style, e_TDC_ENUM);
			MEM_UM_set_val(slot, e_TDC_TEXT, mem);
			MEM_UM_set_val(slot, e_TDC_TEXT_LEN, len);
			MEM_UM_set_val(slot, e_TDC_X, x);
			MEM_UM_set_val(slot, e_TDC_Y, y);
			return PlayerText:id;
		}
	}
	return PlayerText:INVALID_TEXT_DRAW;
}

stock TDC_PlayerTDDestroy(playerid, PlayerText:text) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		TDC_PlayerTDHide(playerid, text);
		MEM_UM_delete(MEM_UM_get_val(slot, e_TDC_TEXT));
		MEM_UM_delete(slot);
	}
}

stock TDC_PlayerTDLetterSize(playerid, PlayerText:text, Float:x, Float:y) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		MEM_UM_set_val(slot, e_TDC_FONTX, x);
		MEM_UM_set_val(slot, e_TDC_FONTY, y);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDTextSize(playerid, PlayerText:text, Float:x, Float:y) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		MEM_UM_set_val(slot, e_TDC_WIDTH, x);
		MEM_UM_set_val(slot, e_TDC_HEIGHT, y);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDAlignment(playerid, PlayerText:text, alignment) {
	/* 1 = left, 2 = centre, 3 = right, 4 = fixed right, 5 = justify */
	if (TDC_ValidPlayer(playerid, text) && 1 <= alignment <= 5) {
		MEM_UM_set_val(gPlayerTDs[playerid][text], e_TDC_ALIGNMENT, alignment);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDColor(playerid, PlayerText:text, color) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_set_val(gPlayerTDs[playerid][text], e_TDC_COLOUR, color);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDUseBox(playerid, PlayerText:text, use) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_BOX) = !!use;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDBoxColor(playerid, PlayerText:text, color) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_set_val(gPlayerTDs[playerid][text], e_TDC_BC, color);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetShadow(playerid, PlayerText:text, size) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_set_val(gPlayerTDs[playerid][text], e_TDC_SHADOW, size);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetOutline(playerid, PlayerText:text, size) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_set_val(gPlayerTDs[playerid][text], e_TDC_OUTLINE, size);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDBackgroundColor(playerid, PlayerText:text, color) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_set_val(gPlayerTDs[playerid][text], e_TDC_BG, color);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDFont(playerid, PlayerText:text, font) {
	if (TDC_ValidPlayer(playerid, text) && 0 <= font <= 5) {
		MEM_UM_set_val(gPlayerTDs[playerid][text], e_TDC_FONT, font);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetProportional(playerid, PlayerText:text, set) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_PROP) = !!set;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetSelectable(playerid, PlayerText:text, set) {
	if (TDC_ValidPlayer(playerid, text)) {
		MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_SELECTABLE) = !!set;
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPos(playerid, PlayerText:text, Float:x, Float:y) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		MEM_UM_set_val(slot, e_TDC_X, x);
		MEM_UM_set_val(slot, e_TDC_Y, y);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDShow(playerid, PlayerText:text) {
	if (TDC_ValidPlayer(playerid, text) && IsPlayerConnected(playerid)) {
		new slot = gPlayerTDs[playerid][text];
		new flags = MEM_UM_get_val(slot, e_TDC_FLAGS);
		if (!(flags & 8)) {
			MEM_UM_set_val(slot, e_TDC_FLAGS, flags | 8);
			TDC_UpdatePlayer(playerid, _:text);
		}
	}
}

stock TDC_PlayerTDHide(playerid, PlayerText:text) {
	if (TDC_ValidPlayer(playerid, text) && IsPlayerConnected(playerid)) {
		new slot = gPlayerTDs[playerid][text];
		new flags = MEM_UM_get_val(slot, e_TDC_FLAGS);
		if (flags & 8) {
			MEM_UM_set_val(slot, e_TDC_FLAGS, flags & ~8);
			TDC_UpdatePlayer(playerid, _:text);
		}
		new UnmanagedPointer:p = UnmanagedPointer:MEM_UM_get_val(slot, e_TDC_TDS);
		for (new i = 0, j = MEM_UM_get_val(slot, e_TDC_TDS_COUNT); i != j; ++i) {
			PlayerTextDrawDestroy(playerid, PlayerText:MEM_UM_get_val(p, i));
		}
		MEM_UM_set_val(slot, e_TDC_TDS_COUNT, 0);
		MEM_UM_delete(p);
	}
}

stock TDC_PlayerTDSetString(playerid, PlayerText:text, string[]) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		new len = strlen(string);
		new UnmanagedPointer:mem = MEM_UM_new(len + 1);
		if (mem == MEM_NULLUMPTR) {
			return;
		}
		if (len) {
			MEM_UM_set_arr(mem, e_TDC_ENUM, text, len + 1);
		} else {
			MEM_UM_set_arr(mem, e_TDC_ENUM, " ", 2);
		}
		MEM_UM_delete(MEM_UM_get_val(slot, e_TDC_TEXT));
		MEM_UM_set_val(slot, e_TDC_TEXT, mem);
		MEM_UM_set_val(slot, e_TDC_TEXT_LEN, len);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPreviewModel(playerid, PlayerText:text, modelindex) {
	if (TDC_ValidPlayer(playerid, text))
		new slot = gPlayerTDs[playerid][text];
		if (MEM_UM_get_val(slot, e_TDC_FONT) != 5) {
			return;
		}
		MEM_UM_set_val(slot, e_TDC_MODEL, modelindex);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPreviewRot(playerid, PlayerText:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0) {
	if (TDC_ValidPlayer(playerid, text))
		new slot = gPlayerTDs[playerid][text];
		if (MEM_UM_get_val(slot, e_TDC_FONT) != 5) {
			return;
		}
		MEM_UM_set_val(slot, e_TDC_ROT_X, fRotX);
		MEM_UM_set_val(slot, e_TDC_ROT_Y, fRotY);
		MEM_UM_set_val(slot, e_TDC_ROT_Z, fRotZ);
		MEM_UM_set_val(slot, e_TDC_ZOOM, fZoom);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock TDC_PlayerTDSetPreviewVehCol(playerid, PlayerText:text, color1, color2) {
	if (TDC_ValidPlayer(playerid, text))
		new slot = gPlayerTDs[playerid][text];
		if (MEM_UM_get_val(slot, e_TDC_FONT) != 5) {
			return;
		}
		MEM_UM_set_val(slot, e_TDC_COLOUR_1, color1);
		MEM_UM_set_val(slot, e_TDC_COLOUR_2, color2);
		TDC_UpdatePlayer(playerid, _:text);
	}
}

stock bool:TDC_PlayerTDGetLetterSize(playerid, PlayerText:text, &Float:x, &Float:y) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		x = MEM_UM_get_val(slot, e_TDC_FONTX);
		y = MEM_UM_get_val(slot, e_TDC_FONTY);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetTextSize(playerid, PlayerText:text, &Float:x, &Float:y) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		x = MEM_UM_get_val(slot, e_TDC_WIDTH);
		y = MEM_UM_get_val(slot, e_TDC_HEIGHT);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetAlignment(playerid, PlayerText:text, &alignment) {
	if (TDC_ValidPlayer(playerid, text)) {
		alignment = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_ALIGNMENT);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetColor(playerid, PlayerText:text, &color) {
	if (TDC_ValidPlayer(playerid, text)) {
		color = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_COLOUR);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetUseBox(playerid, PlayerText:text, &bool:use) {
	if (TDC_ValidPlayer(playerid, text)) {
		use = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_BOX);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetBoxColor(playerid, PlayerText:text, &color) {
	if (TDC_ValidPlayer(playerid, text)) {
		color = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_BC);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetShadow(playerid, PlayerText:text, &size) {
	if (TDC_ValidPlayer(playerid, text)) {
		size = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_SHADOW);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetOutline(playerid, PlayerText:text, &size) {
	if (TDC_ValidPlayer(playerid, text)) {
		size = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_OUTLINE);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetBackgroundColor(playerid, PlayerText:text, &color) {
	if (TDC_ValidPlayer(playerid, text)) {
		color = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_BG);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetFont(playerid, PlayerText:text, &font) {
	if (TDC_ValidPlayer(playerid, text)) {
		font = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_FONT);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetProportional(playerid, PlayerText:text, &bool:set) {
	if (TDC_ValidPlayer(playerid, text)) {
		set = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_PROP);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetSelectable(playerid, PlayerText:text, &bool:set) {
	if (TDC_ValidPlayer(playerid, text)) {
		set = MEM_UM_get_val(gPlayerTDs[playerid][text], e_TDC_SELECTABLE);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPos(playerid, PlayerText:text, &Float:x, &Float:y) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		x = MEM_UM_get_val(slot, e_TDC_X);
		y = MEM_UM_get_val(slot, e_TDC_Y);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetString(playerid, PlayerText:text, string[], size = sizeof (string)) {
	if (TDC_ValidPlayer(playerid, text)) {
		new slot = gPlayerTDs[playerid][text];
		new len = min(MEM_UM_get_val(slot, e_TDC_TEXT_LEN), size - 1);
		MEM_UM_get_arr(UnmanagedPointer:MEM_UM_get_val(slot, e_TDC_TEXT), 0, string, len);
		string[len] = '\0';
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPreviewModel(playerid, PlayerText:text, &modelindex) {
	if (TDC_ValidPlayer(playerid, text))
		new slot = gPlayerTDs[playerid][text];
		if (MEM_UM_get_val(slot, e_TDC_FONT) != 5) {
			return;
		}
		modelindex = MEM_UM_get_val(slot, e_TDC_MODEL);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPreviewRot(playerid, PlayerText:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom = 1.0) {
	if (TDC_ValidPlayer(playerid, text))
		new slot = gPlayerTDs[playerid][text];
		if (MEM_UM_get_val(slot, e_TDC_FONT) != 5) {
			return;
		}
		fRotX = MEM_UM_get_val(slot, e_TDC_ROT_X);
		fRotY = MEM_UM_get_val(slot, e_TDC_ROT_Y);
		fRotZ = MEM_UM_get_val(slot, e_TDC_ROT_Z);
		fZoom = MEM_UM_get_val(slot, e_TDC_ZOOM);
		return true;
	} else {
		return false;
	}
}

stock bool:TDC_PlayerTDGetPreviewVehCol(playerid, PlayerText:text, &color1, &color2) {
	if (TDC_ValidPlayer(playerid, text))
		new slot = gPlayerTDs[playerid][text];
		if (MEM_UM_get_val(slot, e_TDC_FONT) != 5) {
			return;
		}
		color1 = MEM_UM_get_val(slot, e_TDC_COLOUR_1);
		color2 = MEM_UM_get_val(slot, e_TDC_COLOUR_2);
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

#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw TDC_PlayerTDCreate

#if defined _ALS_PlayerTextDrawDestroy
	#undef PlayerTextDrawDestroy
#else
	#define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy TDC_PlayerTDDestroy

#if defined _ALS_PlayerTextDrawLetterSize
	#undef PlayerTextDrawLetterSize
#else
	#define _ALS_PlayerTextDrawLetterSize
#endif
#define PlayerTextDrawLetterSize TDC_PlayerTDLetterSize

#if defined _ALS_PlayerTextDrawTextSize
	#undef PlayerTextDrawTextSize
#else
	#define _ALS_PlayerTextDrawTextSize
#endif
#define PlayerTextDrawTextSize TDC_PlayerTDTextSize

#if defined _ALS_PlayerTextDrawAlignment
	#undef PlayerTextDrawAlignment
#else
	#define _ALS_PlayerTextDrawAlignment
#endif
#define PlayerTextDrawAlignment TDC_PlayerTDAlignment

#if defined _ALS_PlayerTextDrawColor
	#undef PlayerTextDrawColor
#else
	#define _ALS_PlayerTextDrawColor
#endif
#define PlayerTextDrawColor TDC_PlayerTDColor

#if defined _ALS_PlayerTextDrawUseBox
	#undef PlayerTextDrawUseBox
#else
	#define _ALS_PlayerTextDrawUseBox
#endif
#define PlayerTextDrawUseBox TDC_PlayerTDUseBox

#if defined _ALS_PlayerTextDrawBoxColor
	#undef PlayerTextDrawBoxColor
#else
	#define _ALS_PlayerTextDrawBoxColor
#endif
#define PlayerTextDrawBoxColor TDC_PlayerTDBoxColor

#if defined _ALS_PlayerTextDrawSetShadow
	#undef PlayerTextDrawSetShadow
#else
	#define _ALS_PlayerTextDrawSetShadow
#endif
#define PlayerTextDrawSetShadow TDC_PlayerTDSetShadow

#if defined _ALS_PlayerTextDrawSetOutline
	#undef PlayerTextDrawSetOutline
#else
	#define _ALS_PlayerTextDrawSetOutline
#endif
#define PlayerTextDrawSetOutline TDC_PlayerTDSetOutline

#if defined _ALS_PlayerTDBackgroundColor
	#undef PlayerTextDrawBackgroundColor
#else
	#define _ALS_PlayerTDBackgroundColor
#endif
#define PlayerTextDrawBackgroundColor TDC_PlayerTDBackgroundColor

#if defined _ALS_PlayerTextDrawFont
	#undef PlayerTextDrawFont
#else
	#define _ALS_PlayerTextDrawFont
#endif
#define PlayerTextDrawFont TDC_PlayerTDFont

#if defined _ALS_PlayerTDSetProportional
	#undef PlayerTextDrawSetProportional
#else
	#define _ALS_PlayerTDSetProportional
#endif
#define PlayerTextDrawSetProportional TDC_PlayerTDSetProportional

#if defined _ALS_PlayerTDSetSelectable
	#undef PlayerTextDrawSetSelectable
#else
	#define _ALS_PlayerTDSetSelectable
#endif
#define PlayerTextDrawSetSelectable TDC_PlayerTDSetSelectable

#if defined _ALS_PlayerTextDrawSetPos
	#undef PlayerTextDrawSetPos
#else
	#define _ALS_PlayerTextDrawSetPos
#endif
#define PlayerTextDrawSetPos TDC_PlayerTDSetPos

#if defined _ALS_PlayerTextDrawShow
	#undef PlayerTextDrawShow
#else
	#define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow TDC_PlayerTDShow

#if defined _ALS_PlayerTextDrawHide
	#undef PlayerTextDrawHide
#else
	#define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide TDC_PlayerTDHide

#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString TDC_PlayerTDSetString

#if defined _ALS_PlayerTDSetPreviewModel
	#undef PlayerTextDrawSetPreviewModel
#else
	#define _ALS_PlayerTDSetPreviewModel
#endif
#define PlayerTextDrawSetPreviewModel TDC_PlayerTDSetPreviewModel

#if defined _ALS_PlayerTDSetPreviewRot
	#undef PlayerTextDrawSetPreviewRot
#else
	#define _ALS_PlayerTDSetPreviewRot
#endif
#define PlayerTextDrawSetPreviewRot TDC_PlayerTDSetPreviewRot

#if defined _ALS_PlayerTDSetPreviewVehCol
	#undef PlayerTextDrawSetPreviewVehCol
#else
	#define _ALS_PlayerTDSetPreviewVehCol
#endif
#define PlayerTextDrawSetPreviewVehCol TDC_PlayerTDSetPreviewVehCol

#if defined _ALS_PlayerTDGetLetterSize
	#undef PlayerTextDrawGetLetterSize
#else
	#define _ALS_PlayerTDGetLetterSize
#endif
#define PlayerTextDrawGetLetterSize TDC_PlayerTDGetLetterSize

#if defined _ALS_PlayerTextDrawGetTextSize
	#undef PlayerTextDrawGetTextSize
#else
	#define _ALS_PlayerTextDrawGetTextSize
#endif
#define PlayerTextDrawGetTextSize TDC_PlayerTDGetTextSize

#if defined _ALS_PlayerTextDrawGetAlignment
	#undef PlayerTextDrawGetAlignment
#else
	#define _ALS_PlayerTextDrawGetAlignment
#endif
#define PlayerTextDrawGetAlignment TDC_PlayerTDGetAlignment

#if defined _ALS_PlayerTextDrawGetColor
	#undef PlayerTextDrawGetColor
#else
	#define _ALS_PlayerTextDrawGetColor
#endif
#define PlayerTextDrawGetColor TDC_PlayerTDGetColor

#if defined _ALS_PlayerTextDrawGetUseBox
	#undef PlayerTextDrawGetUseBox
#else
	#define _ALS_PlayerTextDrawGetUseBox
#endif
#define PlayerTextDrawGetUseBox TDC_PlayerTDGetUseBox

#if defined _ALS_PlayerTextDrawGetBoxColor
	#undef PlayerTextDrawGetBoxColor
#else
	#define _ALS_PlayerTextDrawGetBoxColor
#endif
#define PlayerTextDrawGetBoxColor TDC_PlayerTDGetBoxColor

#if defined _ALS_PlayerTextDrawGetShadow
	#undef PlayerTextDrawGetShadow
#else
	#define _ALS_PlayerTextDrawGetShadow
#endif
#define PlayerTextDrawGetShadow TDC_PlayerTDGetShadow

#if defined _ALS_PlayerTextDrawGetOutline
	#undef PlayerTextDrawGetOutline
#else
	#define _ALS_PlayerTextDrawGetOutline
#endif
#define PlayerTextDrawGetOutline TDC_PlayerTDGetOutline

#if defined _ALS_PlayerTDGetBackgroundColor
	#undef PlayerTDGetBackgroundColor
#else
	#define _ALS_PlayerTDGetBackgroundColor
#endif
#define PlayerTDGetBackgroundColor TDC_PlayerTDGetBackgroundColor

#if defined _ALS_PlayerTextDrawGetFont
	#undef PlayerTextDrawGetFont
#else
	#define _ALS_PlayerTextDrawGetFont
#endif
#define PlayerTextDrawGetFont TDC_PlayerTDGetFont

#if defined _ALS_PlayerTDGetProportional
	#undef PlayerTextDrawGetProportional
#else
	#define _ALS_PlayerTDGetProportional
#endif
#define PlayerTextDrawGetProportional TDC_PlayerTDGetProportional

#if defined _ALS_PlayerTDGetSelectable
	#undef PlayerTextDrawGetSelectable
#else
	#define _ALS_PlayerTDGetSelectable
#endif
#define PlayerTextDrawGetSelectable TDC_PlayerTDGetSelectable

#if defined _ALS_PlayerTextDrawGetPos
	#undef PlayerTextDrawGetPos
#else
	#define _ALS_PlayerTextDrawGetPos
#endif
#define PlayerTextDrawGetPos TDC_PlayerTDGetPos

#if defined _ALS_PlayerTextDrawGetString
	#undef PlayerTextDrawGetString
#else
	#define _ALS_PlayerTextDrawGetString
#endif
#define PlayerTextDrawGetString TDC_PlayerTDGetString

#if defined _ALS_PlayerTDGetPreviewModel
	#undef PlayerTextDrawGetPreviewModel
#else
	#define _ALS_PlayerTDGetPreviewModel
#endif
#define PlayerTextDrawGetPreviewModel TDC_PlayerTDGetPreviewModel

#if defined _ALS_PlayerTDGetPreviewRot
	#undef PlayerTextDrawGetPreviewRot
#else
	#define _ALS_PlayerTDGetPreviewRot
#endif
#define PlayerTextDrawGetPreviewRot TDC_PlayerTDGetPreviewRot

#if defined _ALS_PlayerTDGetPreviewVehCol
	#undef PlayerTextDrawGetPreviewVehCol
#else
	#define _ALS_PlayerTDGetPreviewVehCol
#endif
#define PlayerTextDrawGetPreviewVehCol TDC_PlayerTDGetPreviewVehCol

/*
native Text:TextDrawCreate(Float:x, Float:y, text[]);
native TextDrawDestroy(Text:text);
native TextDrawLetterSize(Text:text, Float:x, Float:y);
native TextDrawTextSize(Text:text, Float:x, Float:y);
native TextDrawAlignment(Text:text, alignment);
native TextDrawColor(Text:text, color);
native TextDrawUseBox(Text:text, use);
native TextDrawBoxColor(Text:text, color);
native TextDrawSetShadow(Text:text, size);
native TextDrawSetOutline(Text:text, size);
native TextDrawBackgroundColor(Text:text, color);
native TextDrawFont(Text:text, font);
native TextDrawSetProportional(Text:text, set);
native TextDrawSetSelectable(Text:text, set);
native TextDrawSetPos(Text:text, Float:x, Float:y);
native TextDrawShowForPlayer(playerid, Text:text);
native TextDrawHideForPlayer(playerid, Text:text);
native TextDrawShowForAll(Text:text);
native TextDrawHideForAll(Text:text);
native TextDrawSetString(Text:text, string[]);
native TextDrawSetPreviewModel(Text:text, modelindex);
native TextDrawSetPreviewRot(Text:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0);
native TextDrawSetPreviewVehCol(Text:text, color1, color2);
native bool:TextDrawGetLetterSize(Text:text, &Float:x, &Float:y);
native bool:TextDrawGetTextSize(Text:text, &Float:x, &Float:y);
native bool:TextDrawGetAlignment(Text:text, &alignment);
native bool:TextDrawGetColor(Text:text, &color);
native bool:TextDrawGetUseBox(Text:text, &bool:use);
native bool:TextDrawGetBoxColor(Text:text, &color);
native bool:TextDrawGetShadow(Text:text, &size);
native bool:TextDrawGetOutline(Text:text, &size);
native bool:TextDrawGetBackgroundColor(Text:text, &color);
native bool:TextDrawGetFont(Text:text, &font);
native bool:TextDrawGetProportional(Text:text, &bool:set);
native bool:TextDrawGetSelectable(Text:text, &bool:set);
native bool:TextDrawGetPos(Text:text, &Float:x, &Float:y);
native bool:TextDrawGetString(Text:text, string[], size = sizeof (string));
native bool:TextDrawGetPreviewModel(Text:text, &modelindex);
native bool:TextDrawGetPreviewRot(Text:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom = 1.0);
native bool:TextDrawGetPreviewVehCol(Text:text, &color1, &color2);
native PlayerText:CreatePlayerTextDraw(playerid, Float:x, Float:y, text[]);
native PlayerTextDrawDestroy(playerid, PlayerText:text);
native PlayerTextDrawLetterSize(playerid, PlayerText:text, Float:x, Float:y);
native PlayerTextDrawTextSize(playerid, PlayerText:text, Float:x, Float:y);
native PlayerTextDrawAlignment(playerid, PlayerText:text, alignment);
native PlayerTextDrawColor(playerid, PlayerText:text, color);
native PlayerTextDrawUseBox(playerid, PlayerText:text, use);
native PlayerTextDrawBoxColor(playerid, PlayerText:text, color);
native PlayerTextDrawSetShadow(playerid, PlayerText:text, size);
native PlayerTextDrawSetOutline(playerid, PlayerText:text, size);
native PlayerTextDrawBackgroundColor(playerid, PlayerText:text, color);
native PlayerTextDrawFont(playerid, PlayerText:text, font);
native PlayerTextDrawSetProportional(playerid, PlayerText:text, set);
native PlayerTextDrawSetSelectable(playerid, PlayerText:text, set);
native PlayerTextDrawSetPos(playerid, PlayerText:text, Float:x, Float:y);
native PlayerTextDrawShow(playerid, PlayerText:text);
native PlayerTextDrawHide(playerid, PlayerText:text);
native PlayerTextDrawSetString(playerid, PlayerText:text, string[]);
native PlayerTextDrawSetPreviewModel(playerid, PlayerText:text, modelindex);
native PlayerTextDrawSetPreviewRot(playerid, PlayerText:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0);
native PlayerTextDrawSetPreviewVehCol(playerid, PlayerText:text, color1, color2);
native bool:PlayerTextDrawGetLetterSize(playerid, PlayerText:text, &Float:x, &Float:y);
native bool:PlayerTextDrawGetTextSize(playerid, PlayerText:text, &Float:x, &Float:y);
native bool:PlayerTextDrawGetAlignment(playerid, PlayerText:text, &alignment);
native bool:PlayerTextDrawGetColor(playerid, PlayerText:text, &color);
native bool:PlayerTextDrawGetUseBox(playerid, PlayerText:text, &bool:use);
native bool:PlayerTextDrawGetBoxColor(playerid, PlayerText:text, &color);
native bool:PlayerTextDrawGetShadow(playerid, PlayerText:text, &size);
native bool:PlayerTextDrawGetOutline(playerid, PlayerText:text, &size);
native bool:PlayerTDGetBackgroundColor(playerid, PlayerText:text, &color);
native bool:PlayerTextDrawGetFont(playerid, PlayerText:text, &font);
native bool:PlayerTextDrawGetProportional(playerid, PlayerText:text, &bool:set);
native bool:PlayerTextDrawGetSelectable(playerid, PlayerText:text, &bool:set);
native bool:PlayerTextDrawGetPos(playerid, PlayerText:text, &Float:x, &Float:y);
native bool:PlayerTextDrawGetString(playerid, PlayerText:text, string[], size = sizeof (string));
native bool:PlayerTextDrawGetPreviewModel(playerid, PlayerText:text, &modelindex);
native bool:PlayerTextDrawGetPreviewRot(playerid, PlayerText:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom = 1.0);
native bool:PlayerTextDrawGetPreviewVehCol(playerid, PlayerText:text, &color1, &color2);
*/

