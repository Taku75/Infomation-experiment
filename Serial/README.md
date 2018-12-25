# Serial
====

WindowsでSerial Portを使うクラス

## Dependency
使用言語：C++
必要ライブラリ：windows.h  
               stdio.h

## Usage
### インスタンス化
```
char* port = const_cast<char *>("\\\\.\\COM3");    //使うポート番号を選択
SerialPort *serial;
serial = new SerialPort(port);
```
### 送信
```
serial->writeSerialPort(`byte(char)型の配列`,`配列の要素数`); 
```
### 受信
```
int readResult = serial->readSerialPort(`byte(char)型の配列`,`配列の要素数`); //正常だとreadResultに0が代入される
print("%s", `byte(char)型の配列`)
```
