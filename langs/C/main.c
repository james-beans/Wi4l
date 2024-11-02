// wi4l - C implementation - main.c
#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "Window";

    RegisterClass(&wc);
    HWND hwnd = CreateWindow(wc.lpszClassName, "Window", WS_OVERLAPPEDWINDOW, 
                             CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);
    ShowWindow(hwnd, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

#else
#include <X11/Xlib.h>
#include <unistd.h>

int main() {
    Display* display = XOpenDisplay(NULL);
    if (display == NULL) return 1;

    Window window = XCreateSimpleWindow(display, DefaultRootWindow(display), 
                                        0, 0, 800, 600, 0, 0, BlackPixel(display, 0));
    XMapWindow(display, window);
    XFlush(display);

    sleep(5); // Keeps the window open for 5 seconds
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
#endif

