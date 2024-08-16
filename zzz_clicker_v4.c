#include <Windows.h>
#include <stdio.h>
#include <process.h> // _beginthread 函数的头文件
#include <stdlib.h>  // 包含标准库头文件

volatile int toggle = 0; // 0表示关，1表示开
HANDLE toggleMutex;      // 用于保护 toggle 变量的互斥锁

unsigned __stdcall CheckToggle(void *param)
{
  while (1)
  {
    if (GetKeyState(VK_XBUTTON1) < 0)
    {
      WaitForSingleObject(toggleMutex, INFINITE); // 获取互斥锁
      toggle = !toggle;
      ReleaseMutex(toggleMutex); // 释放互斥锁
      Sleep(300);
    }
    Sleep(1);
  }
  return 0;
}

unsigned __stdcall HandleMouse(void *param)
{
  int counter = 0;
  while (1)
  {
    WaitForSingleObject(toggleMutex, INFINITE); // 获取互斥锁
    int localToggle = toggle;
    ReleaseMutex(toggleMutex); // 释放互斥锁

    if (localToggle)
    {
      mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
      Sleep(22);

      mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
      Sleep(22);
      counter++;
      printf("Counter: %d\n", counter); // 修正了 printf 的使用
      SetConsoleTitle("running...");
    }
    Sleep(1);
  }
  return 0;
}

int main()
{
  printf("ready for zzz\n"); // 加上了换行符

  toggleMutex = CreateMutex(NULL, FALSE, NULL); // 创建互斥锁

  HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, CheckToggle, NULL, 0, NULL); // 创建检查切换状态的线程
  HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, HandleMouse, NULL, 0, NULL); // 创建处理鼠标事件的线程

  // 主线程可以做其他事情或进入无限等待
  while (1)
  {
    Sleep(1000);
    printf(".\n");
    SetConsoleTitle("waiting...");
  }

  WaitForSingleObject(hThread1, INFINITE); // 等待线程结束
  WaitForSingleObject(hThread2, INFINITE); // 等待线程结束

  CloseHandle(hThread1);    // 关闭线程句柄
  CloseHandle(hThread2);    // 关闭线程句柄
  CloseHandle(toggleMutex); // 关闭互斥锁句柄
  return 0;
}
