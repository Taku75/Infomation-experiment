# Serial
WindowsでSerial Portを使うライブラリ

## Dependency
使用言語：C++
必要ライブラリ：windows.h, SetupAPI.h, vector

## Usage
### 利用できるすべてのシリアルポートのリストの取得
```
auto list = getSerialList();          //戻り値は std::vector<SerialInfo>
const auto info = list[0];            //vectorは<>内の型の配列のように扱える
for(const auto info : list){};        //for文の中ではinfoはSerialInfo型の変数として扱う。
```
### インスタンス化
```
Serial serial;                        //インスタンス1つに対してポートは一つしか扱えない
```

### シリアルポートの開閉
```
//シリアルポートを開く
//全メソッド開くのに成功した場合、戻り値は true, 失敗した場合、戻り値は false
serial.open(list[0]);                //引数(SerialInfo '使えるポートの情報')
serial.open(list[0], 9600);          //引数(SerialInfo '使えるポートの情報', int 'ボートレート')
serial.open("COM3");                 //引数(std::string 'ポート番号')
serial.open("COM3", 9600);           //引数(std::string 'ポート番号', int 'ボートレート')

//シリアルポートを閉じる
serial.close();                      //serialが扱っているポートを閉じる

//ポートが開いているか
serial.isOpened();                   //開いていたら戻り値にtrueが、閉じていたらfalse
```


### 送信
```
//一文字送信
unsigned char c = 'a';
serial.write(&c, 1);                 //引数(unsigned char* '文字列のポインタ', int '文字列のバイト数')

//複数文字送信(ポインタ)
unsigned char s[] = "aaaaaaaaaa";
serial.write(s, 10);                 //引数(unsigned char* '文字列のポインタ', int '文字列のバイト数')

//複数文字送信(vector)
vector<unsigned char> s;
s.push_back('a');
s.push_back('a');
s.push_back('a');
s.push_back('a');
s.push_back('a');
serial.write(s);                     //引数(vrctor<unsigned char> '文字列')
```

### 受信
```
if(serial.available() > 0)//available()はreadBuff内の文字数を返す
{
  //一文字受信
  unsigned char c = serial.read1byte(); //戻り値に文字が入る

  //複数文字受信(ポインタ)
  unsigned char * s;
  serial.read(s, 10);                //引数(unsigned char* '文字列', int size)
                                     //sizeバイトもしくはバッファにあるだけ受信

  //複数文字受信(vector)
  auto s = serial.read()             //戻り値はvector<unsigned char>
}
```
