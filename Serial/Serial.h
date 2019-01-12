#pragma once

#include <string>
#include <vector>

#ifndef _UNICODE
using Tstring = std::string;
using Tchar = char;
#else
using Tstring = std::wstring;
using Tchar = wchar_t;
#endif

class SerialInfo
{
private:
	Tstring port_name;
	Tstring device;

public:
	//ポート名
	const Tstring& port() const;
	const Tstring& device_name() const;
	SerialInfo();
	SerialInfo(const SerialInfo&);
	SerialInfo(const Tstring& port);
	SerialInfo(const Tstring& port, const Tstring& device_name);
};

std::vector<SerialInfo> getSerialList();

class Serial
{
public:
	//設定
	struct Config
	{
		unsigned int baudRate;
		unsigned int byteSize;
		enum class Parity
		{
			NO,//パリティなし
			EVEN,//偶数パリティ
			ODD//奇数パリティ
		}parity;

		enum class StopBits
		{
			//1ビット
			ONE,
			//1.5ビット
			ONE5,
			//2ビット
			TWO
		}stopBits;
	};

private:
	//ポート情報
	SerialInfo info;

	//オープンしてるか
	bool opened;

	//設定
	Config conf;

	void* handle;
	void setBuffSize(unsigned long read, unsigned long write);

public:
	Serial();
	Serial(const Serial&) = delete;
	~Serial();

	//<sammary>
	//バッファに格納されたデータのバイト数を返す
	//</sammary>
	int available();

	//<sammary>
	//デバイスをオープン
	//</sammary>
	bool open(const Tstring& port_name, unsigned int baudRate = 9600);
	bool open(const SerialInfo& serial_info, unsigned int baudRate = 9600);

	//<sammary>
	//デバイスをクローズ
	//</sammary>
	void close();

	//<sammary>
	//ポート情報の取得
	//</sammary>
	const Config& getConfig() const;

	//<sammary>
	//ポート情報を設定
	//</sammary>
	void setConfig(const Config&);

	//<sammary>
	//デバイス情報の取得
	//</sammary>
	const SerialInfo& getInfo() const;

	//<sammary>
	//デバイスがオープンしているか
	//</sammary>
	bool isOpened() const;

	//<sammary>
	//sizeバイトもしくはバッファにあるだけ受信
	//</sammary>
	int read(unsigned char* data, int size);

	//<sammary>
	//1バイト受信
	//</sammary>
	unsigned char read1byte();

	//<sammary>
	//バッファすべて受信
	//最低1バイト
	//</sammary>
	std::vector<unsigned char> read();

	//<sammary>
	//バッファをクリア
	//</sammary>
	void clear();

	//<sammary>
	//出力バッファをクリア
	//</sammary>
	void clearWrite();

	//<sammary>
	//入力バッファをクリア
	//</sammary>
	void clearRead();

	//<sammary>
	//送信
	//</sammary>
	int write(unsigned char* data, int size);

	//<sammary>
	//送信
	//</sammary>
	int write(const std::vector<unsigned char>& data);
};
