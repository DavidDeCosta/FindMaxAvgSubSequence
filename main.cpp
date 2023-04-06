#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

//=========================================================PROTOTYPES ==========================================================================================
void findMaxSubBruteForce(const vector<double>& vec, int k, double& max_avg, int& beginingIndex, int& endIndex);
void divideAndConq(const vector<double>& vec, int k, double& max_avg, int start_idx, int end_idx, int& max_start_idx, int& max_end_idx);
void findMiddle(const vector<double>& vec, int k, int startIndex, int endIndex, int midIndex,double &maxMiddleAvg, int &maxMiddleStartIndex,int &maxMiddleEndIndex);
void displayTheSequence(const vector<double>& vec, int k, double maximumAvg, int startIndex, int endIndex);


int main(int argc, char *argv[])     //argc is the number of arguments passed to the program and argv is an array of pointers to the arguments
{
    
    vector<double> vec;                                     //vector to store the elements of the input file
    double maximumAvg =-1;                                     //maximum average of the subarray
    int startIndex = 0;                                       //start index of the subarray to be printed

    if(argc !=4)
    {
        cout << "Not enough arguments \n";
        return 1;
    }

    string input_file = argv[1];        //input file name
    int k = atoi(argv[2]);             //convert the string to an integer  k is the size of the subarray
    string option = argv[3];           //Brute Force or Divide and Conquer


    ifstream inputFile(input_file);                    //open the input file
    if(inputFile.is_open())
    {
        int numOfElementsInFile;                                 //number of elements in the input file
        inputFile >> numOfElementsInFile;                       //get the number of elements in the file
        
        for(int i = 0; i <= numOfElementsInFile; i++)           //read the numbers of the input file and put them in the vector
        {
            double number;                              
            inputFile >> number;                         //get the number
            vec.push_back(number);                      //add the number to the vector
        }
        inputFile.close();                              
    }
    else
    {
        cout << "Unable to open file" << endl;
        return 1;
    }


    int startIndexForSubArrays = 0;                         //start index of the subarray that has the max average
    int endIndexForSubArrays = 0;                           //end index of the subarray that has the max average
    for (int n = 100000; n <= 1000000; n += 100000)         //n is the size of the vector
    {
        vector<double> subVec(vec.begin(), vec.begin() + n);      //subVec is a vector that contains the first n elements of the vector vec
        int endIndex = subVec.size()-1;                             //end index of the subarray to be printed

        if(option == "-b")
        {
            auto start = high_resolution_clock::now();   //start the timer
            findMaxSubBruteForce(subVec, k, maximumAvg, startIndex, endIndex);  //call the function to find the maximum average subarray
            auto end = high_resolution_clock::now();   //end the timer
            auto duration = duration_cast<chrono::milliseconds>(end - start).count();  //calculate the running time
            cout << "Running time for Brute Force: "  << duration << " ms" << endl;  //print the running time
            displayTheSequence(subVec, k, maximumAvg, startIndex, endIndex);  //print the subarray that has the max average
            maximumAvg =-1;                                     
            startIndex = 0;  
            startIndexForSubArrays = 0;
            endIndexForSubArrays = 0;
        }
        else if(option == "-d")
        {
            auto start = high_resolution_clock::now();  //start the timer   
            divideAndConq(subVec, k, maximumAvg, startIndex, endIndex, startIndexForSubArrays, endIndexForSubArrays); //call the function to find the maximum average subarray
            auto end = high_resolution_clock::now(); //end the timer
            auto duration = duration_cast<chrono::milliseconds>(end - start).count(); //calculate the running time
            cout << "Running time for Divide and Conquer: "<< duration << " ms" << endl; //print the running time
            displayTheSequence(subVec, k, maximumAvg, startIndexForSubArrays, endIndexForSubArrays); //print the subarray that has the max average
            maximumAvg =-1;                                     
            startIndex = 0;
            startIndexForSubArrays = 0;
            endIndexForSubArrays = 0;
        }
        else
        {
            cout << "Invalid option" << endl;
            return 1;
        }
    }

    return 0;
}


//this function disays the sequence that has the max average    
void displayTheSequence(const vector<double>& vec, int k, double maximumAvg, int startIndex, int endIndex)
{
    int n = vec.size();
    cout << "n: " << n << endl;
    cout << "The max avg subsequence with a size of (k= " << k << ") is: \n";
    for (int i = startIndex; i <= endIndex; i++) 
    {
        if(i == endIndex)   //so that there is no comma after the last element
        {
            cout << vec[i];
        }
        else
        {
            cout << vec[i] << ", ";
        }
    }
    cout << "\n";
    cout << "with a Average of:  " << maximumAvg << "\n";
    cout << "begining at index:  " << startIndex << " and ending at index:  " << endIndex << "\n\n";
    
}


// Function to find the maximum average subarray of size k in the vector vec
void findMaxSubBruteForce(const vector<double>& vec, int k, double& maximumAvg, int& beginingIndex, int& endIndex)   //k is the size for each subarray
{                                                                                       
    int n = vec.size();
    for (int i = 0; i <= n-k; i++)               //n-k is the start index of the last subarray because the last subarray will have n-k numbers
    {
        double sum = 0;                               // sum of the elements in the subarray, reset to 0 for each subarray
        for (int j = i; j < i+k; j++)                       //i+k because the last element of the subarray is i+k-1
        {
            sum += vec[j];                                   //add the elements of the subarray
        }
        double avg = sum / k;                                    //calculate the average of the subarray
        if (avg > maximumAvg)                                                      
        {
            maximumAvg = avg;                          //update the max average if the current average is greater than the max average
            beginingIndex = i;                         //update the start index of the  subarray that has the max average
            endIndex = i+k-1;                           //update the end index of the subarray that has the max average
        } 
    }
}


/*Input:
        k                   : is the size of the subarray
        startIdx            : is the start index of the array
        endIdx              : is the end index of the array
        maxAvg              : is the maximum average of the array
        indexOfMaxSubStart  : is the start index of the subarray that has the max average
        indexOfMaxSubEnd    : is the end index of the subarray that has the max average
    Output:
        maxAvg, startIndexOfMaxsub, endIndexOfMaxSub
*/
void divideAndConq(const vector<double>& vec, int k,  double& maxAvg, int startIndex, int endIndex, int& indexOfMaxSubStart, int& indexOfMaxSubEnd) 
{
    if (endIndex - startIndex + 1 <= k) // base case: array size is less than or equal to k this finds the average of the subarray with each function call
    {
        double sum = 0;                                     // sum of the elements in the subarray, reset to 0 for each subarray
        for (int i = startIndex; i <= endIndex; i++)           
        {
            sum += vec[i];                                 //add the elements of the subarray
        }
        double avg = sum / (endIndex - startIndex + 1);             //calculate the average of the subarray
        if (avg > maxAvg)
        {
            maxAvg = avg;                                   //update the max average if the current average is greater than the max average
            indexOfMaxSubStart = startIndex;           //update the start index of the  subarray that has the max average
            indexOfMaxSubEnd = endIndex;                //update the end index of the subarray that has the max average
        }
        return;                                     //return to the previous function call
    }

    double maxLeftAvg = -1;     
    double maxRightAvg = -1; 
    int maxLeftStartIndex=0;   //start index of the subarray that has the max average in the left subarray
    int maxLeftEndIndex=0;  
    int maxRightStartIndex=0;
    int maxRightEndIdx=0;

    int midIndex = (startIndex + endIndex) / 2;     //midIdx is the middle index of the subarray

    double maxMiddleAvg = -1;
    int maxMiddleStartIndex = 0;
    int maxMiddleEndIndex = 0;
    findMiddle(vec,k, startIndex,endIndex,midIndex, maxMiddleAvg, maxMiddleStartIndex, maxMiddleEndIndex);  //find the max average of the middle subarray
    divideAndConq(vec, k, maxLeftAvg, startIndex, midIndex, maxLeftStartIndex, maxLeftEndIndex);    //find the max average of the left subarray and update the start and end indexes of the subarray that has the max average
    divideAndConq(vec, k,maxRightAvg ,midIndex + 1, endIndex, maxRightStartIndex, maxRightEndIdx);  //find the max average of the right subarray
    if (maxLeftAvg >= maxRightAvg && maxLeftAvg >= maxMiddleAvg)    
    {
        maxAvg = maxLeftAvg;
        indexOfMaxSubStart = maxLeftStartIndex;
        indexOfMaxSubEnd = maxLeftEndIndex;

    } 
    else if (maxRightAvg >= maxLeftAvg && maxRightAvg >= maxMiddleAvg) 
    {
        maxAvg = maxRightAvg;
        indexOfMaxSubStart = maxRightStartIndex;
        indexOfMaxSubEnd = maxRightEndIdx;
    } 
    else 
    {
        maxAvg = maxMiddleAvg;
        indexOfMaxSubStart = maxMiddleStartIndex;
        indexOfMaxSubEnd = maxMiddleEndIndex;
    }
}


void findMiddle(const vector<double>& vec, int k, int startIndex, int endIndex, int midIndex,double &maxMiddleAvg, int &maxMiddleStartIndex,int &maxMiddleEndIndex)   //k is the size for each subarray
{                                                                                       
    for (int i = midIndex;( i >= startIndex) && (i > midIndex - k); i--) //i is the start index of the subarray and it goes from the middle index to the start index
    {
        for (int j = midIndex + 1; j <= endIndex && j < midIndex + 1 + k; j++) //j is the end index of the subarray and it goes from the middle index to the end index
        {
            int subarraySize = j - i + 1;           //size of the subarray is j- i + 1 because the last element of the subarray is j and the first element is i
            if (subarraySize >= k)                  //if the size of the subarray is greater than or equal to k meaning that the subarray is valid
            {
                double sum = 0;
                for (int l = i; l <= j; l++)      //add the elements of the subarray
                {
                    sum += vec[l];
                }
                double avg = sum / subarraySize;           //calculate the average of the subarray
                if (avg > maxMiddleAvg)                   
                {
                    maxMiddleAvg = avg;                   //update the max average if the current average is greater than the max average
                    maxMiddleStartIndex = i;              //update the start index of the  subarray that has the max average
                    maxMiddleEndIndex = j;                //update the end index of the subarray that has the max average
                }
            }
        }
    }
}