from platformio import util
import os


if __name__ == '__main__':
    ports = util.get_serial_ports()
    for port in ports:
        os.system("pio run --target upload --upload-port "+ port["port"])
        print("Successfully update port: "+ port["port"] )


