#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int bitmap[50];
struct finfo
{
    string filename;
    int filesize;
    int pos;
    int fd;
    int mode;
    int status;
};
struct finfo arr[50];
//struct finfo arr2[50];
//struct finfo arr3[50];
void processCommand();
void createDisk(string);
void mountDisk();
void createDisk(string fname)
{
    int X = 500*1000000;
    FILE *fp = fopen(fname.c_str(), "w");
    fseek(fp, X , SEEK_SET);
    fputc('@', fp);
    fclose(fp);
}

void mountDisk(string dname)
{
    FILE* fp=fopen(dname.c_str(),"r+");
    int X=1000000;
    fseek(fp,X,SEEK_SET);
    fread(bitmap,sizeof(int),50,fp);
    fread(arr,sizeof(struct finfo),50,fp);
    /*for(int i=0;i<5;i++)
     cout << arr[i].filename << " " << arr[i].filesize << " " << arr[i].status << endl;
    for(int i=0;i<5;i++)
        cout << bitmap[i] <<"\t";*/
    int choice;
    while(true)
    {
        cout << "Enter choice of operation" << endl;
        cout << "1. Create file" << endl;
        cout << "2. Open file" << endl;
        cout << "3. Read file" << endl;
        cout << "4. Write file" << endl;
        cout << "5. Append file" << endl;
        cout << "6. Close file" << endl;
        cout << "7. Delete file" << endl;
        cout << "8. List all files" << endl;
        cout << "9. List opened files" << endl;
        cout << "10. Unmount Disk" << endl;
        cin >> choice;
        if(choice==1)   //Create file
        {
            string fname;
            cout << "Enter file name" << endl;
            cin >> fname;
            int fpos=-1;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==0)
                {
                    fpos=i;
                    break;
                }
            }
            if(fpos==-1)
                cout << "No space left to create new file" << endl;
            else
                {
                arr[fpos].filename=fname;
                arr[fpos].filesize = 0;
                arr[fpos].mode = 0;
                arr[fpos].pos = fpos;
                arr[fpos].fd=fpos-1;
                arr[fpos].status=0;
                bitmap[fpos]=1;
                cout << "File successfully created with file descriptor " << arr[fpos].fd << endl;
                }
        }
        else if(choice==2)  //Open file
        {
            string fname;
            cout << "Enter file name" << endl;
            cin >> fname;
            int fl=0;
            int choic;
            int gh;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    if(arr[i].filename==fname)
                    {
                        cout << "1. Read Mode" << endl;
                        cout << "2. Write Mode" << endl;
                        cout << "3. Append Mode" << endl;
                        cin >> choic;
                        cout << "Enter file descriptor" << endl;
                        cin >> gh;
                        if(arr[i].fd==gh)
                        {
                        arr[i].mode=choic;
                        arr[i].status=1;
                        fl=1;
                        cout << "File opened successfully" << endl;
                        break;
                        }
                        else
                        {
                        cout << "Wrong file descriptor entered" << endl;
                        fl=1;
                        break;
                        }    
                    }
                }
            }
            if(fl==0)
                cout << "No such file exists" << endl;
        }
        else if(choice==3)  //read file   
        {
            string fname;
            cout << "Enter filename to be read" << endl;
            cin >> fname;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    if(arr[i].filename==fname && arr[i].status==1)
                    {
                        if(arr[i].mode==1)
                        {
                        arr[i].mode=1;
                        arr[i].status=1;
                        int g=arr[i].filesize;
                        int X=i*10*1000000;
                        fseek(fp,X,SEEK_SET);
                        char text[g];
                        fread(text,sizeof(char),g,fp);
                        for(int l=0;l<sizeof(text);l++)
                            cout << text[l];
                        cout << endl << "File Read Successfully" <<endl;
                        break;
                        }
                        else
                        {
                        cout << "File not opened in read mode" << endl;
                        break;
                        }
                    }
                }
            }
        }
        else if(choice==4)  //write file
        {
            string fname;
            cout << "Enter filename to be written" << endl;
            cin >> fname;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    if(arr[i].filename==fname && arr[i].status==1)
                    {
                        if(arr[i].mode==2)
                        {
                        arr[i].mode=2;
                        arr[i].status=1;
                        string str;
                        cin.ignore();
                        getline(cin,str);
                        char content[str.length()];
                        for(int p=0;p<sizeof(content);p++)
                            content[p]=str[p];
                        /*char content[str.size() + 1];
                        strcpy(content, str.c_str());*/
                        arr[i].filesize=str.length();
                        int X = i*10*1000000;
                        fseek(fp, X , SEEK_SET);
                        fwrite(content,sizeof(char),str.length(),fp);
                        cout <<"File written successfully" << endl;
                        break;
                        }
                        else
                        {
                        cout << "File not opened in write mode" << endl;
                        break;
                        }
                    }
                    else if(arr[i].status==0)
                    {
                        cout << "File not opened" << endl;
                        break;
                    }
                }
            }
        }
        else if(choice==5)  //append file
        {
            string fname;
            cout << "Enter filename to be written" << endl;
            cin >> fname;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    if(arr[i].filename==fname && arr[i].status==1)
                    {
                        if(arr[i].mode==3)
                        {
                        arr[i].mode=3;
                        arr[i].status=1;
                        string str;
                        cin.ignore();
                        getline(cin, str);
                        char content[str.length()];
                        for(int p=0;p<sizeof(content);p++)
                            content[p]=str[p];
                        int temp=arr[i].filesize;
                        /*char content[str.size() + 1];
                        strcpy(content, str.c_str());*/
                        int X = i*10*1000000;
                        fseek(fp, X+temp , SEEK_SET);
                        fwrite(content,sizeof(char),str.length(), fp);
                        arr[i].filesize=temp+str.length();
                        cout <<"File appended successfully" << endl;
                        }
                        else
                            cout << "File not opened in append mode" << endl;
                    }
                    else if(arr[i].status==0)
                    {
                        cout << "File not opened" << endl;
                        break;
                    }
                }
            }
        }
        else if(choice==6)  //close file
        {
            string fname;
            cout << "Enter file name" << endl;
            cin >> fname;
            int choic;
            int fl=0;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    if(arr[i].filename==fname)
                    {
                        cout << "Enter file descriptor to close file" << endl;
                        cin >> choic;
                        if(choic!=arr[i].fd)
                            cout << "Wrong file descriptor given" << endl;
                        else
                        {
                        arr[i].status=0;
                        fl=1;
                        cout << "File successfully closed" << endl;
                        break;
                        }
                    }
                }
            }
            if(fl==0)
                cout << "No such file exists" << endl;
        }
        else if(choice==7)  //delete file
        {
            string fname;
            cout << "Enter filename to be deleted" << endl;
            cin >> fname;
            int choic;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    if(arr[i].filename==fname)
                    {
                        if(arr[i].status!=0)
                            cout << "Cannot delete while file is open" << endl;
                        else
                        {
                        arr[i].filename="";
                        arr[i].filesize=0;
                        arr[i].mode=0;
                        arr[i].pos=-1;
                        arr[i].status=-1;
                        bitmap[i]=0;
                        cout << "File successfully deleted" << endl;
                        break;
                        }
                    }
                }
            }
        }
        else if(choice==8)  //list file
        {
            cout << "List of files" << endl;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    cout << arr[i].filename << " opened with inode " << i << endl;
                }
            }
        }
        else if(choice==9)  //list opened files
        {
            vector<string> res;
            cout << "List of opened files" << endl;
            for(int i=1;i<50;i++)
            {
                if(bitmap[i]==1)
                {
                    if(arr[i].status==1)
                    {
                        if(arr[i].mode==1)
                            cout << arr[i].filename << " opened with file descriptor [" << arr[i].fd<<"] in read mode" << endl;
                        else if(arr[i].mode==2)
                            cout << arr[i].filename << " opened with file descriptor [" << arr[i].fd <<"] in write mode" << endl;
                        else if(arr[i].mode==3)
                            cout << arr[i].filename << " opened with file descriptor [" << arr[i].fd <<"] in append mode" << endl;
                    }
                }
            }
        }
        else if(choice==10) //unmount disk
        {
            int X=1000000;
            for(int i=1;i<50;i++)
            {
                arr[i].mode=0;
                arr[i].status=0;
            }
            fseek(fp,X,SEEK_SET);
            fwrite(bitmap,sizeof(int),50,fp);
            fwrite(arr,sizeof(struct finfo),50,fp);
            /*for(int i=0;i<5;i++)
                cout << arr[i].filename << " " << arr[i].filesize << " " << arr[i].status << endl;
            */fclose(fp);
            
            cout <<"Disk successfully unmounted" << endl;
            processCommand();
        }
    }
}

void processCommand()
{
    int choice;
    while(true)
    {
        cout << "Enter choice of operation" << endl;
        cout << "1. Create Disk" << endl;
        cout << "2. Mount Disk" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        if(choice==1)
        {
            string fname;
            cout << "Enter disk name" << endl;
            cin >> fname;
            createDisk(fname);
            cout << "Disk successfully created" << endl;
            for(int i=0;i<50;i++)
            {
                bitmap[i]=0;
            }
            bitmap[0]=1;
            for(int i=1;i<50;i++)
            {
                arr[i].filename="";
                arr[i].filesize=0;
                arr[i].mode=-1;
                arr[i].pos=-1;
                arr[i].status=-1;
            }
            FILE* fp=fopen(fname.c_str(),"r+");
            int X=1000000;
            fseek(fp,X,SEEK_SET);
            fwrite(bitmap,sizeof(int),50,fp);
            fwrite(arr,sizeof(struct finfo),50,fp);
            fclose(fp);
        }
        else if(choice==2)
        {
            string dname;
            cout <<"Enter disk name to be mounted" << endl;
            cin >> dname;
            cout << "Disk successfully mounted" << endl;
            mountDisk(dname);
        }
        else
        {
            cout << "Exiting application" << endl;
            exit(1);
        }
    }
}
int main()
{   
    processCommand();
}