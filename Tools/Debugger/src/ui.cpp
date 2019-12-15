#include "..\headers\debugger.h"
#include "..\headers\structs.h"

DWORD editorOffset;
extern AsmLine codeDisplay[150000];
extern DWORD currentParsedOffset;
extern int parsedLines;

int selectedLine = -1;

int displayOffset;

#define MAX_LOADSTRING 100
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

void Attach(HWND window);
HANDLE GetProcessByName(const wchar_t* processName, DWORD& outpid);
void ReadBytes(HANDLE fo2, HWND window, LPCVOID baseOffset, int bytes);
void LoadSymbols();

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND hWndVScrollBar;
RECT selectionRect;

int APIENTRY ui_init(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEBUGGER, szWindowClass, MAX_LOADSTRING);

    // Main window
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEBUGGER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEBUGGER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    hInst = hInstance; // Store instance handle in our global variable
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEBUGGER));
    MSG msg;

    // Main message loop
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

void Attach(HWND window) {

    DWORD pid;
    HANDLE fo2 = GetProcessByName(_T("Fallout2.exe"), pid);
    if (fo2 == 0) {
        return;
    }
    char buf[50];

    sprintf_s(buf, "Attached to Fallout2.exe - PID %d", pid);
    SetWindowTextA(window, buf);

    for (auto i = 0; i < 2000; i++) {

        if (parsedLines > 0) {
            // reparse 2 lines to avoid corruption.
            auto last = codeDisplay[parsedLines - 3];
            auto next = last.offset + last.bytes;
            parsedLines -= 2;
            ReadBytes(fo2, window, (LPCVOID)next, 500);
            
        }
        else {
            ReadBytes(fo2, window, (LPCVOID)editorOffset, 100);
        }
    }
    displayOffset = 0;
    LoadSymbols();
    for (auto i = 0; i < parsedLines; i++) {

    }

    InvalidateRect(window, 0, TRUE);

    //sprintf_s(out, "%x %x %x\n", buf[0] & 0xFF, buf[1] & 0xFF, buf[2] & 0xFF);
}

void DrawDivider(HDC hdc, int x) {
    HPEN hLinePen;
    COLORREF qLineColor;
    qLineColor = RGB(0, 255, 60);
    hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
    (HPEN)SelectObject(hdc, hLinePen);

    MoveToEx(hdc, x, 0, NULL);
    LineTo(hdc, x, 2000);
}

void ChangeDisplayOffset(HWND window, int amount) {
    displayOffset += amount;
    if (displayOffset < 0) {
        displayOffset = 0;
    }
    else {
        selectedLine -= amount;
    }
    InvalidateRect(window, 0, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        parsedLines = 0;
        editorOffset = 0x410013;
        displayOffset = 5;

        RECT Rect;
        GetClientRect(hWnd, &Rect);

        hWndVScrollBar = CreateWindowExA(
            0,
            "SCROLLBAR",
            NULL,
            WS_VISIBLE | WS_CHILD | SBS_VERT,
            Rect.right - 15,
            0,
            15,
            Rect.bottom - 15,
            hWnd,
            (HMENU)IDC_SCROLLBAR,
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
            NULL);

        Attach(hWnd);
        SetScrollRange(hWndVScrollBar, SB_CTL, 0, parsedLines / 8, TRUE);
        break;

    case WM_LBUTTONDOWN:
    {
        auto xPos = GET_X_LPARAM(lParam);
        auto yPos = GET_Y_LPARAM(lParam);

        selectedLine = yPos / 11;
        InvalidateRect(hWnd, 0, TRUE);
    }
    break;
    case WM_SIZE:
    {
        RECT Rect;
        GetClientRect(hWnd, &Rect);
        MoveWindow(hWndVScrollBar, Rect.right - 15, 0, 15, Rect.bottom, true);
    }
    break;
    case WM_VSCROLL:
    {

        switch ((int)LOWORD(wParam))
        {
            case SB_LINEUP:
                ChangeDisplayOffset(hWnd, -1);
                SetScrollPos((HWND)lParam, SB_CTL, displayOffset / 8, TRUE);
                break;
            case SB_LINEDOWN:
                ChangeDisplayOffset(hWnd, 1);
                SetScrollPos((HWND)lParam, SB_CTL, displayOffset / 8, TRUE);
                break;
            case SB_PAGEUP:
                ChangeDisplayOffset(hWnd, -1000);
                SetScrollPos((HWND)lParam, SB_CTL, displayOffset / 8, TRUE);
                break;
            case SB_PAGEDOWN:
                ChangeDisplayOffset(hWnd, 1000);
                SetScrollPos((HWND)lParam, SB_CTL, displayOffset / 8, TRUE);
                break;
            case SB_THUMBPOSITION:
                //SCROLLINFO si;
                //ZeroMemory(&si, sizeof(si));
                //si.cbSize = sizeof(si);
                //si.fMask = SIF_ALL;
                auto pos = HIWORD(wParam);

                // Call GetScrollInfo to get current tracking 
                //    position in si.nTrackPos

                //if (!GetScrollInfo(hWnd, SB_VERT, &si))
                //    return 1; // GetScrollInfo failed
                
                // before and after used to calculate
                // how to adjust selected line.
                auto before = displayOffset;
                auto after = pos;

                displayOffset = pos*8;

                if (selectedLine != -1) {
                    auto diff = after - before;
                    selectedLine += diff;
                }
                
                SetScrollPos((HWND)lParam, SB_CTL, pos, TRUE);
                InvalidateRect(hWnd, 0, TRUE);
                break;
        }
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_ATTACH:
            Attach(hWnd);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_MOUSEWHEEL:
    {
        auto delta = GET_WHEEL_DELTA_WPARAM(wParam);
        ChangeDisplayOffset(hWnd, delta < 0 ? 1 : -1);
    }
    break;

    case WM_KEYUP:
    {
        switch (wParam)
        {
            case VK_UP: ChangeDisplayOffset(hWnd, -1); break;
            case VK_DOWN: ChangeDisplayOffset(hWnd, 1); break;
        } 
    }
    break;
    // For doublebuffering
    case WM_ERASEBKGND:
        return 1;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        RECT rect;
        GetClientRect(hWnd, &rect);
        HDC hdc = GetDC(hWnd);
        int winHeight = rect.bottom - rect.top;
        int winWidth = rect.right - rect.left;

        // Double buffered drawing
        auto hdcMem = CreateCompatibleDC(hdc);
        auto bitmap = CreateCompatibleBitmap(hdc, winWidth, winHeight);
        SelectObject(hdcMem, bitmap);

        // Background
        HBRUSH background = CreateSolidBrush(RGB(30, 30, 30));
        SetRect(&rect, 0, 0, winWidth, winHeight);
        FillRect(hdcMem, &rect, background);

        //windowBackgroundColor = RGB(0xff, 0xff, 0x00);
        //windowBackgroundBrush = CreateSolidBrush(windowBackgroundColor);
        //wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

        
        SetTextColor(hdcMem, RGB(0, 255, 60));
        SetBkMode(hdcMem, TRANSPARENT);

        HFONT hFont = CreateFont(11, 7, 0, 0, 0, FW_DONTCARE,
            false, false, ANSI_CHARSET,
            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
            TEXT("Lucida Console"));
        HFONT hOldFont = (HFONT)SelectObject(hdcMem, hFont);
        //DrawTextA(hdc, codeDisplay, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        auto linesToDisplay = (rect.bottom / 9);



        char parsestatus[128];

        int i = 0;
        int height = 0;
        rect.left = 550;
        rect.top = 20;
        sprintf_s(parsestatus, 128, "Last parsed 0x%x, parsed %d lines. Selected line: %d", currentParsedOffset, parsedLines, selectedLine);
        DrawTextA(hdcMem, parsestatus, -1, &rect, DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
        //height = DrawTextA(hdc, "Fallout2.exe:", -1, &rect,
        //    DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
        //OffsetRect(&rect, 0, height);

        HBRUSH hGray = CreateSolidBrush(RGB(66, 66, 66));
        SetRect(&selectionRect, 0, selectedLine * 11, 520, (selectedLine * 11) + 11);
        FillRect(hdcMem, &selectionRect, hGray);

        DrawDivider(hdcMem, 80);
        DrawDivider(hdcMem, 240);
        DrawDivider(hdcMem, 520);

        rect.left = 15;
        rect.top = 0;
        char hexbuf[32];
        auto max = displayOffset + linesToDisplay;
        for (i = displayOffset; i < max; i++) {
            sprintf_s(hexbuf, "0x%x", codeDisplay[i].offset);
            OffsetRect(&rect, 0, height);
            height = DrawTextA(hdcMem, hexbuf, -1, &rect,
                DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
        }
       
        height = 0;
        rect.left = 90;
        rect.top = 0;
        for (i = displayOffset; i < max; i++) {
            OffsetRect(&rect, 0, height);
            height = DrawTextA(hdcMem, codeDisplay[i].instructionhex, -1, &rect,
                DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
        }

        
        height = 0;
        rect.left = 250;
        rect.top = 0;
        for (i = displayOffset; i < max; i++) {
            OffsetRect(&rect, 0, height);
            height = DrawTextA(hdcMem, codeDisplay[i].disasm, -1, &rect,
                DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
        }

        BitBlt(hdc, 0, 0, winWidth, winHeight, hdcMem, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);
        DeleteObject(bitmap);
        ReleaseDC(hWnd, hdc);

        // This is needed to draw the scrollbar
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
        return (INT_PTR)FALSE;
}
