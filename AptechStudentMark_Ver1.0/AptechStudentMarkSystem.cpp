//////////////////////////////////////////////////////////////////
//////////////Aptech studen's mark system (ver1.0)////////////////
//////////////Author : liemmaster                 ////////////////
//////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>


//**********************************************************************************************************************************
/////////////////////////////////////////////////////////////////Dinh ngia cac kieu du lieu/////////////////////////////////////////
//**********************************************************************************************************************************

typedef struct
{
	char tenlop[10];
	char giangvien[20];//ten giao vien chu nhiem
	char giohoc[15];
	char phonghoc[18];
	short int siso;
}LOPHOC;

typedef struct
{
	char mahv[10];
	char hoten[25];
	char ngaysinh[11];
	char diachi[25];
	char tenlop[10];
}HOCVIEN;

typedef struct
{
    char mahv[10];
    char mon[5];
	float t;
	float p;
}DIEM;

typedef struct
{
    char hoten[25];
    DIEM diem;
}DIEMHV;

typedef struct
{
    char mahv[10];
	float avg;
	char hoten[25];
}RANK;


//**********************************************************************************************************************************
///////////////////////////////////////////////////////////////Cac ham bo cho cho chuc nang chinh///////////////////////////////////
//**********************************************************************************************************************************


//dat mau nen
void mau_nen()
{
    window(1,1,80,25);
    textmode(C4350);
    textbackground(LIGHTCYAN);
	textcolor(BLACK);
    clrscr();
}

//kiem tra chuoi co duoc nhap va co du so luong ko
int nhapsai(char chuoi[], int max, int min)
{
    int n=strlen(chuoi);
    if(n==0)
    {
        printf("\nThere not string entered.-> Retype !\n");
        return 1;
    }
	else
        if(n>max || n<min)
        {
            printf("\nThe character of string from %d to %d -> Retype !\n",min,max);
            return 1;
        }
    return 0;
}

//chuon hoa ten
char * chuonhoaten(char chuoi[])
{
	//xoa dau cach o dau
    while(chuoi[0]==' ')
    {
        strcpy(chuoi,&chuoi[1]);
    }
    //xoa dau cach o cuoi
    while(chuoi[strlen(chuoi)] == ' ')
    {
        chuoi[strlen(chuoi)] = '\0';
    }
    //xoa dau cach o giua
    register int i=0;
    while(chuoi[i] != '\0')
	{
        if(chuoi[i] == ' ' && chuoi[i+1] == ' ')
            strcpy(&chuoi[i],&chuoi[i+1]);
        else
            i++;
    }
    //chuyen chu cai dau thanh hoa va cac chu cai khac la thuong
    i=0;
    strcpy(chuoi,strupr(chuoi));
    strcpy(&chuoi[i+1],strlwr(&chuoi[i+1]));
    while(i<strlen(chuoi))
    {
        if(chuoi[i] == ' ')
		{
            strcpy(&chuoi[i+1],strupr(&chuoi[i+1]));
            strcpy(&chuoi[i+2],strlwr(&chuoi[i+2]));
        }
        i++;
    }
    return chuoi;
}

//ham tra lai ten phong hoc
char * tenphong(int sclass, int lab)
{
	char lythuyet[18];
	char thuchanh[6];
	char *chuoi;

	switch(sclass)
	{
		case 1 :
			strcpy(lythuyet,"Class 1 - ");
			break;
		case 2 :
			strcpy(lythuyet,"Class 2 - ");
			break;
		case 3 :
			strcpy(lythuyet,"Class 3 - ");
			break;
		case 4 :
			strcpy(lythuyet,"Class 4 - ");
			break;
	}

	switch(lab)
	{
		case 1 :
			strcpy(thuchanh,"Lab 1");
			break;
		case 2 :
			strcpy(thuchanh,"Lab 2");
			break;
		case 3 :
			strcpy(thuchanh,"Lab 3");
			break;
		case 4 :
			strcpy(thuchanh,"Lab 4");
			break;
	}
	strcat(lythuyet,thuchanh);
	chuoi=lythuyet;
	return chuoi;
}


//doc file CLASS.DAT va cho vao mang danhdachlop
LOPHOC *danhsachlop(int *n)
{
    FILE *fclass;
	LOPHOC *mang;
	LOPHOC tg;
	register int dem;
	dem=0;
	//tg=(LOPHOC*) calloc(1,sizeof(LOPHOC));
	if((fclass=fopen("C:/DATA/CLASS/CLASS.DAT","rb")) == NULL)
	{
		printf("\nError read student mark in file !");
		getch();
	}
	else
	{
		while(fread(&tg,sizeof(LOPHOC),1,fclass)>0)
		{
			dem++;
		}
		mang=(LOPHOC*) calloc(dem,sizeof(LOPHOC));
		rewind(fclass);
		fread(mang,sizeof(LOPHOC),dem,fclass);
		fclose(fclass);
	}
	*n=dem;
	return mang;
}



//doc file STUDENT.DAT
HOCVIEN *danhsachhv(int *n)
{
    FILE *fstudent;
	HOCVIEN *mang;
	HOCVIEN tg;
	register int dem;
	dem=0;
	if((fstudent=fopen("C:/DATA/STUDENT/STUDENT.DAT","rb")) == NULL)
	{
		printf("\nError read student mark in file !");
		getch();
	}
	else
	{
		while(fread(&tg,sizeof(HOCVIEN),1,fstudent)>0)
		{
			dem++;
		}
		mang=(HOCVIEN*) calloc(dem,sizeof(HOCVIEN));
		rewind(fstudent);
		fread(mang,sizeof(HOCVIEN),dem,fstudent);
		fclose(fstudent);
	}
	*n=dem;
	return mang;
}

//kiem tra lop hoc co ton tai hay khong
int dupclass(LOPHOC *danhsach, int n, char *tenlop, int *vitri)
{
	register int i;
	for(i=0;i<n;i++)
        if(strcmp(tenlop,danhsach[i].tenlop)==0)
        {
            *vitri=i;
            return 1;
        }
	return 0;
}

//kiem tra lop hoc co ton tai hay khong
int dupstudent(HOCVIEN *danhsach, int n, char *ma,int *vitri)
{
	register int i;
	for(i=0;i<n;i++)
	if(strcmp(ma,danhsach[i].mahv)==0)
	{
		*vitri=i;
		return 1;
	}
	return 0;
}

//ham tra ve gio hoc da chon
void timeslot(char *giohoc)
{
	char select;
	do
	{
		printf("\n\nTime slot.");
		printf("\n---------------");
		printf("\n1.  8h30->10h30");
		printf("\n\n2. 17h30->19h30");
		printf("\n\n3. 19h30->21h30");
		printf("\n\n4. 19h45->21h45");
		printf("\n---------------");
		printf("\n\nSelect the number corresponding to timeslot : ");
		select=getche();
		switch(select)
		{
			case '1' :
				strcpy(giohoc,"8h30->10h30");
				break;
			case '2' :
				strcpy(giohoc,"14h30->16h30");
				break;
			case '3' :
				strcpy(giohoc,"17h30->19h30");
				break;
			case '4' :
				strcpy(giohoc,"19h45->21h45");
				break;
			default:
				printf("\nSelect 1 to 4 !");
				continue;
		}
	}while(select < '1' || select > '4');
}


//ham tra lai ten lop hoc
void classno(char *chuoi)
{
	register int i=0;
	int sai;
	do
	{
		sai=0;
		chuoi[0]='\0';
		printf("\nClass No.(ex: C1007M ) : ");
		gets(chuoi);
		strcpy(chuoi,strupr(chuoi));
		//xoa dau cach o cuoi
		while(chuoi[strlen(chuoi)-1] == ' ')
		{
			chuoi[strlen(chuoi)-1] = '\0';
		}
		if(chuoi[0] != 'C' && chuoi[0] != 'P')
		{
			printf("\nError .Class No Started by 'C' or 'P' -> Retype !\n");
			sai=1;
		}
		int n=strlen(chuoi);
		i=0;
		while(i<n)
		{
			if(chuoi[i] == ' ')
			{
				printf("\nClass name may not contain the characters space !\n");
				sai=1;
				break;
			}
			i++;
		}
	}while((nhapsai(chuoi,9,6) == 1) || sai==1);
}

//ham tra lai ma hoc vien
void rollno(char *chuoi)
{
	register int i=0;
	int sai;
    //--
    do
	{
	    sai=0;
		printf("\nRoll No.(ex: A00160 ) : ");
		gets(chuoi);
		strcpy(chuoi,strupr(chuoi));
		//xoa dau cach o cuoi
        while(chuoi[strlen(chuoi)-1] == ' ')
        {
			chuoi[strlen(chuoi)-1] = '\0';
		}
		if(chuoi[0] != 'P' && chuoi[0] != 'A')
		{
			printf("\nError .Roll No Start with 'A' or 'P' -> Retype !\n");
			sai=1;
			continue;
        }
        i=0;
        while(chuoi[i] != '\0')
        {
            if(chuoi[i] == ' ')
            {
				printf("\nroll no may not contain the characters space !\n");
				getch();
                sai=1;
                break;
            }
            i++;
        }
        i=1;
        int n=strlen(chuoi);
		while(i<n)
        {
			if(chuoi[i] < 48 || chuoi[i] > 57)
			{
				printf("\nRollno start with 'P' or 'A' and the next character is the number !");
				sai=1;
				break;
			}
			i++;
		}
	}while(nhapsai(chuoi,6,4)==1 || sai==1);
	//--
}

//ham tra lai ngay thang nam sinh
void birthday(char *ngaysinh)
{
	char ngay[3],thang[3],nam[5];
	printf("\nBirthday....");
	do
	{
		printf("\nEnter date of birth (01->31): ");
		gets(ngay);
		if(atoi(ngay)<1 || atoi(ngay)>31)
			printf("\n\nYou must enter an integer from 1 to 31 !");
	}while(atoi(ngay)<1 || atoi(ngay)>31);
	do
	{
		printf("\nEnter the month of birth (01->12) : ");
		gets(thang);
		if(atoi(thang)<1 || atoi(thang)>12)
			printf("\n\nYou must enter an integer from 1 to 12 !");
	}while(atoi(thang)<1 || atoi(thang)>12);

	do
	{
		printf("\nEnter birth year (1970 -> 2010): ");
		gets(nam);
		if(atoi(nam)<1970 || atoi(nam)>2010)
			printf("\n\nYou must enter an integer from 1970 to 2010 !");
	}while(atoi(nam)<1970 || atoi(nam)>2010);

	strcpy(ngaysinh,ngay);
	strcat(ngaysinh,"/");
	strcat(ngaysinh,thang);
	strcat(ngaysinh,"/");
	strcat(ngaysinh,nam);
}


//ham hien lop

void hienlop(LOPHOC lop)
{
	printf("\n ÚÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ¿");
	printf("\n ³No³ Class No ³ Head teacher         ³    Room No     ³ Time Slot   ³S_Number³");
	printf("\n ÃÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
	printf("\n ³  ³%-10s³%-22s³%-16s³%-13s³   %-5d³",lop.tenlop,lop.giangvien,lop.phonghoc,lop.giohoc,lop.siso);
	printf("\n ÀÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÙ");
}


//ham hien hoc vien

void hienhv(HOCVIEN hv)
{
	printf("\nÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ¿");
	printf("\n³ Roll No ³   Full name       ³ Birth day³           Adress          ³  Class ³");
	printf("\nÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
	printf("\n³%-9s³%-19s³%-10s³%-27s³%-8s³",hv.mahv,hv.hoten,hv.ngaysinh,hv.diachi,hv.tenlop);
	printf("\nÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÙ");
}

//ham hien diem

void hiendiem(DIEMHV d,int chon)
{
    if(chon==1)
    {
        printf("\n              ÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
        printf("\n              ³ roll No ³   Full name       ³  Subject  ³   T   ³");
        printf("\n              ÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
        printf("\n              ³%-9s³%-19s³    %-7s³  %-5.2f³",d.diem.mahv,d.hoten,d.diem.mon,d.diem.t);
        printf("\n              ÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ");
    }
    else
    {
        printf("\n              ÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
        printf("\n              ³ roll No ³   Full name       ³  Subject  ³   P   ³");
        printf("\n              ÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
        printf("\n              ³%-9s³%-19s³    %-7s³  %-5.2f³",d.diem.mahv,d.hoten,d.diem.mon,d.diem.p);
        printf("\n              ÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ");
    }
}


//ham hien thong tin ngan gon cua hoc vien

void hientthv(HOCVIEN hv)
{
	printf("\nÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
	printf("\n³ roll No ³   Full name       ³");
	printf("\nÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´");
	printf("\n³%-9s³%-19s³",hv.mahv,hv.hoten);
	printf("\nÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
}



//ham kiem tra ten lop hien tai da co hoc vien hay chua
int cohv(char *tenlop)
{
    HOCVIEN *ds;
    int n;
    ds=danhsachhv(&n);
    register int i;
    for(i=0;i<n;i++)
        if(strcmp(ds[i].tenlop,tenlop)==0)
        {
            free(ds);
            return 1;
        }
    free(ds);
    return 0;
}

//nhap mot ma hoc vien va kiem tra co ton tai khong
int find_by_roll(int *vitri)
{
    fflush(stdin);
	char rollfind[10];
	HOCVIEN *danhsach;
	int n;
	register int i;
	danhsach=danhsachhv(&n);
    rollno(rollfind);//nhap mahv
    for(i=0;i<n;i++)
        if(strcmp(danhsach[i].mahv,rollfind)==0)
        {
            free(danhsach);
            *vitri=i;
            return 1;
        }
    free(danhsach);
	return 0;
}

//doc file kiem tra xem mon nhap vao co ton tai kho va co bao nhieu bai thi ly thuyet, thuc hanh

int issubject(char *subject,int *t,int *p,int *tt, int *pp)
{
    FILE *fsubject;
    char chuoi[10];
    char mon[5];
    register int i;
	if((fsubject=fopen("C:/DATA/MARK/mark.txt","r")) == NULL)
    {
        printf("\nError read file mark.txt !");
        getch();
		return 0;
	}
	else
	{
        char phantram_t[3];
	    char phantram_p[3];
		fgets(chuoi,10,fsubject);
        phantram_t[0]=chuoi[2];
        phantram_t[1]=chuoi[3];
        phantram_t[2]='\0';
        *tt=atoi(phantram_t);
        phantram_p[0]=chuoi[7];
        phantram_p[1]=chuoi[8];
        phantram_p[2]='\0';
        *pp=atoi(phantram_p);
		while(strcmp(chuoi,"END/") != 0)
		{
			fgets(chuoi,10,fsubject);
			i=0;
			while(chuoi[i] != '/')
			{
				mon[i]=chuoi[i];
				mon[i+1]='\0';
				i++;
			}
			if(strcmp(mon,subject)==0)
			{
				*t=chuoi[i+1]-48;
                *p=chuoi[i+4]-48;
				fclose(fsubject);
				chuoi[0]='\0';
				mon[0]='\0';
				return 1;
			}
			else
				continue;
		}
		fclose(fsubject);
		chuoi[0]='\0';
		mon[0]='\0';
		return 0;
	}
}


//add student mark

int write_student_mark(DIEM mark)
{
	FILE *fsmark;
	if((fsmark=fopen("C:/DATA/MARK/MARK.DAT","ab")) == NULL)
	{
		printf("\nError add new student mark to file !");
		return 0;
	}
	else
	{
	    if(mark.t<0)
            mark.t=0.00;
        if(mark.p<0)
            mark.p=0.00;
		fwrite(&mark,sizeof(DIEM),1,fsmark);
		fclose(fsmark);
		return 1;
	}
}

//danh sach diem sinh vien

DIEM *danhsachdiem(int *n)
{
	FILE *fsmark;
	DIEM *mang,tg;
	int dem=0;
	if((fsmark=fopen("C:/DATA/MARK/MARK.DAT","rb")) == NULL)
	{
		printf("\nError read student mark in file !");
		getch();
	}
	else
	{
		while(fread(&tg,sizeof(DIEM),1,fsmark)>0)
		{
			dem++;
		}
		mang=(DIEM*) calloc(dem,sizeof(DIEM));
		rewind(fsmark);
		fread(mang,sizeof(DIEM),dem,fsmark);
		fclose(fsmark);
	}
	*n=dem;
	return mang;
}



//chon de kiem tra mon hoc co ton tai khong va so bai thi ly thuyet hay thuc hanh la bao nhieu
void subject(char *mon, int *t, int *p,int *chon)
{
    char tg[5];
	int i,j,temp;
    do
    {
        printf("\nSubject : ");
        gets(tg);
        strcpy(tg,strupr(tg));
		if(issubject(tg,&i,&j,&temp,&temp)==0)
        {
            printf("\n\nSubject you enterd is not found !");
            printf("\n\nPress any key to continue !");
            getch();
        }
	}while(issubject(tg,&i,&j,&temp,&temp)==0 || nhapsai(tg,4,2)==1);
    if(i>0 && j>0)
	{
		char ch;
		do
		{
			printf("\n\nType <1> T mark type.\n");
			printf("\n\nType <2> P mark type.\n>");
			ch=getch();
			if(ch=='1')
				*chon=1;
			else
				*chon=2;
		}while(ch != '1' && ch != '2');
    }
    else
    {
        if(i==0)
        {
            printf("\n\nSubject [%s] only 'P' mark type !\n\n",tg);
            printf("\n\nPress any key to continue !");
            getch();
			*chon=2;
		}
		else
		{
			printf("\n\nSubject [%s] only 'T' mark type !\n\n",tg);
            printf("\n\nPress any key to continue !");
            getch();
			*chon=1;
		}
	}
    strcpy(mon,tg);
	*t=i;
    *p=j;
}

//ham tra lai ten hoc vien khi biet ma hoc vien
DIEMHV mark_info(DIEM a)
{
    DIEMHV tg;
    HOCVIEN *ds;
    int n,vitri;
    ds=danhsachhv(&n);
	if(dupstudent(ds,n,a.mahv,&vitri)==1)
    {
        strcpy(tg.hoten,ds[vitri].hoten);
    }
    tg.diem=a;
    free(ds);
    return tg;
}

//kiem tra viec nhap diem
float mark()
{
    float tg;
    do
    {
		printf("\nMark (float 0->25): ");
		fflush(stdin);
		scanf("%f",&tg);
		if(tg<0.00 || tg>25.00)
            printf("\nRetype (float 0->25) !");
	}while(tg<0.00 || tg>25.00);
	return tg;
}

//kiem tra ma hoc vien hien tai da co diem chua

int exit_student(char *mahv)
{
    DIEM *ds;
    int n;
    register int i;
	ds=danhsachdiem(&n);
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].mahv,mahv)==0)
        {
            free(ds);
            return 1;
        }
	}
	free(ds);
	return 0;
}

//kiem tra diem da ton tai chua
int exit_mark(char *mahv, char *mon, int chon)
{
    DIEM *ds;
    int n;
    register int i;
	ds=danhsachdiem(&n);
    for(i=0;i<n;i++)
    {
        if(chon==1)
        {
			if(strcmp(ds[i].mahv,mahv)==0)
			{
				if(strcmp(ds[i].mon,mon)==0)
                {
                    if(ds[i].t > 0.00)
                    {
                        free(ds);
                        return 1;
                    }
                    else
                    {
                        free(ds);
                        return 0;
                    }
                }
                else
                    continue;
            }
            else
                continue;
        }
        else
        {
			if(strcmp(ds[i].mahv,mahv)==0)
			{
				if(strcmp(ds[i].mon,mon)==0)
                {
                    if(ds[i].p > 0.00)
                    {
                        free(ds);
                        return 1;
                    }
                    else
                    {
                        free(ds);
                        return 0;
                    }
                }
                else
                    continue;
			}
			else
				continue;
		}

	}
	free(ds);
	return 0;
}


//ham tra lai diem

void nhap_diem(float *t, float *p,int tt, int pp, int chon)
{
	if(chon==1)
	{
		if(tt==1)
		{
		    printf("\n\nEnter mark....\n");
			*t=mark();
		}
		if(tt==2)
		{
			float m1,m2;
			printf("\nThis second mark type of test.\n");
			printf("\nMark 1 : ");
			m1=mark();
			printf("\nMark 2 : ");
			m2=mark();
			*t=(float) (m1+m2)/(float) 2;
		}
	}
	else
	{
		if(pp==1)
		{
		    printf("\n\nEnter mark....\n");
			*p=mark();
		}
		if(pp==2)
		{
			float m1,m2;
			printf("\nThis second mark type of test.\n");
			printf("\nMark 1 : ");
            m1=mark();
            printf("\nMark 2 : ");
            m2=mark();
            *p=(m1+m2)/(float) 2;
        }
    }
}


//danh sach hoc vien theo lop

HOCVIEN *danh_sach_hv_theo_lop(char *tenlop,int *siso)
{
    HOCVIEN *ds,*lop;
    int n;
    register int dem=0,i;
    ds=danhsachhv(&n);
    for(i=0;i<n;i++)
    {
		if((strcmp(ds[i].tenlop,tenlop))==0)
            dem++;
    }
    lop=(HOCVIEN*) calloc(dem,sizeof(HOCVIEN));
	*siso=dem;
    dem=0;
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].tenlop,tenlop)==0)
        {
            lop[dem]=ds[i];
            dem++;
        }
    }
    free(ds);
    return lop;
}

//kiem tra lop co hoc vien hay khong

int empty_student(char *tenlop)
{
    HOCVIEN *ds;
    int n;
    register int i;
    ds=danhsachhv(&n);
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].tenlop,tenlop)==0)
        {
            free(ds);
            return 0;
        }
    }
    free(ds);
    return 1;
}

//chuyen he 25 sang 100;

float mot_tram(float a)
{
    float kq;
    kq=((float) a * (float) 100)/ (float) 25;
    return kq;
}


//ham tinh diem trung binh

float avg(char *mahv)
{
    DIEM *ds;
    int n,t,p,tt,pp,somon=0;
    float diemtb=0.00,tong=0.00,tbmon=0.00;
    register  int i;
    ds=danhsachdiem(&n);
    for(i=0;i<n;i++)
    {
        if(strcmp(mahv,ds[i].mahv)==0)
        {
            somon++;
            issubject(ds[i].mon,&t,&p,&tt,&pp);
            if(t!=0 && p!=0)
            {
                    tbmon = ((mot_tram(ds[i].t)* (float) tt) / (float) 100) + ((mot_tram(ds[i].p) * (float) pp) / (float) 100);
            }
            else
            {
                if(t==0)
                {
                        tbmon=mot_tram(ds[i].p);
                }
                else
                {
                        tbmon=mot_tram(ds[i].t);
                }
            }
            tong=tong+tbmon;
        }
    }
    diemtb= (float) tong / (float) somon;
    free(ds);
    return diemtb;
}


//tra lai ten lop khi biet ma hoc vien

void class_name(char *mahv,char *tenlop)
{
    HOCVIEN *ds;
    int n;
    register int i;
    ds=danhsachhv(&n);
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].mahv,mahv)==0)
        {
			strcpy(tenlop,ds[i].tenlop);
            break;
        }
    }
    free(ds);
}

//ham tra lai ten khi biet ho ten

char *get_last_name(char *hoten)
{
    char *ten;
    register int i;
    i=strlen(hoten)-1;
    while(hoten[i]!=' ')
    {
        i--;
    }
	ten=&hoten[i+1];
    return ten;
}


//tra lai ten khi biet ma

void student_name(char *id,char *hoten)
{
    HOCVIEN *ds;
    int n;
    register int i;
    ds=danhsachhv(&n);
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].mahv,id)==0)
        {
            strcpy(hoten,ds[i].hoten);
            break;
        }
    }
    free(ds);
    return;
}


//tra lai diem khi biet thong tin day du

DIEM get_mark(char *mahv,char *mon)
{
	DIEM doc;
    FILE *fmark;
    fmark=fopen("C:/DATA/MARK/MARK.DAT","rb");
	while(fread(&doc,sizeof(DIEM),1,fmark)>0)
    {
        if(strcmp(doc.mahv,mahv)==0 && strcmp(doc.mon,mon)==0)
        {
            fclose(fmark);
            break;
        }
    }
    return doc;
}


//kiem tra sinh vien hien tai da co it nhat diem mot mon nao do chua

int co_diem(char *mahv)
{
	DIEM *ds;
    int n;
    ds=danhsachdiem(&n);
    register int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].mahv,mahv)==0)
		{
			free(ds);
			return 1;
		}
    }
	free(ds);
    return 0;
}


//lay danh sach hoc vien co diem

HOCVIEN *danhsach_hocvien_co_diem(int *so)
{
	HOCVIEN *ds, *ds_co_diem;
	int n, dem=0;
    ds=danhsachhv(&n);
    register int i;
    for(i=0;i<n;i++)
    {
        if(co_diem(ds[i].mahv)==1)
			dem++;
    }
	*so=dem;
	ds_co_diem = (HOCVIEN*) calloc(dem,sizeof(HOCVIEN));
	dem=0;
	for(i=0;i<n;i++)
    {
        if(co_diem(ds[i].mahv)==1)
		{
			ds_co_diem[dem]=ds[i];
			dem++;
		}
    }
	free(ds);
	return ds_co_diem;
}

///////////////////////giai thuat sap xep////////////////////////

void bubble_rank(int n, RANK *a)
{
    register int i,j;
    int vtmin;
    RANK tg;
    for(i=0;i<n-1;i++)
    {
        vtmin=i;
        for(j=i+1;j<n;j++)
			if(a[j].avg<a[vtmin].avg)
                vtmin=j;
        if(vtmin!=i)
        {
            tg=a[i];
            a[i]=a[vtmin];
            a[vtmin]=tg;
        }
    }
}


void bubble_class(int n, LOPHOC *a,int chon)
{
    /*
    tham so chon de xac dinh sap xep theo class no hay theo siso
    */
    register int i,j;
    int vtmin;
    LOPHOC tg;
    if(chon==1)//ten lop
    {
        for(i=0;i<n-1;i++)
        {
            vtmin=i;
            for(j=i+1;j<n;j++)
                if(strcmp(a[j].tenlop,a[vtmin].tenlop)<0)
                    vtmin=j;
            if(vtmin!=i)
            {
                tg=a[i];
                a[i]=a[vtmin];
                a[vtmin]=tg;
            }
        }
    }
    else//siso
    {
        for(i=0;i<n-1;i++)
        {
            vtmin=i;
            for(j=i+1;j<n;j++)
                if(a[j].siso<a[vtmin].siso)
                    vtmin=j;
            if(vtmin!=i)
            {
                tg=a[i];
                a[i]=a[vtmin];
                a[vtmin]=tg;
            }
        }
    }
}

void bubble_student(int n, HOCVIEN *a,int chon)
{
    register int i,j;
    int vtmin;
    HOCVIEN tg;
    if(chon==1)//ma hoc vien
    {
        for(i=0;i<n-1;i++)
        {
            vtmin=i;
            for(j=i+1;j<n;j++)
                if(strcmp(a[j].mahv,a[vtmin].mahv)<0)
                    vtmin=j;
			if(vtmin!=i)
			{
				tg=a[i];
				a[i]=a[vtmin];
				a[vtmin]=tg;
			}
		}
	}
  	else
	    if(chon==2)//ho ten
		{
			for(i=0;i<n-1;i++)
			{
				vtmin=i;
				for(j=i+1;j<n;j++)
					if(strcmp(get_last_name(a[j].hoten),get_last_name(a[vtmin].hoten))<0)
						vtmin=j;
				if(vtmin!=i)
				{
					tg=a[i];
					a[i]=a[vtmin];
					a[vtmin]=tg;
				}
			}
		}
    else
	    if(chon==3)//ten lop
		{
			for(i=0;i<n-1;i++)
			{
				vtmin=i;
				for(j=i+1;j<n;j++)
					if(strcmp(a[j].tenlop,a[vtmin].tenlop)<0)
						vtmin=j;
				if(vtmin!=i)
				{
					tg=a[i];
					a[i]=a[vtmin];
					a[vtmin]=tg;
				}
			}
		}
}

void bubble_student_mark(int n, DIEM *a,int chon,int kieu)
{
    register int i,j;
	int vtmin;
	DIEM tg;
	char tenlop1[10];
	char tenlop2[10];
	if(chon==1)//ten lop
	{
		for(i=0;i<n-1;i++)
		{
			vtmin=i;
			for(j=i+1;j<n;j++)
			{
				class_name(a[j].mahv,tenlop1);
				class_name(a[vtmin].mahv,tenlop2);
				if(strcmp(tenlop1,tenlop2)<0)
					vtmin=j;
			}
            if(vtmin!=i)
            {
                tg=a[i];
                a[i]=a[vtmin];
                a[vtmin]=tg;
            }
        }
    }
    else//diem
    {
        if(kieu==1)
        {
            for(i=0;i<n-1;i++)
            {
                vtmin=i;
                for(j=i+1;j<n;j++)
                    if(a[j].t>a[vtmin].t)
                        vtmin=j;
                if(vtmin!=i)
                {
                    tg=a[i];
                    a[i]=a[vtmin];
                    a[vtmin]=tg;
                }
            }
        }
        else
        {
             for(i=0;i<n-1;i++)
            {
                vtmin=i;
                for(j=i+1;j<n;j++)
                    if(a[j].p<a[vtmin].p)
                        vtmin=j;
                if(vtmin!=i)
                {
                    tg=a[i];
                    a[i]=a[vtmin];
                    a[vtmin]=tg;
                }
            }
        }
    }
}



void bubble_class_mark_list(int n, HOCVIEN *a,char *mon, int kieu)
{
	register int i,j;
	int vtmin;
	HOCVIEN tg;
	if(kieu == 1)
	{
		for(i=0;i<n-1;i++)
		{
			vtmin=i;
			for(j=i+1;j<n;j++)
			{
				if(get_mark(a[j].mahv,mon).t>get_mark(a[vtmin].mahv,mon).t)
					vtmin=j;
			}
			if(vtmin!=i)
			{
				tg=a[i];
				a[i]=a[vtmin];
				a[vtmin]=tg;
			}
		}
	}
	else
	{
		for(i=0;i<n-1;i++)
		{
			vtmin=i;
			for(j=i+1;j<n;j++)
				if(get_mark(a[j].mahv,mon).p>get_mark(a[vtmin].mahv,mon).p)
					vtmin=j;
			if(vtmin!=i)
			{
				tg=a[i];
				a[i]=a[vtmin];
				a[vtmin]=tg;
			}
		}
	}
}

void bubble_avg(int n, DIEM *a)
{
	register int i,j;
	int vtmin;
	DIEM tg;
	for(i=0;i<n-1;i++)
	{
		vtmin=i;
		for(j=i+1;j<n;j++)
			if(avg(a[j].mahv)<avg(a[vtmin].mahv))
				vtmin=j;
        if(vtmin!=i)
        {
            tg=a[i];
            a[i]=a[vtmin];
            a[vtmin]=tg;
        }
    }
}


void bubble_class_avg(int n, HOCVIEN *a, int chon)
{
	register int i,j;
	int vtmin;
	HOCVIEN tg;
	if(chon==1)//ho ten
	{
        for(i=0;i<n-1;i++)
        {
            vtmin=i;
            for(j=i+1;j<n;j++)
            {
				if(strcmp(get_last_name(a[j].hoten),get_last_name(a[vtmin].hoten))<0)
					vtmin=j;
            }
            if(vtmin!=i)
            {
                tg=a[i];
                a[i]=a[vtmin];
                a[vtmin]=tg;
            }
        }
	}
	else//avg
	{
        for(i=0;i<n-1;i++)
        {
			if(co_diem(a[i].mahv)==1)
			{
				vtmin=i;
				for(j=i+1;j<n;j++)
					if(avg(a[j].mahv)>avg(a[vtmin].mahv))
						vtmin=j;
				if(vtmin!=i)
				{
					tg=a[i];
					a[i]=a[vtmin];
					a[vtmin]=tg;
				}
			}
        }
	}
}

void bubble_upgradge(int n, HOCVIEN *a, int chon)
{
	register int i,j;
	int vtmin;
	HOCVIEN tg;
	if(chon==1)//ho ten
	{
		for(i=0;i<n-1;i++)
		{
			vtmin=i;
			for(j=i+1;j<n;j++)
				if(strcmp(get_last_name(a[j].hoten),get_last_name(a[vtmin].hoten))>0)
					vtmin=j;
			if(vtmin!=i)
			{
				tg=a[i];
				a[i]=a[vtmin];
				a[vtmin]=tg;
			}
		}
	}
	else
	    if(chon==2)//ten lop
		{
			for(i=0;i<n-1;i++)
			{
				vtmin=i;
				for(j=i+1;j<n;j++)
					if(strcmp(a[j].tenlop,a[vtmin].tenlop)>0)
						vtmin=j;
				if(vtmin!=i)
				{
					tg=a[i];
					a[i]=a[vtmin];
					a[vtmin]=tg;
				}
			}
		}
	else
		if(chon==3)//sap xep theo avg
		{
			for(i=0;i<n-1;i++)
			{
				vtmin=i;
				for(j=i+1;j<n;j++)
					if(avg(a[j].mahv)<avg(a[vtmin].mahv))
						vtmin=j;
				if(vtmin!=i)
				{
					tg=a[i];
					a[i]=a[vtmin];
					a[vtmin]=tg;
				}
			}
		}
}

//ham tra lai ten khi biet id

void get_name(char *id,char *name)
{
    HOCVIEN *ds;
    int n;
    register int i;
    ds=danhsachhv(&n);
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].mahv,id)==0)
        {
            strcpy(name,ds[i].hoten);
            break;
        }
    }
    free(ds);
    return;
}


//dem si so
int siso(char *tenlop)
{
    HOCVIEN *ds;
    int n,dem=0;
    ds=danhsachhv(&n);
    register int i;
    for(i=0;i<n;i++)
        if(strcmp(ds[i].tenlop,tenlop)==0)
            dem++;
    free(ds);
    return dem;
}

//vi tri lop
int siso_gioihan(LOPHOC *ds,int n,char *tenlop)
{
    register int i;
    for(i=0;i<n;i++)
        if(strcmp(ds[i].tenlop,tenlop)==0)
            break;
    return ds[i].siso;
}



//**********************************************************************************************************************************
/////////////////////////////////////////////////////////////Lam viec voi file//////////////////////////////////////////////////
//**********************************************************************************************************************************
//ghi lop hoc moi vao file

int write_class(LOPHOC moi)
{
    FILE *fclass;
    char ch;
    fclass = fopen("C:/DATA/CLASS/CLASS.DAT","ab");
    if(fclass==NULL)
    {
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File CLASS.DAT is not found !");
        printf("\n\t\t\tDo you want to create it (Y/N) ?\n\t\t\t          >");
        ch=getch();
        if(ch=='y' || ch=='Y')
        {
            fclass = fopen("C:/DATA/CLASS/CLASS.DAT","wb");
            fwrite(&moi,sizeof(LOPHOC),1,fclass);
            fclose(fclass);
            return 1;
        }
        else
            return 0;
    }
    else
    {
        fwrite(&moi,sizeof(LOPHOC),1,fclass);
        fclose(fclass);
        return 1;
    }
}

//ghi sinh vien moi vao file

int write_student(HOCVIEN moi)
{
	FILE *fstudent;
	char ch;
	fstudent = fopen("C:/DATA/STUDENT/STUDENT.DAT","ab");
	if(fstudent==NULL)
	{
		clrscr();
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File STUDENT.DAT is not found !");
		printf("\n\t\t\tDo you want to create it (Y/N) ?\n\t\t\t          >");
		ch=getch();
		if(ch=='y' || ch=='Y')
		{
			fstudent = fopen("C:/DATA/STUDENT/STUDENT.DAT","wb");
			fwrite(&moi,sizeof(HOCVIEN),1,fstudent);
			fclose(fstudent);
			return 1;
		}
        else
            return 0;
    }
    else
    {
        fwrite(&moi,sizeof(HOCVIEN),1,fstudent);
        fclose(fstudent);
        return 1;
    }
}


//ghi thong tin diem moi

int write_mark(DIEM moi)
{
	FILE *fmark;
	char ch;
	fmark = fopen("C:/DATA/MARK/MARK.DAT","ab");
	if(fmark==NULL)
	{
		clrscr();
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File MARK.DAT is not found !");
		printf("\n\t\t\tDo you want to create it (Y/N) ?\n\t\t\t          >");
		ch=getch();
		if(ch=='y' || ch=='Y')
		{
			fmark = fopen("C:/DATA/MARK/MARK.DAT","wb");
			fwrite(&moi,sizeof(DIEM),1,fmark);
			fclose(fmark);
			return 1;
		}
		else
			return 0;
    }
    else
    {
        fwrite(&moi,sizeof(DIEM),1,fmark);
        fclose(fmark);
        return 1;
    }
}

//sua thong tin cua lop roi ghi lai vao file

int write_edit_class(LOPHOC moi)
{
    FILE *fclass;
    char ch;
    fclass = fopen("C:/DATA/CLASS/CLASS.DAT","r+b");
    if(fclass==NULL)
    {
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File CLASS.DAT is not found !");
        printf("\n\t\t\tDo you want to create it (Y/N) ?\n\t\t\t          >");
        ch=getch();
        if(ch=='y' || ch=='Y')
        {
            fclass = fopen("C:/DATA/CLASS/CLASS.DAT","wb");
            fwrite(&moi,sizeof(LOPHOC),1,fclass);
            fclose(fclass);
            return 1;
        }
        else
            return 0;
    }
    else
    {
        LOPHOC doc;
        int dem=0;
        while(fread(&doc,sizeof(LOPHOC),1,fclass)>0)
        {
            dem++;
            if(strcmp(doc.tenlop,moi.tenlop)==0)
            {
                fseek(fclass,(dem-1)*sizeof(LOPHOC),SEEK_SET);
                fwrite(&moi,sizeof(LOPHOC),1,fclass);
                fclose(fclass);
                return 1;
            }
        }
		return 0;
    }
}

//ghi lai thong tin hoc vien vao file

int write_edit_student(HOCVIEN moi)
{
    FILE *fstudent;
    char ch;
    fstudent = fopen("C:/DATA/STUDENT/STUDENT.DAT","r+b");
    if(fstudent==NULL)
    {
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File STUDENT.DAT is not found !");
        printf("\n\t\t\tDo you want to create it (Y/N) ?\n\t\t\t          >");
        ch=getch();
        if(ch=='y' || ch=='Y')
        {
			fstudent = fopen("C:/DATA/STUDENT/STUDENT.DAT","wb");
            fwrite(&moi,sizeof(HOCVIEN),1,fstudent);
            fclose(fstudent);
            return 1;
        }
        else
            return 0;
    }
    else
    {
        HOCVIEN doc;
        int dem=0;
        while(fread(&doc,sizeof(HOCVIEN),1,fstudent)>0)
        {
            dem++;
            if(strcmp(doc.mahv,moi.mahv)==0)
            {
                fseek(fstudent,(dem-1)*sizeof(HOCVIEN),SEEK_SET);
                fwrite(&moi,sizeof(HOCVIEN),1,fstudent);
                fclose(fstudent);
                return 1;
            }
        }
		return 0;
    }
}


//ghi lai thong tin diem ly thuyet sau khi da sua

int write_edit_mark(DIEM moi)
{
    FILE *fmark;
    char ch;
    fmark = fopen("C:/DATA/MARK/MARK.DAT","r+b");
    if(fmark==NULL)
    {
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File MARKT.DAT is not found !");
        printf("\n\t\t\tDo you want to create it (Y/N) ?\n\t\t\t          >");
        ch=getch();
        if(ch=='y' || ch=='Y')
        {
			fmark = fopen("C:/DATA/MARK/MARK.DAT","wb");
            fwrite(&moi,sizeof(DIEM),1,fmark);
            fclose(fmark);
            return 1;
        }
        else
            return 0;
    }
    else
    {
        DIEM doc;
        int dem=0;
        while(fread(&doc,sizeof(DIEM),1,fmark)>0)
        {
            dem++;
            if(strcmp(doc.mahv,moi.mahv)==0 && strcmp(doc.mon,moi.mon)==0)
            {
                fseek(fmark,(dem-1)*sizeof(DIEM),SEEK_SET);
                fwrite(&moi,sizeof(DIEM),1,fmark);
                fclose(fmark);
                return 1;
            }
        }
		return 0;
    }
}


//xoa thong tin cua 1 lop trong file

int remove_class(LOPHOC xoa)
{
    FILE *fclass;
    LOPHOC *ds;
    int n;
    register int i;
    ds=danhsachlop(&n);
    fclass = fopen("C:/DATA/CLASS/CLASS.DAT","wb");
	if(fclass==NULL)
    {
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File CLASS.DAT is not found !");
        printf("\n\t\t\t  Press any key to continue !\n\t\t\t          >");
		getch();
        return 0;
    }
    else
    {
        for(i=0;i<n;i++)
        {
            if(strcmp(ds[i].tenlop,xoa.tenlop) != 0)
            {
                fwrite(&ds[i],sizeof(LOPHOC),1,fclass);
            }
        }
        fclose(fclass);
        free(ds);
        return 1;
	}
}

//xoa thong tin hoc vien

int remove_student(HOCVIEN xoa)
{
    FILE *fstudent;
    HOCVIEN *ds;
    int n;
    register int i;
    ds=danhsachhv(&n);
    fstudent = fopen("C:/DATA/STUDENT/STUDENT.DAT","wb");
	if(fstudent==NULL)
    {
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t File STUDENT.DAT is not found !");
        printf("\n\t\t\t  Press any key to continue !\n\t\t\t          >");
		getch();
        return 0;
    }
    else
    {
        for(i=0;i<n;i++)
        {
            if(strcmp(ds[i].mahv,xoa.mahv) != 0)
            {
                fwrite(&ds[i],sizeof(HOCVIEN),1,fstudent);
            }
        }
        fclose(fstudent);
        free(ds);
        return 1;
	}
}

//kiem tra diem da ton tai chua( tham so kieu(1/2) xac dinh la t hay p)
int exist_mark(char *mahv, char *mon, int kieu,DIEM *tg)
{
    DIEM doc;
    FILE *fmark;
	if((fmark=fopen("C:/DATA/MARK/MARK.DAT","rb")) == NULL)
		return 0;
	else
	{
		while(fread(&doc,sizeof(DIEM),1,fmark)>0)
		{
			if(strcmp(doc.mahv,mahv)==0 && strcmp(doc.mon,mon)==0)
			{
				fclose(fmark);
				if(kieu==1)
				{
					if(doc.t == (float) -1.00)
					{
						*tg=doc;
						return 0;
					}
					else
					{
						*tg=doc;
						return 1;
					}
				}
				else
				{
					if(doc.p == (float) -1.00)
					{
						*tg=doc;
						return 0;
					}
					else
					{
						*tg=doc;
						return 1;
					}
				}
			}
		}
		fclose(fmark);
		return 0;
	}
}


//nhap diem t

void input_mark_t(DIEM *a,char *mahv,char *mon, int t)
{
    if(t==1)
    {
        printf("\nMark : ");
		a->t=mark();
    }
    if(t==2)
    {
        float m1,m2;
        printf("\nThis type has two tests.\n");
        printf("\nMark 1 : ");
        m1=mark();
        printf("\nMark 2 : ");
        m2=mark();
		a->t=(m1+m2)/(float) 2;
    }
	strcpy(a->mon,mon);
	strcpy(a->mahv,mahv);
}


//kiem tra da co diem mon hien tai cho sinh vien hien tai hay chua

int ton_tai_diem(char *mahv, char * mon)
{
    DIEM *ds;
    int n;
    ds=danhsachdiem(&n);
    register int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(ds[i].mahv,mahv)==0 && strcmp(ds[i].mon,mon)==0)
		{
			free(ds);
			return 1;
		}
    }
    return 0;
}



//**********************************************************************************************************************************
/////////////////////////////////////////////////////////////////Class information//////////////////////////////////////////////////
//**********************************************************************************************************************************


////add new class
void new_class()
{
	LOPHOC moi;
	LOPHOC *danhsach;
	int n,vitri;
    do
    {
        danhsach=danhsachlop(&n);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³        ADD CLASS INFORMATION        ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n");
        printf("\n\nType class no to add new !\n");
        fflush(stdin);
        classno(moi.tenlop);
        if(dupclass(danhsach,n,moi.tenlop,&vitri) == 1)
        {
            printf("\nThe Class No you entered already exists !");
            printf("\n\n           Retype(Y/N) ?");
            char tt=getch();
            if(tt=='y' || tt=='Y')
				continue;
            else
                break;
        }
        //Head teacher
        do
        {
            printf("\nHead Teacher : ");
            gets(moi.giangvien);
            strcpy(moi.giangvien,chuonhoaten(moi.giangvien));
        }while(nhapsai(moi.giangvien,25,2)==1);
        //room no
        int lythuyet,thuchanh;
        char ch;
        do
        {
            printf("\nRoom No.");
            printf("\n\nClass (1->4) : ");
            ch=getche();
            if(ch<49 || ch>52)
                printf("\nError. class No from 1 to 4 -> retype !");
        }while(ch<49 || ch>52);
        lythuyet=ch-48;
        do
        {
            printf("\n\nLab (1->4) : ");
            ch=getche();
            if(ch<49 || ch>52)
            {
                printf("\nError. class No from 1 to 4 -> retype !");
                ch=getche();
            }
        }while(ch<49 || ch>52);
        thuchanh=ch-48;
        strcpy(moi.phonghoc,tenphong(lythuyet,thuchanh));

        timeslot(moi.giohoc);

        fflush(stdin);
        do
        {
            printf("\n\nStudent Number (5->30) : ");
            scanf("%d",&moi.siso);
            if(moi.siso<5 || moi.siso>30)
            {
                printf("\nError Student number from 5 to 30 -> retype !\n");
            }
        }while(moi.siso<5 || moi.siso>30);
        //--ghi lop hoc moi vao file CLASS.DAT
        clrscr();
        printf("\n\n\n\n\n\n\n\n");
        printf("\n->Your new class you entered\n\n\n\n\n");
        hienlop(moi);
        printf("\n\n\n\t\t\t        Save this class (Y/N) ?");
        char save;
        save=getch();
        if(save == 'y' || save == 'Y')
        {
            if(write_class(moi)==1)
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t    Add new class sucessfull !");
				printf("\n\t\t\t      Press any key to continue !");
                getch();
            }
            else
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t    Add new class not sucess !");
				printf("\n\t\t\t      Press any key to continue !");
                getch();
            }
        }
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tDo you want continue add new class (Y/N) ?");
        char tieptuc=getch();
        if(tieptuc=='y' || tieptuc=='Y')
            continue;
        else
        {
            free(danhsach);
            return;
        }
    }while(1);
}

//edit class

void edit_class()
{
	char classedit[10],ch;
	LOPHOC *danhsach;
	int vitri, n;
	do
	{
        danhsach=danhsachlop(&n);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³        EDIT CLASS INFORMATION       ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n");
        printf("\n\nType class no to edit !\n");
        fflush(stdin);
        classno(classedit);
        if(dupclass(danhsach,n,classedit,&vitri) == 0)
        {
            char ch;
            printf("\n\nClass No. you entered is not found !");
            printf("\n          Retype (Y/N) ?");
            ch=getch();
            if(ch=='y' || ch == 'Y')
                continue;
            else
                break;
        }
        else
        {
			char ch;
			do
			{
				clrscr();
				printf("\n\n\n");
				hienlop(danhsach[vitri]);
				printf("\n\nSelect the information you want to edit\n");
				printf("\n-----------------------");
				printf("\n1. Edit all information");
				printf("\n2. Head teacher");
				printf("\n3. Room No.");
				printf("\n4. Time slot");
				printf("\n5. Student number");
				printf("\n6. Back to menu");
				printf("\n-----------------------");
				printf("\n   Enter number : ");
				ch=getche();
				clrscr();
				//---------
				switch(ch)
				{
					case '1':
					{
							do
							{
								printf("\nHead Teacher : ");
								gets(danhsach[vitri].giangvien);
								strcpy(danhsach[vitri].giangvien,chuonhoaten(danhsach[vitri].giangvien));
							}while(nhapsai(danhsach[vitri].giangvien,25,2)==1);
							int lythuyet,thuchanh;
							do
							{
								printf("\nRoom No.");
								printf("\nClass (1->4) : ");
								ch=getche();
								if(ch<49 || ch>52)
								{
									printf("\nSelect 1 to 4  !\n");
                                }
                            }while(ch<49 || ch>52);
                            lythuyet=ch-48;
                            do
                            {
                                printf("\nLab (1->4) : ");
                                ch=getche();
                                if(ch<49 || ch>52)
                                {
                                    printf("\nSelect 1 to 4 !");
                                }
                            }while(ch<49 || ch>52);
                            thuchanh=ch-48;
                            strcpy(danhsach[vitri].phonghoc,tenphong(lythuyet,thuchanh));
                            printf("\n");
                            timeslot(danhsach[vitri].giohoc);
                            fflush(stdin);
                            do
                            {
                                printf("\n\nStudent Number (5->30) : ");
                                scanf("%d",&danhsach[vitri].siso);
                                if(danhsach[vitri].siso<5 || danhsach[vitri].siso>30)
                                {
                                    printf("\nError Student number from 5 to 30 -> retype !");
                                }
                            }while(danhsach[vitri].siso<5 || danhsach[vitri].siso>30);
                        }
                        break;
                    case '2' :
                        {
                            do
                            {
                            printf("\nHead Teacher : ");
                            gets(danhsach[vitri].giangvien);
                            strcpy(danhsach[vitri].giangvien,chuonhoaten(danhsach[vitri].giangvien));
                            }while(nhapsai(danhsach[vitri].giangvien,25,2)==1);
                        }
                        break;
                    case '3' :
						{
                            int lythuyet,thuchanh;
                            do
                            {
                                printf("\nRoom No.");
                                printf("\n\nClass (1->4) : ");
                                ch=getche();
                                if(ch<49 || ch>52)
                                    printf("\nError. class No from 1 to 4 -> retype !");
                            }while(ch<49 || ch>52);
                            lythuyet=ch-48;
                            do
                            {
                                printf("\n\nLab (1->4) : ");
                                ch=getche();
                                if(ch<49 || ch>52)
                                {
                                    printf("\nError. class No from 1 to 4 -> retype !");
                                    ch=getche();
                                }
                            }while(ch<49 || ch>52);
                            thuchanh=ch-48;
							strcpy(danhsach[vitri].phonghoc,tenphong(lythuyet,thuchanh));
                        }
                        break;
                    case '4' :
                        timeslot(danhsach[vitri].giohoc);
                        break;
                    case '5' :
                        {
                            do
                            {
                                printf("\nStudent Number (5->30) : ");
                                fflush(stdin);
                                scanf("%d",&danhsach[vitri].siso);
                                if(danhsach[vitri].siso<5 || danhsach[vitri].siso>30)
                                {
                                    printf("\nError Student number from 5 to 30 -> retype !\n");
                                }
                            }while(danhsach[vitri].siso<5 || danhsach[vitri].siso>30);
                        }
                        break;
                    case '6' :
                        break;
                    default :
                        continue;
                }
                clrscr();
                printf("\n->After edit  \n\n\n");
                hienlop(danhsach[vitri]);
                printf("\n\n\t\t\t          Continue to edit (Y/N) ?");
                char tt=getch();
                if(tt=='n' || tt=='N')
                    break;
                fflush(stdin);
            }while(ch != '6');
            clrscr();
            printf("\n\n\n->Final edit.\n\n\n");
            hienlop(danhsach[vitri]);
            printf("\n\n\t\t\t        Save the change (Y/N) ?");
            char save=getch();
            if(save == 'y' || save == 'Y')
            {
                if(write_edit_class(danhsach[vitri])==1)
                {
                    clrscr();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t       Edit class sucessfull !");
                    getch();
                }
                else
                {
                    clrscr();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t        Error in write file !");
                    getch();
                }
            }

        }
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t   Do you want continue to edit other class (Y/N) ?");
        char continueedit=getch();
        if(continueedit=='y' || continueedit=='Y')
            continue;
        else
        {
            free(danhsach);
            return;
        }
	}while(1);
}

//ham xoa lop hoc
void delete_class()
{
	char classdelete[10],ch;
	LOPHOC *danhsach;
	int vitri, n;
    do
    {
        danhsach=danhsachlop(&n);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³       DELETE CLASS INFORMATION      ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n");
        printf("\n\nType class no to delete !\n");
        fflush(stdin);
        classno(classdelete);
        //kiem tra ten lop co ton tai hay khong
        if(dupclass(danhsach,n,classdelete,&vitri) == 0)
        {
            printf("\nClass No you entered is not found !");
            printf("\n           Retype(Y/N) ?");
            char ch=getch();
            if(ch=='y' || ch=='Y')
                continue;
            else
                return;
        }
        //kiem tra ten lop da co sinh vien hay chua
        if(cohv(classdelete)==1)
        {
            clrscr();
            printf("\n\n\n");
            hienlop(danhsach[vitri]);
            printf("\n\n\n      This class is referenced by students list -> not delete !");
            printf("\n\n\n\n\n\n\n\n\t\t Press any key to continue !");
            getch();
        }
        else
        {
            clrscr();
            printf("\n\n");
            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
            printf("\n                    ³       DELETE CLASS INFORMATION      ³");
            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
            printf("\n\n\n");
            hienlop(danhsach[vitri]);
            printf("\n\n\n\t\t\t  Do you want delete this class (Y/N) ?");
            char chdelete=getch();
            if(chdelete=='y' || chdelete=='Y')
            {
                        if(remove_class(danhsach[vitri])==1)
                        {
                            clrscr();
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t       Delete Class Information Sucessfull !");
                            printf("\n\t\t\t      Press any key to continue !");
                            getch();
                        }
                        else
                        {
                            clrscr();
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t      Delete Class Information not Sucess !");
                            printf("\n\n\n\t\t\t      Press any key to continue !");
                            getch();
                        }
            }
        }
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\t   Do you want to continue delete other class information (Y/N) ?");
        char chdelete=getch();
        if(chdelete=='y' || chdelete=='Y')
			continue;
        else
            return;
    }while(1);
}


//hien danh sach lop
void class_list()
{
	LOPHOC *danhsach;
	int n;
	char ch;
	danhsach=danhsachlop(&n);
	if(n==0)
	{
	    clrscr();
		printf("\n\n\n\n\n\n\n\n\n\t\t\tEmpty class list. please check back later !");
		printf("\n\n\n\t\t\t      Press any key to continue !");
		getch();
		return;
	}
	register int i,dem=0;
	do
	{
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³               CLASS LIST            ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        printf("\n\n\n\n\n                          Select the type to display");
        printf("\n");
        printf("\n                           --------------------------");
        printf("\n                           1. Sort by class name");
        printf("\n                           2. Sort by student number");
        printf("\n                           3. Back to menu");
        ch=getch();
        if(ch=='1' || ch=='2' || ch=='3')
        {
            if(ch=='1')
                bubble_class(n,danhsach,1);
            if(ch=='2')
                bubble_class(n,danhsach,2);
            if(ch=='3')
            {
                free(danhsach);
                return;
            }
        }
        else
            continue;
        clrscr();
        dem=0;
        printf("\n\n\n");
        printf("\n ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n ³                                CLASS LIST                                  ³");
        printf("\n ÃÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ´");
        printf("\n ³No³ Class No ³    Head teacher      ³    Room No     ³ Time Slot   ³S_Number³");
        printf("\n ÃÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");

        for(i=0;i<n;i++)
        {
            dem++;
            printf("\n ³%02d³%-10s³%-22s³%-16s³%-13s³   %-5d³",i+1,danhsach[i].tenlop,danhsach[i].giangvien,danhsach[i].phonghoc,danhsach[i].giohoc,danhsach[i].siso);
            printf("\n ÃÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
            if(dem == 10 && i<n-1)
            {
                printf("\n\n                     Press any key to display next page !");
                getch();
                dem=0;
                clrscr();
                printf("\n ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n ³                                CLASS LIST                                  ³");
                printf("\n ÃÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ´");
                printf("\n ³No³ Class No ³    Head teacher      ³    Room No     ³ Time Slot   ³S_Number³");
                printf("\n ÃÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
            }
        }
        printf("\n\n\n\t\t\t      Press any key to continue !");
        getch();
	}while(1);
}



//**********************************************************************************************************************************
///////////////////////////////////////////////////////////////Student information//////////////////////////////////////////////////
//**********************************************************************************************************************************

////////////////////////////////////////////////////////////new student
void new_student()
{
	HOCVIEN moi;
	HOCVIEN *danhsach;
	LOPHOC *mang;
	char ch;
	int solop,k,n;
	mang=danhsachlop(&solop);
    do
    {
        danhsach=danhsachhv(&n);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³        ADD STUDENT INFORMATION      ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n");
        printf("\n\nType roll no to add new !\n");
        fflush(stdin);
        rollno(moi.mahv);
        if(dupstudent(danhsach,n,moi.mahv,&k) == 1)
        {
            printf("\nThe Roll No you entered already exists !");
            printf("\n           Retype (Y/N) ?");
            ch=getch();
            if(ch=='y' || ch=='Y')
                continue;
            else
                return;
        }
        do
        {
            printf("\nFull Name : ");
            gets(moi.hoten);
            strcpy(moi.hoten,chuonhoaten(moi.hoten));
        }while(nhapsai(moi.hoten,25,2)==1);
        //birthday
        birthday(moi.ngaysinh);
        //Address
        do
        {
            printf("\nAddress : ");
            gets(moi.diachi);
            strcpy(moi.diachi,chuonhoaten(moi.diachi));
        }while(nhapsai(moi.diachi,24,5));
        //class
        do
        {
            classno(moi.tenlop);
            if(dupclass(mang,solop,moi.tenlop,&k) == 0)
            {
                printf("\nClass No. you entered is not found ! --> Retype .\n");
            }
            if(siso(moi.tenlop)>=siso_gioihan(mang,solop,moi.tenlop))
            {
                printf("\nClass No. you entered is full student !");
                printf("\n\nRetype other class no (Y/N) ?");
                ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
                    return;
            }
        }while(dupclass(mang,solop,moi.tenlop,&k) == 0 || siso(moi.tenlop)>=siso_gioihan(mang,solop,moi.tenlop));
        //-----------------------
        clrscr();
        printf("\n\n\n\t\t         Information you have entered as students \n\n");
        hienhv(moi);
        printf("\n\t\t\t        Save this student (Y/N) ?");
        char save;
        save=getch();
        if(save == 'y' || save == 'Y')
        {
            if(write_student(moi)==1)
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t   Add new student sucessfull !");
                printf("\n\n\n\t\t\t  Press any key to continue !");
                getch();
            }
            else
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t   Add new student not sucess !");
                printf("\n\n\n\t\t\t   Press any key to continue !");
                getch();
            }
        }
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t      Do you want continue add new student (Y/N) ?");
        char tieptuc=getch();
        if(tieptuc=='y' || tieptuc=='Y')
        {
            fflush(stdin);
            continue;
        }
        else
        {
            free(danhsach);
            free(mang);
            return;
        }
    }while(1);
}

void edit_per_student(int vitri)
{
	HOCVIEN *danhsach;
	LOPHOC *ds;
	int i,k,n;
	char ch;
	danhsach=danhsachhv(&n);
	ds=danhsachlop(&i);
    do
    {
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³        EDIT STUDENT INFORMATION     ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        hienhv(danhsach[vitri]);
        printf("\n\n\n\n\t          Select the information to edit");
        printf("\n");
        printf("\n\t\t         ------------------------");
        printf("\n\t\t         1. Edit all information");
        printf("\n\t\t         2. Full name");
        printf("\n\t\t         3. Birthday");
        printf("\n\t\t         4. Address");
        printf("\n\t\t         5. Class");
        printf("\n\t\t         6. Back to menu");
        printf("\n\t\t         ----------------------");
        printf("\n\t\t            Enter number : ");
        ch=getche();
        //---------
        switch(ch)
        {
            case '1':
            {
                do
                {
                    printf("\nFull Name : ");
                    gets(danhsach[vitri].hoten);
                    strcpy(danhsach[vitri].hoten,chuonhoaten(danhsach[vitri].hoten));
                }while(nhapsai(danhsach[vitri].hoten,25,2)==1);
                //birthday
                birthday(danhsach[vitri].ngaysinh);
                //Address
                do
                {
                    printf("\nAddress : ");
                    gets(danhsach[vitri].diachi);
                    strcpy(danhsach[vitri].diachi,chuonhoaten(danhsach[vitri].diachi));
                }while(nhapsai(danhsach[vitri].diachi,24,5));
                //class
                do
                {
                    classno(danhsach[vitri].tenlop);
                    if(dupclass(ds,i,danhsach[vitri].tenlop,&k) == 0)
                    {
                        printf("\nClass No. you entered is not found ! ->Retype !");
                    }
                }while(dupclass(ds,i,danhsach[vitri].tenlop,&k) == 0);
            }
            break;

            case '2' :
                {
                    do
                    {
                        printf("\nFull Name : ");
                        gets(danhsach[vitri].hoten);
                        strcpy(danhsach[vitri].hoten,chuonhoaten(danhsach[vitri].hoten));
                    }while(nhapsai(danhsach[vitri].hoten,25,2)==1);
                }
                break;
            case '3' :
                birthday(danhsach[vitri].ngaysinh);
                break;
            case '4' :
                {
                    do
                    {
                        printf("\nAddress : ");
                        gets(danhsach[vitri].diachi);
                        strcpy(danhsach[vitri].diachi,chuonhoaten(danhsach[vitri].diachi));
                    }while(nhapsai(danhsach[vitri].diachi,24,5));
                }
                break;
            case '5' :
                {
                    do
                    {
                        classno(danhsach[vitri].tenlop);
                        if(dupclass(ds,i,danhsach[vitri].tenlop,&k) == 0)
                        {
                            char chtt;
                            printf("\nClass No. you entered is not found !");
                            printf("\n\n\        Retype (Y/N) ?");
                            chtt=getch();
                            if(chtt == 'y' || chtt == 'Y')
                                continue;
                            else
                                break;
                        }
						if(siso(danhsach[vitri].tenlop)>=siso_gioihan(ds,i,danhsach[vitri].tenlop))
                        {
                            printf("\nClass No. you entered is full student !");
                            printf("\n\nRetype other class no (Y/N) ?");
                            ch=getch();
                            if(ch=='y' || ch=='Y')
                                continue;
                            else
                                break;
                        }
                    }while(dupclass(ds,i,danhsach[vitri].tenlop,&k) == 0 || siso(danhsach[vitri].tenlop)>=siso_gioihan(ds,i,danhsach[vitri].tenlop));
                }
                break;
            case '6' :
                break;
            default :
                continue;
        }
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³        EDIT STUDENT INFORMATION     ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        printf("\nAfter edit......");
        hienhv(danhsach[vitri]);
        printf("\n\n\n\t\t\tContinue to edit other information (Y/N) ? ");
        char tt=getch();
        if(tt=='n' || tt=='N')
            break;
        fflush(stdin);
    }while(ch != '6');
    clrscr();
    printf("\n\n");
    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
    printf("\n                    ³        EDIT STUDENT INFORMATION     ³");
    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
    printf("\n\n\n");
    printf("\nAfter final edit......");
    hienhv(danhsach[vitri]);
    printf("\n\n\t\t\t\t  Save the change (Y/N) ?");
    char save=getch();
    if(save == 'y' || save == 'Y')
    {
        if(write_edit_student(danhsach[vitri])==1)
        {
            clrscr();
            printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t Edit student information sucessfull !");
            printf("\n\n\n\t\t\t      Press any key to continue !");
            getch();
        }
        else
        {
            clrscr();
            printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t Edit student information not sucess !");
            printf("\n\n\n\t\t\t      Press any key to continue !");
            getch();
        }
    }
}

//edit student
void edit_student()
{
    int thoat,vitri,i;
    char ch;
    do
    {
        clrscr();
        fflush(stdin);
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³       EDIT STUDENT INFORMATION      ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n");
        printf("\n\nType roll no to add edit !\n");
        fflush(stdin);
        do
        {
            if(find_by_roll(&vitri)==0)
            {
                printf("\nroll no you entered id not found !");
                printf("\n         Retype (Y/N) ?");
                char ch=getch();
                    if(ch=='y' || ch=='Y')
                        continue;
                    else
                        break;
            }
            else
            {
				edit_per_student(vitri);
				break;
            }
        }while(1);
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\t\t Continue edit other student information (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
            return;
    }while(1);
}

/////////////////////////////////////////////////////ham xoa hoc vien


void delete_per_student(int vitri)
{
	HOCVIEN *danhsach;
	char ch;
	int n;
    danhsach=danhsachhv(&n);
    clrscr();
    printf("\n\n");
    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
    printf("\n                    ³      DELETE STUDENT INFORMATION     ³");
    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
    printf("\n\n\n");
    hienhv(danhsach[vitri]);
    printf("\n\n\n\t\tDo you want delete this student (Y/N) ?");
    char chdelete=getch();
    if(chdelete=='y' || chdelete=='Y')
    {
        if(exit_student(danhsach[vitri].mahv)==1)
        {
            clrscr();
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n  This student is being referenced by student mark. Can not delete !");
            getch();
        }
        else
        {
            if(remove_student(danhsach[vitri])==1)
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t       Delete student information sucessfull !");
                printf("\n\n\n\t\t\t      Press any key to continue !");
                getch();
            }
            else
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t       Delete student information not sucess !");
                printf("\n\n\n\t\t\t      Press any key to continue !");
                getch();
            }
        }
    }
}

//delete student
void delete_student()
{
	int vitri;
	char ch;
	do
	{
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³      DELETE STUDENT INFORMATION     ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
		printf("\nType roll no to delete ........\n");
		if(find_by_roll(&vitri)==0)
        {
            printf("\n\nroll no you entered id not found !");
            printf("\n            Retype (Y/N) ?");
            ch=getch();
            if(ch=='y' || ch=='Y')
                continue;
            else
                return;
        }
        else
        {
            delete_per_student(vitri);
        }
		clrscr();
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t        Continue delete other student information (Y/N) ?");
		ch=getch();
		if(ch=='y' || ch=='Y')
			continue;
		else
			return;
	}while(1);
}

//////////////student list

void student_list()
{
	HOCVIEN *hv;
	int n;
	char ch;
	register int i,dem=0;
	hv=danhsachhv(&n);
	if(n==0)
	{
	    clrscr();
		printf("\n\n\t\t\tEmpty student list. please check back later !");
		printf("\n\n\n\t\t\t      Press any key to continue !");
		getch();
        return;
	}
	do
	{
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³              STUDENT LIST           ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n\n                   Select the type to display");
        printf("\n");
        printf("\n                           -------------------");
        printf("\n                           1. Sort by roll no");
        printf("\n                           2. Sort by name");
        printf("\n                           3. Sort by class");
        printf("\n                           4. Back to menu");
        ch=getch();
        if(ch=='1' || ch=='2' || ch=='3' || ch=='4')
        {
            if(ch=='1')
                bubble_student(n,hv,1);
            if(ch=='2')
                bubble_student(n,hv,2);
            if(ch=='3')
                bubble_student(n,hv,3);
            if(ch=='4')
            {
                free(hv);
                return;
            }
        }
        else
            continue;
        clrscr();
        printf("\n\n\n");
        printf("\nÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n³                                 STUDENT LIST                                ³");
        printf("\nÃÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ´");
        printf("\n³No³ roll No ³   Full name       ³ Birth day³        Address         ³  Class ³");
        printf("\nÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
        dem=0;
        for(i=0;i<n;i++)
        {
            dem++;
            printf("\n³%02d³%-9s³%-19s³%-10s³%-24s³%-8s³",i+1,hv[i].mahv,hv[i].hoten,hv[i].ngaysinh,hv[i].diachi,hv[i].tenlop);
            printf("\nÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
            if(dem == 10 && i<n-1)
            {
                printf("\n\n\t\t        Press any key to display next page !");
                getch();
                dem=0;
                clrscr();
                printf("\n\n\n");
                printf("\nÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n³                                 STUDENT LIST                                ³");
                printf("\nÃÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ´");
                printf("\n³No³ roll No ³   Full name       ³ Birth day³        Address         ³  Class ³");
                printf("\nÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
            }
        }
        printf("\n\n\t\t       Presss any key to continue !");
        getch();
	}while(1);
}


///////////////////////////////tim kiem hoc vien

void findbyroll()
{
	HOCVIEN *hv;
	int n;
	int vitri;
	char ch;
	hv=danhsachhv(&n);
	do
	{
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³       FIND STUDENT INFORMATION      ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        printf("\nType roll no to find.....\n\n");
		if(find_by_roll(&vitri)==0)
		{
			printf("\nRoll no you entered id not found !");
			printf("\n        Retype (Y/N) ?");
			char ch=getch();
				if(ch=='y' || ch=='Y')
					continue;
				else
					return;
		}
		else
		{
            clrscr();
            printf("\n\n");
            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
            printf("\n                    ³       FIND STUDENT INFORMATION      ³");
            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
            printf("\n\n\n");
			hienhv(hv[vitri]);
			printf("\n\n\t\t   You want to do with this student ?");
			printf("\n\t\t\t             -------------");
			printf("\n\t\t\t             1. Edit");
			printf("\n\t\t\t             2. Delete");
			printf("\n\t\t\t             3. No thank !");
			printf("\n\t\t\t             -------------");
			printf("\n\t\t\t             Enter num ber : ");
			char todo=getche();
			if(todo=='1')
				edit_per_student(vitri);
			else
				if(todo=='2')
					delete_per_student(vitri);
		}
		clrscr();
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t            Continue find other roll no (Y/N) ?");
		ch=getch();
		if(ch=='y' || ch=='Y')
            continue;
        else
            return;
	}while(1);
}


void find_by_name()
{
	char namefind[25];
	HOCVIEN *danhsach;
	int n;
	register int i;
	char ch;
	do
	{
	    danhsach=danhsachhv(&n);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³       FIND STUDENT INFORMATION      ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        printf("\n\nType the name to find......\n\n");
        do
        {
            printf("\nFull Name : ");
            gets(namefind);
            strcpy(namefind,chuonhoaten(namefind));
        }while(nhapsai(namefind,25,2)==1);
        for(i=0;i<n;i++)
        {
            if(strstr(danhsach[i].hoten,namefind) != NULL)
            {
                clrscr();
                printf("\n\n");
                printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n                    ³       FIND STUDENT INFORMATION      ³");
                printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                printf("\n\n\n");
                hienhv(danhsach[i]);
                printf("\n\n\n\n\t           Is this student that you're find (Y/N) ?");
                char chon=getch();
                if(chon == 'y' || chon == 'Y')
                {
                    clrscr();
                    printf("\n\n");
                    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n                    ³       FIND STUDENT INFORMATION      ³");
                    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n\n\n");
                    hienhv(danhsach[i]);
                    printf("\n\n\t\t\tYou want to do with this student ?");
                    printf("\n\t\t\t         -------------");
                    printf("\n\t\t\t         1. Edit");
                    printf("\n\t\t\t         2. Delete");
                    printf("\n\t\t\t         3. No thank !");
                    printf("\n\t\t\t         -------------");
                    printf("\n\t\t\t         Enter num ber : ");
                    char todo=getche();
                    if(todo=='1')
                    {
						edit_per_student(i);
						break;
                    }
                    else
                    {
                        if(todo=='2')
                        {
							delete_per_student(i);
							break;
                        }
                    }
                }
                else
                {
                    continue;
                }
            }
        }
        if(i==n)
        {
            clrscr();
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t         Name you entered is not found.");
            printf("\n\n\n\n\n\n\n\n\n\t\t           Press any key to continue !.");
            getch();
        }
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t            Continue find other name (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
            free(danhsach);
            return;
        }
	}while(1);
}

//find by address

void find_by_address()
{
	char addressfind[25],ch;
	HOCVIEN *danhsach;
	int n;
	register int i;
	do
	{
	    fflush(stdin);
	    fflush(stdout);
	    danhsach=danhsachhv(&n);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³       FIND STUDENT INFORMATION      ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        printf("\n\nType the address to find......\n\n");
        do
        {
            printf("\nAddress : ");
            gets(addressfind);
            strcpy(addressfind,chuonhoaten(addressfind));
        }while(nhapsai(addressfind,24,2));
        for(i=0;i<n;i++)
        {
            if(strstr(danhsach[i].diachi,addressfind) != NULL)
            {
                clrscr();
                printf("\n\n");
                printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n                    ³       FIND STUDENT INFORMATION      ³");
                printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                printf("\n\n\n");
                hienhv(danhsach[i]);
                printf("\n\n\t\t\tIs this student that you're find  (Y/N) ?");
                char chon=getch();
                if(chon == 'y' || chon == 'Y')
                {
                    clrscr();
                    printf("\n\n");
                    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n                    ³       FIND STUDENT INFORMATION      ³");
                    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n\n\n");
                    hienhv(danhsach[i]);
                    printf("\n\n\t\t\tYou want to do with this student ?");
                    printf("\n\t\t\t         -------------");
                    printf("\n\t\t\t         1. Edit");
                    printf("\n\t\t\t         2. Delete");
                    printf("\n\t\t\t         3. No thank !");
                    printf("\n\t\t\t         -------------");
					printf("\n\t\t\t         Enter num ber : ");
                    char todo=getch();
                    if(todo=='1')
                    {
						edit_per_student(i);
						break;
                    }
                    else
                    {
                        if(todo=='2')
                        {
							delete_per_student(i);
							break;
                        }
                    }
                }
                else
                {
                    continue;
                }
            }
        }
        if(i==n)
        {
            clrscr();
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t         Address you entered is not found.");
            printf("\n\n\n\n\n\n\n\n\n\t\t           Press any key to continue !.");
            getch();
        }
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t        Continue find other address (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
            free(danhsach);
            return;
        }
	}while(1);
}


//********************************************************************************************************************
///////////////////////////////////////////////////Studen Mark////////////////////////////////////////////////////////
//********************************************************************************************************************

////add student mark

void add_student_mark_per_student(char *mahv, char *mon, int kieu)
{
	char ch,hoten[25];
	int vitri,t,p,tt,pp,chon;
	float nhap;
	DIEM tg;
	DIEMHV vidu;
    clrscr();
    printf("\n\n");
    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
    printf("\n                    ³           ADD STUDENT MARK          ³");
    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
    printf("\n\n\n\n");
	if(ton_tai_diem(mahv,mon)==0)
	{
		strcpy(tg.mahv,mahv);
		strcpy(tg.mon,mon);
		vidu=mark_info(tg);
		clrscr();
		printf("\n\n");
		printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
		printf("\n                    ³           ADD STUDENT MARK          ³");
		printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
		printf("\n\n\n\n");
		printf("\n                  ÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄ¿");
		printf("\n                  ³ roll No ³   Full name       ³  Subject  ³");
		printf("\n                  ÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
		printf("\n                  ³%-9s³%-19s³    %-7s³",vidu.diem.mahv,vidu.hoten,vidu.diem.mon);
		printf("\n                  ÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÙ");
		tg.t = -1.00;
		tg.p = -1.00;
		issubject(mon,&t,&p,&tt,&pp);
		if(kieu==1)
			nhap_diem(&tg.t,&nhap,t,p,kieu);
		else
			nhap_diem(&nhap,&tg.p,t,p,kieu);
		clrscr();
		printf("\n\n");
		printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
		printf("\n                    ³           ADD STUDENT MARK          ³");
		printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
		printf("\n\n\n\n");
		vidu=mark_info(tg);
		printf("\nStudent mark you entered.....\n\n\n");
		hiendiem(vidu,kieu);
		printf("\n\n\t\t          Save this student mark (Y/N) ?");
		ch=getch();
		if(ch=='y' || ch=='Y')
		{
			if(write_mark(tg)==1)
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t           Add student mark sucessfull !");
                printf("\n\n\n\n\n\n\n\t\t            Press any key to continue !");
                getch();
            }
            else
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t          Add new student mark not sucess !");
                printf("\n\n\n\n\n\n\n\n\n\n\t\t             Press any key to continue !");
                getch();
            }
		}
	}
	else
	{
		if(exist_mark(mahv,mon,kieu,&tg)==1)
		{
			vidu=mark_info(tg);
			printf("\n\n\t              Subject of this type already exists !\n\n\n");
			hiendiem(vidu,kieu);
			printf("\n\n\n\t\t        Press any key to continue !");
			getch();
		}
		else
		{
			vidu=mark_info(tg);
			clrscr();
			printf("\n\n");
			printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
			printf("\n                    ³           ADD STUDENT MARK          ³");
			printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
			printf("\n\n\n\n");
			printf("\n                  ÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄ¿");
			printf("\n                  ³ roll No ³   Full name       ³  Subject  ³");
			printf("\n                  ÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
			printf("\n                  ³%-9s³%-19s³    %-7s³",vidu.diem.mahv,vidu.hoten,vidu.diem.mon);
			printf("\n                  ÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÙ");
			issubject(mon,&t,&p,&tt,&pp);
			if(kieu==1)
				nhap_diem(&tg.t,&nhap,t,p,kieu);
			else
				nhap_diem(&nhap,&tg.p,t,p,kieu);
			clrscr();
			printf("\n\n");
			printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
			printf("\n                    ³           ADD STUDENT MARK          ³");
			printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
			printf("\n\n\n\n");
			vidu=mark_info(tg);
			printf("\nStudent mark you entered.....\n\n\n");
			hiendiem(vidu,kieu);
			printf("\n\n\t\t          Save this student mark (Y/N) ?");
			ch=getch();
			if(ch=='y' || ch=='Y')
			{
				if(write_edit_mark(tg)==1)
                {
                    clrscr();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t           Add student mark sucessfull !");
                    printf("\n\n\n\n\n\n\n\t\t            Press any key to continue !");
                    getch();
                }
                else
                {
                    clrscr();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t          Add new student mark not sucess !");
                    printf("\n\n\n\n\n\n\n\n\n\n\t\t             Press any key to continue !");
                    getch();
                }
			}
		}
    }
    return;
}

//them diem moi

void add_student_mark()
{
    char mahv[10],mon[5],ch;
    int kieu,n,vitri,t,p;
    HOCVIEN *ds;
    ds=danhsachhv(&n);
    do
    {
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³           ADD STUDENT MARK          ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        printf("\nType roll no .....\n");
        fflush(stdin);
        rollno(mahv);
		if(dupstudent(ds,n,mahv,&vitri)==0)
        {
            printf("\n\nRoll no you entered is not found !");
            printf("\n           Retype (Y/N) ?");
            ch=getch();
            if(ch=='y' || ch=='Y')
                continue;
            else
                return;
        }
        else
        {
            subject(mon,&t,&p,&kieu);
            add_student_mark_per_student(mahv,mon,kieu);
        }
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³           ADD STUDENT MARK          ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        printf("\n\n\n\t\tDo you want continue add new student mark (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
            free(ds);
            return;
        }
    }while(1);
}


//hien thi danh sach diem hoc vien

void student_mark_list()
{
	DIEM *ds;
	DIEMHV tem;
	calloc(1,sizeof(DIEM));
	int n,t,p,chon,dem=0,page=0;
	register int i;
	char mon[5],ch,tenlop[10];
	ds=danhsachdiem(&n);
	do
	{
	    fflush(stdin);
        clrscr();
        printf("\n\n\n\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³           STUDENT MARK LIST         ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        printf("\nType Subject and subject type to display.....\n");
        subject(mon,&t,&p,&chon);
        do
        {
            clrscr();
            printf("\n\n\n\n\n");
            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
            printf("\n                    ³           STUDENT MARK LIST         ³");
            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
            printf("\n\n\n\n");
            printf("\n\n\n\n\n                          Select the type to display");
            printf("\n");
            printf("\n                                Subject: [%s]",mon);
            printf("\n                           --------------------------");
            printf("\n                           1. Sort by class no");
            printf("\n                           2. Sort by mark");
            printf("\n                           3. Other subject");
            ch=getch();
            if(ch=='1' || ch=='2' || ch=='3')
            {
                if(ch=='1')
                    bubble_student_mark(n,ds,1,chon);
                if(ch=='2')
                    bubble_student_mark(n,ds,2,chon);
                if(ch=='3')
                {
                    break;
                }
            }
            else
                    continue;
            if(chon==1)
            {
                page=0;
                dem=0;
                clrscr();
                printf("\n\n");
                printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n                    ³           STUDENT MARK LIST         ³");
                printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                printf("\n\n\n");
                printf("\n                                Subject: [%s]",mon);
                printf("\n            ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n            ³No³ roll No ³ Class no ³   Full name       ³ Mark of T ³");
                printf("\n            ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
                for(i=0;i<n;i++)
                {
                    if(strcmp(ds[i].mon,mon)==0 && ds[i].t>0)
                    {
                        class_name(ds[i].mahv,tenlop);
                        dem++;
                        page++;
                        tem=mark_info(ds[i]);
                        printf("\n            ³%02d³%-9s³  %-8s³%-19s³   %-8.2f³",dem,tem.diem.mahv,tenlop,tem.hoten,tem.diem.t);
                        printf("\n            ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
                        if(page == 10 && i<n-1)
                        {
                            printf("\n\n\t\t      Press any key to display next page !");
                            page=0;
                            getch();
                            clrscr();
                            printf("\n\n");
                            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n                    ³           STUDENT MARK LIST         ³");
                            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                            printf("\n\n\n");
                            printf("\n                                Subject: [%s]",mon);
                            printf("\n            ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n            ³No³ roll No ³ Class no ³   Full name       ³ Mark of T ³");
                            printf("\n            ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
                        }
                    }
                }
            }
            else
            {
                dem=0;
                page=0;
                clrscr();
                printf("\n\n");
                printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n                    ³           STUDENT MARK LIST         ³");
                printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                printf("\n\n\n");
                printf("\n                                Subject: [%s]",mon);
                printf("\n            ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄ¿");
                printf("\n            ³No³ roll No ³ Class no ³   Full name       ³ Mark of P ³");
                printf("\n            ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
                for(i=0;i<n;i++)
                {
                    if(strcmp(ds[i].mon,mon)==0 && ds[i].p>0)
                    {
                        dem++;
                        page++;
                        tem=mark_info(ds[i]);
                        printf("\n            ³%02d³%-9s³  %-8s³%-19s³   %-8.2f³",dem,tem.diem.mahv,tenlop,tem.hoten,tem.diem.p);
                        printf("\n            ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
                        if(page == 10 && i<n-1)
                        {
                            printf("\n\n\tPress any key to display next page !");
                            page=0;
                            getch();
                            clrscr();
                            printf("\n\n");
                            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n                    ³           STUDENT MARK LIST         ³");
                            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                            printf("\n\n\n");
                            printf("\n                                Subject: [%s]",mon);
                            printf("\n            ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄ¿");
                            printf("\n            ³No³ roll No ³ Class no ³   Full name       ³ Mark of P ³");
                            printf("\n            ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄ´");
                        }
                    }
                }
            }
            if(dem==0)
            {
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\tThis subject has no student mark. Please check back later !");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t            Press any key to continue !");
                getch();
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t            Press any key to continue !");
                getch();
            }

        }while(1);
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t       Continue with other subject (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
            free(ds);
            return;
        }
	}while(1);
}

//them diem cho mot lop
void add_class_mark()
{
    LOPHOC *dslop;
	HOCVIEN *dshv;
	int n,vitri,t,p,kieu,siso;
	char tenlop[10],mon[5],ch;
	register int i;
	dslop=danhsachlop(&n);
    do
    {
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³            ADD CLASS MARK           ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        fflush(stdin);
        printf("\nType class no to add class mark ......\n\n");
        do
        {
            classno(tenlop);
            if(dupclass(dslop,n,tenlop,&vitri)==0)
            {
                printf("\nClass no you entered is not found !");
                printf("\n\n         Retype (Y/N) ?");
                ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(dslop);
                    free(dshv);
                    return;
                }
            }
            if(cohv(tenlop)==0)
            {
                printf("\n\nClass no you entered not student !");
                printf("\n\n         Retype (Y/N) ?");
                ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(dslop);
                    free(dshv);
                    return;
                }
            }
        }while(dupclass(dslop,n,tenlop,&vitri)==0 || cohv(tenlop)==0);
        dshv=danh_sach_hv_theo_lop(tenlop,&siso);
        subject(mon,&t,&p,&kieu);
        //----------------------------------------
        for(i=0;i<siso;i++)
        {
			add_student_mark_per_student(dshv[i].mahv,mon,kieu);
        }
        //----------------------------------------
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t       Continue with other class (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
		{
			free(dshv);
            continue;
		}
        else
        {
            free(dshv);
            free(dslop);
            return;
        }
    }while(1);
}


//sua diem hoc vien

void edit_student_mark_per_student(char *mahv, char *mon, int kieu)
{
	char ch;
	int n,vitri,t,p,tt,pp,chon;
	HOCVIEN *ds;
	DIEM tg;
	DIEMHV vidu;
	ds=danhsachhv(&n);
    clrscr();
    printf("\n\n");
    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
    printf("\n                    ³           EDIT STUDENT MARK         ³");
    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
    printf("\n\n\n\n");
    if(exist_mark(mahv,mon,kieu,&tg)==0)
    {
        vidu=mark_info(tg);
        printf("\n\n\t            This student does not type of mark you chose !\n\n\n");
        printf("\n\n\t\t        Add new student mark with us (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
        {
            add_student_mark_per_student(mahv,mon,kieu);
        }
        else
        {
            free(ds);
            return;
        }
    }
    else
    {
        fflush(stdin);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³          EDIT STUDENT MARK          ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        vidu=mark_info(tg);
        printf("\n\n\n\n");
        hiendiem(vidu,kieu);
        printf("\n\n\n\n\n\t\t             Edit this student mark (Y/N) ?");
        fflush(stdin);
        ch=getch();
        if(ch=='y' || ch=='Y')
        {
            issubject(mon,&t,&p,&tt,&pp);
            printf("\n\nEnter mark to edit........");
            nhap_diem(&tg.t,&tg.p,t,p,kieu);
            strcpy(tg.mahv,mahv);
            strcpy(tg.mon,mon);
            vidu=mark_info(tg);
            clrscr();
            printf("\n\n");
            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
            printf("\n                    ³          EDIT STUDENT MARK          ³");
            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
            printf("\n\n\n\n");
            printf("\nStudent mark after edit.....\n\n\n");
            hiendiem(vidu,kieu);
            printf("\n\n\t\t           Save this student mark (Y/N) ?");
            ch=getch();
            if(ch=='y' || ch=='Y')
            {
                if(write_edit_mark(tg)==1)
                {
                    clrscr();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t          Edit student mark sucessfull !");
                    printf("\n\n\n\t\t           Press any key to continue !");
                    getch();
                }
                else
                {
                    clrscr();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t    Edit new student mark not sucess !");
                    printf("\n\n\n\n\t\t       Press any key to continue !");
                    getch();
                }
            }
        }
    }
    free(ds);
    return;
}

//--------------------

void edit_student_mark()
{
    HOCVIEN *dshv;
	int n,t,p,kieu,vitri;
	char mon[5],ch;
    do
    {
        dshv=danhsachhv(&n);
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³          EDIT STUDENT MARK          ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        fflush(stdin);
        printf("\nType roll no ......\n\n");
        fflush(stdin);
        do
        {
           if(find_by_roll(&vitri)==0)
           {
			   printf("\n\nThe roll you entered is not found ! ->Retype !\n\n");
               continue;
           }
           else
           {
			   break;
           }
        }while(1);
        printf("\n\nType subject and subject type to continue.......\n");
        fflush(stdin);
        subject(mon,&t,&p,&kieu);
        //----------------------------
		edit_student_mark_per_student(dshv[vitri].mahv,mon,kieu);
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t    Continue with other student mark (Y/N) ?");
		ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
            return;

    }while(1);
}

//sua diem cho ca lop

void edit_class_mark()
{
    LOPHOC *dslop;
    HOCVIEN *dshv;
	int n,vitri,t,p,kieu,siso;
	char tenlop[10],mon[5],ch;
	register int i;
	dslop=danhsachlop(&n);
    do
    {
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³           EDIT CLASS MARK           ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        fflush(stdin);
        printf("\nType class no to edit class mark ......\n\n");
        do
        {
            classno(tenlop);
            if(dupclass(dslop,n,tenlop,&vitri)==0)
            {
                printf("\nClass no you entered is not found !");
                printf("\n\n         Retype (Y/N) ?");
                ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(dslop);
                    free(dshv);
                    return;
                }
            }
            if(cohv(tenlop)==0)
            {
                printf("\n\nClass no you entered not student !");
                printf("\n\n         Retype (Y/N) ?");
                ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(dslop);
                    free(dshv);
                    return;
                }
            }
        }while(dupclass(dslop,n,tenlop,&vitri)==0 || cohv(tenlop)==0);
        dshv=danh_sach_hv_theo_lop(tenlop,&siso);
        subject(mon,&t,&p,&kieu);
        //----------------------------------------
        for(i=0;i<siso;i++)
        {
			edit_student_mark_per_student(dshv[i].mahv,mon,kieu);
        }
        //----------------------------------------
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t      Continue edit with other class (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
            free(dshv);
            free(dslop);
            return;
        }
    }while(1);
}

//hien thi danh sach diem theo lop - loc theo mon

void class_mark_list_per_subject()
{
    char tenlop[10],mon[5],ch;
    HOCVIEN *dslop;
    DIEM *ds;
	DIEMHV tem;
	LOPHOC *lop;
	int siso,t,p,chon,n,co,dem,page,vitri,solop;
    register int i,j;
	ds=danhsachdiem(&n);
	lop=danhsachlop(&solop);
    do
    {
        clrscr();
        printf("\n\n");
        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    ³      CLASS MARK LIST PER SUBJECT    ³");
        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        fflush(stdin);
        printf("\nType class no......\n\n");
        do
        {
            classno(tenlop);
			if(dupclass(lop,solop,tenlop,&vitri)==0)
            {
                printf("\nClass no you entered is not found !");
                printf("\n\n         Retype (Y/N) ?");
                ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(dslop);
					free(ds);
					free(lop);
                    return;
                }
            }
            if(cohv(tenlop)==0)
            {
                printf("\n\nClass no you entered not student !");
                printf("\n\n         Retype (Y/N) ?");
                ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(dslop);
					free(ds);
					free(lop);
                    return;
                }
            }
		}while(dupclass(lop,solop,tenlop,&vitri)==0 || cohv(tenlop)==0);
        fflush(stdin);
        dslop=danh_sach_hv_theo_lop(tenlop,&siso);
        do
        {
            fflush(stdin);
            printf("\n\nType subject to display ...........\n");
            subject(mon,&t,&p,&chon);
            co=0;
            for(j=0;j<siso;j++)
            {
				for(i=0;i<n;i++)
                {
                    if(strcmp(dslop[j].mahv,ds[i].mahv)==0 && strcmp(ds[i].mon,mon)==0)
                    {
                        if(chon==1)
                        {
                            if(ds[i].t>0)
                            {
                                co=1;
                                break;
                            }
                        }
                        else
                        {
                            if(ds[i].p>0)
                            {
                                co=1;
                                break;
                            }
                        }

                    }
                }
                if(co==1)
                    break;
            }
            if(co==0)
            {
                clrscr();
				printf("\n\n        This class is not the kind of subjects or type of your choice !");
				printf("\n\n\n\t\t        Continue with other subject (Y/N)?");
				ch=getch();
                if(ch=='y' || ch=='Y')
                    continue;
                else
					break;
			}
			else
            {
                do
                {
                    clrscr();
                    printf("\n\n");
                    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n                    ³      CLASS MARK LIST PER SUBJECT    ³");
                    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n\n\n\n");
                    printf("\n\n\n\n\n                          Select the type to display");
                    printf("\n");
                    printf("\n                  Class [%s] - Subject [%s] - Mark type [T]\n\n",tenlop,mon);
                    printf("\n                           --------------------------");
                    printf("\n                           1. Sort by student name");
                    printf("\n                           2. Sort by mark");
                    printf("\n                           3. Other object");
                    ch=getch();
                    if(ch=='1' || ch=='2' || ch=='3')
                    {
                        if(ch=='1')
							bubble_student(siso,dslop,2);
                        //    bubble_class_mark_list(n,ds,chon);
                        if(ch=='2')
							bubble_class_mark_list(siso,dslop,mon,chon);
                            //bubble_class_mark_list(n,ds,chon);
                        if(ch=='3')
                        {
                            break;
                        }
                    }
                    else
                            continue;
                    if(chon==1)
                    {
                        dem=0;
                        page=0;
                        clrscr();
                        printf("\n\n");
                        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                        printf("\n                    ³      CLASS MARK LIST PER SUBJECT    ³");
                        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                        printf("\n\n\n\n");
                        printf("\n                 Class [%s] - Subject [%s] - Mark type [T]\n\n",tenlop,mon);
                        printf("\n                  ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
                        printf("\n                  ³No³ Roll No ³   Full name       ³   T   ³");
                        printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                        for(j=0;j<siso;j++)
                        {
                            for(i=0;i<n;i++)
                            {
                                if(strcmp(dslop[j].mahv,ds[i].mahv)==0 && strcmp(ds[i].mon,mon)==0 && ds[i].t>0.00)
                                {
                                    dem++;
                                    page++;
                                    tem=mark_info(ds[i]);
                                    printf("\n                  ³%02d³%-9s³%-19s³ %-6.2f³",dem,tem.diem.mahv,tem.hoten,tem.diem.t);
                                    printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                                    if(page == 10 && i<n-1)
                                    {
                                        printf("\n\n\t\t\tPress any key to display next page !");
                                        page=0;
                                        getch();
                                        clrscr();
                                        printf("\n\n");
                                        printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                                        printf("\n                    ³      CLASS MARK LIST PER SUBJECT    ³");
                                        printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                                        printf("\n\n\n\n");
                                        printf("\n                 Class [%s] - Subject [%s] - Mark type [T]\n\n",tenlop,mon);
                                        printf("\n                  ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
                                        printf("\n                  ³No³ Roll No ³   Full name       ³   T   ³");
                                        printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                                    }
                                }
                            }
                        }
                        printf("\n\n\t\t\t   Press any key to continue !");
                        getch();
                        clrscr();
                    }
                    else
                    {
                        dem=0;
                        page=0;
                        clrscr();
                        printf("\n                 Class [%s] - Subject [%s] - Mark type [P]",tenlop,mon);
                        printf("\n                  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                        printf("\n                  ³       Class Mark List Per Subject      ³");
                        printf("\n                  ÃÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ´");
                        printf("\n                  ³No³ Roll No ³   Full name       ³   P   ³");
                        printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                        dem=0;
                        for(j=0;j<siso;j++)
                        {
                            for(i=0;i<n;i++)
                            {
                                if(strcmp(dslop[j].mahv,ds[i].mahv)==0 && strcmp(ds[i].mon,mon)==0 && ds[i].p>0)
                                {
                                    dem++;
                                    page++;
                                    tem=mark_info(ds[i]);
                                    printf("\n                  ³%02d³%-9s³%-19s³ %-6.2f³",dem,tem.diem.mahv,tem.hoten,tem.diem.p);
                                    printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                                    if(page == 10 && i<n-1)
                                    {
                                        printf("\n\n\t\t\tPress any key to display next page !");
                                        page=0;
                                        getch();
                                        clrscr();
                                        printf("\n                 Class [%s] - Subject [%s] - Mark type [P]",tenlop,mon);
                                        printf("\n                  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                                        printf("\n                  ³       Class Mark List Per Subject      ³");
                                        printf("\n                  ÃÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ´");
                                        printf("\n                  ³No³ Roll No ³   Full name       ³   P   ³");
                                        printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");

                                    }
                                }
                            }
                        }
                        printf("\n\n\t\t\t   Press any key to continue !");
                        getch();
                        clrscr();
                    }
                }while(1);
            }
            clrscr();
            printf("\n\n\n\n\n\n\n\n\t\t\tContinue with other subject (Y/N) ?");
            ch=getch();
            if(ch=='y' || ch=='Y')
                continue;
            else
                break;
        }while(1);
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\t\t\tContinue with other class (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
		else
		{
			free(ds);
			free(lop);
			free(dslop);
			return;
		}
    }while(1);
}

//********************************************************************************************************************
///////////////////////////////////////////////      Report    ///////////////////////////////////////////////////////
//********************************************************************************************************************

//diem trung binh cac mon cua mot lop

void class_avg_mark_list()
{
	char tenlop[10],ch;
	LOPHOC *lop;
	HOCVIEN *dshv;
	int n,dem,i,solop,vitri,page,siso;
	lop=danhsachlop(&solop);
	do
	{
		clrscr();
		printf("\n\n");
		printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
		printf("\n                    ³       CLASS AVARAGE MARK LIST       ³");
		printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
		printf("\n\n\n\n");
		fflush(stdin);
		printf("\nType class no to display ...........\n\n");
		do
		{
			classno(tenlop);
			if(dupclass(lop,solop,tenlop,&vitri)==0)
			{
				printf("\nClass no you entered is not found !");
				printf("\n\n         Retype (Y/N) ?");
				ch=getch();
				if(ch=='y' || ch=='Y')
					continue;
				else
				{
					free(lop);
					free(dshv);
					return;
				}
			}
			if(cohv(tenlop)==0)
			{
				printf("\n\nClass no you entered not student !");
				printf("\n\n         Retype (Y/N) ?");
				ch=getch();
				if(ch=='y' || ch=='Y')
					continue;
				else
				{
					free(dshv);
					free(lop);
					return;
				}
			}
		}while(dupclass(lop,solop,tenlop,&vitri)==0 || cohv(tenlop)==0);
		dshv=danh_sach_hv_theo_lop(tenlop,&siso);
		do
		{
            clrscr();
            printf("\n\n");
            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
            printf("\n                    ³       CLASS AVARAGE MARK LIST       ³");
            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
            printf("\n\n\n\n");
            printf("\n\n\n\n\n                   Select the type to display");
            printf("\n");
			printf("\n                                Class [%s]\n\n",tenlop);
            printf("\n                           -----------------------");
            printf("\n                           1. Sort by student name");
            printf("\n                           2. Sort by avg mark");
            printf("\n                           3. Other class");
            ch=getch();
            if(ch=='1' || ch=='2' || ch=='3')
            {
                if(ch=='1')
                    bubble_class_avg(siso,dshv,1);
                if(ch=='2')
                    bubble_class_avg(siso,dshv,2);
                if(ch=='3')
                {
                    break;
                }
            }
            else
                continue;
            dem=0;
            page=0;
            clrscr();
            printf("\n\n");
            printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
            printf("\n                    ³       CLASS AVARAGE MARK LIST       ³");
            printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
            printf("\n\n\n");
            printf("\n                               Class [%s]\n\n",tenlop);
            printf("\n                  ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
            printf("\n                  ³No³ Roll No ³   Full name       ³  AVG  ³");
            printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
            for(i=0;i<siso;i++)
            {
                dem++;
                page++;
                printf("\n                  ³%02d³%-9s³%-19s³ %-6.2f³",dem,dshv[i].mahv,dshv[i].hoten,avg(dshv[i].mahv));
                printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                if(page == 10 && i<siso-1)
                {
                    printf("\n\n            Press any key to display next page !");
                    getch();
                    page=0;
                    clrscr();
                    printf("\n\n");
                    printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n                    ³       CLASS AVARAGE MARK LIST       ³");
                    printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n\n\n");
                    printf("\n                             Class [%s]\n\n",tenlop);
                    printf("\n                  ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
                    printf("\n                  ³No³ Roll No ³   Full name       ³  AVG  ³");
                    printf("\n                  ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                }
            }
            printf("\n\n\t\t\t    Press any key to continue !");
            getch();
		}while(1);
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tContinue with other class (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
			free(dshv);
            free(lop);
            return;
		}
	}while(1);
}

//diem chi tiet va diem trung binh cua tung hoc vien

void student_average_mark()
{
	DIEM *ds;
	HOCVIEN *mang;
	float tbmon;
	int sohv,vitri,page;
	int n,dem,t,p,tt,pp,chon,a;
	char mahv[10],tenlop[10],ch;
	register int i;
	ds=danhsachdiem(&n);
	mang=danhsachhv(&sohv);
	do
	{
		clrscr();
		printf("\n\n");
		printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
		printf("\n                    ³         STUDENT AVERAGE MARK        ³");
		printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
		printf("\n\n\n\n");
		fflush(stdin);
		printf("\nType roll no to display ...........\n\n");
		do
		{
			rollno(mahv);
			if(dupstudent(mang,sohv,mahv,&vitri)==0)
			{
				printf("\nroll no you enter not found !\n");
				printf("\n\n     Retype (Y/N) ?");
				ch=getche();
				if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(ds);
                    free(mang);
                    return;
                }
			}
			if(exit_student(mahv)==0)
			{
				printf("\n\nroll no you enter any subject no point !\n");
				printf("\n\n               Retype (Y/N) ?");
				ch=getche();
				if(ch=='y' || ch=='Y')
                    continue;
                else
                {
                    free(ds);
					free(mang);
                    return;
                }
			}
		}while(dupstudent(mang,sohv,mahv,&vitri)==0 || exit_student(mahv)==0);
		clrscr();
		issubject("EPC",&t,&p,&tt,&pp);//chi co tac dung lay so lieu
		class_name(mahv,tenlop);
        page=0;
        dem=0;
        clrscr();
        printf("\n\n");
        printf("\n                    	ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    	³         STUDENT AVERAGE MARK        ³");
        printf("\n                    	ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        printf("\n                ÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                ³ Roll No ³   Full name       ³  Class  ³   AVG   ³");
        printf("\n                ÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄ´");
        printf("\n                ³%-9s³%-19s³  %-7s³   %-6.2f³",mahv,mang[vitri].hoten,tenlop,avg(mahv));
        printf("\n                ÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n");
        printf("\n      ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n      ³  T/P: %2d/%2d  ³",tt,pp);
        printf("\n      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n      ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
        printf("\n      ³No³ Subject ³ Test of T ³ Test of P ³ Mark of T ³ Mark of P ³  AVG  ³");
        printf("\n      ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
        for(i=0;i<n;i++)
        {
            if(ds[i].t<0)
                ds[i].t=0.0;
            if(ds[i].p<0.0)
                ds[i].p=0.0;
            if(strcmp(ds[i].mahv,mahv)==0)
            {
                issubject(ds[i].mon,&t,&p,&tt,&pp);
                //------------------------------------------
                if(t!=0 && p!=0)
                {
                        tbmon = ((mot_tram(ds[i].t)* (float) tt) / (float) 100) + ((mot_tram(ds[i].p) * (float) pp) / (float) 100);
                }
                else
                {
                    if(t==0)
                    {
                            tbmon=mot_tram(ds[i].p);
                    }
                    else
                    {
                            tbmon=mot_tram(ds[i].t);
                    }
                }
                //-----------------------------------------
                dem++;
                page++;
                printf("\n      ³%02d³   %-6s³     %-6d³     %-6d³",dem,ds[i].mon,t,p);
                if(t==0)
                    printf("    ---    ³");
                else
                    printf("    %-7.2f³",ds[i].t);
                if(p==0)
                    printf("    ---    ³");
                else
                    printf("    %-7.2f³",ds[i].p);
                printf(" %-6.2f³",tbmon);
                printf("\n      ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                if(page == 10 && i<n-1)
                {
                    printf("\n\n\t\t\tPress any key to display next page !");
                    page=0;
                    getch();
                    clrscr();
                    printf("\n\n\n");
                    printf("\n                ÚÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n                ³ Roll No ³   Full name       ³  Class  ³   AVG   ³");
                    printf("\n                ÃÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄ´");
                    printf("\n                ³%-9s³%-19s³  %-7s³   %-6.2f³",mahv,mang[vitri].hoten,tenlop,avg(mahv));
                    printf("\n                ÀÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n\n\n");
                    printf("\n      ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n      ³  T/P: %2d/%2d  ³",tt,pp);
                    printf("\n      ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n      ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
                    printf("\n      ³No³ Subject ³ Test of T ³ Test of P ³ Mark of T ³ Mark of P ³  AVG  ³");
                    printf("\n      ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                }
            }
        }
        printf("\n\n\t\t\t  Press any key to continue !");
        getch();
		clrscr();
		printf("\n\n\n\n\n\n\n\n\n\t\t\tContinue wiht other student (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
            free(ds);
            free(mang);
            return;
        }
    }while(1);

}

//sap xep hoc vien theo diem trung binh

void student_ranking_in_class()
{
	char tenlop[10],ch;
	int dem,siso,page,solop,vitri;
	register int i;
	RANK *mang;
	HOCVIEN *danhsach;
	LOPHOC *lop;
	lop=danhsachlop(&solop);
	do
	{
		clrscr();
		printf("\n\n");
		printf("\n                    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
		printf("\n                    ³       STUDENT RANKING IN CLASS      ³");
		printf("\n                    ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
		printf("\n\n\n\n");
		printf("\nType class no to display.........\n");
        do
		{
			classno(tenlop);
			if(dupclass(lop,solop,tenlop,&vitri)==0)
			{
				printf("\n\nClass no you entered is not found !");
				printf("\n\n         Retype (Y/N) ?");
				ch=getch();
				if(ch=='y' || ch=='Y')
					continue;
				else
				{
					free(mang);
					free(danhsach);
					return;
				}
			}
			if(cohv(tenlop)==0)
			{
				printf("\n\nClass no you entered not student !");
				printf("\n\n         Retype (Y/N) ?");
				ch=getch();
				if(ch=='y' || ch=='Y')
					continue;
				else
				{
					free(mang);
					free(danhsach);
					return;
				}
			}
		}while(dupclass(lop,solop,tenlop,&vitri)==0 || cohv(tenlop)==0);
		danhsach=danh_sach_hv_theo_lop(tenlop,&siso);
		mang=(RANK*) calloc(siso,sizeof(RANK));
		for(i=0;i<siso;i++)
		{
		    strcpy(mang[i].mahv,danhsach[i].mahv);
			mang[i].avg=avg(danhsach[i].mahv);
			strcpy(mang[i].hoten,danhsach[i].hoten);
		}
		bubble_rank(siso,mang);
		clrscr();
		printf("\n\n");
		printf("\n                    	ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
		printf("\n                    	³       STUDENT RANKING IN CLASS      ³");
		printf("\n                    	ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
		printf("\n\n\n\n");
		printf("\n                                 Class [%s]\n\n\n",tenlop);
		printf("\n                 ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ¿");
		printf("\n                 ³No³ Roll No ³   Full name       ³  AVG  ³  Rank  ³");
		printf("\n                 ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
		dem=0;
		page=0;
		int rank_no;
		float truoc,sau;
		truoc=mang[siso-1].avg;
		rank_no=1;
		for(i=siso-1;i>=0;i--)
		{
			sau=mang[i].avg;
			if(sau<truoc)
			{
				rank_no++;
				truoc=sau;
			}
			dem++;
			page++;
			printf("\n                 ³%02d³%-9s³%-19s³ %-6.2f³   %-02d   ³",dem,mang[i].mahv,mang[i].hoten,mang[i].avg,rank_no);
			printf("\n                 ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
			if(page == 10 && i>1)
			{
				printf("\n\n\t\t   Press any key to display next page !");
				page=0;
				getch();
				clrscr();
				printf("\n\n");
				printf("\n                    	ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
				printf("\n                    	³       STUDENT RANKING IN CLASS      ³");
				printf("\n                    	ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
				printf("\n\n\n\n");
				printf("\n                                 Class [%s]\n\n\n",tenlop);
				printf("\n                 ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ¿");
				printf("\n                 ³No³ Roll No ³   Full name       ³  AVG  ³  Rank  ³");
				printf("\n                 ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´");
            }
		}
        printf("\n\n\t\t\t    Press any key to continue !");
        getch();
        clrscr();
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tContinue with other class (Y/N) ?");
        ch=getch();
        if(ch=='y' || ch=='Y')
            continue;
        else
        {
            free(mang);
			free(danhsach);
			return;
		}
	}while(1);
}


//hien thi danh sach hoc vien trong truon du dieu kien len lop

void upgradable_student_list()
{
	HOCVIEN *dshv;
	RANK *mang;
	int n,dem,page,sohv;
	char tenlop[10],hoten[25],ch;
	register int i;
	float diemtb;
	dshv=danhsach_hocvien_co_diem(&sohv);
    mang=(RANK*) calloc(sohv,sizeof(RANK));
	do
	{
		clrscr();
        printf("\n\n");
        printf("\n                    	ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    	³        UPGRADABLE STUDENT LIST      ³");
        printf("\n                    	ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        printf("\n\n\n\n\n                          Select the type to display");
        printf("\n");
        printf("\n                              -----------------------");
        printf("\n                              1. Sort by student name");
        printf("\n                              2. Sort by class");
        printf("\n                              3. Sort by avg mark");
        printf("\n                              4. Back to menu");
        ch=getch();
		if(ch=='1' || ch=='2' || ch=='3'|| ch == '4')
        {
            if(ch=='1')
                bubble_upgradge(sohv,dshv,1);
            if(ch=='2')
                bubble_upgradge(sohv,dshv,2);
            if(ch=='3')
				bubble_upgradge(sohv,dshv,3);
            if(ch=='4')
            {
                free(mang);
                free(dshv);
                return;
            }
        }
        else
            continue;
		for(i=0;i<sohv;i++)
		{
				strcpy(mang[i].mahv,dshv[i].mahv);
				mang[i].avg=avg(dshv[i].mahv);
				strcpy(mang[i].hoten,dshv[i].hoten);
		}
//		bubble_rank(sohv,mang);
		//------------------------
		dem=0;
		page=0;
        clrscr();
        printf("\n\n");
        printf("\n                    	ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                    	³        UPGRADABLE STUDENT LIST      ³");
        printf("\n                    	ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n\n\n\n");
        printf("\n                 ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
        printf("\n                 ³ Conditions : AVG > 50 ³");
        printf("\n                 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
        printf("\n                 ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
        printf("\n                 ³No³ Roll No ³   Full name       ³  Class  ³  AVG  ³");
        printf("\n                 ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
        for(i=sohv-1;i>=0;i--)
        {
            if(mang[i].avg>50.00)
            {
                dem++;
                page++;
                class_name(mang[i].mahv,tenlop);
                printf("\n                 ³%02d³%-9s³%-19s³  %-7s³ %-6.2f³",dem,mang[i].mahv,mang[i].hoten,tenlop,mang[i].avg);
                printf("\n                 ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                if(page == 10 && i>1)
                {
                    printf("\n\n\t\t\t  ->Press any key to display next page !");
                    getch();
                    clrscr();
                    page=0;
                    printf("\n\n");
                    printf("\n                    	ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n                    	³        UPGRADABLE STUDENT LIST      ³");
                    printf("\n                    	ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n\n\n\n");
                    printf("\n                 ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
                    printf("\n                 ³ Conditions : AVG > 50 ³");
                    printf("\n                 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
                    printf("\n                 ÚÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
                    printf("\n                 ³No³ Roll No ³   Full name       ³  Class  ³  AVG  ³");
                    printf("\n                 ÃÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´");
                }

            }
        }
        printf("\n\n\t\t\t  ->Press any key to continue !");
        getch();
	}while(1);
}


//********************************************************************************************************************
//////////////////////////////////////////////Giao dien menu/////////////////////////////////////////////////////////
//********************************************************************************************************************

//ham hien cua so va ky tu
void hienkt(char *dkt, int h, int c, int dai, int mn, int mc)
{
    textbackground(mn);
    textcolor(mc);
    window(c,h,c+dai-1,h);
    clrscr();
    if(strlen(dkt) >= dai)
	dkt[dai]=0;
    puts(dkt);
    gotoxy(1,1);
}

//dat mau nen cho menu
void mau_nen_menu()
{
    window(1,1,80,25);
    textmode(C80);
    textbackground(BLUE);
	textcolor(WHITE);
    clrscr();
}

//ham in mot so ky tu dac biet
void in(int maascii,int sokytu)
{
	int i;
	for(i=1;i<=sokytu;i++)
	{
		printf("%c",-maascii);
	}
}


//ham demo ten chuong trinh
void loading()
{
    window(1,1,80,25);
	int i;
	clrscr();
	printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t");
	printf("Aptech");
	delay(120);
	printf(" Student's");
	delay(120);
	printf(" Marks");
	delay(120);
	printf(" System");
	delay(120);
	printf("\n\t\t\t");
	for(i=1;i<=25;i++)
	{
		putchar(-81);
		delay(20);
	}
	clrscr();
}

//ham dua ra lua chon yes-no va tra ve lua chon tuong ung la 1 hoac 0
int question(int h,int cot,int khoangcach)
{
	int i,chon,ch1,ch2;
	chon=1;
	char yes[6];
	char no[6];
	strcpy(yes,"  YES");
	strcpy(no,"  NO");
	hienkt(yes,h,cot,6,RED,WHITE);
	hienkt(no,h,cot+khoangcach,6,RED,WHITE);
	hienkt(yes,h,cot,6,GREEN,WHITE);
	ch1=0;
	while(ch1!=13)
	{
		ch1=getch();
		if(ch1==0)
			ch2=getch();
		if(ch1==0)
		if(ch2==77 || ch2==75)
		{
			if(chon==1)
			{
				chon=2;
				hienkt(yes,h,cot,6,RED,WHITE);
				hienkt(no,h,cot+khoangcach,6,GREEN,WHITE);
			}
			else
			{
				chon=1;
				hienkt(no,h,cot+khoangcach,6,RED,WHITE);
				hienkt(yes,h,cot,6,GREEN,WHITE);
			}
		}
	}
	if(chon==1)
		return 1;
	else
		return 0;

}

//ham tao me nu
void menu(int n, int hd, int cd, int dai, char nd[][40], int mnc, int mcc, int mnr, int mcr,  int *ch)
{
	int i, chonm, mn, mc;
	int ch1, ch2, chon;
	chon = *ch;
	if(n<=0 || n>=20) return;
	if(chon<0 || chon >n)
		chon=1;
	chonm=chon;
	for(i=1;i<=n;i++)
		hienkt(nd[i],hd+i-1,cd,dai,mnc,mcc);
	hienkt(nd[chonm],hd+chonm-1,cd,dai,mnr,mcr);
	ch1=0;
	while(ch1!=13)
	{
        ch1=getch();
        if(ch1==0)
            ch2=getch();
        if(ch1==0)
            if(ch2==72 || ch2==75)
            {
                chonm=chon-1;
                if(chonm <= 0)
                chonm=n;
            }
            else
            if(ch2==80 || ch2==77)
            {
                chonm=chon+1;
                if(chonm>n)
                chonm=1;
            }
        if(chonm != chon)
        {
            hienkt(nd[chon],hd+chon-1,cd,dai,mnc,mcc);
            hienkt(nd[chonm],hd+chonm-1,cd,dai,mnr,mcr);
            chon=chonm;
        }
	}
	*ch=chon;
	textcolor(WHITE);
}


//menu lop hoc
void menuclass()
{
	char nd[6][40];
	int chon=1;
	clrscr();
	strcpy(nd[1],"ADD NEW CLASS");
	strcpy(nd[2],"EDIT CLASS INFORMATION");
	strcpy(nd[3],"DELETE CLASS INFORMATION");
	strcpy(nd[4],"CLASS LIST");
	strcpy(nd[5],"BACK TO MAIN MENU");
	while(chon != 5)
	{
        mau_nen_menu();
        in(79,80);
        in(79,34);
        printf(" Aiti-Aptech ");
        in(79,33);
		in(79,80);
        printf("\n");
        printf("                      ÉÍ                               Í»\n");
        printf("                         APTECH STUDENT'S MARKS MANAGER  \n");
        printf("	              ÈÍ                               Í¼\n\n\n");
        printf("\n                             CLASS INFORMATION\n");
        printf("                         ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("                         º                           º\n");
        printf("     	                 º                           º\n");
        printf("	                 º                           º\n");
        printf("                         º                           º\n");
        printf("	                 º                           º\n");
        printf("		         ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
		printf("\n                  Use ");
        putchar(-232); putchar(-1); putchar(-231);
        printf(" to moves and press Enter to select !\n\n");
        printf("     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("     º Author: Qu");
        putchar(-123);
        printf("ng V");
        putchar(-124);
        printf("n Li");
        putchar(-120);
        printf("m (A00160) - Contact: liemmaster1990@gmail.com º\n");
        printf("     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        //-------------------------------------------------------------------------------------------
		menu(5,13,28,24,nd,BLUE,WHITE,CYAN,RED,&chon);
        switch(chon)
        {
            case 1 :
                mau_nen();
                new_class();
                break;
            case 2 :
                mau_nen();
                edit_class();
                break;
            case 3 :
                mau_nen();
				delete_class();
                break;
            case 4 :
                mau_nen();
                class_list();
                break;
            case 5 :
                loading();
                mau_nen_menu();
				return;
        }
	}
}

//menu tim kiem hoc vien
void menufind()
{
	char nd[5][40];
	int chon=1;
	clrscr();
    strcpy(nd[1],"FIND BY ROLL NO");
    strcpy(nd[2],"FIND BY NAME");
    strcpy(nd[3],"FIND BY ADRESS");
    strcpy(nd[4],"BACK TO STUDENT INFORMATION");
	while(chon != 4)
    {
        mau_nen_menu();
		in(79,80);
        in(79,34);
        printf(" Aiti-Aptech ");
        in(79,33);
        in(79,80);
        printf("\n");
        printf("                      ÉÍ                               Í»\n");
        printf("                         APTECH STUDENT'S MARKS MANAGER  \n");
        printf("	              ÈÍ                               Í¼\n\n\n");
        printf("\n                                 FIND STUDENT\n");
        printf("                        ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("                        º                             º\n");
        printf("     	                º                             º\n");
		printf("	                º                             º\n");
        printf("                        º                             º\n");
        printf("		        ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        printf("\n                  Use ");
        putchar(-232); putchar(-1); putchar(-231);
        printf(" to moves and press Enter to select !\n\n");
        printf("     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("     º Author: Qu");
        putchar(-123);
        printf("ng V");
        putchar(-124);
        printf("n Li");
        putchar(-120);
		printf("m (A00160) - Contact: liemmaster1990@gmail.com º\n");
        printf("     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        //-------------------------------------------------------------------------------------------
        menu(4,13,27,27,nd,BLUE,WHITE,CYAN,RED,&chon);
        switch(chon)
        {
            case 1 :
                mau_nen();
                findbyroll();
                break;
            case 2 :
                mau_nen();
                find_by_name();
				break;
            case 3 :
                mau_nen();
                find_by_address();
                break;
            case 4 :
                loading();
                mau_nen_menu();
				return;
        }
    }
}

//menu thong tin hoc vien
void menustudent()
{
	char nd[7][40];
	int chon=1;
	clrscr();
    strcpy(nd[1],"ADD NEW STUDENT");
    strcpy(nd[2],"EDIT STUDENT INFORMATION");
    strcpy(nd[3],"DELETE STUDENT INFORMATION");
    strcpy(nd[4],"STUDENT LIST");
    strcpy(nd[5],"FIND STUDENT");
	strcpy(nd[6],"BACK TO MAIN MENU");
	while(chon != 6)
    {
		mau_nen_menu();
        in(79,80);
        in(79,34);
        printf(" Aiti-Aptech ");
        in(79,33);
        in(79,80);
        printf("\n");
        printf("                      ÉÍ                               Í»\n");
        printf("                         APTECH STUDENT'S MARKS MANAGER  \n");
        printf("	              ÈÍ                               Í¼\n\n\n");
        printf("\n                            STUDENT INFORMATION\n");
        printf("                        ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("                        º                             º\n");
		printf("     	                º                             º\n");
        printf("	                º                             º\n");
        printf("                        º                             º\n");
        printf("	                º                             º\n");
        printf("	                º                             º\n");
        printf("		        ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        printf("\n                  Use ");
        putchar(-232); putchar(-1); putchar(-231);
        printf(" to moves and press Enter to select !\n");
        printf("     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("     º Author: Qu");
        putchar(-123);
        printf("ng V");
		putchar(-124);
        printf("n Li");
        putchar(-120);
        printf("m (A00160) - Contact: liemmaster1990@gmail.com º\n");
        printf("     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        //-------------------------------------------------------------------------------------------
        menu(6,13,27,26,nd,BLUE,WHITE,CYAN,RED,&chon);
        switch(chon)
        {
            case 1 :
                mau_nen();
                new_student();
                break;
			case 2 :
                mau_nen();
                edit_student();
                break;
            case 3 :
                mau_nen();
                delete_student();
                break;
            case 4 :
                mau_nen();
                student_list();
                break;
            case 5 :
				mau_nen_menu();
                menufind();
                break;
            case 6 :
                loading();
                mau_nen_menu();
				return;
        }
    }
}

//menu diem hoc vien

void menumark()
{
	char nd[8][40];
	int chon=1;
	clrscr();
    strcpy(nd[1],"ADD CLASS MARK");
    strcpy(nd[2],"EDIT CLASS MARK");
    strcpy(nd[3],"ADD STUDENT MARK");
    strcpy(nd[4],"EDIT STUDENT MARK");
    strcpy(nd[5],"CLASS MARK LIST PER SUBJECT");
	strcpy(nd[6],"STUDENT MARK LIST");
	strcpy(nd[7],"BACK TO MAIN MENU");
	while(chon != 7)
    {
		mau_nen_menu();
        in(79,80);
        in(79,34);
        printf(" Aiti-Aptech ");
        in(79,33);
        in(79,80);
        printf("\n");
        printf("                      ÉÍ                               Í»\n");
        printf("                         APTECH STUDENT'S MARKS MANAGER  \n");
        printf("	              ÈÍ                               Í¼\n\n");
        printf("\n                                 STUDENT MARK\n");
        printf("                        ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("                        º                             º\n");
		printf("     	                º                             º\n");
        printf("	                º                             º\n");
        printf("                        º                             º\n");
        printf("	                º                             º\n");
        printf("	                º                             º\n");
        printf("	                º                             º\n");
        printf("		        ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        printf("\n                  Use ");
        putchar(-232); putchar(-1); putchar(-231);
        printf(" to moves and press Enter to select !\n");
        printf("     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("     º Author: Qu");
        putchar(-123);
		printf("ng V");
        putchar(-124);
        printf("n Li");
        putchar(-120);
        printf("m (A00160) - Contact: liemmaster1990@gmail.com º\n");
        printf("     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        //-------------------------------------------------------------------------------------------
        menu(7,12,27,27,nd,BLUE,WHITE,CYAN,RED,&chon);
        switch(chon)
        {
            case 1 :
                mau_nen();
                add_class_mark();
				break;
            case 2 :
                mau_nen();
                edit_class_mark();
                break;
            case 3 :
                mau_nen();
                add_student_mark();
                break;
            case 4 :
                mau_nen();
                edit_student_mark();
                break;
			case 5 :
                mau_nen();
                class_mark_list_per_subject();
                break;
            case 6 :
                mau_nen();
                student_mark_list();
                break;
            case 7 :
                loading();
                mau_nen_menu();
				return;
        }
    }
}

//menu bao cao
void menureport()
{
	char nd[6][40];
	int chon=1;
	clrscr();
    strcpy(nd[1],"CLASS AVERAGE MARK LIST");
    strcpy(nd[2],"STUDENT AVERAGE MARK");
    strcpy(nd[3],"STUDENT RANKING IN CLASS");
    strcpy(nd[4],"UPGRADEABLE STUDENT LIST");
    strcpy(nd[5],"BACK TO MAIN MENU");
	while(chon != 5)
    {
        mau_nen_menu();
        in(79,80);
        in(79,34);
        printf(" Aiti-Aptech ");
        in(79,33);
        in(79,80);
        printf("\n");
        printf("                      ÉÍ                               Í»\n");
        printf("                         APTECH STUDENT'S MARKS MANAGER  \n");
        printf("	              ÈÍ                               Í¼\n\n");
        printf("\n\n                               REPORT\n");
		printf("                         ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("                         º                           º\n");
        printf("     	                 º                           º\n");
        printf("	                 º                           º\n");
        printf("                         º                           º\n");
        printf("	                 º                           º\n");
        printf("		         ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        printf("\n                  Use ");
        putchar(-232); putchar(-1); putchar(-231);
        printf(" to moves and press Enter to select !\n\n");
        printf("     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("     º Author: Qu");
        putchar(-123);
		printf("ng V");
        putchar(-124);
        printf("n Li");
        putchar(-120);
        printf("m (A00160) - Contact: liemmaster1990@gmail.com º\n");
        printf("     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        //-------------------------------------------------------------------------------------------
        menu(5,13,28,24,nd,BLUE,WHITE,CYAN,RED,&chon);
        switch(chon)
        {
            case 1 :
                mau_nen();
                class_avg_mark_list();
				break;
            case 2 :
                mau_nen();
                student_average_mark();
                break;
            case 3 :
                mau_nen();
                student_ranking_in_class();
                break;
            case 4 :
                mau_nen();
                upgradable_student_list();
                break;
			case 5 :
                loading();
                mau_nen_menu();
				return;
        }
    }
}

//menu chinh cua chuong trinh
void main_menu()
{
	char nd[6][40];
	int chon=1;
	clrscr();
	strcpy(nd[1],"CLASS INFORMATION");
    strcpy(nd[2],"STUDENT INFORMATION");
    strcpy(nd[3],"STUDENT MARKS");
    strcpy(nd[4],"REPORTS");
    strcpy(nd[5],"EXIT");
	while(1==1)
    {
        mau_nen_menu();
        in(79,80);
        in(79,34);
        printf(" Aiti-Aptech ");
        in(79,33);
        in(79,80);
		printf("\n");
        printf("                      ÉÍ                               Í»\n");
        printf("                         APTECH STUDENT'S MARKS MANAGER  \n");
        printf("	              ÈÍ                               Í¼\n\n\n");
        printf("\n                                   MAIN MENU\n");
        printf("                           ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("                           º                       º\n");
        printf("     	                   º                       º\n");
        printf("	                   º                       º\n");
        printf("                           º                       º\n");
        printf("	                   º                       º\n");
        printf("		           ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        printf("\n                  Use ");
		putchar(-232); putchar(-1); putchar(-231);
        printf(" to moves and press Enter to select !\n\n");
        printf("     ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
        printf("     º Author: Qu");
        putchar(-123);
        printf("ng V");
        putchar(-124);
        printf("n Li");
        putchar(-120);
        printf("m (A00160) - Contact: liemmaster1990@gmail.com º\n");
        printf("     ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
        //-------------------------------------------------------------------------------------------
        menu(5,13,30,20,nd,BLUE,WHITE,CYAN,RED,&chon);
		switch(chon)
        {
			case 1 :
                    loading();
                    mau_nen_menu();
                    menuclass();
            break;
            case 2 :
                    loading();
                    mau_nen_menu();
                    menustudent();
                break;
            case 3 :
					loading();
                    mau_nen_menu();
                    menumark();
                break;
            case 4 :
                    loading();
                    mau_nen_menu();
                    menureport();
            break;
            case 5:
            {
                window(1,1,80,25);
                textbackground(BLACK);
				clrscr();
                loading();
                clrscr();
                printf("\n\n\n\n\n\n\n\n\n\n\t\t\t     Are you sure to exit ?");
                if(question(15,30,15)==1)
                    exit(0);
            }
            break;
        }
	}

}


//********************************************************************************************************************
////////////////////////////////////////////////Main memu/////////////////////////////////////////////////////////////
//********************************************************************************************************************

int main()
{
	//mau_nen();
	//new_class();
	//class_list();
	//edit_class();
	//delete_class();
	//new_student();
	//student_list();
	//edit_student();
	//delete_student();
	//findbyroll();
	//find_by_name();
	//find_by_address();
	//add_student_mark();
	//student_mark_list();
	//edit_student_mark();
	//add_class_mark();
	//edit_class_mark();
	//class_mark_list_per_subject();
	//class_avg_mark_list();
	//student_average_mark();
	//student_ranking_in_class();
	//upgradable_student_list();
	main_menu();
	return 0;
}
