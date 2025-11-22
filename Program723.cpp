///////////////////////////////////////////////////////////////////////
//
//  Header files inclusion
//
///////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include<iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////
//
//  User defined Macros
//
///////////////////////////////////////////////////////////////////////

//Max filesize
//Maximum number of files that we can  open
//Maximum number of files that we can create


# define MAXFILESIZE 100                
# define MAXINODE 5                     
# define MAXOPENEDFILES 20              

# define READ 1
# define WRITE 2
# define EXECUTE 4

# define REGULARFILE 1
# define SPECIALFILE 2

# define START 0
# define CURRENT 1
# define END 2


# define EXECUTE_SUCCESS 0

///////////////////////////////////////////////////////////////////////
//
//  User defined Macros for error handling
//
///////////////////////////////////////////////////////////////////////

# define ERR_INVALID_PARAMETER -1
# define ERR_NO_INODES -2
# define ERR_FILE_ALREADY_EXIST -3
# define ERR_FILE_NOT_EXIST -4
# define ERR_PERMISSION_DENIED -5
# define ERR_INSUFFICIENT_SPACE -6

///////////////////////////////////////////////////////////////////////
//
//  User defined Macros 
//
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock 
//  Description :       Holds information to boot the operating system
//
///////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

///////////////////////////////////////////////////////////////////////
//
//  Structure Name :    SuperBlock 
//  Description :       Holds information about the file system
//
///////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

///////////////////////////////////////////////////////////////////////
//
//  Structure Name :    Inode 
//  Description :       Holds information about the file
// 
///////////////////////////////////////////////////////////////////////

typedef struct Inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int LinkCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
}INODE, *PINODE, **PPINODE;

///////////////////////////////////////////////////////////////////////
//
//  Structure Name :    FileTable 
//  Description :       Holds information about the opened file
// 
///////////////////////////////////////////////////////////////////////

typedef struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Count;
    int Mode;
    PINODE ptrinode;
}FILETABLE, *PFILETABLE;

///////////////////////////////////////////////////////////////////////
//
//  Structure Name :    UAREA 
//  Description :       Holds information about the process
// 
///////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXOPENEDFILES];
};

///////////////////////////////////////////////////////////////////////
//
//  Global variables or objects used in the project
// 
///////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
PINODE head = NULL;
UAREA uareaobj;

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseUAREA
//  Description :       It is used to intialise the contents UAREA
//  Author :            Chaitanya Prakash nawade
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0;

    while(i < MAXINODE)
    {
        uareaobj.UFDT[i] = NULL;
        i++;
    }
    cout<<"Marvellous CVFS : UAREA initialised succesfully\n";
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseSuperblock
//  Description :       It is used to intialise the contents of super block
//  Author :            Chaitanya Prakash nawade
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////

void InitialiseSuperblock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    cout<<"Marvellous CVFS : Superblock initialised succesfully\n";
}


///////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateDILB
//  Description :       It is used to create Linked List of Inodes
//  Author :            Chaitanya Prakash nawade
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i <= MAXINODE)
    {
        newn = new INODE;

        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->LinkCount = 0;
        newn->Permission = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp->next = newn;
            temp = temp->next;
        }

        i++;
    }

    cout<<"Marvellous CVFS : DILB created succesfully\n";
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     StartAuxilaryDataInitialisation
//  Description :       It is used to intialise the Auxilary data
//  Author :            Chaitanya Prakash nawade
//  Date :              10/08/2025
//
///////////////////////////////////////////////////////////////////////

void StartAuxilaryDataInitialisation()
{

    strcpy(bootobj.Information,"Boot process of Opertaing System done");

    cout<<bootobj.Information<<"\n";

    InitialiseSuperblock();

    CreateDILB();

    InitialiseUAREA();
    
    cout<<"Marvellous CVFS : Auxilary data initalised succesfully\n";
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     DisplayHelp
//  Description :       It is used to Display the information about commands
//  Author :            Chaitanya Prakash nawade
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("---------------------------------------------------------\n");
    printf("----------- Command Manual of Marvellous CVFS -----------\n");
    printf("---------------------------------------------------------\n");


    printf("exit : It is used to terminate the shell of Marvellous CVFS\n");
    printf("clear : It is used to clear the console of Marvellous CVFS\n");
    printf("Clear : It is used to Create new regular filr\n");
    printf("Creat : It is used to create new regular file\n");
    printf("Unlink: It is used to delete existing ");
    printf("stat : It is used to display statisteical informatio about file\n");
    printf("ls : It is used to list to all file from the directory \n");
    printf("write : It is usef to write the data into the file\n");


    // Add more options here

    printf("---------------------------------------------------------\n");
}


///////////////////////////////////////////////////////////////////////
//
//  Function Name :     ManPage
//  Description :       It is used to Display the manual page of the command
//  Input :             It accepts the command name
//  Output :            Displays the manual details of the command
//  Author :            Chaitanya Prakash nawade
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////

void ManPage(
                char *name      // Name of command
            )
{
    if(strcmp(name,"creat") == 0)
    {
        printf("Description : This command is used to create new regular file on our file system\n");

        printf("Usage : creat File_name Permissions\n");
        printf("File_name : The name of file that you want to create\n");
        printf("Permissions : \n1 : Read \n2 : Write \n3 : Read + Write\n");
    }

    
     else   if(strcmp(name,"Unlink") == 0)
    {
        printf("Description : This command is used to delete new regular file from our file system\n");

        printf("Usage : Unlink File_name Permissions\n");
        printf("File_name : The name of file that you want to create\n");
        printf("Permissions : \n1 : Read \n2 : Write \n3 : Read + Write\n");
    }
    else if(strcmp(name,"exit") == 0)
    {
        printf("Description : This command is used to terminate the Marvellous CVFS\n");

        printf("Usage : exit\n");     
    }

     else   if(strcmp(name,"stat") == 0)
    {
        printf("Description : This command is used to display  statistical informatioin file \n");

        printf("Usage : stat File_name Permissions\n");
        printf("File_name : The name of whose information you  want to display\n");
        printf("Permissions : \n1 : Read \n2 : Write \n3 : Read + Write\n");
    }


     else   if(strcmp(name,"ls") == 0)
    {
        printf("Description : This command is used to list all file naem  from directory\n");

        printf("Usage : ls File_name Permissions\n");
    }

    else if(strcmp(name,"write")== 0)
    {
        printf("Description : This command is used to write the data into the file\n");

        printf("Usage : write File_name Permissions\n");
    }
    // Add more options here
    else
    {
        printf("No manual entry for %s\n",name);
    }
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     IsFileExists
//  Description :       It is used to check whether the given file name is exist or not
//  Input :             It accepts the file name
//  Output :            It returns boolean value (True : if present False : if not present)
//  Author :            Chaitanya Prakash nawade
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////

bool IsFileExists(
                    char *name  // Name of file that we want to check
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name, temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }

        temp = temp->next;
    }

    return bFlag;
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateFile
//  Description :       It is used to create a new regular file
//  Input :             It accepts the file name and permission
//  Output :            It returns the file descriptor
//  Author :            Chaitanya Prakash nawade
//  Date :              11/08/2025
//
///////////////////////////////////////////////////////////////////////

int CreateFile(
                char *name,         // Name of file
                int permission      // Permission to create file
            )
{
    PINODE temp = head;
    int i = 0;

    printf("Current Inodes remaining : %d\n",superobj.FreeInodes);
    // Filters

    // If file name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If entered permission is invalid
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Check whether empty inode is there or not
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }
    
    // Check whether file is already exist or not
    if(IsFileExists(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Loop to search free Inode
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp -> next;
    }

    // Inode not found
    if(temp == NULL)
    {
        printf("Inode not found\n");
        return ERR_NO_INODES;
    }

    // Search first non NULL value from UFDT
    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    if(i == MAXINODE)
    {
        printf("Unable to create file as MAX OPENED FILE LIMIT REACHED\n");
        return -1;
    }

    // Allocate ememory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initailise elements of File table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Count = 1;
    uareaobj.UFDT[i]->Mode = permission;
    
    // Connect file table with IIT
    uareaobj.UFDT[i]->ptrinode = temp;
    
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName, name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->LinkCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate memory for Buffer

    uareaobj.UFDT[i]->ptrinode->Buffer = (char * )malloc(MAXFILESIZE);

    //Decrement the free Inodes
    superobj.FreeInodes--;
    return i;
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     UnlinkFile
//  Description :       It is used to Delete a new regular file
//  Input :             It accepts the file name and 
//  Output :            It returns nothing
//  Author :            Chaitanya Prakash nawade
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////


int UnlikFile(
                char *name  //Name of file
              )
{

        int i = 0;
        if (name == NULL)
        {
            return ERR_INVALID_PARAMETER;
        }


        if(IsFileExists(name) == false)
        {
            return ERR_FILE_NOT_EXIST -4;
        }
       

        for(i = 0; i < MAXINODE ; i++)
        {
            if(uareaobj.UFDT[i] != NULL)
            {
                if(strcmp (uareaobj.UFDT[i]->ptrinode->FileName,name) == 0)
                {
                    //Deallocate the memory of buffer
                    free(uareaobj.UFDT[i]->ptrinode->Buffer);

                    //Reset all values of Inodes
                    uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                    uareaobj.UFDT[i]->ptrinode->LinkCount = 0;
                    uareaobj.UFDT[i]->ptrinode->Permission = 0;
                    uareaobj.UFDT[i]->ptrinode->FileType = 0;
                    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;

                    //Deallocate memeory of file table 
                    free(uareaobj.UFDT[i] = NULL);

                    //Ncrement the valie of free inodes
                    superobj.FreeInodes++;

                    break;
                }
            }
        }

        return EXECUTE_SUCCESS;
}


///////////////////////////////////////////////////////////////////////
//
//  Function Name :     Ls_file
//  Description :       It is used to Display the information about all fiiles in the direactory 
//  Input :             Nothing
//  Output :            Nothing
//  Author :            Chaitanya Prakash nawade
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////

//Marvellou

void ls_file()
{
    PINODE temp = head;

    while(temp != NULL)
    {
        if(temp ->FileType != 0)
        {
            printf("%s \n",temp->FileName);
        }

        temp = temp->next;
    }
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     stat_file
//  Description :       It is used to Display the information about the given file
//  Input :             File name
//  Output :            Nothing
//  Author :            Chaitanya Prakash nawade
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////

int stat_file(
                char *name  //Name of file
              )
{

        PINODE temp = head;

        if (name == NULL)
        {
            return ERR_INVALID_PARAMETER;
        }


        if(IsFileExists(name) == false)
        {
            return ERR_FILE_NOT_EXIST ;
        }


        while(temp != NULL)
        {
            if((strcmp(name,temp->FileName)== 0)&& (temp ->FileType != 0))
            {
                printf("_____________-Statistical information of file___________________________\n");
                printf("File name ; %s\n",temp->FileName);
                printf("File Size  on Disk : %d\n",temp->FileSize);
                printf("Actual  file Size: %d\n",temp->ActualFileSize);
                printf("Link Count\n");
                printf("File permission\n");
                if(temp ->Permission == READ)
                {
                    printf("Read\n");
                }
                else if(temp ->Permission == WRITE)
                {
                    printf("Writte\n");
                }
                else if(temp ->Permission == READ + WRITE)
                {
                    printf("Read + Write\n");
                }
                printf("File Type :\n");

                if(temp ->FileType == REGULARFILE)
                {
                    printf("Regular file\n");
                }

                else if(temp ->FileType == SPECIALFILE)
                {
                    printf("Special file\n");
                }
                printf("___________________________________________________________________________");
            }
            temp = temp ->next;
        }

        return EXECUTE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////
//
//  Function Name :     write_file
//  Description :       It is used to write the contents into  the file
//  Input :             File descriptor
//  Input :             Adderess of buffe whihc contains data
//  Input :             Size of data that we want to write
//  Output :            Number of bytes successfully written into the file
//  Author :            Chaitanya Prakash nawade
//  Date :              15/08/2025
//
///////////////////////////////////////////////////////////////////////

int write_file(
                int fd, // File Descriptor of file
                char *data, //Data that we want to write
                int size   //size of data that we want to write
            )
{
    unsigned long int offset = 0;
    printf("File descriptor is : %d\n",fd);
    printf("Data that we want towrite : %s\n",data);
    printf("Number of bytes that we want to write : %d\n",size);

    //Invalid value of fd
    if(fd < 0 || fd > MAXOPENEDFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    //File is not opened or created with the given fd
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    //If there is no permission to write the data into the file
    if(uareaobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    //Unable to weite there is no sufficeint space
    if((MAXFILESIZE - uareaobj.UFDT[fd] ->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }       

    ///////////////////////////////////
    offset = uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset;

   // (offset,data,size);

    strcpy(uareaobj.UFDT[fd]->WriteOffset = uareaobj.UFDT[fd]->WriteOffset + size);

    //Update the actual size of file after writtong the new data
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return size;
}

///////////////////////////////////////////////////////////////////////
//
//  Entry point function of project (main)
//
///////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    int iCount = 0;
    int iRet = 0;
    char Command[5][80];
    char InputBuffer[MAXFILESIZE] = {'\0'};

    StartAuxilaryDataInitialisation();

    cout<<"---------------------------------------------------------\n";
    cout<<"--------- Marvellous CVFS Started Succesfully ------------\n";
    cout<<"----------------------------------------------------------\n";
    
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");
        printf("\nMarvellous CVFS > ");
        fgets(str,sizeof(str),stdin);

        iCount = sscanf(str,"%s %s %s %s",Command[0],Command[1], Command[2], Command[3]);

        if(iCount == 1)
        {
            // Marvellous CVFS > exit

            if(strcmp(Command[0], "exit") == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all resources...\n");

                break;
            }

            // Marvellous CVFS > help
            
            else if(strcmp(Command[0], "help") == 0)
            {
                DisplayHelp();
            }

            // Marvellous CVFS > clear

            else if(strcmp(Command[0], "clear") == 0)
            {
                system("clear");
            }

            else if(strcmp(Command[0],"ls") == 0)
            {
                ls_file();
            }

            else
            {
                printf("Coomand not found...\n");
                printf("Please refer Help option or use man command\n");
            }
        }   // End of if iCount == 1

        else if(iCount == 2)
        {
            // Marvellous CVFS > man creat

            if(strcmp(Command[0],"man") == 0)
            {
                ManPage(Command[1]);
            }

            else if(strcmp(Command[0],"Unlink") == 0)
            {
                iRet = UnlikFile(Command[1]);

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("Unlink operation is successfully performed\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Unable to dounlink s as file is not present");
                }
                else if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
            }

            else if(strcmp(Command[0],"stat") == 0)
            {
                iRet = stat_file(Command[1]);

                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Unable to do dispaly statistics as file is not present");
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
            }

            else if(strcmp(Command[0],"write")== 0)
            {
                printf("Please enter the data that you want to write into the file\n");
                scanf("%[^'\n']s",InputBuffer);

                iRet = write_file(atoi(Command[1]),InputBuffer,strlen(InputBuffer));

                if(iRet  == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Insufficient space in the data block for the file\n");
                }

                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no jpermission\n");
                }

                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Coomand not found...\n");
                    printf("Please refer Help option or use man command\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : FD is invalid\n");
                }
                else
                {
                    printf("%d bytes gets succrssfully written into the file\n",iRet);
                    printf("DAta from file is : %d\n",uareaobj.UFDT[0]->ptrinode->Buffer);
                }
            }

            else
            {
                printf("Coomand not found...\n");
                printf("Please refer Help option or use man command\n");
             }
        }   // End of if iCount == 2
        
        else if(iCount == 3)
        {
            // Marvellous CVFS > creat Ganesh.txt 3

            if(strcmp(Command[0], "creat") == 0)
            {
                iRet = CreateFile(Command[1], atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parameters for the function\n");
                    printf("Please check Man page for more details\n");
                }
                else if(iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create file as there is no Inodes\n");
                }
                else if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file as file is already existing\n");
                }
                else
                {
                    printf("File is succesfully created with FD : %d\n",iRet);
                }

            }

                else
                {
                   printf("Coomand not found...\n");
                   printf("Please refer Help option or use man command\n");
                }

        }   // End of if iCount == 3
        
        else if(iCount == 4)
        {

        }   // End of if iCount == 4
        
        else
        {
            printf("Coomand not found...\n");
            printf("Please refer Help option or use man command\n");
        }   // End of invalid command part

    }   // End of while (Custom Shell)

    return 0;
}   // End of main