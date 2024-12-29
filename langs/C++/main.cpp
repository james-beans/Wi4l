// wi4l - C++ implementation - main.cpp

// Compile with:
// 
// Windows (tested on windows 11):
// g++ -DUNICODE -D_UNICODE main.cpp -o main.exe -mwindows
// 
// Linux (debian 12 tested):
// g++ main.cpp -o main -lX11 -lwayland-client

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

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

// X11 includes
#include <X11/Xlib.h>

// Wayland includes
#include <wayland-client.h>
#include <xdg-shell-client-protocol.h>

// Check for Wayland environment
bool isWayland() {
    const char* waylandDisplay = getenv("WAYLAND_DISPLAY");
    return waylandDisplay != nullptr;
}

// To create a window in X11
void createX11Window() {
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

// Function to create a window in Wayland
void createWaylandWindow() {
    struct wl_display* display = wl_display_connect(nullptr);
    if (!display) {
        fprintf(stderr, "Failed to connect to Wayland display.\n");
        return;
    }

    struct wl_registry* registry = wl_display_get_registry(display);
    if (!registry) {
        wl_display_disconnect(display);
        return;
    }

    struct wl_compositor* compositor = nullptr;
    struct xdg_wm_base* wm_base = nullptr;

    // Registry listener (populate compositor and wm_base)
    static const struct wl_registry_listener registryListener = {
        [](void* data, struct wl_registry* registry, uint32_t id, const char* interface, uint32_t version) {
            if (strcmp(interface, "wl_compositor") == 0) {
                *(struct wl_compositor**)data = static_cast<struct wl_compositor*>(
                    wl_registry_bind(registry, id, &wl_compositor_interface, 1));
            } else if (strcmp(interface, "xdg_wm_base") == 0) {
                *(struct xdg_wm_base**)data = static_cast<struct xdg_wm_base*>(
                    wl_registry_bind(registry, id, &xdg_wm_base_interface, 1));
            }
        },
        [](void*, struct wl_registry*, uint32_t) {}
    };

    wl_registry_add_listener(registry, &registryListener, &compositor);
    wl_display_roundtrip(display);
    wl_registry_add_listener(registry, &registryListener, &wm_base);
    wl_display_roundtrip(display);

    if (!compositor || !wm_base) {
        fprintf(stderr, "Failed to obtain necessary Wayland globals.\n");
        wl_registry_destroy(registry);
        wl_display_disconnect(display);
        return;
    }

    struct wl_surface* surface = wl_compositor_create_surface(compositor);
    if (!surface) {
        fprintf(stderr, "Failed to create Wayland surface.\n");
        wl_registry_destroy(registry);
        wl_display_disconnect(display);
        return;
    }

    struct xdg_surface* xdgSurface = xdg_wm_base_get_xdg_surface(wm_base, surface);
    struct xdg_toplevel* toplevel = xdg_surface_get_toplevel(xdgSurface);
    xdg_toplevel_set_title(toplevel, "Window");

    wl_surface_commit(surface);

    // Run the Wayland event loop
    while (wl_display_dispatch(display) != -1) {
        // Wayland event handling
    }

    wl_registry_destroy(registry);
    wl_display_disconnect(display);
}

// Unified createWindow function
void createWindow() {
    if (isWayland()) {
        createWaylandWindow();
    } else {
        createX11Window();
    }
}

#endif

int main() {
#ifdef _WIN32
    createWindow();
#else // Linux
    createWindow();
#endif
    return 0;
}
