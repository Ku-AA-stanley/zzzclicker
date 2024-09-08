#include <Windows.h> // 包含 Windows API 標頭檔
#include <stdio.h>

int main()
{
  printf("ready for zzz");

  int toggle = 0; // 0表示關，1表示開

  while (1)
  {
    if (GetKeyState(VK_XBUTTON1) < 0) // 檢查滑鼠側鍵是否按下，VK_XBUTTON1代表滑鼠的第一個側鍵
    {
      toggle = !toggle; // 切換狀態
      Sleep(300);       // 避免因長按側鍵而不停切換
    }

    if (toggle) // 若為「開」狀態
    {
      mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
      Sleep(8);

      mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
      Sleep(8);
      printf("toggle\n");
    }
    Sleep(1);
    printf(".\n"); // 休眠1毫秒，避免無限迴圈過於耗費CPU資源
  }

  return 0;
}
