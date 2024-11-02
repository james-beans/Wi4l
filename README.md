# Wi4l
## W - window
## i - in
## 4 - 4
## l - languages

<hr />

> [!TIP]
> The implementations of the window in each language might be a bit different. But they should be similar.

<hr />

> [!WARNING]
> This is tested on Windows 11 and Debian 12. This will not work on MacOS but might on other Linux distros.

> [!WARNING]
> Linux files do not have the `.exe` extension. The windows executables do.

### Links to the code and executables:
- [C Files](langs/C/)
- [C++ Files](langs/C++/)
- [Rust Files](langs/Rust/)
- [Python Files](langs/Python/)

### Known issues:
#### Windows:
- C: 
	- When the window is closed the program will still be running in the background.
- C++ :
	- None known.
- Rust:
	- None known.
- Python:
	- None known.

### Litterally just a single window implemented in 4 languages.
- All code and executables will be in the [langs]() folder to use.
- This will be implemented in:
	- C using [Windows.h](https://en.wikipedia.org/wiki/Windows.h), X11/xlib.h and [unistd.h](https://en.wikipedia.org/wiki/Unistd.h) for Linux
	- C++ using [Windows.h](https://en.wikipedia.org/wiki/Windows.h) and X11/xlib.h for Linux
	- Rust using [Winit](https://docs.rs/winit/latest/winit/)
	- Python using 

> [!WARNING]
> To compile the executables made with Python you will need to install [Pyinstaller](https://pyinstaller.readthedocs.io/en/stable/index.html) and [Nuitka](https://nuitka.net/) for compiling the Python files.

### Command used to compile in each language:
#### Windows:
- C: `gcc main.c -o main.exe -mwindows`
- C++ : `g++ -DUNICODE -D_UNICODE main.cpp -o main.exe -mwindows`
- Rust: `cargo run` or `cargo build`
- Python: `pyinstaller --onefile --windowed main.py` or `nuitka --onefile --windows-console-mode=disable --enable-plugin=tk-inter main.py`
#### Linux (tested on Debian):
- C: `gcc main.c -o main -lX11`
- C++ : `g++ main.cpp -o main -lX11`
- Rust: `cargo run` or `cargo build`
- Python: `pyinstaller --onefile --windowed main.py` or `nuitka --onefile --windows-console-mode=disable --enable-plugin=tk-inter main.py`

<hr /> 

# Disclamers:
- All implementations will not be tested on MacOS or any other version of Linux apart from Debian.
	- I will not test if it works. But if it does please tell me through an issue.
