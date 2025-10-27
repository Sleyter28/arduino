CXX = g++
CXXFLAGS = -std=c++23 `pkg-config --cflags gtkmm-4.0`
LDFLAGS = `pkg-config --libs gtkmm-4.0`
TARGET = temp_controller
SOURCES = main.cc arduino_controller.cc
NASM = nasm
NASMFLAGS = -f elf64
NASMSOURCES = print.asm
NASMTARGET = print.o


$(TARGET): $(SOURCES)
	$(NASM) $(NASMFLAGS) $(NASMSOURCES) -o $(NASMTARGET)
	$(CXX) $(SOURCES) $(NASMTARGET) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f  $(TARGET) $(NASMTARGET)

run: $(TARGET)
	./$(TARGET)