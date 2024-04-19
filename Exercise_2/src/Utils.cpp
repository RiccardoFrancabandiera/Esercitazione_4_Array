#include "iostream"
#include "fstream"
#include "sstream"
#include "iomanip"
#include "Utils.hpp"

using namespace std;

bool ImportVectors(const string& inputFileName,
                   double& S,
                   size_t& n,
                   double*& w,
                   double*& r)
{   //Open input file
    ifstream file;
    file.open(inputFileName);

    if (file.fail())
    {
        cerr << "Failed input file opening" << endl;
        return false;
    }
    // Getting S and n values
    string line;

    getline(file,line);
    char a;
    istringstream string1(line);
    string1 >> a >> a >> S;

    getline(file, line);
    char b;
    istringstream string2(line);
    string2 >> b >> b >> n;

    // Getting rid of the line w;r
    getline(file,line);

    w = new double[n];
    r = new double[n];
    int i = 0;
    //Getting the arrays w and r from the other lines
    while (getline(file, line))
    {
        istringstream string3(line);
        char c;
        string3 >> w[i] >> c >> r[i];

        i++;
    }
    //Close input file
    file.close();

    return true;
}


double DotProduct(const size_t& n,
                  const double* const& w,
                  const double* const& r)
{
    double dotProduct = 0;
    for (unsigned int i = 0; i < n; i++)
        dotProduct += w[i] * r[i];

    return dotProduct;
}

string ArrayToString(const size_t& n,
                     const double* const& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << " ]";

    return toString.str();
}


bool ExportResult(const string& outputFileName,
                  const double& S,
                  const size_t& n,
                  const double* const& w,
                  const double* const& r,
                  const double& dotProduct)
{
    ofstream file;
    file.open(outputFileName); //Open output file

    if (file.fail())
    {
        cerr << "Failed output file opening" << endl;
        return false;
    }

    file << "S = " << fixed << setprecision(2) <<  S << "," << "n = " << n << endl;

    file << "w = " << ArrayToString(n, w) << endl;
    file << "r = " << ArrayToString(n, r) << endl;

    file << setprecision(4) << "Rate of return of the portfolio: " << dotProduct << endl;
    file << "V: " << setprecision(2) << (1+ dotProduct)*S << endl;

    // Close output file
    file.close();

    return true;
}

