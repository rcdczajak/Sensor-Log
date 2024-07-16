#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <filesystem>

// Declaring local variables
using namespace std;
namespace fs = filesystem;

// Function to generate a random number between 0 and 100 to emulate sensor data 
double readSensorData ( ) 
{
    // Generate random number between 0 and 100
    return static_cast <double> (rand ( )) / RAND_MAX * 100.0;
}

// Method responsible for reading, processing, and writing received sensor data to a seperate data file
int main ( ) 
{
    // Declaring class variables
    double sensorData [10];
    double data;

    // Seed the random number generator with the current time
    srand (static_cast <unsigned int> (time (0)));

    try 
    {
        // Get the current directory path
        fs::path currentDir = fs::current_path ( );

        // Create a path to a new SensorData.txt data file
        fs::path filePath = currentDir / "SensorData.txt";

        // If the SensorData.txt file does not exist yet
        if (!fs::exists (filePath))
        {
            // Create the new file
            cout << "New file created: SensorData" << endl;
        }
        // Otherwise if the file already exsists
        else
        {
            // Move on to the data handling
            cout << "File already exists, skipping creation." << endl;
        }

        // Open the SensorData,txt file to write to
        ofstream outFile (filePath);

        // If there is no file to write to
        if (!outFile)
        {
            // Throw an error
            throw runtime_error ("Error opening writing file");
        }

        // Simulate and log sensor data 10 times
        for (int i = 0; i < 10; i++)
        {
            // Read and remember the sensor data
            sensorData [i] = readSensorData ( );
        }

        // Per data the sensor receives
        for (int i = 0; i < sizeof (sensorData) / sizeof (sensorData [0]); i++)
        {
            // Write that individual data to the SensorData.txt file
            outFile << sensorData [i] << endl;
        }

        // Close the SensorData.txt file for writing
        outFile.close ( );

        // Open the SensorData.txt file for reading
        ifstream inFile (filePath);

        // If there is no file to open
        if (!inFile)
        {
            // Throw an error
            throw runtime_error ("Error opening reading file");
        }

        // While there is data currently in the file
        while (inFile >> data)
        {
            // Read the file data and print it to the console
            cout << "Read data: " << data << endl;
        }

    // If anything goes wrong
    } catch (const exception& e)
    {
        // Catch any exceptions thrown and display an error message
        cerr << "An Error Occured: " << e.what ( ) << endl;
        return 1;
    }

    return 0;
}