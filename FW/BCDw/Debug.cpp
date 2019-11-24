#include "Debug.hpp"

namespace Debug
{
    void Debug::Write(const char *s) {
        // Do nothing
    }

    void Debug::Write(uint8_t i) {
        // Do nothing
    }
    
    void Debug::Write(uint16_t i) {
        // Do nothing
    }

    void Debug::Write(uint32_t i) {
        // Do nothing
    }

    void Debug::Write(int8_t i) {
        // Do nothing
    }

    void Debug::Write(int16_t i) {
        // Do nothing
    }

    void Debug::Write(int32_t i) {
        // Do nothing
    }

    void Debug::WriteLine(const char *line) {
        // Do nothing
    }

    void Debug::NewLine() {
        // Do nothing
    }



    SerialDebug::SerialDebug(UART::SerialPort *port) {
        this->m_port = port;
    }

    void SerialDebug::Write(const char *s) {
        this->m_port->Write(s);
    }

    void SerialDebug::Write(uint8_t i) { this->Write((uint32_t)i); }
    void SerialDebug::Write(uint16_t i) { this->Write((uint32_t)i); }
    void SerialDebug::Write(uint32_t i) {
        uint8_t s[12];
        uint16_t len = 0;

        // End with nullchar
        s[11] = '\0';
        len++;

        for(len = 1; len < 12; len++) {
            s[12-len] = '0' + i % 10;
            i = i / 10;
            if(i == 0) break;
        }

        this->m_port->Write(&s[12-len], len);
    }

    void SerialDebug::Write(int8_t i) { this->Write((int32_t)i); }
    void SerialDebug::Write(int16_t i) { this->Write((int32_t)i); }
    void SerialDebug::Write(int32_t i) {
        if(i < 0) {
            this->m_port->Write("-");
            i = -i;
        }
        this->Write((uint32_t)i);
    }
    
    void SerialDebug::WriteLine(const char *line) {
        this->Write(line);
        this->NewLine();
    }

    void SerialDebug::NewLine() {
        this->m_port->Write("\r\n");
    }


} // namespace Debug
