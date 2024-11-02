// wi4l - C++ implementation - main.cpp
#ifdef _WIN32
#include <windows.h>

// Function to create a window in Windows
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            // Optional: You can add code to draw something here
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void createWindow() {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowExW(
        0,                            // Optional window styles.
        CLASS_NAME,                  // Window class
        L"Window",                   // Window text
        WS_OVERLAPPEDWINDOW,         // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,                     // Parent window    
        nullptr,                     // Menu
        wc.hInstance,                // Instance handle
        nullptr                       // Additional application data
    );

    if (hwnd == nullptr) {
        return;
    }

    ShowWindow(hwnd, SW_SHOW);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

#else // Linux

#include <X11/Xlib.h>
#include <unistd.h>

void createWindow() {
    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        return;
    }

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 
                                         10, 10, 800, 600, 1, 
                                         BlackPixel(display, screen), 
                                         WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    // Main event loop
    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Optional: You can add code to draw something here
        }
        if (event.type == KeyPress) {
            break; // Exit on key press
        }
    }

    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

#endif

int main() {
#ifdef _WIN32
    createWindow();
#else
    createWindow();
#endif
    return 0;
}