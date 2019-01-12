#include "Serial.h"
#include <vector>
#include <string>
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	auto list = getSerialList();
	for (const auto info : list) {
		cout << "device name:" << info.device_name() << endl;
		cout << "name:" << info.port() << "\n" << endl;
	}
	Serial serial;
	Serial dev;
	/*int port;
	cin >> port;
	if (!serial.open(list[port]))
		return -1;
	*/
	for (const auto info : list)
	{
		if (!serial.isOpened())
		{
			if (serial.open(info))
			{
				unsigned char c = 'S';
				serial.write(&c, 1);
				while (serial.available() == 0) {};
				auto v = serial.read();
				if (v[0] != 'k')
				{
					serial.close();
				}
			}
		}
	}
	SerialInfo info = serial.getInfo();
	cout << "open success" << endl;
	cout << "device name:" << info.device_name() << endl;
	cout << "name:" << info.port() << "\n" << endl;
	while (true) {
		unsigned char c = 'a';
		//serial.write(&c, 1);
		if (serial.available() > 0)
		{
			auto v = serial.read();
			for (auto c : v) {
				cout << c;
			}
		}

	}
	return 0;
}
