CC = g++

TARGET = wavy

$(TARGET): $(TARGET).cpp
	$(CC) $(TARGET).cpp -o $(TARGET)