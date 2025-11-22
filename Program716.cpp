////////////////////////////////////////////////////////////////////////////////
//
//Header Fiele Inclusion
//
///////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<unistd.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//
//User Defined Macros
//
///////////////////////////////////////////////////////////////////////////////

# define MAXFILESIZE 100
# define MAXINODE 5

# define READ 1
# define WRITE 2
# define EXECUTE 4

# define REGULARFILE 1
# define SPECIALFILE 2

# define START 0
# define CURRENT 1
# define END 2

//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : BootBlock
//Description :   Holds information to boot the operating system
//
//////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};



//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : SuperBlock
//Description :   Holds information about the file system
//
//////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};


//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : Inode
//Description :   Holds information about the file 
//
//////////////////////////////////////////////////////////////////////////////

typedef struct Inode
{
    char Filename[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    int LinkCount;
    char *Buffer;
    struct Inode *next;
}INODE,*PINODE,**PPINODE;



//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : FileTable
//Description :   Holds information about the opened file
//
//////////////////////////////////////////////////////////////////////////////


typedef struct FileTable
{
    int REadOffset;
    int WriteOffset;
    int Count;
    int Mode;
    PINODE ptrinode;

}FILETABLE,*PFILETABLE;


//////////////////////////////////////////////////////////////////////////////
//
//Structre Name : UAREA
//Description :   Holds information about the Process
//
//////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXINODE];
};


//////////////////////////////////////////////////////////////////////////////
//
//Global variables for object used in the projcet
//
//////////////////////////////////////////////////////////////////////////////
SuperBlock superobj;
PINODE head = NULL;
UAREA uareaobj;
BootBlock bootobj;


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : InitialisUAREA
//Description : Ir is used to initiaxlie the contents of super UFDT
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////

void InitialisUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;
     while( i < MAXINODE)
     {
        uareaobj.UFDT[i] = NULL;
        i++;
     }
     cout<<"Marvellos CVFS : UAREAD  Initialized succussfully\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : InitialiseSuperblock
//Description : Ir is used to initialiase the contents of super block
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////

void InitialiseSuperblock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    cout<<"Marvellos CVFS : DILS  created succussfully\n";

}

//////////////////////////////////////////////////////////////////////////////
//
//Function Name : CreateDILB
//Description : It is used to create Linked List of iNODs
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////


void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = new INODE;
        newn ->InodeNumber = i;
        newn ->FileSize = 0;
        newn ->ActualFileSize = 0;
        newn ->LinkCount= 0;
        newn ->Permission = 0;
        newn ->Buffer = NULL;
        newn ->next = NULL;

        if(temp == NULL)
        {
            head  = newn;
            temp = head;
        }
        else 
        {
            temp ->next = newn;
            temp = temp ->next;
        }
        i++;
    }

    cout<<"Marvellos CVFS : CreateDILB data  created succussfully\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : StartAuxillaryDataInitialisation
//Description : It is used to initialise the Auxilarry  data
//Author :       
//Date :
//////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Information,"Boot process of Operating System done\n");

    cout<<bootobj.Information<<"\n";

    CreateDILB();

    InitialiseSuperblock();

    InitialisUAREA();
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name : DisplayHelp
//Description : It is used to Display the information aobut commands
//Author :       
//Date :         11 
//////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("___________________________________________________________________\n");
    printf("______________________Command manual of marvellous CVFS____________\n");
    printf("___________________________________________________________________\n");
;
    printf("It is used to terminate the shell of marvellous CVFS\n");
    printf("It is used to clear the console of marvellous cvfs");

    printf("___________________________________________________________________\n");
}


//////////////////////////////////////////////////////////////////////////////
//
//Function Name :    ManPage
//Description :      It is used to Display the manual page of the commands
//Input :            It Accepts The Command Name
//Output :           Displays the manual details of the command
//Author :       
//Date :             11/08/2025 
//////////////////////////////////////////////////////////////////////////////


void ManPage(char *name)
{
    if(strcmp(name,"creat") == 0)
    {
        printf("Description : This command is used to create new regular file on our file system\n");

        printf("Usage : Create File_Name Permissions\n");
        printf("File_name : the namae of file that you want to create\n");
        printf("Permissions : \n1 : read , \n2 : write , \n3 : read and write\n");
    }
    else if(strcmp(name,"exit") == 0)
    {
        printf("Description : This command is used to terminate Marvellous CVFS\n");

        printf("usage : exit\n");
    }

    //Add more options here
    else 
    {
        printf("No manual entry for %s",name);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//Entry point function of project (main)
//
///////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    int iCount = 0;
    char Command[5][80];

    StartAuxillaryDataInitialisation(); 

    cout<<"______________________________________________________________________________________________\n";
    cout<<"______________________________Marvellous CVFS Started Successfully____________________________\n";
    cout<<"______________________________________________________________________________________________\n";


    while(1)   //shell
    {
        fflush(stdin);

        printf("\nMarvellous CVFS>");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);
        
        if(iCount == 1)
        {
            if(strcmp(Command[0],"exit") == 0)
            {
                printf("thank you for using marvellous CVFS\n");
                printf("Deallocating all resources...\n");

                break;
            }

             //Marvellous CVFS >HELP
            else if(strcmp(Command[0],"Help") == 0)
            {
                DisplayHelp();
            }
           
             //Marvellous CVFS >cls
            else if(strcmp(Command[0],"clear") == 0)
            {
                system("cls");
            }

        }//End of if iCount == 1


        else if(iCount == 2)
        {
            //Marvellous CVFS >Man

            if(strcmp(Command[0],"man") == 0)
            {
                ManPage(Command[1]);
            }
        }//End of if iCount == 2


        else if(iCount == 3)
        {

        }//End of if iCount == 3


        else if(iCount == 4)
        {

        }//End of if iCount == 4


        else
        {
            printf("Command not found\n");
            printf("Please refer Help option or man command\n");
        }//End of invalid command part

    }//End of while(Custom Shell)

    return 0;
} //End of main