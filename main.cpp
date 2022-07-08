#include <iostream>
#include <fstream>
using namespace std;

// function to get input from file
void getFromFile(ifstream &, int *, int *, int);
// function to get maximize profit
void maximizeProfit(int, int *, int *, int);

int main()
{
    int *revenue = nullptr, *units = nullptr;
    int num, limit;

    // open input.txt file
    ifstream fin;
    fin.open("input.txt");
    if (!fin.fail())
    {
        // get the data
        fin >> limit;
        fin >> num;
        revenue = new int[num]; // making an array based on number of clients
        units = new int[num];
        // store info in the arrays
        getFromFile(fin, revenue, units, num);
        // calculate maximimum profit
        maximizeProfit(limit, revenue, units, num);
        cout << "Sucess! \n";
        // close the file
        fin.close();
    }
    else
    {
        cout << "Unable to open the file\n";
    }
    return 0;
}

void getFromFile(ifstream &fin, int *revenue, int *units, int num)
{
    int i = 0;
    int dummyRevenue, dummyUnits;
    while (i < num)
    {
        fin >> dummyRevenue;
        revenue[i] = dummyRevenue;
        fin.ignore();
        fin >> dummyUnits;
        units[i] = dummyUnits;
        i++;
    }
}

void maximizeProfit(int limit, int *revenue, int *units, int num)
{
    ofstream fout;
    fout.open("output.txt");
    int profit = 0, dummyUnits = 0, dummyRevenue = 0;
    int indicator = 0, subIndicator = 0;
    for (int i = 0; i < num; i++)
    {
        if (dummyUnits <= limit)
        {
            indicator++;
            dummyUnits = dummyUnits + units[i];
            if (indicator == 1 && dummyUnits > limit)
            {
                dummyUnits = 0;
                subIndicator = indicator;
            }
            dummyRevenue = dummyRevenue + revenue[i];
        }
    }
    if (!fout.fail())
    {
        if (dummyUnits > limit)
        {
            profit = (110 * (dummyUnits - limit)) / (100 * 100);
            fout << "1" << endl;
            fout << indicator - 1 << "," << dummyUnits - limit << endl;
            for (int i = 0; i < num; i++)
            {
                if (i != indicator - 1)
                {
                    fout << i << endl;
                }
            }
        }
        else // if your client's bandwidth match your limit
        {
            fout << "0" << endl;
            fout << indicator << endl;
            for (int i = 0; i < num; i++)
            {
                fout << i << endl;
            }
        }

        // close the file
        fout.close();
    }
    else
    {
        cout << "Unable to open the file\n";
        return;
    }
}
