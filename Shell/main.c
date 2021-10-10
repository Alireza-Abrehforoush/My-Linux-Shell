#include<stdio.h>
#include<time.h>
#include<limits.h>
#include<math.h>
#include<unistd.h>
#include<conio.h>
#include<unistd.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
#include<direct.h>
#include<sys/stat.h>
#include<dirent.h>


//////////functions//////////

//////////removing directory//////////
int remove_directory(const char *path)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2;
          buf = malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = remove_directory(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }

   if (!r)
   {
      r = rmdir(path);
   }

   return r;
}
//calculating the strength of a password//////////
int calst(char ar[100], int n)
{
	int x=0;
	int i=0;
	for(; i<n; i++)
	{
		if(ar[i]>=97 && ar[i]<=122) x+=2;
		else if(ar[i]>=65 && ar[i]<=90) x+=4;
		else if(ar[i]>=48 && ar[i]<=57) x+=3;
		else if(ar[i]==32) x+=1;
		else x+=8;
	}
	if(x>100) x=100;
	return x;
}
//////////ls//////////
void show_contents(void)
{
    system("cls");
    struct dirent *de;
    DIR *dr = opendir(".");
    if (dr == NULL)
    {
        printf("Could not open current directory" );
        return 0;
    }
    int i=0;
    while ((de = readdir(dr)) != NULL)
    {
        printf("%s\n", de->d_name);
        i++;
        if(i<=2) system("cls");
    }
    closedir(dr);
}
//////////file_existence//////////
int flxst(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
int dirxst(const char *d)
{
    DIR *dirptr;

    if (access(d, F_OK)!=-1){
        // file exists
        if ((dirptr = opendir (d)) != NULL) {
            closedir (dirptr);
        } else {
            return -2; /* d exists, but not dir */
        }
    } else {
        return -1;     /* d does not exist */
    }

    return 1;
}
//////////structs//////////


typedef struct user
{
	char na[100];	//name
	char un[100];	//username
	char pw[100];	//password
	int st;	//strength of password
	char ex[19];	//expiry date
	int pe;	//permission
	int wc;	//wrong command
}user;


int main()
{
//testing area!


//    FILE * f1;
    int nou=-2;
    char gar7;
    FILE * f10=fopen("C:/Users/10/My Projects/Shell/root/users.txt", "r");
    while(!feof(f10))
    {
        fscanf(f10, "%c", &gar7);
        if(gar7=='\n') nou++;
    }
    int no_users=nou-1;
    int per=0, always_true=1;//which user is writing command!
//    mkdir("root");
//    mkdir("root/users");
//    mkdir("root/users/admin");
//    f1=fopen("root/users.txt", "w");
//    user * u=(user *)malloc(sizeof(user));
    user admin, u[30];
	strcpy(admin.na, "admin");
	strcpy(admin.un, "admin");
	strcpy(admin.pw, "##########");
	admin.st=calst(admin.pw, strlen(admin.pw));
	strcpy(admin.ex, "0");
	admin.pe=1;
	admin.wc=0;
	no_users++;
//	fprintf(f1, "%s\t%s\t%s\t%d\t%s\t%d\t%d\n", admin.na, admin.un, admin.pw, admin.st, admin.ex, admin.pe, admin.wc);
//	fclose(f1);

	puts("Welcome to Shell");
	Sleep(2000);
	system("cls");

	while(1)
    {
        char t_na[100], t_un[100], t_pw[100], str_t[100], str1[100], str2[100], is[100], cur_dir[PATH_MAX], t_ex[19];
        int t_st, t_pe, t_wc, len=0, x1=0, x2, x3=0, x4=0, gar2;
        long long int gar3;
        struct tm * time_now;
        time_t * cur_tm;
        FILE * f2;
        puts("Enter your username");
        gets(str1);
        system("cls");
		f2=fopen("C:/Users/10/My Projects/Shell/root/users.txt", "r");
		while(!feof(f2))
        {
            fscanf(f2, "%s\t%s\t%s\t%d\t%s\t%d\t%d\n", t_na, t_un, t_pw, &t_st, t_ex, &t_pe, &t_wc);
            if(strcmp(str1, t_un)==0)
            {
                x1=1;//user found!
                break;
            }
            else
            {
                x1=0;
                continue;
            }
        }
        fclose(f2);
        if(x1==0)
        {
            puts("Couldn't find your account");
            Sleep(1000);
            puts("Press Enter to back to login page");
            str_t[0]=getchar();
            system("cls");
            continue;
        }
        if(x1==1)
        {
            if(t_pe==1 && per==0) x2=1;//password required!
            else if(t_pe==0 && per==0) x2=1;
            else if(t_pe==0 && per==1) x2=0;//admin is commanding, password isn't required!
            else x2=1;
            if(x2==0) x3=1;
            if(x2==1)
            {
                puts("Enter your password");
                gets(str1);
                system("cls");
                if(strcmp(str1, t_pw)==0) x3=1;//successfully signed in!
                else
                {
                    x3=0;
                    puts("Wrong password!");
                    Sleep(1000);
                    puts("Press Enter to back to login page");
                    str1[0]=getchar();
                    system("cls");
                }
            }
            if(x3==1)
            {
                char curtmstr[19], gar5[10];
                cur_tm=time(NULL);
                time_now=localtime(&cur_tm);
                itoa((time_now->tm_year)+1900, gar5, 10);
                strcpy(curtmstr, gar5);
                itoa((time_now->tm_mon)+1, gar5, 10);
                strcat(curtmstr, "-");
                if(log10((time_now->tm_mon)+1)==0) strcat(curtmstr, "0");
                strcat(curtmstr, gar5);
                strcat(curtmstr, "-");
                itoa(time_now->tm_mday, gar5, 10);
                if(log10(time_now->tm_mday)==0) strcat(curtmstr, "0");
                strcat(curtmstr, gar5);
                strcat(curtmstr, "_");
                itoa(time_now->tm_hour, gar5, 10);
                if(log10(time_now->tm_hour)==0 || time_now->tm_hour==0) strcat(curtmstr, "0");
                strcat(curtmstr, gar5);
                strcat(curtmstr, ":");
                itoa(time_now->tm_min, gar5, 10);
                if(log10(time_now->tm_min)==0 || time_now->tm_min==0) strcat(curtmstr, "0");
                strcat(curtmstr, gar5);
                strcat(curtmstr, ":");
                itoa(time_now->tm_sec, gar5, 10);
                if(log10(time_now->tm_sec)==0 || time_now->tm_sec==0) strcat(curtmstr, "0");
                strcat(curtmstr, gar5);
                if(t_pe==0 && strcmp(curtmstr, t_ex)>=0)
                {
                    puts("Account expired!");
                    Sleep(1000);
                    puts("Press Enter to log out");
                    str_t[0]=getchar();
                    system("cls");
                    //continue;
                }
                else
                {
                    printf("Welcome %s\n", t_na);
                    Sleep(2000);
                    system("cls");
                    chdir("root/users");
                    chdir(t_un);
                    while(1)
                    {
                        char com[100], cd_postfix[100], dirname[100], swuser[100], gar1;
                        system("cls");
                        scanf("%s", com);
                        if(strcmp(com, "cd")==0)
                        {
                            char yu[PATH_MAX];
                            getcwd(yu, sizeof(yu));
                            char cdcurpath[PATH_MAX], corpath[300];
                            strcpy(corpath, "C:\\Users\\10\\My Projects\\Shell\\root\\users\\");
                            strcat(corpath, t_un);
                            gar1=getchar();
                            gets(cd_postfix);
                            if(chdir(cd_postfix)!=0)
                            {
                                puts("An error occurred!");
                                system("pause");
                            }
                            getcwd(cdcurpath, sizeof(cdcurpath));
                            if(strstr(cdcurpath, corpath)==NULL && t_pe==0)
                            {
                                chdir(yu);
                            }
                        }
                        else if(strcmp(com, "pwd")==0)
                        {
                            gar1=getchar();
                            if(getcwd(cur_dir, sizeof(cur_dir))!=NULL)
                            {
                                printf("%s\n", cur_dir);
                                printf("Press Enter to back to home");
                                gar1=getchar();
                            }
                            else
                            {
                                puts("An error occurred!");
                                puts("Press Enter to back to home");
                                gar1=getchar();
                            }
                        }
                        else if(strcmp(com, "mkdir")==0)
                        {
                            gar1=getchar();
                            gets(dirname);
                            mkdir(dirname);
                            puts("Directory created successfully!");
                            puts("Press Enter to back to home");
                            gar1=getchar();
                        }
                        else if(strcmp(com, "create_user")==0)
                        {
                            char fair[PATH_MAX];
                            getcwd(fair, sizeof(fair));
                            gar1=getchar();
                            if(t_pe==0)
                            {
                                puts("You are not permitted to do the operation");
                                puts("Press Enter to back to home");
                                gar1=getchar();
                            }
                            if(t_pe==1)
                            {
                                FILE * f3;
                                struct tm * expr;
                                long long int expdt=0;
                                system("cls");
                                puts("Enter name of new user");
                                scanf("%s", u[no_users-1].na);
                                gar1=getchar();
                                system("cls");
                                puts("Enter username of new user");
                                scanf("%s", u[no_users-1].un);
                                gar1=getchar();
                                system("cls");
                                u[no_users-1].st=0;
                                while(u[no_users-1].st<=33)
                                {
                                    puts("Set the password of new user");
                                    scanf("%s", u[no_users-1].pw);
                                    gar1=getchar();
                                    u[no_users-1].st=calst(u[no_users-1].pw, strlen(u[no_users-1].pw));
                                    if(u[no_users-1].st<=33)
                                    {
                                        puts("The password is not strong enough!");
                                        continue;
                                    }

                                    system("cls");
                                }
                                //puts("Enter expiry date");
                                //scanf("%s")


                                puts("Set the expiration date of the account");
                                gets(u[no_users-1].ex);
                                system("cls");
                                puts("Is user an administrator?(0 if no and 1 if yes!)");
                                scanf("%d", &u[no_users-1].pe);
                                gar1=getchar();
                                system("cls");
                                u[no_users-1].wc=0;
                                f3=fopen("C:/Users/10/My Projects/Shell/root/users.txt", "r+");
                                fseek(f3, 0, SEEK_END);
                                fprintf(f3, "%s\t%s\t%s\t%d\t%s\t%d\t%d\n", u[no_users-1].na, u[no_users-1].un, u[no_users-1].pw, u[no_users-1].st, u[no_users-1].ex, u[no_users-1].pe,u[no_users-1].wc);
                                fclose(f3);
                                chdir("C:/Users/10/My Projects/Shell/root/users/");
                                mkdir(u[no_users].un);
                                no_users++;
                                puts("User successfully created!");
                                chdir(fair);
                                Sleep(5000);
                                system("cls");
                            }
                        }
                        else if(strcmp(com, "su")==0)
                        {
                            gar1=getchar();
                            chdir("C:/Users/10/My Projects/Shell/root/");
                            if(t_pe==1) per=1;
                            //f2=fopen("users.txt", "r");
                            x4=1;//to inform switching between users!
                            break;
                        }



                        else if(strcmp(com, "passwd")==0)
                        {
                            gar1=getchar();
                            char chngpw[100];
                            FILE * f4;
                            puts("Enter new password:");
                            gets(chngpw);
                            if(strcmp(admin.un, t_un)==0)
                            {
                                strcpy(admin.pw, chngpw);
                            }
/*
                            printf("\n%s\n\n", admin.na);//
                            system("pause");
                            printf("\n%s\n\n", admin.un);
                            system("pause");
                            printf("\n%s\n\n", admin.pw);
                            system("pause");
                            printf("\n%d\n\n", admin.st);
                            system("pause");
                            printf("\n%s\n\n", admin.ex);
                            system("pause");
                            printf("\n%d\n\n", admin.pe);
                            system("pause");
                            printf("\n%d\n\n", admin.wc);
                            system("pause");
*/
                            f4=fopen("C:/Users/10/My Projects/Shell/root/users.txt", "w");
                            fprintf(f4, "%s\t%s\t%s\t%d\t%s\t%d\t%d\n", admin.na, admin.un, admin.pw, admin.st, admin.ex, admin.pe, admin.wc);
                            int cnt1=0;
                            while(cnt1<no_users-1)
                            {
                                if(strcmp(u[cnt1].un, t_un)==0)
                                {
                                    strcpy(u[cnt1].pw, chngpw);
                                }
                                fprintf(f4, "%s\t%s\t%s\t%d\t%s\t%d\t%d\n", u[cnt1].na, u[cnt1].un, u[cnt1].pw, u[cnt1].st, u[cnt1].ex, u[cnt1].pe, u[cnt1].wc);
                                cnt1++;
                            }
                            fclose(f4);
                            chdir("C:\\Users\\10\\My Projects\\Shell\\root");
                            system("cls");
                            printf("Password successfully changed!\n");
                            Sleep(3000);
                            puts("Press Enter to back to home");
                            gar1=getchar();
                            continue;
                        }
                        else if(strcmp(com, "cat")==0)
                        {
                            char fop[100];
                            gar1=getchar();
                            scanf("%s", fop);
                            system("cls");
                            FILE * f5=fopen(fop, "r");
                            while(!feof(f5))
                            {
                                fscanf(f5, "%c", &gar1);
                                printf("%c", gar1);
                            }
                            printf("\n");
                            printf("\n");
                            fclose(f5);
                            puts("Press Enter to back to home");
                            gar1=getchar();
                            gar1=getchar();
                            continue;
                        }
                        else if(strcmp(com, "rm")==0)
                        {
                            char rmfile[100];
                            gar1=getchar();
                            scanf("%s", rmfile);
                            system("cls");
                            if(remove(rmfile)==0) printf("%s removed successfully\n", rmfile);
                            else printf("File not found!\n");
                            puts("Press Enter to back to home");
                            gar1=getchar();
                            gar1=getchar();
                            continue;
                        }
                        else if(strcmp(com, "rm-r")==0)
                        {
                            char t_rmdr[100], rmdr[100];
                            gar1=getchar();
                            scanf("%s", t_rmdr);
                            system("cls");
                            strcpy(rmdr, "rmdir /s ");
                            strcat(rmdr, t_rmdr);
                            printf("%s", rmdr);
                            Sleep(6000);
                            if(system(rmdr)==0) printf("Directory successfully removed\n");
                            else printf("Directory not found!\n");
                            puts("Press Enter to back to home");
                            gar1=getchar();
                            gar1=getchar();
                            continue;
                        }
                        else if(strcmp(com, "ls")==0)
                        {
                            system("cls");
                            gar1=getchar();
                            system("dir");
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "exif")==0)
                        {
                            char exifcmd[300], exifstr1[200];
                            gar1=getchar();
                            strcpy(exifcmd, "dir /T:C ");
                            gets(exifstr1);
                            system("cls");
                            strcat(exifcmd, exifstr1);
                            system(exifcmd);
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strchr(com, '>')!=NULL)
                        {
                            char strchrcmd[200];
                            strcpy(strchrcmd, "\"");
                            strcat(strchrcmd, "echo ");
                            strcat(strchrcmd, com);
                            strcat(strchrcmd, "\"");
                            gar1=getchar();
                            system("cls");
                            system(strchrcmd);
                            printf("Successfully redirected!\n");
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "help")==0)
                        {
                            char cm12[100];
                            gar1=getchar();
                            char cmdcmd[100], hlpcmd[100];
                            scanf("%s", cm12);
                            chdir("..");
                            chdir("..");
                            FILE * f7=fopen("C:/Users/10/My Projects/Shell/root/help.txt", "r");
                            chdir("users");
                            chdir(t_un);
                            system("cls");
                            while(!feof(f7))
                            {
                                fscanf(f7, "%s\t%s\n", cmdcmd, hlpcmd);
                                if(strcmp(cmdcmd, cm12)==0)
                                {
                                    printf("%s", hlpcmd);
                                    break;
                                }
                                else continue;
                            }
                            fclose(f7);
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "helpc")==0)
                        {
                            gar1=getchar();
                            system("cls");
                            chdir("..");
                            chdir("..");
                            FILE * f8=fopen("C:/Users/10/My Projects/Shell/root/commands.txt", "r");
                            while(!feof(f8))
                            {
                                fscanf(f8, "%c", &gar1);
                                printf("%c", gar1);
                            }
                            fclose(f8);
                            chdir("users");
                            chdir(t_un);
                            printf("\n");
                            Sleep(3000);
                            system("pause");
                        }
/*                        else if(strcmp(com, "wc")==0)
                        {
                            int wcline=1, wcword=-1;
                            gar1=getchar();
                            char wcflnm[100], utre[400];
                            gets(wcflnm);
                            FILE * f9=fopen(wcflnm, "r");
                            while(!feof(f9))
                            {
                                fscanf(f9, "%s", utre);
                                wcword++;
                            }
                            fclose(f9);
                            f9=fopen(wcflnm, "r");
                            while(!feof(f9))
                            {
                                fscanf(f9, "%c", &gar1);
                                if(gar1=='\n') wcline++;
                            }
                            fclose(f9);
                            system("cls");
                            printf("The number of lines in the text is %d\n&\nThe number of words in the text is %d\n", wcline, wcword);
                            Sleep(3000);
                            system("pause");
                        }
*/
                        else if(strcmp(com, "diff")==0)
                        {
                            char diff1[100], diff2[100], diff[100];
                            gar1=getchar();
                            gets(diff1);
                            gar1=getchar();
                            gets(diff2);
                            system("cls");
                            strcpy(diff, "fc ");
                            strcat(diff, diff1);
                            strcat(diff, " ");
                            strcat(diff, diff2);
                            system(diff);
                            Sleep(5000);
                            system("pause");
                        }
                        else if(strcmp(com, "hide")==0)
                        {
                            char hidf[100], hid1[100], refhid1[100];
                            gar1=getchar();
                            gets(hid1);
                            strcpy(hidf, "attrib +h ");
                            strcpy(refhid1, "\"");
                            strcat(refhid1, hid1);
                            strcat(refhid1, "\"");
                            strcat(hidf, refhid1);
                            system("cls");
                            system(hidf);
                            printf("Item is hidden now!\n");
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "unhide")==0)
                        {
                            char hidf[100], hid1[100], refhid1[100];
                            gar1=getchar();
                            gets(hid1);
                            strcpy(hidf, "attrib -h ");
                            strcpy(refhid1, "\"");
                            strcat(refhid1, hid1);
                            strcat(refhid1, "\"");
                            strcat(hidf, refhid1);
                            system("cls");
                            system(hidf);
                            printf("Item is visible now!\n");
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "cp")==0)
                        {
                            gar1=getchar();
                            char cpadd1[1000], cpadd2[1000], cpcom[3000];
                            strcat(cpcom, "copy ");
                            gets(cpadd1);
                            gets(cpadd2);
                            strcat(cpcom, " ");
                            strcat(cpcom, "\"");
                            strcat(cpcom, cpadd1);
                            strcat(cpcom, "\"");
                            strcat(cpcom, " ");
                            strcat(cpcom, "\"");
                            strcat(cpcom, cpadd2);
                            strcat(cpcom, "\"");
                            system(cpcom);
                            printf("Successfully copied!\n");
                            system("pause");
                        }
                        else if(strcmp(com, "mv")==0)
                        {
                            gar1=getchar();
                            char mvadd1[1000], mvadd2[1000], mvcom[3000];
                            strcat(mvcom, "move ");
                            gets(mvadd1);
                            gets(mvadd2);
                            strcat(mvcom, " ");
                            strcat(mvcom, "\"");
                            strcat(mvcom, mvadd1);
                            strcat(mvcom, "\"");
                            strcat(mvcom, " ");
                            strcat(mvcom, "\"");
                            strcat(mvcom, mvadd2);
                            strcat(mvcom, "\"");
                            system(mvcom);
                            printf("Successfully moved!\n");
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "flxst")==0)
                        {
                            char flxst2[200];
                            gar1=getchar();
                            gets(flxst2);
                            system("cls");
                            if(flxst(flxst2)==1) printf("File exists!\n");
                            else printf("File not found!\n");
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "dirxst")==0)
                        {
                            char dirxst2[200];
                            gar1=getchar();
                            gets(dirxst2);
                            system("cls");
                            if(dirxst(dirxst2)==1) printf("Directory exists!\n");
                            else printf("Directory not found!\n");
                            Sleep(3000);
                            system("pause");
                        }
                        else if(strcmp(com, "passwd-l_time")==0)
                        {
                            if(t_pe==1)
                            {

                                FILE * f17=fopen("C:/Users/10/My Projects/Shell/root/users.txt", "r");
                                while(!feof(f17))
                                {
                                    fscanf(f17, "%c", &gar7);
                                    if(gar7=='\n') nou++;
                                }
                                no_users=nou-1;
                                char por[300], tip[300];
                                gar1=getchar();
                                system("cls");
                                printf("Enter username\n");
                                gets(por);
                                system("cls");
                                printf("Enter new expiration date\n");
                                gets(tip);
                                printf("\n%d\n%d\n\n", no_users, nou);
                                system("pause");
                                int cnt2=0;
                                for(; cnt2<=no_users-1; cnt2++)
                                {
                                    if(strcmp(por, u[cnt2].un)==0)
                                    {
                                        strcpy(u[cnt2].ex, tip);
                                        break;
                                    }
                                }
                                FILE * f15=fopen("C:/Users/10/My Projects/Shell/root/users.txt", "w");
                                fprintf(f15, "%s\t%s\t%s\t%d\t%s\t%d\t%d\n", admin.na, admin.un, admin.pw, admin.st, admin.ex, admin.pe, admin.wc);
                                cnt2=0;
                                for(; cnt2<no_users; cnt2++)
                                {
                                    fprintf(f15, "%s\t%s\t%s\t%d\t%s\t%d\t%d\n", u[cnt2].na, u[cnt2].un, u[cnt2].pw, u[cnt2].st, u[cnt2].ex, u[cnt2].pe, u[cnt2].wc);
                                }
                                fclose(f15);
                                system("cls");
                                printf("Expiration date is changed successfully!\n");
                                Sleep(3000);
                                system("pause");
                            }
                            else
                            {
                                printf("You do not have permission to do the operation!\n");
                                Sleep(3000);
                                system("pause");
                            }
                        }
                        else if(strcmp(com, "hidls")==0)
                        {
                            gar1=getchar();
                            char zer[300], hdls[400];
                            gets(hdls);
                            system("cls");
                            strcpy(zer, "dir /ah ");
                            strcat(zer, hdls);
                            system(zer);
                            Sleep(3000);
                            system("pause");
                        }
                    }
                    if(x4==1) continue;
                }

            }
        }
    }
    return 0;
}
