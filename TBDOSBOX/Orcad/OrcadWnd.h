#pragma once


// COrcadWnd

class COrcadWnd : public CWnd
{
	DECLARE_DYNAMIC(COrcadWnd)

public:
	COrcadWnd();
	virtual ~COrcadWnd();

	#define	PUTPIXEL(a, b)	SetPixel(hdcMemoryBuffer, a, b, RGBPalette[MapMask]);

	// Bitmap	////////////////////////////////////////////////

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void DrawBitmapRelative(const unsigned char *bitmap,
		unsigned short rows, unsigned short cols, short dx, short dy,
		unsigned short xsize, unsigned short ysize, unsigned char function);

	// Circle	////////////////////////////////////////////////

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void DrawArcAbsolute(short x, short y, short endxa,
		short endya, short endxb, short endyb, unsigned short radius,
		unsigned short thickness);
	void DrawWideArcAbsolute32(long xc, long yc, long xa, long ya,
		long xb, long yb, unsigned long radius, unsigned long thickness,
		const unsigned char fillMode);
	void DrawCircleAbsolute(short x, short y,
		unsigned short xsize, unsigned short ysize, unsigned char fillStyle);
	void DrawCircleRelative(short dx, short dy,
		unsigned short xsize, unsigned short ysize, unsigned char fill);
	void DrawCircleAbsolute32(long xc, long yc, long radius,
		unsigned char fillType);

	// Cursor	////////////////////////////////////////////////

	#define CURSOR_HSIZE	8
	#define CURSOR_VSIZE	15

	unsigned char CursorStyle;
	unsigned char CursorState;

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void InitCursor(void);
	void UnloadCursor(void);
	void SetCursorState(unsigned char state, short x, short y);
	unsigned char SetCursorStyle(unsigned char style);

	void ZoomScroll(void);

	//	Grid	////////////////////////////////////////////////

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void DrawGridDots(unsigned short spacing);
	void DrawGridDotsRelative(unsigned short spacing, unsigned short dx,
		unsigned short dy);

	// Line 	////////////////////////////////////////////////

	#define INSIDE	0
	#define LEFT	1
	#define RIGHT	2
	#define TOP 	4
	#define BOTTOM	8

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void DrawWideLineAbsolute(short xa, short ya, short xb, short yb);
	void DrawWideLineRelative(short dx, short dy);
	void DrawDashedLineAbsolute(short xa, short ya, short xb, short yb);
	void DrawDashedLineRelative(short dx, short dy);
	void DrawSolidLineAbsolute(short xa, short ya, short xb, short yb);
	void DrawSolidLineRelative(short dx, short dy);
	void DrawWideLineAbsolute32(long xa, long ya, long xb, long yb,
		long thickness, unsigned char fillType);
	void DrawLineFunction(short xa, short ya, short xb, short yb);

	// Rectangle	////////////////////////////////////////////////

	HDC hdcSavedRect;
	HBITMAP hbmSavedRect;

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void FillRectangle(short xa, short ya, short xb, short yb);
	void HighlightRectangle(short xa, short ya, short xb, short yb);
	void SaveRectangle(short xa, short ya, short xb, short yb);
	void RestoreRectangle(void);
	void CopyRectangle(short xa, short ya, short xb, short yb);

	// State	////////////////////////////////////////////////

	#define  ZOOM      2

	#define ZoomXY(x, y)	\
	{                   	\
	x = (x - ZoomScrollX) * ZOOM;	\
	y = (y - ZoomScrollY) * ZOOM;	\
	}

	struct WindowState {
		unsigned char Color;
		unsigned short Scale;
		unsigned short DrawingPositionX;
		unsigned short DrawingPositionY;
		unsigned short WindowStartX;
		unsigned short WindowStartY;
		unsigned short WindowEndX;
		unsigned short WindowEndY;
		unsigned short WindowOriginX;
		unsigned short WindowOriginY;
	};

	unsigned char Color;
	unsigned short Scale;
	unsigned short Zoom;
	unsigned short ZoomScrollX;
	unsigned short ZoomScrollY;
	unsigned short DrawingPositionX;
	unsigned short DrawingPositionY;
	short WindowStartX;
	short WindowStartY;
	short WindowEndX;
	short WindowEndY;
	unsigned short WindowOriginX;
	unsigned short WindowOriginY;
	long WindowStartX32;
	long WindowStartY32;
	long WindowEndX32;
	long WindowEndY32;
	unsigned long Scale32;
	unsigned long Scale32Div2;
	unsigned char Mode;
	bool CharSetSpecial;
	bool CharSetIEEE;
	unsigned char MapMask;
	int LineDrawingMode;
	int TopOfWindowStateStack;
	unsigned char Palette[16];
	unsigned char MapMaskMap[16];
	struct WindowState WindowStateStack[8];
	COLORREF RGBPalette[16];
	HPEN hPen;

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void GetScreenResolution(unsigned short *const maxX,
		unsigned short *const maxY);
	unsigned char GetColor(void);
	void SetColor(unsigned char index);
	unsigned short GetScale(void);
	void SetScale(unsigned short scale);
	void SetWindow(short minX, short minY, short maxX, short maxY);
	void SetWindowOrigin(unsigned short originX, unsigned short originY);
	void SaveWindowState(void);
	void RestoreWindowState(void);
	void SetWindow32(long minX, long minY, long maxX, long maxY,
		unsigned long scale);
	void MoveAbsolute(short x, short y);
	void MoveRelative(short dx, short dy);
	void SetModeHighlight(void);
	void SetModeNormal(void);
	void SetModeXor(void);

	// Text	////////////////////////////////////////////////

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	void PrintDriverInfo(void);
	void DrawFixedStringAbsolute(unsigned short length,
		const unsigned char *string, short x, short y);
	void DrawFixedStringRelative(unsigned short length,
		const unsigned char *string, short dx, short dy);
	void DrawVariableStringAbsolute(unsigned short length,
		const unsigned char *string, short x, short y, short scale);
	void DrawVariableStringRelative(unsigned short length,
		const unsigned char *string, short dx, short dy, short scale);
	void DrawFixedTextAbsolute(const unsigned char *text,
		short x, short y);
	void DrawFixedTextRelative(const unsigned char *text,
		short dx, short dy);
	void DrawVariableTextAbsolute(const unsigned char *text,
		short x, short y, short scale);
	void DrawVariableTextRelative(const unsigned char *text,
		short dx, short dy, short scale);

	HWND hWnd;
	HDC hdcWindow;
	HANDLE hmMemoryBuffer;
	HDC hdcMemoryBuffer;
	HDC hdcScaledBuffer;
	HANDLE hKeyMouseEvent;

	BOOL bDelayDraw;
	int RedrawTimer;

	/* -- PUBLIC DATA DEFINITIONS ------------------------------------------- */

	unsigned char CursorStyle = 0;
	unsigned char CursorState = 0;
	unsigned short CursorScreenX = 0;
	unsigned short CursorScreenY = 0;

	unsigned char Color;
	unsigned short Scale;
	unsigned short Zoom = 0;
	unsigned short ZoomScrollX = 0;
	unsigned short ZoomScrollY = 0;
	unsigned short DrawingPositionX;
	unsigned short DrawingPositionY;
	short WindowStartX;
	short WindowStartY;
	short WindowEndX;
	short WindowEndY;
	unsigned short WindowOriginX;
	unsigned short WindowOriginY;
	long WindowStartX32;
	long WindowStartY32;
	long WindowEndX32;
	long WindowEndY32;
	unsigned long Scale32;
	unsigned long Scale32Div2;
	unsigned char Mode;
	bool CharSetSpecial;
	bool CharSetIEEE;
	unsigned char MapMask;
	int LineDrawingMode;
	int TopOfWindowStateStack;
	unsigned char Palette[16];
	struct WindowState WindowStateStack[8];

	HPEN hPen = NULL;

	//	Video	////////////////////////////////////////////////

	#define Redraw()	{if (!RedrawTimer) RedrawTimer=10;}
	#define BeginDraw()	WaitForSingleObject(hmMemoryBuffer, INFINITE)
	#define EndDraw()	ReleaseMutex(hmMemoryBuffer)

	/* -- PUBLIC FUNCTION DECLARATIONS -------------------------------------- */

	bool InitVideo(unsigned short resX, unsigned short resY);
	void ShutdownVideo();
	void Translate(short *const x, short *const y);
	void PutPixel(short x, short y);

	void KeybrdServe(union REGPACK *pRegs);
	void MouseServe(union REGPACK *pRegs);
	void VideoInt10Serve(union REGPACK *pRegs);

	/* -- Used for multi-montor selection ----------------------------------- */

	HMONITOR hMonitor2Use;
	RECT rectMonitor;

	BOOL CALLBACK MonitorEnumProc(
		HMONITOR hMonitor,  // handle to display monitor
		HDC hdcMonitor,     // handle to monitor DC
		LPRECT lprcMonitor, // monitor intersection rectangle
		LPARAM dwData       // data
		);

protected:
	short clipxa, clipya, clipxb, clipyb;

	HDC    	hdcSavedCursor;
	HBITMAP	hbmSavedCursor;

	COLORREF CursorBackground[CURSOR_VSIZE][CURSOR_HSIZE];

	unsigned short CursorPositionX;
	unsigned short CursorPositionY;
	unsigned int CursorVisibleColumns = 0;
	unsigned int CursorVisibleRows = 0;

	HDC hdcSavedRect;
	HBITMAP hbmSavedRect;

	short RectangleStartX;
	short RectangleStartY;
	short RectangleEndX;
	short RectangleEndY;

	unsigned char TextBuffer[256];

	void ClpPixel(short x, short y);
	void Translate2(short *const x, short *const y);

	unsigned char GetQuadrant(long xc, long yc,
		long *const x, long *const y, long radius);
	void DrawArc(long xc, long yc, long xa, long ya, long xb, long yb,
		long radius, long thickness);
	void PutPixel32(long x, long y);
	void DrawCircleOctants(short dx, short dy, unsigned short distance,
		int type);
	void FillCircleOctants(short dx, short dy, unsigned short distance,
		int type);
	void DrawCirclePoint(short dx, short dy);
	void DrawCircleLine(short dx, short dy);

	void DrawCursor(unsigned short x, unsigned short y,
		unsigned int cols, unsigned int rows);
	void SaveCursorBackground(unsigned short x, unsigned short y,
		unsigned int cols, unsigned int rows);
	void RestoreCursorBackground(short x, short y,
		unsigned int cols, unsigned int rows);

	bool ClipLine(short *const xa, short *const ya,
		short *const xb, short *const yb);
	unsigned char GetOutcode(short x, short y);
	void DrawSolidLine(unsigned short xa, unsigned short ya,
		unsigned short xb, unsigned short yb);
	void DrawDashedLine(unsigned short xa, unsigned short ya,
		unsigned short xb, unsigned short yb);
	void DrawWideLine(short xa, short ya, short xb, short yb,
		short thickness, unsigned char fillType);
	void DrawGridDots32(long spacing, long divisor);

	int ClipRectangle(short *xa, short *ya, short *xb, short *yb);

	DECLARE_MESSAGE_MAP()
};


