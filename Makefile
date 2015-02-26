CC = g++

TARGET = wavy

$(TARGET): $(TARGET).cpp pcmwavgen.h wavytypes.h
	$(CC) $(TARGET).cpp -o $(TARGET)