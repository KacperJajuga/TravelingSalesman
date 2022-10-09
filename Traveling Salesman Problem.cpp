//Kacper Jajuga, grupa: D2, kierunek: informatyka (PUW), rok I, semestr II
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#define matrixSize 16 //constant numer signifying size of the matrix

using namespace std;

bool readingData(int arr[][matrixSize], string arr_cities[], int r);
int settingStartingCity(int starting_city, int r);
int shortestDistanceToNextCity(int arr[][matrixSize], int r, bool visited[], int &curr_city, vector <int> &vect);

int main()
{
    int D[matrixSize][matrixSize], L, city_start, current_city;
    vector <int> vecto;
    bool visited_cities[matrixSize], check;
    string cities[matrixSize] = {"Bial","Bydg","Gdan","Gorz","Kato","Kiel","Krak","Lubl","Lodz","Olsz","Opol","Pozn","Rzesz","Szcz","Warsz","Wroc"};
    char next;
    do
    {
        L = 0;
        if (next == 'Y' || next == 'y')
        {
            vecto.erase(vecto.begin(), vecto.end());
        }
        check = readingData(D, cities, matrixSize); //readingData function returns value 1, when reading data from file fails, otherwise returns 0
        if(check == 1)  //checking what value was returned by readingData function , if it's 0, then ignore if
        {
            return 1;   //if returned value equals 1 then end the program because there was no data imported
        }

        city_start = settingStartingCity(city_start, matrixSize); //settingStartingCity function asks for a city number from which we start calculations

        current_city = city_start-1;   //decrease value of current_city by one because I am using two-dimensional array and elements are being counted from 0

        for (int i = 0; i < matrixSize; i++)
        {
            visited_cities[i] = false; //in this loop I set every value in the arr visited_cities to false, to make sure no unwanted values appear
        }

        visited_cities[current_city] = true;  //setting value in visited_cities[current_city] to true so program knows it has already been visited and won't travel to itself, creating an infinite loop
        vecto.push_back(city_start);  //add the city number to vector

        for (int i = 0; i < matrixSize; i++)
        {
            L += shortestDistanceToNextCity(D, matrixSize, visited_cities, current_city, vecto); //this function returns shortest distance to the city in which we are currently in and sum it invariable L
        }

        cout << "Total traveled distance: " << L << endl;
        cout << "Numbers of traveled city: ";
        for (int i = 0; i <= matrixSize; i++)
        {
            cout << vecto[i] << " ";  //printing next city we traveled through
        }
        cout << "\nNames of visited cities: ";
        for (int i = 0; i <= matrixSize; i++)
        {
            cout << cities[vecto[i]-1]  << " ";
        }
        cout << "\nDo you want to check the way when starting from different city? (Y/N)" << endl;
        cin >> next;
    }
    while(next=='y'||next=='Y');
    return 0;
}

bool readingData(int arr[][matrixSize], string arr_cities[], int r)
{
    ifstream readingFile("data.txt");
    if(readingFile.is_open() == false)
    {
        cout << "File was not opened. Check whether the file named ''data.txt'' is located in the folder containing the program and run it again." << endl;
        return 1; //returning value 1 when file was not opened. It will let the program know to terminate because there is not data to work with
    }
    else //instructions in else will gather data from the file and print it in console
    {
        cout <<"      ";
        for (int i=0; i < matrixSize; i++)
        {
            cout << setw(6) << arr_cities[i];
        }
        cout << endl;
        cout << "      ________________________________________________________________________________________________";
        cout << endl;
        for (int i=0; i < matrixSize; i++)
        {
            for (int j=0; j < matrixSize; j++)
            {
                if (j%(matrixSize-1)==0 && j!=(matrixSize-1))
                {
                    cout << setw(5) << arr_cities[i] << "|";
                }
                readingFile >> arr[i][j];
                cout << setw(5) << arr[i][j] << " ";
                if (j%(matrixSize-1)==0 && j!=0)
                {
                    cout << endl;
                }
            }
        }
        readingFile.close();
        return 0;
    }
}

int settingStartingCity(int starting_city, int r)
{
    do
    {
        cout << "\nEnter the number of a starting city: ";
        cin >> starting_city;
        if (starting_city <= 0 || starting_city > r) //checking whether the entered number was correct within the range <1, 16>
        {
            cout << "Entered value must be a number within the range <1, 16>" << endl;
        }
    }
    while(starting_city <= 0 || starting_city > r); //instruction in do...while will be executed until number within the range <1, 16> is entered
    return starting_city;
}

int shortestDistanceToNextCity(int arr[][matrixSize], int r, bool visited[], int &curr_city, vector <int> &vect)
{
    bool notOver = 0;
    int temp = 0;

    for(int i = 0; i < r; i++)
    {
        if(visited[i] == false)      //if the cell with index i contains 0 so that city was not visited then...
        {
            notOver = 1;              //... set variable notOver to 1...
            temp = arr[curr_city][i];   //...and set the variable temp to arr[curr_city][i]
            break;                      //end for because one of the value in array is false which is sufficient
        }
    }
    if (notOver == 1) //if at least one city was not visited
    {

        for(int i = 0; i < r; i++)
        {
            if (arr[curr_city][i] < temp && visited[i] == false)  //if distance in cell [curr_city][i] is lower than temp value AND the city [i] was not visited then...
            {
                temp = arr[curr_city][i];                            //...assign this value to temp
            }
        }

        for (int i = 0; i < r; i++)
        {
            if (temp == arr[curr_city][i] && visited[i] == false)    //if temp value equals to distance in cell [curr_city][i] AND the city [i] was not visited then...
            {
                visited[i] = true;                                   //...mark city [i] as visited...
                vect.push_back(i+1);                                     //...insert to the vector number of this visited city...
                curr_city = i;                                          //...and set city [i] as current
            }
        }
    }
    else    //if we visited all cities (notOver is equal to 0) then we return to the city we started from so...
    {
        temp = arr[curr_city][vect[0]-1];    //...to temp assign distance from current city to starting city (that city number is on first place in vector)
        vect.push_back(vect[0]);
    }
    return temp;
}
