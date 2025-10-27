CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags gtkmm-4.0`
LDFLAGS = `pkg-config --libs gtkmm-4.0`
TARGET = led_controller
SOURCES = main.cc arduino_controller.cc
NASM = nasm
NASMFLAGS = -f elf64
NASMSOURCES = greet.asm
NASMTARGET = greet.o


$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f  $(TARGET)

run: $(TARGET)
	./$(TARGET)