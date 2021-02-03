/*PROGRAMMING LANGUAGE USED: C++
  "PROJECT ON MUSIC PLAYER"
  DATA STRUCTURES USED: DOUBLY LINKED LIST, QUEUE*/

//Header files needed for the project are listed below
#include<windows.h>//PlaySound
#include<mmsystem.h>//PlaySound
#include<iostream>
#include<cstring>//null-terminated strings
#include<string>//string objects
#include<cstdlib>//For generating random numbers
#include<conio.h>//For the usage of getche()
#include<time.h>//For generating seed for random numbers
using namespace std;

char s[20][10];//Global array of strings to store the song names
int d=0;//Total number of strings in array

char recsong[20][20];// List of recommended songs
int h=0;//Index associated with the array to store recommended songs

//Class used for login page
class Login
{
public:
    string username,password;//data members
    Login()
    {
        username="\0";
        password="\0";
    }
    bool isLogin()
    {
        string ch_username="Hello",ch_password="123";
        cout<<"\nEnter the Username: ";
        cin>>username;
        cout<<"\nEnter Password: ";
        cin>>password;
        if(username == ch_username && password == ch_password)
            return true;
        else
            return false;
    }
};
struct node
{
    char songname[20];
    char artist[20];
    char lyricist[20];
    char singer[5][20];
    char genre[20];
    char language[20];
    char movie[30];
    char award[50];
    int ynom;
    int year;
    int notimes;
    int rate;
    int fav;
    //Pointers to node type
    node *prev;
    node *next;
};
class Songs
{
public:
    node *head;
    Songs()
    {
        head=NULL;
    }
    void append();
    void insert_middle();
    int number();
    void shuffle();
    void PlayAll();
    void delbeg();
    void delmid(int);
    void dellast();
    void display(node*,int,int);
    void Search_list_artist(char []);
    void Search_list_genre(char []);
    void Search_songname(char []);
    void Search_lyricist(char []);
    void Search_language(char []);
    void Search_movie(char []);
    void Search_singer(char[]);
    void sort_alpha_song();
    void QueueSongs(Songs);
    void MostlyPlayed();
    void Recommended();
    void RecentlyPlayed();
    void StarGallery();
    void OldHits();
    void NewHits();
    void fav();
    void NewReleases();
};
class Queue
{
    int size;
    int front;
    int rear;
    char **b;
public:
    Queue(int n)
    {
        front= -1;
        rear= -1;
        size=n;
        b = new char* [size]; // Dynamic memory allocation of 2D char array of strings
        for(int k=0;k<size;k++)
            b[k]=new char[size];
    }
    // Only Insert operation is needed in Queue as we need to only queue up songs and not delete them in queue(no need).
    void ins(char r[20])//r is the array (song name) to be inserted in the queue
    {
        if(rear==size-1)
        {
            cout<<"\nQueue full\n";
        }
        else
        {
            rear++;//Increment rear by 1
            strcpy(b[rear],r);//Copy the string r got from the user to the array b in the queue with index as "rear"
        }
    }
    void print(Songs l)
    {
        char u[20];
        //For loop to increment k value from 0 till the total number of songs in the playlist.
        for(int k=0; k < l.number(); k++)
        {
            strcpy(u,b[rear-k]);//Copy from the last of the queue(rear end)
            l.Search_songname(u);//Display only the songs in the queue that matches the song in the original playlist.
        }
    }
};
//For storing recently played songs
struct node1
{
    char song[20];
    node1* prev;
    node1* next;
};
class Recent
{
public:
    node1* head;//head pointer that points to node1 type
    Recent()
    {
        head=NULL;
    }
    void insertbeg(char a[20])
    {
        node1 *x=new node1;
        strcpy(x->song,a);
        //If linked list is empty,then make the node x as the head
        if(head==NULL)
        {
            head=x;
            x->prev=NULL;
            x->next=NULL;
        }
        //If not, head is the next of x, prev of x is NULL, x is prev of head and finally x becomes the head
        else
        {
            x->next=head;
            x->prev=NULL;
            head->prev=x;
            head=x;
        }
    }
    void del_insertatbeg(char a[20])
    {
        node1 *x=new node1;
        x=head;
        while(x!=NULL)
        {
            if(strcmpi(x->song,a)==0)
            {
                //If x is the last node
                if(x->next==NULL&&x->prev!=NULL)
                    dellast();
                //If x is somewhere in between
                else if(x->next!=NULL&&x->prev!=NULL)
                    delbetw(x->song);
                // If x is the only node available
                else if(x->prev==NULL&&x->next==NULL)
                {
                    delete x;
                    break;
                }
            }
            x=x->next;
        }
        //At last insert the song a at the beginning
        insertbeg(a);
    }
    void dellast()
    {
        node1 *t=new node1;
        t=head;
        //t to point last node
        while(t->next!=NULL)
            t=t->next;
        //Next of the prev of t is NULL
        (t->prev)->next=NULL;
        delete t;
    }
    void delbetw(char a[20])
    {
        node1 *t=new node1;
        t=head;
        //Move t node till the song name matches
        while(t!=NULL)
        {
            if(strcmpi(t->song,a)==0)
            {
                (t->prev)->next=t->next;// Next of t as the Next of prev of t
                (t->next)->prev=t->prev;//prev of t as the prev of next of t
                delete t;
            }
            t=t->next;
        }
    }
};
Recent fg;//Object of the class Recently played linked list
void Songs::append()
{
    char a[20],b[20],c[20],lang[20],movie[30],nom[50],lyr[20];
    char aa[5][20];
    int y,ynom;
    char ch,ch1;
    cout<<"\nEnter the Name of the Song: ";
    cin.ignore();
    cin.getline(a,20);
    cout<<"\nEnter the Name of the Music Director: ";
    cin.getline(b,20);
    cout<<"\nEnter the Name of the Lyricist: ";
    cin.getline(lyr,20);

    //Singers
    cout<<"\nEnter the Name(s) of the Singer(s): ";
    int j=0;
    char mn;
    do
    {
        cout<<"\n Singer "<<j+1<<" : ";
        cout<<"\n M/F: ";
        cin>>mn;
        cout<<"\t";
        cin.ignore();
        cin.getline(aa[j],20);
        j++;
        cout<<"\nDo you want to Enter another Singer's Name? \t";
        cin>>ch;
    }
    while(j<5 && (ch=='y'||ch=='Y'));
    if(j==5)
        cout<<"\nContent Full! Sorry...!\n";
    //Genre
    do
    {
        cout<<"\nEnter the Genre the Song belongs to ( Capella / Classical / Bass / Western / HipHop / Emo / Blues / Folk / MashUp / Rock / Party) : ";
        cin.ignore();
        cin>>c;
    }
    while(strcmpi(c,"Capella")!=0&&strcmpi(c,"Classical")!=0&&strcmpi(c,"Bass")!=0&&strcmpi(c,"Western")!=0&&strcmpi(c,"HipHop")!=0&&strcmpi(c,"Emo")!=0&&strcmpi(c,"Blues")!=0&&strcmpi(c,"Folk")!=0&&strcmpi(c,"MashUp")!=0&&strcmpi(c,"Rock")!=0&&strcmpi(c,"Party")!=0);
    cout<<"\nEnter the Language of the Song: ";
    cin>>lang;
    cout<<"\nMovie: ";
    cin.ignore();
    cin.getline(movie,30);
    l3:cout<<"\nEnter the Year of Release: ";
    cin>>y;
    if(y<1990||y>2020)
    {
        cout<<"\n Invalid Entry..Re-Enter";
        goto l3;
    }
    cout<<"\nAwards, Nominations and Wins(if any) (Y or N): ";
    cin>>ch1;
    if(ch1=='Y'||ch1=='y')
    {
        cout<<"\nPlease Enter the Description: ";
        cin.ignore();
        cin.getline(nom,50);
        l4:cout<<"\nIn the Year: ";
        cin>>ynom;
        if(ynom<y||ynom>2020)
        {
            cout<<"\n Invalid Entry..Re-Enter";
            goto l4;
        }
    }

    node *x=new node;
    strcpy(x->songname,a);
    strcpy(x->artist,b);
    strcpy(x->lyricist,lyr);
    int t;
    for(t=0; t < j; t++)
        strcpy(x->singer[t],aa[t]);
    for(int c=t;c<5;c++)
    {
        strcpy(x->singer[c],"\0");
    }
    strcpy(x->genre,c);
    strcpy(x->language,lang);
    strcpy(x->movie,movie);
    x->year=y;
    if(ch1!='Y'&&ch1!='y')
    {
        strcpy(x->award,"None");
        x->ynom=0;
    }
    else
    {
        strcpy(x->award,nom);
        x->ynom=ynom;
    }
    srand(time(0));
    x->rate=(rand()%5)+1;
    cout<<"\nRating: "<<x->rate<<"\n";
    x->fav=0;
    strcpy(s[d],a);
    d++;

    //If linked list is empty
    if(head==NULL)
    {
        head=x;
        x->prev=NULL;
        x->next=NULL;
    }
    //If not, move till the end of the linked list and add at the end
    else
    {
        node *r=new node;
        r=head;
        while(r->next!=NULL)
            r=r->next;
        //r is currently the last node
        x->prev=r;
        x->next=NULL;
        r->next=x;
        //Now x becomes the last node
    }
    getche();
}
void Songs::insert_middle()
{
    int num,ch2=1;
    char a[20],b[20],c[20],lang[20],movie[30],nom[50],lyr[20];
    char aa[5][20];
    int y,ynom;
    char ch,ch1;
    cout<<"\nEnter the Name of the Song: ";
    cin.ignore();
    cin.getline(a,20);
    cout<<"\nEnter the Name of the Music Director: ";
    cin.getline(b,20);
    cout<<"\nEnter the Name of the Lyricist: ";
    cin.getline(lyr,20);

    //Singers
    cout<<"\nEnter the Name(s) of the Singer(s): ";
    int j=0;
    char mn;
    do
    {
        cout<<"\n Singer "<<j+1<<" : ";
        cout<<"\n M/F: ";
        cin>>mn;
        cout<<"\t";
        cin.ignore();
        cin.getline(aa[j],20);
        j++;
        cout<<"\nDo you want to Enter another Singer's Name? \t";
        cin>>ch;
    }
    while(j<5 && (ch=='y'||ch=='Y'));
    if(j==5)
        cout<<"\nContent Full! Sorry...!\n";

    //Genre
    do
    {
        cout<<"\nEnter the Genre the Song belongs to ( Capella / Classical / Bass / Western / HipHop / Emo / Blues / Folk / MashUp ) : ";
        cin.ignore();
        cin>>c;
    }
    while(strcmpi(c,"Capella")!=0&&strcmpi(c,"Classical")!=0&&strcmpi(c,"Bass")!=0&&strcmpi(c,"Western")!=0&&strcmpi(c,"HipHop")!=0&&strcmpi(c,"Emo")!=0&&strcmpi(c,"Blues")!=0&&strcmpi(c,"Folk")!=0&&strcmpi(c,"MashUp")!=0&&strcmpi(c,"Party")!=0&&strcmpi(c,"Rock")!=0);
    cout<<"\nEnter the Language of the Song: ";
    cin>>lang;
    cout<<"\nMovie: ";
    cin.ignore();
    cin.getline(movie,30);
    l3:cout<<"\nEnter the Year of Release: ";
    cin>>y;
    if(y<1990||y>2020)
    {
        cout<<"\n Invalid Entry..Re-Enter";
        goto l3;
    }
    cout<<"\nAwards, Nominations and Wins(if any) (Y or N): ";
    cin>>ch1;
    if(ch1=='Y'||ch1=='y')
    {
        cout<<"\nPlease Enter the Description: ";
        cin.ignore();
        cin.getline(nom,50);
        l4:cout<<"\nIn the Year: ";
        cin>>ynom;
        if(ynom<y||ynom>2020)
        {
            cout<<"\n Invalid Entry..Re-Enter";
            goto l4;
        }
    }

    node *x=new node;
    strcpy(x->songname,a);
    strcpy(x->artist,b);
    strcpy(x->lyricist,lyr);
    int t1;
    for(t1=0; t1 < j; t1++)
        strcpy(x->singer[t1],aa[t1]);
    for(int c=t1;c<5;c++)
        strcpy(x->singer[c],"\0");
    strcpy(x->genre,c);
    strcpy(x->language,lang);
    strcpy(x->movie,movie);
    x->year=y;
    if(ch1!='Y'&&ch1!='y')
    {
        strcpy(x->award,"None");
        x->ynom=0;
    }
    else
    {
        strcpy(x->award,nom);
        x->ynom=ynom;
    }
    srand(time(0));
    x->rate=(rand()%5)+1;
    cout<<"\nRating: "<<x->rate<<"\n";
    x->fav=0;
    cout<<"\nInserting the song in between. Enter the position of the new song: ";
    cin>>num;

    //Changes in global array
    int y1;
    d++;// Increment number of songs in the global array of strings by 1
    for(y1=d;y1>=num;y1--)
        strcpy(s[y1],s[y1-1]);
    strcpy(s[y1],x->songname);//Copy the new song name(insertion)

    //Changes in the linked list
    num--;
    node *t=new node;
    t=head;
    //If insertion is not at the beginning of the linked list
    if(num!=0)
    {
        //Move the t node till the given number
        while(ch2!=num)
        {
            t=t->next;
            ch++;
        }
        x->next=t->next;
        x->prev=t;
        (t->next)->prev=x;
        t->next=x;
    }
    //Else insertion is at the beginning of the linked list
    else
    {
        x->next=head;
        x->prev=NULL;
        head->prev=x;
        head=x;
    }
}
int Songs::number()
{
    node *t=new node;
    t=head;
    int c=0;
    while(t!=NULL)
    {
        c++;
        t=t->next;
    }
    return c;
}
void Songs::shuffle()
{
    int last = number();
    srand(time(0));//seed random number
    for( int i=0; i < last; i++)
    {
        //generate random index number
        int index = rand()%last;
        int m,n;
        m=0;
        n=0;
        node *x=new node;
        node *y=new node;
        x=head;
        y=head;
        //Move the x node till m reaches i
        while(m<i)
        {
            x=x->next;
            m++;
        }
        //Move the y node till n is equal to index( the randomly generated number )
        while(n<index)
        {
            y=y->next;
            n++;
        }
        swap(s[i],s[index]);
        swap(x->songname,y->songname);
        swap(x->artist,y->artist);
        swap(x->lyricist,y->lyricist);
        swap(x->genre,y->genre);
        swap(x->language,y->language);
        swap(x->movie,y->movie);
        swap(x->award,y->award);
        swap(x->year,y->year);
        swap(x->ynom,y->ynom);
        swap(x->notimes,y->notimes);
        swap(x->rate,y->rate);
        swap(x->fav,y->fav);
        for(int c=0;c<5;c++)
            swap(x->singer[c],y->singer[c]);
    }
    //Display songs at last
    node *l=new node;
    l=head;
    while(l!=NULL)
    {
        if(l->notimes==0)
            display(l,0,1);
        else
            display(l,1,1);
        l=l->next;
    }
}
void Songs::delbeg()
{
    node *t=new node;
    t=head;
    (head->next)->prev=NULL;
    head=head->next;
    delete t;
    //Changes in the global array
    for(int p=0;p<d;p++)
    {
        strcpy(s[p],s[p+1]);
    }
    d--;
}
void Songs::delmid(int n)// Deleting the nth node
{
    int c=1;
    node *t=new node;
    t=head;
    if(n>number())
        return;
    // Making t node to move next till c is not equal to n
    while(c!=n)
    {
        t=t->next;
        c++;
    }
    (t->prev)->next=t->next;
    (t->next)->prev=t->prev;
    delete t;
    //Changes in the global array
    for(int p=n-1;p<d;p++)
    {
        strcpy(s[p],s[p+1]);
    }
    d--;
}
void Songs::dellast()
{
    node *t=new node;
    t=head;
    while(t->next!=NULL)
        t=t->next;
    (t->prev)->next=NULL;
    delete t;
    //Change in the global array
    d--;
}
void Songs::PlayAll()//Function that calls the display function in a systematic way
{
    int g,j;
    node *t=new node;
    t=head;
    for(g=0;g<d;g++)
    {
        cout<<"\nSONG "<<g+1<<"\n";
        display(t,0,1);
        t=t->next;
        for(j=0;j<168;j++)
            cout<<"*";
        cout<<"\n";
    }
}
void Songs::display(node *x,int first,int play)//Search by node
{
    cout<<"\nSONG NAME: "<<x->songname;
    if(x->fav==1)
        cout<<"***";
    cout<<"\nMUSIC DIRECTOR: "<<x->artist;
    cout<<"\nLYRICIST: "<<x->lyricist;
    cout<<"\nSINGER(S): ";
    for(int u=0;u<5;u++)
    {
        if(x->singer[u][0]!='\0')
            cout<<x->singer[u]<<"\t";
    }
    cout<<"\nGENRE: "<<x->genre;
    cout<<"\nLANGUAGE: "<<x->language;
    cout<<"\nMOVIE: "<<x->movie;
    cout<<"\nYEAR OF RELEASE: "<<x->year;
    cout<<"\nAWARDS, NOMINATIONS AND WINS: "<<x->award<<" ( "<<x->ynom<<" )\n";
    cout<<"\n"<<x->notimes<<" K+ Plays\n";
    cout<<"\nRATING (Out of 5): ";
    int c=x->rate;
    int m;
    for(int j=0;j<c;j++)
        cout<<"* ";
    cout<<"\n";
    if(first==0)//It is the first time the user notices the song, then add it to recommended if condition is satisfied
    {
        if(c==5)
        {
            strcpy(recsong[h],x->songname);
            h++;
        }
        else if(c==4)
        {
            strcpy(recsong[h],x->songname);
            h++;
        }
        else if(c==3)
        {
            strcpy(recsong[h],x->songname);
            h++;
        }
    }

    if(play==1)//If we need to provide the choice to play music, to the user
    {
        cout<<"\n\n\t\t\t\tPress 1 to PLAY THE SONG and 0 to SKIP PLAYING THE SONG ";
        cin>>m;
        if(m==1)
        {
            cout<<"\nNow Playing...";
            PlaySound(TEXT(x->songname),NULL,SND_SYNC);
            cout<<"\nSong Played...";
            if(x->fav==0)
            {
                cout<<"\n  Do you want to add this song to your Favourites? ( Y(1)/N(0) ): ";
                cin>>x->fav;
            }
            //Changes in the "recently played" doubly linked list
            if(x->notimes==0)
                fg.insertbeg(x->songname);
            else
                fg.del_insertatbeg(x->songname);
            x->notimes++;
        }
        else if(m==0)
        {
            cout<<"\nSong not played\n";
        }
        else
        {
            cout<<"\nInvalid Input...Please try again\n";
        }
    }
    for(int j=0;j<168;j++)
            cout<<"*";
        cout<<"\n";
}
void Songs::Search_songname(char a[20])
{
    node *t=new node;
    t=head;
    int c=0;
    while(t!=NULL)
    {
        if(strcmpi(t->songname,a)==0)
        {
            if(t->notimes==0)//If the song has not been played yet, then let the display function know that the first variable is 0 , which means song is played first.
            {
                display(t,0,1);//First time and enable playing only one song
            }
            else
            {
                display(t,1,1);//Not first time and enable playing only one song
            }
            c=1;
            break;
        }
        t=t->next;
    }
    if(c==0)
    {
        cout<<"\nSorry...No such song found in the playlist..Please try again\n";
        return;
    }
}
void Songs::Search_list_artist(char a[20])
{
    node *t=new node;
    t=head;
    int first=0;
    int c=0;
    int num,x=0;
    char ch='y';
    while(t!=NULL)
    {
        if(strcmpi(t->artist,a)==0)
        {
            x++;
            c=1;
            if(first==0)
            {
                cout<<"\n\n\t\t\tSONGS BY THE MUSIC DIRECTOR "<<"' "<<t->artist<<" '\n";
                first=1;
            }
            cout<<"\n";
            if(t->notimes==0)//If the song has not been played yet, then let the display function know that the first variable is 0 , which means song is played first.
            {
                display(t,0,1);
            }
            else
            {
                display(t,1,1);
            }
        }
        t=t->next;
    }
    if(c==0)
    {
        cout<<"\nSorry...No such artist found..Please try again..\n";
        return;
    }
}
void Songs::Search_list_genre(char a[20])
{
    node *t=new node;
    t=head;
    int first=0;
    int c=0;
    int num,x=0;
    char ch='y';
    while(t!=NULL)
    {
        if(strcmpi(t->genre,a)==0)
        {
            x++;
            c=1;
            if(first==0)
            {
                cout<<"\n\n\t\t\tSONGS OF THE GENRE ' "<<t->genre<<" '\n";
                first=1;
            }
            cout<<"\n";
            if(t->notimes==0)//If the song has not been played yet, then let the display function know that the first variable is 0 , which means song is played first.
            {
                display(t,0,1);
            }
            else
            {
                display(t,1,1);
            }
        }
        t=t->next;
    }
    if(c==0)
    {
        cout<<"\nSorry...No such genre found..Please try again..\n";
        return;
    }
}
void Songs::Search_language(char a[])
{
    node *t=new node;
    t=head;
    int first=0;
    int c=0;
    int num,x=0;
    char ch='y';
    while(t!=NULL)
    {
        if(strcmpi(t->language,a)==0)
        {
            x++;
            c=1;
            if(first==0)
            {
                cout<<"\n\n\t\t\t' "<<t->language<<" ' SONGS\n";
                first=1;
            }
            cout<<"\n";
            if(t->notimes==0)//If the song has not been played yet, then let the display function know that the first variable is 0 , which means song is played first.
            {
                display(t,0,1);
            }
            else
            {
                display(t,1,1);
            }
        }
        t=t->next;
    }
    if(c==0)
    {
        cout<<"\nSorry...No such songs in the given language was found..Please try again..\n";
        return;
    }
}
void Songs::Search_lyricist(char a[20])
{
    node *t=new node;
    t=head;
    int first=0;
    int c=0;
    int num,x=0;
    char ch='y';
    while(t!=NULL)
    {
        if(strcmpi(t->lyricist,a)==0)
        {
            x++;
            c=1;
            if(first==0)
            {
                cout<<"\n\n\t\t\tSONGS WHOSE LYRICS WERE WRITTEN BY ' "<<t->lyricist<<" '\n";
                first=1;
            }
            cout<<"\n";
            if(t->notimes==0)//If the song has not been played yet, then let the display function know that the first variable is 0 , which means song is played first.
            {
                display(t,0,1);
            }
            else
            {
                display(t,1,1);
            }
        }
        t=t->next;
    }
    if(c==0)
    {
        cout<<"\nSorry...No such songs whose lyrics were written by the given artist was found..Please try again..\n";
        return;
    }
}
void Songs::Search_movie(char a[20])
{
    node *t=new node;
    t=head;
    int first=0;
    int c=0;
    int num,x=0;
    char ch='y';
    while(t!=NULL)
    {
        if(strcmpi(t->movie,a)==0)
        {
            x++;
            c=1;
            if(first==0)
            {
                cout<<"\n\n\t\t\tSONGS IN THE MOVIE ' "<<t->movie<<" '\n";
                first=1;
            }
            cout<<"\n";
            if(t->notimes==0)//If the song has not been played yet, then let the display function know that the first variable is 0 , which means song is played first.
            {
                display(t,0,1);
            }
            else
            {
                display(t,1,1);
            }
        }
        t=t->next;
    }
    if(c==0)
    {
        cout<<"\nSorry...No such songs under the given movie name was found..Please try again..\n";
        return;
    }
}
void Songs::Search_singer(char a[20])
{
    node *t=new node;
    t=head;
    int first=0;
    int c=0;
    int num,x=0;
    char ch='y';
    while(t!=NULL)
    {
        for(int ij=0;ij<5;ij++)
        {
            if(strcmpi(t->singer[ij],a)==0)
            {
                //x++;
                c=1;
                if(first==0)
                {
                    cout<<"\n\n\t\t\tSONGS BY THE SINGER "<<"' "<<t->artist<<" '\n";
                    first=1;
                }
                cout<<"\n";
                if(t->notimes==0)//If the song has not been played yet, then let the display function know that the first variable is 0 , which means song is played first.
                    display(t,0,1);
                else
                    display(t,1,1);
            }
        }
        t=t->next;
    }
    if(c==0)
    {
        cout<<"\nSorry...No such singer found in the list..Please try again..\n";
        return;
    }
}
void Songs::sort_alpha_song()
{
    int i,j;
    int m=0,n=0;
    //Using the logic of bubble sort
    for(i=0 ; i < number()-1 ; i++)
    {
        node *x=new node;
        x=head;
        m=0;
        while(m<i)
        {
            x=x->next;
            m++;
        }
        for(j=0 ; j < number()-i-1;j++)
        {
            node *y=new node;
            y=head;
            n=0;
            while(n<j)
            {
                y=y->next;
                n++;
            }
            if(strcmpi(y->songname,y->next->songname)>0)
            {
                swap(s[j],s[j+1]);
                swap(y->songname,y->next->songname);
                swap(y->artist,y->next->artist);
                swap(y->lyricist,y->next->lyricist);
                swap(y->genre,y->next->genre);
                swap(y->language,y->next->language);
                swap(y->movie,y->next->movie);
                swap(y->award,y->next->award);
                swap(y->year,y->next->year);
                swap(y->ynom,y->next->ynom);
                swap(y->notimes,y->next->notimes);
                swap(y->rate,y->next->rate);
                swap(y->fav,y->next->fav);
                for(int c=0;c<5;c++)
                    swap(y->singer[c],y->next->singer[c]);
            }
        }
    }
    //Display the song details and play the song
    node *l=new node;
    l=head;
    while(l!=NULL)
    {
        if(l->notimes==0)
            display(l,0,1);
        else
            display(l,1,1);
        l=l->next;
    }
}
void Songs::QueueSongs(Songs l)
{
    Queue r(number());
    int c[20];
    cout<<"\nEnter the order in which songs must be played...\n";
    for(int i=0;i<number();i++)
    {
        cin>>c[i];
        while(c[i]<=0||c[i]>number())
        {
            cout<<"\nInvalid song number..Re-Enter\t";
            cin>>c[i];
        }
        cout<<"\n--\n";
    }
    cout<<"\n";
    cout<<"\nTherefore the given order is : ";
    for(int u=0;u<number();u++)
    {
        c[u]--;
        cout<<c[u]<<" ";
    }
    cout<<"\n";
    for(int j=number()-1;j>=0;j--)
    {
        cout<<c[j]<<" : "<<s[c[j]]<<"\n";
        r.ins(s[c[j]]);
    }
    r.print(l);
}
//The latest song must be at the front of the linked list
void Songs::RecentlyPlayed()
{
    node1 *p=new node1;//recently played
    node *q=new node;//list of all songs
    p=fg.head;
    while(p!=NULL)
    {
        q=head;
        while(q!=NULL)
        {
            if(strcmpi(q->songname,p->song)==0)
                display(q,1,1);
            q=q->next;
        }
        p=p->next;
    }
    cout<<"\nReview the 'Recently Played' Option to spot the changes in case of repitition of the same song\n\n";
    for(int j=0;j<168;j++)
            cout<<"*";
        cout<<"\n";
}
void Songs::fav()
{
    node *t = new node;
    t=head;
    int y=0;
    while(t!=NULL)
    {
        if(t->fav==1)
        {
            display(t,1,1);
            y=1;
        }
        t=t->next;
    }
    if(y==0)
        cout<<"\nYour Favourites is empty...";
}
void Songs::OldHits()
{
    node *t = new node;
    t=head;
    while(t!=NULL)
    {
        if((t->year>=1990&&t->year<2000)&&t->rate>1)
            display(t,1,1);
        t=t->next;
    }
}
void Songs::NewHits()
{
    node *t = new node;
    t=head;
    while(t!=NULL)
    {
        if((t->year>=2000&&t->year<=2017)&&t->rate>1)
            display(t,1,1);
        t=t->next;
    }
}
void Songs::NewReleases()
{
    node *t = new node;
    t=head;
    int y=0;
    while(t!=NULL)
    {
        if((t->year>2017&&t->year<=2020)&&t->notimes==0)
        {
            display(t,0,1);
            y=1;
        }
        t=t->next;
    }
    if(y==0)
        cout<<"\nNo New Releases updated..\n";
}
void Songs::StarGallery()
{
    char a[20];
    int ch1=0,ch2=0,first1=1,first2=1;
    cout<<"\nEnter the name of the Music Director/Singer: ";
    cin.ignore();
    cin.getline(a,20);
    node *t=new node;
    t=head;
    while(t!=NULL)
    {
        if(strcmpi(a,t->artist)==0)
        {
            ch1=1;
            if(first1==1)
            {
                cout<<"\nBEST OF ' "<<t->artist<<" '\n";
                first1=0;
            }
            if(t->rate>2)
            {
                if(t->notimes==0)
                    display(t,0,1);
                else
                    display(t,1,1);
            }
        }
        t=t->next;
    }
    t=head;
    while(t!=NULL)
    {
        for(int i=0;i<5;i++)
        {
            if(strcmpi(a,t->singer[i])==0)
            {
                ch2=1;
                if(first2==1)
                {
                    cout<<"\nBEST OF ' "<<t->singer[i]<<" '\n";
                    first2=0;
                }
                if(t->rate>2)
                {
                    if(t->notimes==0)
                        display(t,0,1);
                    else
                        display(t,1,1);
                }
            }
        }
        t=t->next;
    }
    if(ch1==0&&ch2==0)
        cout<<"\nNot found...\n";
}
void Songs::MostlyPlayed()
{
    cout<<"\n\t\tCRITERIA: Songs played 4 or more times are considered under Mostly Played Songs...\n";
    node *t = new node;
    t=head;
    while(t!=NULL)
    {
        if(t->notimes>=4)
            display(t,1,1);
        t=t->next;
    }
}
void Songs::Recommended()
{
    cout<<"\n\t\tCRITERIA: Songs whose ratings are given as 3 or more are considered under Recommended Songs...\n";
    node *t=new node;
    t=head;
    while(t!=NULL)
    {
        if(t->rate>=3)
        {
            if(t->notimes==0)
                display(t,0,1);
            else
                display(t,1,1);
        }
        t=t->next;
    }
}
int main()
{
    Login l;
    int c=0;
    cout<<"\t\t\t\t\t\t\t\t     BASS BOOSTER - MUSIC PLAYER\n\n\n";
    cout<<"\n";
        for(int i=0;i<150;i++)
        {
            cout<<" ";
        }
    cout<<"NAME: GOMATHI K\n";
        for(int i=0;i<150;i++)
        {
            cout<<" ";
        }
    cout<<"ROLL NO: 19PW10\n\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
    cout<<"LOGIN:\n\n";
    l1: bool status = l.isLogin();
    if(!status)
    {
        cout<<"\nUsername and Password don't match.\n";
        cout<<"\tRetry\n";
        c++;
        if(c<3)
            goto l1;
        else
        {
            cout<<"\nToo many unsuccessful attempts. Please try after sometime.\n";
            return 0;
        }
    }
    else
    {
        cout<<"\nLogin Successful\n";
    }
    cout<<"\n";
    for(int i=0;i<168;i++)
    {
        cout<<"*";
    }
    cout<<"\n";
    getche();
    system("cls");
    Songs z;
    int opt,n;
    char name[20];
    l:cout<<"\nMENU: \n";
    cout<<"Press \n1. Append songs\n2. Insert song in between( Not at end )\n3. Delete song at the beginning only\n4. Delete song in between only\n5. Delete song at the end only \
           \n6. Search by Song Name\n7. Search by Music Director's Name in the playlist\n8. Search by Genre in the playlist\n9. Search by Language in the playlist\n10. Search by Lyricist in the playlist\n11. Search by Movie Name in the playlist\
           \n12. Search by Singer Name in the playlist\n13. Shuffle Songs\n14. Sort the playlist by Song names\
           \n15. Play all songs\n16. Queue Songs\n17. Mostly Played songs\n18. Recommended Songs\n19. Recently Played Songs\n20. 90's Hits\
           \n21. 2K Hits\n22. New Releases \n23. Star Gallery\n24. Favourites\n25. Logout\n\n";
    cin>>opt;
    switch(opt)
    {
    case 1:
        system("cls");
        cout<<"\nAPPEND SONG: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        z.append();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 2:
        system("cls");
        cout<<"\nINSERT SONG IN BETWEEN: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        if(z.number()<2)
            cout<<"\nNumber of songs insufficient to insert a song in between.\n";
        else
            z.insert_middle();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 3:
        system("cls");
        cout<<"\nDELETE THE FIRST SONG: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        if(z.number()==0)
            cout<<"\nNo song available to delete.\n";
        else
        {
            z.delbeg();
            cout<<"\nDeleted the first song";
        }
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 4:
        system("cls");
        cout<<"\nDELETE THE SONG IN BETWEEN: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        if(z.number()==0)
            cout<<"\nNo song available to delete.\n";
        else
        {
            cout<<"\nWhich song do you want to delete? ";
            cin>>n;
            z.delmid(n);
        }
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 5:
        system("cls");
        cout<<"\nDELETE THE SONG AT THE END: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        if(z.number()==0)
            cout<<"\nNo song available to delete.\n";
        else
            z.dellast();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 6:
        system("cls");
        cout<<"\nSEARCH BY SONG NAME: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        cout<<"\nEnter the Song Name: ";
        cin.ignore();
        cin.getline(name,20);
        z.Search_songname(name);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 7:
        system("cls");
        cout<<"\nSEARCH BY MUSIC DIRECTOR'S NAME: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        cout<<"\nEnter the Music Director's Name: ";
        cin.ignore();
        cin.getline(name,20);
        z.Search_list_artist(name);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 8:
        system("cls");
        cout<<"\nSEARCH BY GENRE: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        cout<<"\nEnter the Genre: ";
        cin.ignore();
        cin.getline(name,20);
        z.Search_list_genre(name);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 9:
        system("cls");
        cout<<"\nSEARCH BY LANGUAGE: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        cout<<"\nEnter the Language: ";
        cin.ignore();
        cin.getline(name,20);
        z.Search_language(name);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 10:
        system("cls");
        cout<<"\nSEARCH BY LYRICIST NAME: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        cout<<"\nEnter the Lyricist Name: ";
        cin.ignore();
        cin.getline(name,20);
        z.Search_lyricist(name);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 11:
        system("cls");
        cout<<"\nSEARCH BY MOVIE NAME: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        cout<<"\nEnter the Name of the Movie: ";
        cin.ignore();
        cin.getline(name,20);
        z.Search_movie(name);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 12:
        system("cls");
        cout<<"\nSEARCH BY SINGER NAME: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        cout<<"\nEnter the Name of the Singer: ";
        cin.ignore();
        cin.getline(name,20);
        z.Search_singer(name);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 13:
        system("cls");
        cout<<"\nSHUFFLE SONGS: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        z.shuffle();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 14:
        system("cls");
        cout<<"\nSORT THE PLAYLIST BY SONG NAMES: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        z.sort_alpha_song();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 15:
        system("cls");
        cout<<"\nPLAY ALL SONGS: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        z.PlayAll();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 16:
        system("cls");
        cout<<"\nQUEUE SONGS: ";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        z.QueueSongs(z);
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 17:
        system("cls");
        cout<<"\nMOODS & COLLECTIONS!( MOSTLY PLAYED SONGS ): ";
        z.MostlyPlayed();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 18:
        system("cls");
        cout<<"\nTOP PICKS!---UNIQUELY YOURS!( RECOMMENDED SONGS ): ";
        z.Recommended();
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 19:
        system("cls");
        cout<<"\nRECENTLY PLAYED\n\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        z.RecentlyPlayed();
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 20:
        system("cls");
        cout<<"\n90's HITS\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        z.OldHits();
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 21:
        system("cls");
        cout<<"\n2K HITS\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        z.NewHits();
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 22:
        system("cls");
        cout<<"\nNEW RELEASES\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        z.NewReleases();
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 23:
        system("cls");
        cout<<"\nSTAR GALLERY\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        z.StarGallery();
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 24:
        system("cls");
        cout<<"\nFAVOURITES\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        z.fav();
        cout<<"\n";
        getche();
        system("cls");
        goto l;
    case 25:
        system("cls");
        cout<<"\n\t\t\t\t\t\tEND..HAPPY HEARING SONGS!!!\n";
        cout<<"\n";
        for(int i=0;i<168;i++)
        {
            cout<<"*";
        }
        cout<<"\n";
        return 0;
    default:
        cout<<"\nInvalid Entry: ";
        goto l;
    }
}
