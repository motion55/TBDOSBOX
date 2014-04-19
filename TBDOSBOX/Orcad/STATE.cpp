/* ********************************************************************** */
/*                                                                        */
/*   STATE.C                                                              */
/*                                                                        */
/* ********************************************************************** */

/* -- HEADER FILES ------------------------------------------------------ */

#include "stdafx.h"
#include "OrcadWnd.h"

/* -- PUBLIC DATA DEFINITIONS ------------------------------------------- */

unsigned char MapMaskMap[16] = {
	0, 1, 2, 3, 4, 5, 6, 8, 7, 9, 10, 11, 12, 13, 14, 15
};
struct WindowState WindowStateStack[8];

COLORREF RGBPalette[16] = {
	RGB(0x00, 0x00, 0x00),		/* black */
	RGB(0x00, 0x00, 0xa8),		/* blue */
	RGB(0x00, 0xa8, 0x00),		/* green */
	RGB(0x00, 0xa8, 0xa8),		/* cyan */
	RGB(0xa8, 0x00, 0x00),		/* red */
	RGB(0xa8, 0x00, 0xa8),		/* magenta */
	RGB(0xa8, 0x54, 0x00),		/* brown */
	RGB(0xa8, 0xa8, 0xa8),		/* light gray */
	RGB(0x54, 0x54, 0x54),		/* dark gray */
	RGB(0x54, 0x54, 0xfc),		/* light blue */
	RGB(0x54, 0xfc, 0x54),		/* light green */
	RGB(0x54, 0xfc, 0xfc),		/* light cyan */
	RGB(0xfc, 0x54, 0x54),		/* light red */
	RGB(0xfc, 0x54, 0xfc),		/* light magenta */
	RGB(0xfc, 0xfc, 0x54),		/* yellow */
	RGB(0xfc, 0xfc, 0xfc)		/* white */
};

/* -- PRIVATE DATA DEFINITIONS ------------------------------------------ */

/* -- CODE -------------------------------------------------------------- */

/* ====================================================================== */
/*                                                                        */
/*   GetScreenResolution                                                  */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::GetScreenResolution(unsigned short *const maxX,
	unsigned short *const maxY)
{
	*maxX = ResolutionX - 1;
	*maxY = ResolutionY - 1;
}

/* ====================================================================== */
/*                                                                        */
/*   GetColor                                                             */
/*                                                                        */
/* ====================================================================== */

/* verified */
unsigned char COrcadWnd::GetColor()
{
	if (CharSetSpecial == true) {
		CharSetSpecial = false;
		return -1;
	} else {
		return Color;
	}
}

/* ====================================================================== */
/*                                                                        */
/*   SetColor                                                             */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetColor(unsigned char index)
{
	if (index < 16) {
		Color = Palette[index];
		MapMask = MapMaskMap[Color];

		if (hPen != NULL) {
			DeleteObject(hPen);
		}

		hPen = CreatePen(PS_SOLID, 0, RGBPalette[MapMask]);
		SelectObject(hdcMemoryBuffer, hPen);
		SelectObject(hdcWindow, hPen);
	} else {
		CharSetSpecial = true;
	}
}

/* ====================================================================== */
/*                                                                        */
/*   GetScale                                                             */
/*                                                                        */
/* ====================================================================== */

/* verified */
unsigned short COrcadWnd::GetScale()
{
	return Scale;
}

/* ====================================================================== */
/*                                                                        */
/*   SetScale                                                             */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetScale(unsigned short scale)
{
	if ((Zoom==2)&&(scale>1))
	{
		Zoom = 1;
		Redraw();
	}
	Scale = scale;
}

/* ====================================================================== */
/*                                                                        */
/*   SetWindow                                                            */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetWindow(short minX, short minY, short maxX, short maxY)
{
	WindowStartX = minX;
	WindowStartY = minY;
	WindowEndX = maxX;
	WindowEndY = maxY;
}

/* ====================================================================== */
/*                                                                        */
/*   SetWindowOrigin                                                      */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetWindowOrigin(unsigned short originX, unsigned short originY)
{
	WindowOriginX = originX;
	WindowOriginY = originY;
}

/* ====================================================================== */
/*                                                                        */
/*   SaveWindowState                                                      */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SaveWindowState()
{
	int tos = TopOfWindowStateStack;

	if (tos > 7) {
		return;
	}

	WindowStateStack[tos].Color = Color;
	WindowStateStack[tos].Scale = Scale;
	WindowStateStack[tos].DrawingPositionX = DrawingPositionX;
	WindowStateStack[tos].DrawingPositionY = DrawingPositionY;
	WindowStateStack[tos].WindowStartX = WindowStartX;
	WindowStateStack[tos].WindowStartY = WindowStartY;
	WindowStateStack[tos].WindowEndX = WindowEndX;
	WindowStateStack[tos].WindowEndY = WindowEndY;
	WindowStateStack[tos].WindowOriginX = WindowOriginX;
	WindowStateStack[tos].WindowOriginY = WindowOriginY;

	TopOfWindowStateStack++;
}

/* ====================================================================== */
/*                                                                        */
/*   RestoreWindowState                                                   */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::RestoreWindowState()
{
	int tos = TopOfWindowStateStack;

	if (tos == 0) {
		return;
	}

	TopOfWindowStateStack--;
	tos--;

	Color = WindowStateStack[tos].Color;
	Scale = WindowStateStack[tos].Scale;
	DrawingPositionX = WindowStateStack[tos].DrawingPositionX;
	DrawingPositionY = WindowStateStack[tos].DrawingPositionY;
	WindowStartX = WindowStateStack[tos].WindowStartX;
	WindowStartY = WindowStateStack[tos].WindowStartY;
	WindowEndX = WindowStateStack[tos].WindowEndX;
	WindowEndY = WindowStateStack[tos].WindowEndY;
	WindowOriginX = WindowStateStack[tos].WindowOriginX;
	WindowOriginY = WindowStateStack[tos].WindowOriginY;

	SetColor(Color);
}

/* ====================================================================== */
/*                                                                        */
/*   SetWindow32	                                                  */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetWindow32(long minX, long minY, long maxX, long maxY,
	unsigned long scale)
{
	WindowStartX32 = minX;
	WindowStartY32 = minY;
	WindowEndX32 = maxX;
	WindowEndY32 = maxY;
	Scale32 = scale;
	Scale32Div2 = scale / 2;
}

/* ====================================================================== */
/*                                                                        */
/*   MoveAbsolute                                                         */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::MoveAbsolute(short x, short y)
{
	DrawingPositionX = x;
	DrawingPositionY = y;
}

/* ====================================================================== */
/*                                                                        */
/*   MoveRelative                                                         */
/*                                                                        */
/* ====================================================================== */

/* verified */
void MoveRelative(short dx, short dy)
{
	DrawingPositionX += dx;
	DrawingPositionY += dy;
}

/* ====================================================================== */
/*                                                                        */
/*   SetModeHighlight                                                     */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetModeHighlight()
{
	int i;

	for (i = 1; i < 16; i++) {
		Palette[i] = 0x0f;
	}

	MapMask = MapMaskMap[15];
	Mode = XOR;

	if (hPen != NULL) {
		DeleteObject(hPen);
	}

	hPen = CreatePen(PS_SOLID, 0, RGBPalette[MapMask]);
	SelectObject(hdcMemoryBuffer, hPen);
	SetROP2(hdcMemoryBuffer, R2_XORPEN);
	SelectObject(hdcWindow, hPen);
	SetROP2(hdcWindow, R2_XORPEN);
}

/* ====================================================================== */
/*                                                                        */
/*   SetModeNormal                                                        */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetModeNormal()
{
	int i;

	for (i = 0; i < 16; i++) {
		Palette[i] = i;
	}

	Mode = OR;
	SetROP2(hdcMemoryBuffer, R2_MERGEPEN);
	SetROP2(hdcWindow, R2_MERGEPEN);
}

/* ====================================================================== */
/*                                                                        */
/*   SetModeXor                                                           */
/*                                                                        */
/* ====================================================================== */

/* verified */
void COrcadWnd::SetModeXor()
{
	int i;

	for (i = 0; i < 16; i++) {
		Palette[i] = i;
	}

	Mode = XOR;
	SetROP2(hdcMemoryBuffer, R2_XORPEN);
	SetROP2(hdcWindow, R2_XORPEN);
}

/* -- END --------------------------------------------------------------- */
