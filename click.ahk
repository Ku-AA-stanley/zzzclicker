#Requires AutoHotkey v2.0

#Persistent ture
SetTimer, CheckMouseButton, 1

CheckMouseButton() {
    if GetKeyState("XButton1", "P") { ; 檢查滑鼠側鍵是否按下，XButton1 代表滑鼠的第一個側鍵（下一頁）
        Click Up
        Sleep 200
        Click Down
        Sleep 100
    }
}