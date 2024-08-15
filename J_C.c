#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <process.h>

volatile bool running = false;

DWORD WINAPI ClickJ(LPVOID lpParam)
{
  while (1)
  {
    if (running)
    {
      // Simulate pressing the 'j' key
      keybd_event('J', 0, 0, 0);
      keybd_event('J', 0, KEYEVENTF_KEYUP, 0);
      Sleep(3); // Interval of 10 milliseconds between key presses
    }
    Sleep(1); // Prevent high CPU usage
  }
  return 0;
}

int main()
{
  HANDLE hThread = CreateThread(NULL, 0, ClickJ, NULL, 0, NULL);

  if (hThread == NULL)
  {
    printf("Failed to create thread!\n");
    return 1;
  }

  printf("Press 'p' to toggle pressing 'j', press 'esc' to exit\n");

  while (1)
  {
    if (_kbhit())
    {
      int ch = _getch();
      if (ch == 'p' || ch == 'P')
      {
        running = !running;
        if (running)
        {
          printf("Started pressing 'j'\n");
        }
        else
        {
          printf("Stopped pressing 'j'\n");
        }
      }
      else if (ch == 27)
      { // 27 is the ASCII value for 'esc'
        break;
      }
    }
    Sleep(10); // Reduce CPU usage
  }

  CloseHandle(hThread);
  return 0;
}
