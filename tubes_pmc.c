/*TUGAS BESAR - EL2008 Pemecahan Masalah dengan C 2021/2022
 *Kelompok          : 7
 *Kelas             : K-01
 *Hari dan Tanggal  : Jumat, 20 Mei 2022
 *Nama File         : tubes_pmc.c 
 *Deskripsi         : Progam minimization logic boolean algebra
 */

#include <stdio.h>
#include <malloc.h>
#define bitsSize 4      //banyak variabel pada fungsi
#define limit 16        //jumlah minterms terbanyak

struct vector               //menyimpan list dari pengelompokkan minterm
    {
    int paired[limit];
    };

struct Node                 //struktur node untuk menyimpan informasi dari minterm
    {
    struct Node* next;      //menghubungkan ke node berikutnya
    int hasPaired;          //menyimpan nilai 1 atau 0 untuk menunjukkan tahapan pengelompokkan minterm
    int numberOfOnes;       //menyimpan banyaknya nilai biner 1 pada minterm
    struct vector paired;   //struktur vector yang menunjukkan pasangan minterm lain
    int group;              //menunjukkan kelompok dari minterm sesuai dengan banyaknya biner 1 pada minterm
    int binary[bitsSize];   //array yang menyimpan nilai biner hingga terbentuk pasangan
    int numberOfPairs;      //menyimpan banyak pasangan yang terbentuk
    };
typedef struct Node node;

struct implicantsTable         //Tabel Prime Implicants
    {
    int arr[limit][bitsSize]; 
    int brr[limit][limit];
    int top;                      //menunjukkan banyak prime implicant yang ada
    int mintermCounter[limit];    //menyimpan nilai minterm pada prime implicant tertentu
    } Table;

//DEKLARASI FUNGSI

void tambahMinterm(int); 
node* buatNode(int); 
void gabungMinterm(); 
void print(); 
void printTabel(); 
node* buatNodePair(node*,node*); 
void isiBiner(node*,node*,node*); 
void initTable();
int ifPairingPossible(node*,node*);
int ifMintermPresentInImplicant(int,int); 
void tambahPair(node*,node*); 
void tambahTabel(); 
void analisisTabel(); 
void konversiBiner(int); 
int cariMax(int*); 
int jumlahImplicants(int,int*); 
void hapusMinterm(int); 

node *head,*head2;
int minterms;               //menyimpan banyak minterm yang diberikan
int maxGroup,newMaxGroup;   //menunjukkan di tingkat pengelompokkan tertentu untuk max grup dan menghitung max grup berikutnya
int mintermsGiven[limit];   //array untuk menyimpan minterm yang diberikan

int main(void)
{
    int i,temp;
    maxGroup=-1;
    newMaxGroup=-1;
    printf("[MINIMIZATION LOGIC GATE]\n");
    printf("Masukkan banyak minterm yang akan diminimalisasi :\n");
    scanf("%d",&minterms);
    while(minterms<=0 || minterms>16)
    {
        printf("Input yang dimasukkan salah! Jumlah minterm yang diberikan harus lebih dari 0 dan kurang dari sama dengan 16!\n");
        printf("Masukkan banyak minterm yang akan diminimalisasi :\n");
        scanf("%d",&minterms);
    }
    for(i=0; i<limit; i++)
        mintermsGiven[i]=-1;
    printf("Masukkan minterm yang akan diminimalisasi :\n");
    for(i=0; i<minterms; i++)
        {
        scanf("%d",&temp);
        while(temp<0 || temp>15){
            printf("Input yang diberikan salah, masukkan ulang :\n");
            scanf("%d",&temp);
        }
        mintermsGiven[temp]=1;
        tambahMinterm(temp); //buat linked list untuk minterms
        }
    Table.top=0;
    initTable();        //inisialisasi Tabel Prime Implicants
    gabungMinterm();    //pengelompokkan
    printTabel();       //print Tabel Prime Implicants 
    printf("Boolean Expression telah disederhanakan menjadi : ");
    analisisTabel();    //analisis tabel dan print hasil akhir
    return 1;
}

void tambahMinterm(int n)     //buat linked list untuk menyimpan minterms yang diberikan
    {
    node *p,*q,*temp; //buat linked list baru 
    p=buatNode(n); //output dari createNode : angka biner minterms dan angka 1 dalam binary numbernya
    if(p!=NULL)
        {
        if(head==NULL)
            {
            head=p;
            head->next=NULL;
            return;
            }
        else
            {
            q=head;
            if(p->group<head->group) //group = berapa jumlah yang 1
                {
                p->next=head;
                head=p;
                return;
                } 
            while(q->next!=NULL&&((q->next->group)<=(p->group)))
                {
                q=q->next;
                }
            if(q->next==NULL)
                {
                q->next=p;
                p->next=NULL;
                }
            else 
                {
                temp=q->next;
                q->next=p;
                p->next=temp;
                }
            }
        }
    }
void tambahPair(node *p,node *q)   //buat linked list untuk menyimpan minterm yang berpasangan
    {
    node *r,*temp;
    r=buatNodePair(p,q);
    if(head2==NULL)
        {
        head2=r;
        }
    else
        {
        temp=head2;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=r;
        }
    }
node* buatNodePair(node *p,node *q)    //buat node baru sesuai yang diberikan
    {
    int i,j;
    node *r;
    r=(node *)malloc(sizeof(node)); //inisialisasi node baru
    if(r==NULL)
        printf("[Proses penambahan gagal!]\n");
    else
        {
        for(i=0; i<p->numberOfPairs; i++) 
            {
            r->paired.paired[i]=p->paired.paired[i]; //copy ke dalam node baru
            }
        r->numberOfPairs=p->numberOfPairs*2;
        for(j=0; j<q->numberOfPairs; j++)
            {
            r->paired.paired[i++]=q->paired.paired[j];
            }
        r->hasPaired=0;
        r->next=NULL;
        r->group=p->group;
        isiBiner(p,q,r);
        }
    return r;
    }
void printTabel()   //print tabel prime implicants
    {
    int i,j;
    printf("[Tabel Prime Implicants]\n");
    for(i=0; i<Table.top; i++)
        {
        konversiBiner(i);
        for(j=0; j<=limit-1; j++)
            {
            if(Table.brr[i][j]==1)
                printf("   %d  ",j);
            }
        printf("\n");
        }
    }
void isiBiner(node *p,node *q,node *r)  //mengisi nilai biner di r sesuai p dan q
    {
    int c=bitsSize-1;
    while(c!=-1)
        {
        if(p->binary[c]==q->binary[c])
            {
            r->binary[c]=p->binary[c];
            }
        else
            {
            r->binary[c]=-1;
            }
        c--;
        }
    }
node* buatNode(int n)    //buat node untuk menyimpan informasi minterm
    {
    int c=bitsSize-1;
    node *p;
    p=(node *)malloc(sizeof(node)); //buat linked list
    if(p==NULL)
        printf("[Proses penambahan gagal!]\n");
    else
        {
        p->numberOfOnes=0;
        p->paired.paired[0]=n;
        p->numberOfPairs=1;
        while(n!=0) //menentukan angka biner dalam minterms
            {
            p->binary[c]=n%2;
            if(p->binary[c]==1)
                p->numberOfOnes++; //banyaknya angka 1 dalam minterms
            c--;
            n=n/2;
            }
        while(c!=-1)
            {
            p->binary[c]=0;
            c--;
            }
        p->hasPaired=0;
        }
    p->group=p->numberOfOnes;
    if(p->group>maxGroup)
        maxGroup=p->group;
    return p;
    }
void initTable()
    {
    int i,j;
    for(j=0; j<=limit-1; j++) 
        for(i=0; i<=limit-1; i++)
            {
            Table.brr[j][i]=-1;
            }
    }
void print()     //print minterm dengan pasangannya serta nilai biner dalam tiap iterasi yang dilakukan
    {
    int c=1,count=0,j=0;
    node *p;
    p=head;
    while(p!=NULL)
        {
        j=0;
        while(count<(p->numberOfPairs))
            {
            printf("%d,",p->paired.paired[count]);
            count++;
            }
        printf("\b");
        count=0;
        printf("   ");
        while(j<bitsSize)
            {
            if(p->binary[j]==-1)
                printf("%c",'-');
            else
                printf("%d",p->binary[j]);
            j++;
            }
        printf("\n");
        c++;
        p=p->next;
        }
    }
void gabungMinterm()    //pengelompokkan minterm
    {
    node *p,*q;
    int oneMatched=0;
    static int iteration=1;  //menyimpan iterasi pengelompokkan
    p=head;
    q=p;
    printf("[Iterasi - %d]\n",iteration);
    iteration++;
    print();
    newMaxGroup=-1;
    while(p->group!=maxGroup)
        {
        q=q->next;
        while(q!=NULL&&(q->group==p->group))
            {
            q=q->next;
            }
        if(q==NULL)
            {
            p=p->next;
            q=p;
            continue;
            }
        else
            {
            if(q->group!=(p->group+1))
                {
                p=p->next;
                q=p;
                continue;
                }
            if(ifPairingPossible(p,q))  //cek apakah mungkin untuk dilakukan pairing
                {
                oneMatched=1;
                p->hasPaired=1;
                q->hasPaired=1;
                tambahPair(p,q);
                if((p->group)>newMaxGroup)
                    newMaxGroup=p->group;
                }
            }
        }
    tambahTabel();
    if(oneMatched)      //cek apakah setidaknya berhasil terbentuk setidaknya satu pasangan
        {
        head=head2;
        head2=NULL;
        maxGroup=newMaxGroup;
        gabungMinterm();
        }
    }
void tambahTabel()
    {
    int i,j,k,allMatched;
    node *p;
    p=head;
    while(p!=NULL)
        {
        if(!(p->hasPaired))
            {
            if(Table.top!=0) //cek apakah terdapat duplikasi
                {
                for(j=0; j<Table.top; j++)
                    {
                    allMatched=1;
                    for(k=0; k<p->numberOfPairs; k++)
                        {
                        if(Table.brr[j][p->paired.paired[k]]==1)
                            continue;
                        else
                            {
                            allMatched=0;
                            break;
                            }
                        }
                    if(allMatched==1)
                        {
                        break;
                        }
                    }
                if(allMatched==1)
                    {
                    p=p->next;
                    continue;
                    }
                }
            i=bitsSize-1;
            while(i!=-1)
                {
                Table.arr[Table.top][i]=p->binary[i];
                i--;
                }
            for(i=0; i<p->numberOfPairs; i++)
                {
                Table.mintermCounter[Table.top]++;
                Table.brr[Table.top][p->paired.paired[i]]=1;
                }
            Table.top++;
            }
        p=p->next;
        }
    }
int cariMax(int *row)  //cari prime implicant dengan minterm paling banyak yang tidak digunakan
    {
    int i,greatest=-1;
    for(i=0; i<Table.top; i++)
        {
        if(Table.mintermCounter[i]>greatest)
            {
            *row=i;
            greatest=Table.mintermCounter[i];
            }
        }
    return greatest;
    }
void analisisTabel()      //analisis tabel
    {
    int i,j,k,greatestRow,ifFirst=1;
    int essentialPrimeImplicant[limit];      //menyimpan nilai pada baris di essential prime implicants
    int temp,c;
    for(i=0; i<=limit-1; i++)
        essentialPrimeImplicant[i]=-1;
    for(i=0; i<=limit-1; i++)
        {
        if(mintermsGiven[i]==1)
            {
            if(jumlahImplicants(i,&temp)==1)
                {
                essentialPrimeImplicant[i]=temp;
                }
            }
        }
    for(i=0; i<=limit-1; i++)
        {
        if(essentialPrimeImplicant[i]!=-1)
            {
            if(ifFirst!=1)
                printf(" + ");
            else
                ifFirst=0;
            konversiBiner(essentialPrimeImplicant[i]);

            hapusMinterm(essentialPrimeImplicant[i]);
            for(j=i+1; j<=limit-1; j++)
                {
                if(essentialPrimeImplicant[j]==essentialPrimeImplicant[i])
                    essentialPrimeImplicant[j]=-1;
                }
            essentialPrimeImplicant[i]=-1;

            }
        }
    while(cariMax(&greatestRow)!=0)
        {

        if(ifFirst!=1)
            printf(" + ");
        else
            ifFirst=0;
        konversiBiner(greatestRow);

        hapusMinterm(greatestRow);
        }
    printf("\b");
    }
int ifMintermPresentInImplicant(int minterm,int implicant) 
    {
    if(Table.brr[implicant][minterm]==1)
        return 1;
    else
        return 0;
    }
void hapusMinterm(int n)
    {
    int i,j;
    for(i=0; i<=limit-1; i++)
        {
        if(Table.brr[n][i]==1)
            {
            mintermsGiven[i]=-1;

            for(j=0; j<Table.top; j++)
                {
                if(Table.brr[j][i]==1)
                    {
                    Table.brr[j][i]=-1;
                    Table.mintermCounter[j]--;
                    }
                }
            }
        }
    }
int jumlahImplicants(int n,int *temp) 
    {
    int i,j;
    int count=0;
    for(i=0; i<Table.top; i++)
        {
        if(Table.brr[i][n]==1)
            {
            j=i;
            count++;
            }
        }
    *temp=j;
    return count;
    }
void konversiBiner(int n)   //konversi biner ke dalam notasi variabel
    {
    int c=0;
    char charactersNormal[]= {'A','B','C','D'};
    char charactersComplement[]= {'a','b','c','d'};
    while(c!=bitsSize)
        {
        if(Table.arr[n][c]!=-1)
            {
            if(Table.arr[n][c]==1)
                printf("%c",charactersNormal[c]);
            else
                printf("%c",charactersComplement[c]);
            }
        c++;
        }
    }
int ifPairingPossible(node *a,node *b)   //cek apakah terdapat perbedaan satu bit pada kedua minterm 
    {
    int c=bitsSize-1;
    int ifOneDissimilar=0;
    while(c!=-1)
        {
        if(a->binary[c]!=b->binary[c])
            {
            if(ifOneDissimilar)
                return 0;
            else
                ifOneDissimilar=1;

            }
        c--;
        }
    return 1;
    }