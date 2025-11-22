
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

        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);  

        printf("Number of tokens are : %d\n",iCount);
 

        printf("Tokens no 1 : %s\n",Command[0]);
        printf("Tokens no 2 : %s\n",Command[1]);
        printf("Tokens no 3 : %s\n",Command[2]);
        printf("Tokens no 4 : %s\n",Command[3]);

    return 0;
} //End of main