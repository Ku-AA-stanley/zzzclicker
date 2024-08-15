import pydirectinput
import keyboard
import time
import threading

# 設置點按的間隔時間
interval = 0.0001  # 每次點按之間間隔0.01秒
running = False  # 初始狀態為不運行


def click_j():
    global running
    while True:
        if running:
            pydirectinput.press("j")
            time.sleep(interval)


# 開啟一個新線程來處理點按
click_thread = threading.Thread(target=click_j)
click_thread.daemon = True
click_thread.start()


# 監聽 p 鍵作為切換開關
def toggle_running(event):
    global running
    running = not running
    if running:
        print("開始點按 'j' 鍵")
    else:
        print("停止點按 'j' 鍵")


keyboard.on_press_key("p", toggle_running)

print("按 'p' 鍵來開始/停止點按 'j' 鍵")

# 確保主程式持續運行
keyboard.wait("esc")
print("程式結束")
