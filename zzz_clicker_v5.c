#include <Windows.h>
#include <stdio.h>
#include <process.h> // _beginthreadex function
#include <stdlib.h>  // Standard library headers

volatile int toggleLeftClick = 0; // 0 for off, 1 for on
volatile int toggleFKey = 0;      // 0 for off, 1 for on
HANDLE toggleMutex;               // Mutex to protect toggle variables

unsigned __stdcall CheckToggle(void *param)
{
  while (1)
  {
    // Check for VK_XBUTTON1，下一頁的側鍵
    if (GetKeyState(VK_XBUTTON1) & 0x8000)
    {
      WaitForSingleObject(toggleMutex, INFINITE); // Acquire mutex
      toggleLeftClick = !toggleLeftClick;
      ReleaseMutex(toggleMutex); // Release mutex
      Sleep(90);
    }

    // Check for VK_XBUTTON2，上一頁的側鍵
    if (GetKeyState(VK_XBUTTON2) & 0x8000)
    {
      WaitForSingleObject(toggleMutex, INFINITE); // Acquire mutex
      toggleFKey = !toggleFKey;
      ReleaseMutex(toggleMutex); // Release mutex
      Sleep(90);
    }

    Sleep(50); // Slight delay to prevent high CPU usage
  }
  return 0;
}

unsigned __stdcall HandleMouseAndFKey(void *param)
{
  int clickCounter = 0;
  int fKeyCounter = 0;

  while (1)
  {
    // Handle Left Click Toggle
    WaitForSingleObject(toggleMutex, INFINITE); // Acquire mutex
    int localToggleLeft = toggleLeftClick;
    int localToggleF = toggleFKey;
    ReleaseMutex(toggleMutex); // Release mutex

    if (localToggleLeft)
    {
      mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
      Sleep(25);
      mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
      Sleep(25);
      clickCounter++;
      printf("Left Key Counter: %d\n", clickCounter);
      SetConsoleTitle("Clicking LEFT");
    }

    if (localToggleF)
    {
      // Simulate F key press
      keybd_event('F', 0, 0, 0);               // Key down
      Sleep(25);                               // Hold for 50 ms
      keybd_event('F', 0, KEYEVENTF_KEYUP, 0); // Key up
      fKeyCounter++;
      printf("F Key Pressed: %d\n", fKeyCounter);
      SetConsoleTitle("Pressing F");
    }

    Sleep(1);
  }
  return 0;
}

int main()
{
  printf("# Mouse Side Button Functions\n");
  printf("   - Back : pressing LEFT key\n");
  printf("   - Forward : pressing F key\n");

  toggleMutex = CreateMutex(NULL, FALSE, NULL); // Create mutex

  HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, CheckToggle, NULL, 0, NULL);        // Thread to check toggle status
  HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, HandleMouseAndFKey, NULL, 0, NULL); // Thread to handle mouse and F key

  // Main thread can perform other tasks or enter an infinite wait
  while (1)
  {
    Sleep(1000);
    printf(".\n");
    SetConsoleTitle("Waiting...");
  }

  WaitForSingleObject(hThread1, INFINITE); // Wait for thread to finish
  WaitForSingleObject(hThread2, INFINITE); // Wait for thread to finish

  CloseHandle(hThread1);    // Close thread handle
  CloseHandle(hThread2);    // Close thread handle
  CloseHandle(toggleMutex); // Close mutex handle
  return 0;
}
