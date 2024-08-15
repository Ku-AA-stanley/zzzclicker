#include <Windows.h> // 包含 Windows API 標頭檔
#include <stdio.h>

int main()
{
  printf("ready for zzz");

  while (1)
  {
    if (GetKeyState(VK_XBUTTON1) < 0) // 檢查滑鼠側鍵是否按下，VK_XBUTTON1代表滑鼠的第一個側鍵
    {
      mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
      Sleep(200);

      mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
      Sleep(100);
    }
    Sleep(1); // 休眠1毫秒，避免無限迴圈過於耗費CPU資源
  }

  return 0;
}