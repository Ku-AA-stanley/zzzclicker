#include <stdio.h>
#include <windows.h>
#include <conio.h>

void setWindowTitle(char key)
{
  char title[100];
  sprintf(title, "You just pressed %c key", key);
  SetConsoleTitle(title);
}

int main()
{
  char key;
  printf("Press any key to change the window title. Press 'q' to quit.\n");

  while (1)
  {
    if (kbhit())
    {                 // 檢測是否有按鍵輸入
      key = _getch(); // 讀取按鍵

      if (key == 'q' || key == 'Q')
      { // 如果按下 'q' 鍵，退出
        break;
      }

      // 更改視窗標題
      setWindowTitle(key);
    }
  }

  return 0;
}
