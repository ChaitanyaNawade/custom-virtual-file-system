
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<unistd.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//
//Entry point function of project (main)
//
///////////////////////////////////////////////////////////////////////////////



int main()
{
    char str[80] = {'\0'};
    int iCount = 0;
    char Command[4][80];


    cout<<"______________________________________________________________________________________________\n";
    cout<<"______________________________Marvellous CVFS Started Successfully____________________________\n";
    cout<<"______________________________________________________________________________________________\n";


 
        printf("\nMarvellous CVFS>");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s,Cpmmand{0}");  

        printf("Number of tokens are : %d\n",iCount);
 

    return 0;
} //End of main