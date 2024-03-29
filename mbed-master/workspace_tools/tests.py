from workspace_tools.paths import *
from workspace_tools.data.support import *

TEST_CMSIS_LIB = join(TEST_DIR, "cmsis", "lib")
TEST_MBED_LIB = join(TEST_DIR, "mbed", "env")

PERIPHERALS = join(TEST_DIR, "peripherals")
BENCHMARKS_DIR = join(TEST_DIR, "benchmarks")
SD = join(TEST_DIR, "sd")

"""
Wiring:
  * Ground:
    * LPC1*: p1
    * KL25Z: GND
  
  * Vout
    * LPC1*: p40
    * KL25Z: P3V3
  
  * TMP102 (I2C):
      * LPC1*: (SDA=p28 , SCL=p27)
      * KL25Z: (SDA=PTC9, SCL=PTC8)
  
  * digital_loop (Digital(In|Out|InOut), InterruptIn):
      * LPC1*: (p5   <-> p25 )
      * KL25Z: (PTA1 <-> PTC7)
  
  * port_loop (Port(In|Out|InOut)):
      * LPC1*: (p5   <-> p25 ), (p6   <-> p26 )
      * KL25Z: (PTA1 <-> PTC7), (PTA2 <-> PTC0)
  
  * analog_loop (AnalogIn, AnalogOut):
      * LPC1*: (p17   <-> p18 )
      * KL25Z: (PTE30 <-> PTC2)
  
  * SD (SPI):
      * LPC1*: (mosi=p11 , miso=p12 , sclk=p13 , cs=p14 )
      * KL25Z: (mosi=PTD2, miso=PTD3, sclk=PTD1, cs=PTD0)
      
  * MMA7660 (I2C):
      * LPC1*: (SDA=p28 , SCL=p27)
"""
TESTS = [
    # Automated MBED tests
    {
        "id": "MBED_A1", "description": "Basic",
        "source_dir": join(TEST_DIR, "mbed", "basic"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
    },
    {
        "id": "MBED_A2", "description": "semihost file system",
        "source_dir": join(TEST_DIR, "mbed", "file"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
        "mcu": ["LPC1768", "LPC2368", "LPC11U24"]
    },
    {
        "id": "MBED_A3", "description": "C++ STL",
        "source_dir": join(TEST_DIR, "mbed", "stl"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
    },
    {
        "id": "MBED_A4", "description": "I2C TMP102",
        "source_dir": join(TEST_DIR, "mbed", "i2c_TMP102"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, join(PERIPHERALS, 'TMP102')],
        "automated": True,
        "peripherals": ["TMP102"]
    },
    {
        "id": "MBED_A5", "description": "DigitalIn DigitalOut",
        "source_dir": join(TEST_DIR, "mbed", "digitalin_digitalout"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
        "peripherals": ["digital_loop"]
    },
    {
        "id": "MBED_A6", "description": "DigitalInOut",
        "source_dir": join(TEST_DIR, "mbed", "digitalinout"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
        "peripherals": ["digital_loop"]
    },
    {
        "id": "MBED_A7", "description": "InterruptIn",
        "source_dir": join(TEST_DIR, "mbed", "interruptin"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
        "peripherals": ["digital_loop"]
    },
    {
        "id": "MBED_A8", "description": "Analog",
        "source_dir": join(TEST_DIR, "mbed", "analog"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
        "peripherals": ["analog_loop"],
        "mcu": ["LPC1768", "LPC2368", "KL25Z"]
    },
    {
        "id": "MBED_A9", "description": "Serial Echo at 115200",
        "source_dir": join(TEST_DIR, "mbed", "echo"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "automated": True,
        "host_test": "echo"
    },
    {
        "id": "MBED_A10", "description": "PortOut PortIn",
        "source_dir": join(TEST_DIR, "mbed", "portout_portin"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "peripherals": ["port_loop"],
        "supported": DEFAULT_SUPPORT,
        "automated": True,
    },
    {
        "id": "MBED_A11", "description": "PortInOut",
        "source_dir": join(TEST_DIR, "mbed", "portinout"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "peripherals": ["port_loop"],
        "supported": DEFAULT_SUPPORT,
        "automated": True,
    },
    {
        "id": "MBED_A12", "description": "SD File System",
        "source_dir": join(TEST_DIR, "mbed", "sd"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, SD_FS, FAT_FS],
        "automated": True,
        "peripherals": ["SD"]
    },
    {
        "id": "MBED_A13", "description": "I2C MMA7660",
        "source_dir": join(TEST_DIR, "mbed", "i2c_MMA7660"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, join(PERIPHERALS, 'MMA7660')],
        "automated": True,
        "peripherals": ["MMA7660"]
    },
    {
        "id": "MBED_A14", "description": "I2C Master",
        "source_dir": join(TEST_DIR, "mbed", "i2c_master"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB,],
        "automated": True
    },
    {
        "id": "MBED_A15", "description": "I2C Slave",
        "source_dir": join(TEST_DIR, "mbed", "i2c_slave"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB,],
        "automated": True
    },
    {
        "id": "MBED_A16", "description": "SPI Master",
        "source_dir": join(TEST_DIR, "mbed", "spi_master"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB,],
        "automated": True
    },
    {
        "id": "MBED_A17", "description": "SPI Slave",
        "source_dir": join(TEST_DIR, "mbed", "spi_slave"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB,],
        "automated": True
    },
    
    # Size benchmarks
    {
        "id": "BENCHMARK_1", "description": "Size (c environment)",
        "source_dir": join(BENCHMARKS_DIR, "cenv"),
        "dependencies": [MBED_LIBRARIES]
    },
    {
        "id": "BENCHMARK_2", "description": "Size (float math)",
        "source_dir": join(BENCHMARKS_DIR, "float_math"),
        "dependencies": [MBED_LIBRARIES]
    },
    {
        "id": "BENCHMARK_3", "description": "Size (printf)",
        "source_dir": join(BENCHMARKS_DIR, "printf"),
        "dependencies": [MBED_LIBRARIES]
    },
    {
        "id": "BENCHMARK_4", "description": "Size (mbed libs)",
        "source_dir": join(BENCHMARKS_DIR, "mbed"),
        "dependencies": [MBED_LIBRARIES]
    },
    {
        "id": "BENCHMARK_5", "description": "Size (all)",
        "source_dir": join(BENCHMARKS_DIR, "all"),
        "dependencies": [MBED_LIBRARIES]
    },
    
    # Not automated MBED tests
    {
        "id": "MBED_1", "description": "I2C SRF08",
        "source_dir": join(TEST_DIR, "mbed", "i2c_SRF08"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, join(PERIPHERALS, 'SRF08')],
        "peripherals": ["SRF08"]
    },
    {
        "id": "MBED_2", "description": "stdio",
        "source_dir": join(TEST_DIR, "mbed", "stdio"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_3", "description": "PortOut",
        "source_dir": join(TEST_DIR, "mbed", "portout"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_4", "description": "Sleep",
        "source_dir": join(TEST_DIR, "mbed", "sleep"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
        "duration": 30,
        "mcu": ["LPC1768", "LPC11U24"]
    },
    {
        "id": "MBED_5", "description": "PWM",
        "source_dir": join(TEST_DIR, "mbed", "pwm"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_6", "description": "SW Reset",
        "source_dir": join(TEST_DIR, "mbed", "reset"),
        "dependencies": [MBED_LIBRARIES],
        "duration": 15
    },
    {
        "id": "MBED_7", "description": "stdio  benchmark",
        "source_dir": join(TEST_DIR, "mbed", "stdio_benchmark"),
        "dependencies": [MBED_LIBRARIES],
        "duration": 40
    },
    {
        "id": "MBED_8", "description": "SPI",
        "source_dir": join(TEST_DIR, "mbed", "spi"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_9", "description": "Sleep Timeout",
        "source_dir": join(TEST_DIR, "mbed", "sleep_timeout"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_10", "description": "Hello World",
        "source_dir": join(TEST_DIR, "mbed", "hello"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_11", "description": "Ticker",
        "source_dir": join(TEST_DIR, "mbed", "ticker"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_12", "description": "C++",
        "source_dir": join(TEST_DIR, "mbed", "cpp"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_13", "description": "Heap & Stack",
        "source_dir": join(TEST_DIR, "mbed", "heap_and_stack"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_14", "description": "Serial Interrupt",
        "source_dir": join(TEST_DIR, "mbed", "serial_interrupt"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_15", "description": "RPC",
        "source_dir": join(TEST_DIR, "mbed", "rpc"),
        "dependencies": [MBED_LIBRARIES, join(LIB_DIR, "rpc")],
        "host_test": "rpc",
    },
    {
        "id": "MBED_16", "description": "RTC",
        "source_dir": join(TEST_DIR, "mbed", "rtc"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_17", "description": "Serial Interrupt 2",
        "source_dir": join(TEST_DIR, "mbed", "serial_interrupt_2"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_18", "description": "Local FS Directory",
        "source_dir": join(TEST_DIR, "mbed", "dir"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_19", "description": "SD FS Directory",
        "source_dir": join(TEST_DIR, "mbed", "dir_sd"),
        "dependencies": [MBED_LIBRARIES, SD_FS, FAT_FS],
        "peripherals": ["SD"]
    },
    {
        "id": "MBED_20", "description": "InterruptIn 2",
        "source_dir": join(TEST_DIR, "mbed", "interruptin_2"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_21", "description": "freopen Stream",
        "source_dir": join(TEST_DIR, "mbed", "freopen"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "MBED_22", "description": "Semihost",
        "source_dir": join(TEST_DIR, "mbed", "semihost"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_23", "description": "Ticker 2",
        "source_dir": join(TEST_DIR, "mbed", "ticker_2"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_24", "description": "Timeout",
        "source_dir": join(TEST_DIR, "mbed", "timeout"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_25", "description": "Time us",
        "source_dir": join(TEST_DIR, "mbed", "time_us"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_26", "description": "Integer constant division",
        "source_dir": join(TEST_DIR, "mbed", "div"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB],
    },
    {
        "id": "MBED_27", "description": "SPI ADXL345",
        "source_dir": join(TEST_DIR, "mbed", "spi_ADXL345"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, join(PERIPHERALS, 'ADXL345')],
        "automated": True,
        "peripherals": ["ADXL345"]
    },
    {
        "id": "MBED_29", "description": "I2C master/slave test",
        "source_dir": join(TEST_DIR, "mbed", "i2c_master_slave"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB,],
        "automated": True,
        "mcu": ["LPC1768"]
    },
   
    # CMSIS RTOS tests
    {
        "id": "CMSIS_RTOS_1", "description": "Basic",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "basic"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "CMSIS_RTOS_2", "description": "Mutex",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "mutex"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
        "duration": 20
    },
    {
        "id": "CMSIS_RTOS_3", "description": "Semaphore",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "semaphore"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
        "duration": 20
    },
    {
        "id": "CMSIS_RTOS_4", "description": "Signals",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "signals"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "CMSIS_RTOS_5", "description": "Queue",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "queue"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
        "duration": 20
    },
    {
        "id": "CMSIS_RTOS_6", "description": "Mail",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "mail"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
        "duration": 20
    },
    {
        "id": "CMSIS_RTOS_7", "description": "Timer",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "timer"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "CMSIS_RTOS_8", "description": "ISR",
        "source_dir": join(TEST_DIR, "rtos", "cmsis", "isr"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    
    # mbed RTOS tests
    {
        "id": "RTOS_1", "description": "Basic",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "basic"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "RTOS_2", "description": "Mutex",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "mutex"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
        "duration": 20
    },
    {
        "id": "RTOS_3", "description": "Semaphore",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "semaphore"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "RTOS_4", "description": "Signals",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "signals"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "RTOS_5", "description": "Queue",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "queue"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "RTOS_6", "description": "Mail",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "mail"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "RTOS_7", "description": "Timer",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "timer"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "RTOS_8", "description": "ISR",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "isr"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES],
    },
    {
        "id": "RTOS_9", "description": "File",
        "source_dir": join(TEST_DIR, "rtos", "mbed", "file"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, TEST_MBED_LIB, SD_FS, FAT_FS],
    },
    
    # Networking Tests
    {
        "id": "NET_1", "description": "TCP client hello world",
        "source_dir": join(TEST_DIR, "net", "helloworld", "tcpclient"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_2", "description": "UDP client hello world",
        "source_dir": join(TEST_DIR, "net", "helloworld", "udpclient"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_3", "description": "TCP echo server",
        "source_dir": join(TEST_DIR, "net", "echo", "tcp_server"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_4", "description": "TCP echo client",
        "source_dir": join(TEST_DIR, "net", "echo", "tcp_client"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_5", "description": "UDP echo server",
        "source_dir": join(TEST_DIR, "net", "echo", "udp_server"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_6", "description": "UDP echo client",
        "source_dir": join(TEST_DIR, "net", "echo", "udp_client"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_7", "description": "HTTP client",
        "source_dir": join(TEST_DIR, "net", "protocols", "HTTPClient_HelloWorld"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_8", "description": "NTP client",
        "source_dir": join(TEST_DIR, "net", "protocols", "NTPClient_HelloWorld"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_9", "description": "Multicast Send",
        "source_dir": join(TEST_DIR, "net", "helloworld", "multicast_send"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_10", "description": "Multicast Receive",
        "source_dir": join(TEST_DIR, "net", "helloworld", "multicast_receive"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_11", "description": "Broadcast Send",
        "source_dir": join(TEST_DIR, "net", "helloworld", "broadcast_send"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_12", "description": "Broadcast Receive",
        "source_dir": join(TEST_DIR, "net", "helloworld", "broadcast_receive"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "NET_13", "description": "TCP client echo loop",
        "source_dir": join(TEST_DIR, "net", "echo", "tcp_client_loop"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, ETH_LIBRARY],
        "supported": CORTEX_ARM_SUPPORT,
    },
    
    # Vodafone tests
    {
        "id": "VF_1", "description": "HTTP client",
        "source_dir": join(TEST_DIR, "net", "vodafone", "HTTPClient_HelloWorld"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, VODAFONE_LIBRARY, TEST_MBED_LIB],
        "supported": CORTEX_ARM_SUPPORT,
        "automated": False,
    },
    {
        "id": "VF_2", "description": "USSD & SMS Test",
        "source_dir": join(TEST_DIR, "net", "vodafone", "USSD_SMS_HelloWorld"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, VODAFONE_LIBRARY, TEST_MBED_LIB],
        "supported": CORTEX_ARM_SUPPORT,
        "automated": False,
    },
    
    # USB Tests
    {
        "id": "USB_1", "description": "Mouse",
        "source_dir": join(TEST_DIR, "usb", "device", "basic"),
        "dependencies": [MBED_LIBRARIES, USB_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "USB_2", "description": "Keyboard",
        "source_dir": join(TEST_DIR, "usb", "device", "keyboard"),
        "dependencies": [MBED_LIBRARIES, USB_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "USB_3", "description": "Mouse_Keyboard",
        "source_dir": join(TEST_DIR, "usb", "device", "keyboard"),
        "dependencies": [MBED_LIBRARIES, USB_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "USB_4", "description": "Serial Port",
        "source_dir": join(TEST_DIR, "usb", "device", "serial"),
        "dependencies": [MBED_LIBRARIES, USB_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "USB_5", "description": "Generic HID",
        "source_dir": join(TEST_DIR, "usb", "device", "raw_hid"),
        "dependencies": [MBED_LIBRARIES, USB_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "USB_6", "description": "MIDI",
        "source_dir": join(TEST_DIR, "usb", "device", "midi"),
        "dependencies": [MBED_LIBRARIES, USB_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    {
        "id": "USB_7", "description": "AUDIO",
        "source_dir": join(TEST_DIR, "usb", "device", "audio"),
        "dependencies": [MBED_LIBRARIES, USB_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    
    # CMSIS DSP
    {
        "id": "CMSIS_DSP_1", "description": "FIR",
        "source_dir": join(TEST_DIR, "dsp", "cmsis", "fir_f32"),
        "dependencies": [MBED_LIBRARIES, DSP_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    
    # mbed DSP
    {
        "id": "DSP_1", "description": "FIR",
        "source_dir": join(TEST_DIR, "dsp", "mbed", "fir_f32"),
        "dependencies": [MBED_LIBRARIES, DSP_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
    },
    
    # KL25Z
    {
        "id": "KL25Z_1", "description": "LPTMR",
        "source_dir": join(TEST_DIR, "KL25Z", "lptmr"),
        "dependencies": [MBED_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
        "mcu": ["KL25Z"],
    },
    {
        "id": "KL25Z_2", "description": "PIT",
        "source_dir": join(TEST_DIR, "KL25Z", "pit"),
        "dependencies": [MBED_LIBRARIES],
        "supported": CORTEX_ARM_SUPPORT,
        "mcu": ["KL25Z"],
    },
    {
        "id": "KL25Z_3", "description": "TSI Touch Sensor",
        "source_dir": join(TEST_DIR, "mbed", "tsi"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, join(PERIPHERALS, 'TSI')],
        "mcu": ["KL25Z"],
    },
    {
        "id": "KL25Z_4", "description": "RTC",
        "source_dir": join(TEST_DIR, "KL25Z", "rtc"),
        "dependencies": [MBED_LIBRARIES],
        "mcu": ["KL25Z"],
    },
    {
        "id": "KL25Z_5", "description": "MMA8451Q accelerometer",
        "source_dir": join(TEST_DIR, "mbed", "i2c_MMA8451Q"),
        "dependencies": [MBED_LIBRARIES, TEST_MBED_LIB, join(PERIPHERALS, 'MMA8451Q')],
        "mcu": ["KL25Z"],
    },
    
    # Examples
    {
        "id": "EXAMPLE_1", "description": "/dev/null",
        "source_dir": join(TEST_DIR, "mbed", "dev_null"),
        "dependencies": [MBED_LIBRARIES],
    },
    {
        "id": "EXAMPLE_2", "description": "FS + RTOS",
        "source_dir": join(TEST_DIR, "mbed", "fs"),
        "dependencies": [MBED_LIBRARIES, RTOS_LIBRARIES, TEST_MBED_LIB, SD_FS, FAT_FS],
    },
]

class Test:
    DEFAULTS = {
        'dependencies': None,
        'duration': 10,
        'host_test': 'host_test',
        'automated': False,
        'peripherals': None,
        'extra_files': None
    }
    def __init__(self, n):
        self.n = n
        self.__dict__.update(Test.DEFAULTS)
        self.__dict__.update(TESTS[n])

    def is_supported(self, target, toolchain):
        if not hasattr(self, 'supported'):
            return True
        return (target in self.supported) and (toolchain in self.supported[target])
    
    def get_description(self):
        if hasattr(self, 'description'):
            return self.description
        else:
            return self.id
    
    def __cmp__(self, other):
        return cmp(self.n, other.n)
    
    def __str__(self):
        return "[%3d] %s: %s" % (self.n, self.id, self.get_description())


TEST_MAP = dict([(test['id'], Test(i)) for i, test in enumerate(TESTS)])
