const int size = 10;

class RollingAve
{
private:
    long pastReadings[size];
    int index = 0;
    bool firstReading;

public:
    RollingAve()
    {
        index = 0;
        firstReading = true;
    }

    void reading(long value)
    {
        if (firstReading)
        {
            for (int i = 0; i < size; i++)
            {
                pastReadings[i] = value;
            }
            firstReading = false;
        }

        pastReadings[index] = value;
        index = (index + 1) % 10;
    }

    long getAvg()
    {
        long sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += pastReadings[i];
        }

        return sum / size;
    }
};