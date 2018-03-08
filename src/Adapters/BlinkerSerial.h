#ifndef BlinkerSerial_H
#define BlinkerSerial_H

#define BLINKER_SERIAL_BLE

#include <SoftwareSerial.h>
#include <Blinker/BlinkerProtocol.h>

SoftwareSerial SerialBLE(SERIAL_BLE_RX_PIN, SERIAL_BLE_TX_PIN);
// SoftwareSerial *SerialBLE;//TODO

class BlinkerTransportStream
{
    public :
        BlinkerTransportStream()
            : stream(NULL), isConnect(false)
        {}

        bool available()
        {
            if (stream->available()) {
                strcpy(streamData, (stream->readString()).c_str());
#ifdef BLINKER_DEBUG_ALL
                BLINKER_LOG2(BLINKER_F("handleSerial: "), streamData);
#endif
                return true;
            }
            else {
                return false;
            }
        }

        void begin(Stream& s)
        {
            stream = &s;
            stream->setTimeout(BLINKER_STREAM_TIMEOUT);
        }

        String lastRead() { return STRING_format(streamData); }

        void print(String s)
        {
#ifdef BLINKER_DEBUG_ALL
            BLINKER_LOG2(BLINKER_F("Response: "), s);
#endif
            if(connected()) {
#ifdef BLINKER_DEBUG_ALL
                BLINKER_LOG1(BLINKER_F("Succese..."));
#endif
                stream->print(s);
            }
            else {
#ifdef BLINKER_DEBUG_ALL
                BLINKER_LOG1(BLINKER_F("Faile... Disconnected"));
#endif
            }
        }

        bool connect()
        {
            isConnect = true;
            return connected();
        }

        bool connected() { return isConnect; }

        void disconnect() { isConnect = false; }

    protected :
        Stream* stream;
        char    streamData[BLINKER_BUFFER_SIZE];
        bool    isConnect;
};

class BlinkerSerail
    : public BlinkerProtocol<BlinkerTransportStream>
{
    typedef BlinkerProtocol<BlinkerTransportStream> Base;

    public :
        BlinkerSerail(BlinkerTransportStream& transp)
            : Base(transp)
        {}

        // void begin(uint8_t rx_pin = SERIAL_BLE_RX_PIN,
        //             uint8_t tx_pin = SERIAL_BLE_TX_PIN,
        //             uint32_t baud = SERIAL_BLE_Baud)
        void begin()
        {
            Base::begin();
            SerialBLE.begin(SERIAL_BLE_Baud);
            // SerialBLE = new SoftwareSerial(rx_pin, tx_pin);
            // SerialBLE->begin(baud);//TODO
            // this->conn.begin(*SerialBLE);
            this->conn.begin(SerialBLE);
            BLINKER_LOG1("SerialBLE Initialled...");
        }
};

#endif