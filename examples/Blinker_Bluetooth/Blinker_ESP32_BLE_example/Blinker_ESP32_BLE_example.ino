#define	BLINKER_PRINT	Serial

#include <BlinkerSimpleESP32_BLE.h>

void setup()
{
	Serial.begin(115200);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	Blinker.begin();
}

void loop()
{
	Blinker.run();

	if (Blinker.available()) {
		BLINKER_LOG2("Blinker.readString(): ", Blinker.readString());

		Blinker.vibrate();
		
		uint32_t BlinkerTime = millis();
		Blinker.print(BlinkerTime);
		Blinker.print("millis", BlinkerTime);
	}

	if (Blinker.button("Button1")) {
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(LED_BUILTIN, LOW);
	}
}
