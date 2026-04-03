//              plataform globals

static bool running = true;


//              Plataform functions
bool plataform_create_window(int width, int height, char* title);
void plataform_create_window();



///             Windows plataform
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>


//                  Windows globals
static HWND window;



//              plataform impletations
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
                                        WPARAM wParam,LPARAM lParam)

{      
LRESULT result = 0;

switch(msg)
{
    case WM_CLOSE:
    {
        running = false;
        break;
    }

        default:
        {        // let windows handle the default  input for now
        result = DefWindowProcA(window, msg, wParam, lParam);
        }
    }

    return result;
}




bool plataform_create_window(int width, int height, char* title)
{
    HINSTANCE instance = GetModuleHandleA(0);

    WNDCLASSA  wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);    // This means we decide the look of the cursor (arrow)
    wc.lpszClassName = title;                   //This is NOT the title, just a unique identifier(ID)
    wc.lpfnWndProc = windows_window_callback;             // Callback for input the Window

    if(!RegisterClassA(&wc))
    {
        return false;
    }

    // WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
    int dwStyle = WS_OVERLAPPEDWINDOW;
    
    HWND window = CreateWindowExA(0, title, //This reference lpszClassName from wc
                                  title, // This is the actual Title
                                  dwStyle,
                                100,
                                100,
                                width,
                                height,
                                NULL,       // parent
                                NULL,       // menu
                                instance,
                                NULL);      //lpParam
if(window == NULL)
{
    return false;
}

    ShowWindow(window, SW_SHOW);

    return true;


}

void plataform_create_window()

    {
    MSG msg;

        while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg); // Call the callback specified when creating the window
        }
}

#endif






int main()
{
    plataform_create_window(1200, 720, "Schnitzel Motor");

    while (running)
    {
            //Update
            plataform_create_window();
    }

    return 0;
}