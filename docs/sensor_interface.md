## Sensor interface
Sensor readings will be abstracted to minimise the dependency of specific pin configurations. Functions will be defined in `sensors.cpp` which take no arguments and return the value of the sensor, for example:

```cpp
bool readLineSensorLeft()
{
    // Function to read the left line sensor
    // Reads from correct pin and returns boolean
    // HIGH means the line is detected, LOW means no line is detected
    return HIGH
}
```