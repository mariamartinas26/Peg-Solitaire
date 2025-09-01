#include <iostream>
#include <winbgim.h>
#include <mmsystem.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <fstream>

using namespace std;

#define MAX 20

int stanga,sus,width,height,latura, nrPatrateLatura=7;

int latime, inaltime;

int culoareFundal= COLOR(222, 202, 24), culoarePiesa=GREEN , culoareTabla= WHITE;

int tipTabla=0, tipJoc=0;

int ok=0; //ptr butonul de iesire din meniu
int undo;
int TablaDeJoc[MAX][MAX], randJucator=1, nrPieseJucator1=0, nrPieseJucator2=0;
int k; //pentru coada
int gata=0, reguli=0, solo=0, duo=0, reguliIesire=0, soloIesire=0, duoIesire=0, continentala=0, setari=0, setariIesire=0, provocare=0, iesireProvocare=0;
int cronometru=0, usor=0,greu=0, provocare1=0,provocare2=0,normal=0;
int iesire_joc;
char contor1[20], contor2[20],copie_contor1[20],copie_contor2[20];

char minute[3]="00";
char secunde[4]=":00";
int contor=0;
char minute6[3]="01";
char secunde6[4]=":00";
char secunde3[4]=":30";
int numar;

struct
{
    int a,b,c,d;
} coada[100];


void afiseazaMesaj(char mesaj[200])
{
    setcolor(RED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10, HORIZ_DIR, 1);
    int latimeFereastra = getmaxx()/2;
    outtextxy(latimeFereastra,25,mesaj);
    delay(2000);
    setcolor(getbkcolor());
    outtextxy(latimeFereastra, 25, mesaj);

}

void ultim_apasat()
{
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        cout<<mousex()<<" "<<mousey()<<' '<<endl;
    }
}

void deseneazaPiesa(int linia, int coloana, int culoare)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    // stergere
    setcolor(culoareFundal);
    setfillstyle(SOLID_FILL,culoareFundal);
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    // desenez piesa
    setcolor(culoare);
    setfillstyle(SOLID_FILL,culoare);
    fillellipse(xmijloc,ymijloc,latura/3,latura/3);
}

void stabilestePieseTabla()
{
    int i,j,linia1, coloana1, linia2, coloana2;

    if(tipTabla==0)
    {

        TablaDeJoc[1][1]=-1;
        TablaDeJoc[1][2]=-1;
        TablaDeJoc[2][1]=-1;//colt stanga sus
        TablaDeJoc[2][2]=-1;

        TablaDeJoc[nrPatrateLatura-1][1]=-1;
        TablaDeJoc[nrPatrateLatura-1][2]=-1;
        TablaDeJoc[nrPatrateLatura][1]=-1;//colt stanga jos
        TablaDeJoc[nrPatrateLatura][2]=-1;

        TablaDeJoc[1][nrPatrateLatura-1]=-1;
        TablaDeJoc[1][nrPatrateLatura]=-1;
        TablaDeJoc[2][nrPatrateLatura-1]=-1;//colt dreapta sus
        TablaDeJoc[2][nrPatrateLatura]=-1;

        TablaDeJoc[nrPatrateLatura-1][nrPatrateLatura-1]=-1;
        TablaDeJoc[nrPatrateLatura-1][nrPatrateLatura]=-1;
        TablaDeJoc[nrPatrateLatura][nrPatrateLatura-1]=-1;//colt dreapta jos
        TablaDeJoc[nrPatrateLatura][nrPatrateLatura]=-1;
    }

    if(tipTabla==1) //continentala
    {
        TablaDeJoc[1][1]=-1;
        TablaDeJoc[1][2]=-1; //colt stanga sus
        TablaDeJoc[2][1]=-1;

        TablaDeJoc[nrPatrateLatura-1][1]=-1;
        TablaDeJoc[nrPatrateLatura][1]=-1; //colt stanga jos
        TablaDeJoc[nrPatrateLatura][2]=-1;

        TablaDeJoc[1][nrPatrateLatura-1]=-1;
        TablaDeJoc[1][nrPatrateLatura]=-1; //colt dreapta sus
        TablaDeJoc[2][nrPatrateLatura]=-1;

        TablaDeJoc[nrPatrateLatura-1][nrPatrateLatura]=-1;
        TablaDeJoc[nrPatrateLatura][nrPatrateLatura-1]=-1; //colt dreapta jos
        TablaDeJoc[nrPatrateLatura][nrPatrateLatura]=-1;
    }

    if(tipTabla==3)//diamant
    {
        TablaDeJoc[1][1]=-1;
        TablaDeJoc[1][2]=-1;
        TablaDeJoc[1][3]=-1;
        TablaDeJoc[1][4]=-1;
        TablaDeJoc[2][1]=-1;  //colt stanga sus
        TablaDeJoc[2][2]=-1;
        TablaDeJoc[2][3]=-1;
        TablaDeJoc[3][1]=-1;
        TablaDeJoc[3][2]=-1;
        TablaDeJoc[4][1]=-1;

        TablaDeJoc[6][1]=-1;
        TablaDeJoc[nrPatrateLatura-2][1]=-1;
        TablaDeJoc[nrPatrateLatura-2][2]=-1;
        TablaDeJoc[nrPatrateLatura-1][1]=-1;
        TablaDeJoc[nrPatrateLatura-1][2]=-1; //colt stanga jos
        TablaDeJoc[nrPatrateLatura-1][3]=-1;
        TablaDeJoc[nrPatrateLatura][1]=-1;
        TablaDeJoc[nrPatrateLatura][2]=-1;
        TablaDeJoc[nrPatrateLatura][3]=-1;
        TablaDeJoc[nrPatrateLatura][4]=-1;

        TablaDeJoc[1][6]=-1;
        TablaDeJoc[1][nrPatrateLatura-2]=-1;
        TablaDeJoc[1][nrPatrateLatura-1]=-1;
        TablaDeJoc[1][nrPatrateLatura]=-1;
        TablaDeJoc[2][nrPatrateLatura-2]=-1; //colt dreapta sus
        TablaDeJoc[2][nrPatrateLatura-1]=-1;
        TablaDeJoc[2][nrPatrateLatura]=-1;
        TablaDeJoc[3][nrPatrateLatura-1]=-1;
        TablaDeJoc[3][nrPatrateLatura]=-1;
        TablaDeJoc[4][nrPatrateLatura]=-1;

        TablaDeJoc[6][nrPatrateLatura]=-1;
        TablaDeJoc[nrPatrateLatura-2][nrPatrateLatura-1]=-1;
        TablaDeJoc[nrPatrateLatura-2][nrPatrateLatura]=-1;
        TablaDeJoc[nrPatrateLatura-1][nrPatrateLatura-2]=-1;
        TablaDeJoc[nrPatrateLatura-1][nrPatrateLatura-1]=-1; //colt dreapta jos
        TablaDeJoc[nrPatrateLatura-1][nrPatrateLatura]=-1;
        TablaDeJoc[nrPatrateLatura][6]=-1;
        TablaDeJoc[nrPatrateLatura][nrPatrateLatura-2]=-1;
        TablaDeJoc[nrPatrateLatura][nrPatrateLatura-1]=-1;
        TablaDeJoc[nrPatrateLatura][nrPatrateLatura]=-1;
    }


    if(tipTabla==4)
    {
        int i=1;
        while(i<=9)
        {
            TablaDeJoc[1][i]=-1;
            TablaDeJoc[2][i]=-1;
            TablaDeJoc[8][i]=-1;
            TablaDeJoc[9][i]=-1;
            i++;
        }
        TablaDeJoc[3][1]=-1;
        TablaDeJoc[3][2]=-1;
        TablaDeJoc[3][3]=-1;
        TablaDeJoc[3][4]=-1;
        TablaDeJoc[4][1]=-1;        //colt stanga
        TablaDeJoc[4][2]=-1;
        TablaDeJoc[4][3]=-1;
        TablaDeJoc[5][1]=-1;
        TablaDeJoc[5][2]=-1;
        TablaDeJoc[6][1]=-1;

        TablaDeJoc[3][6]=-1;
        TablaDeJoc[3][7]=-1;
        TablaDeJoc[3][8]=-1;
        TablaDeJoc[3][9]=-1;
        TablaDeJoc[4][7]=-1;       //colt dreapta
        TablaDeJoc[4][8]=-1;
        TablaDeJoc[4][9]=-1;
        TablaDeJoc[5][8]=-1;
        TablaDeJoc[5][9]=-1;
        TablaDeJoc[6][9]=-1;
    }
}


int existaPiesaIntre(int linia1, int coloana1, int linia2, int coloana2)
{
    if (linia1 == linia2)
    {
        int coloanaMin = min(coloana1, coloana2);
        int coloanaMax = max(coloana1, coloana2);
        for (int coloana = coloanaMin + 1; coloana < coloanaMax; coloana++)//verificam daca existam o piesa intre
            if (TablaDeJoc[linia1][coloana] == 1)
                return 1;
    }
    else if (coloana1 == coloana2)
    {
        int liniaMin = min(linia1, linia2);
        int liniaMax = max(linia1, linia2);
        for (int linia = liniaMin + 1; linia < liniaMax; linia++)
            if (TablaDeJoc[linia][coloana1] == 1)
                return 1;
    }
    return 0;
}

bool suprapunePiesaAlaturata(int linia1, int coloana1, int linia2, int coloana2)
{
    if ((linia1 == linia2 && abs(coloana1 - coloana2) == 1) || (coloana1 == coloana2 && abs(linia1 - linia2) == 1))
        return true;
    return false;
}

int verifTabla(int linie,int coloana)
{
    if(tipTabla==0) ///englezeasca
        if((linie>2 && linie<nrPatrateLatura-1)||( coloana>2 && coloana<nrPatrateLatura-1))
            return 1;


    if(tipTabla==1) ///continentala
    {
        if((linie==2 && (coloana==2 || coloana==nrPatrateLatura-1)) || (linie==nrPatrateLatura-1 && (coloana==2 || coloana==nrPatrateLatura-1)))
            return 1;
        if((linie>2 && linie<nrPatrateLatura-1)||( coloana>2 && coloana<nrPatrateLatura-1))
            return 1;
    }


    if(tipTabla==2) ///patrat
        return 1;


    if(tipTabla==3) ///diamant
    {
        nrPatrateLatura=9;
        if((linie>=1 && linie<=nrPatrateLatura && coloana==nrPatrateLatura/2+1) ||  //coloana intreaga
                (linie==nrPatrateLatura/2+1 && coloana>=1 && coloana<=nrPatrateLatura) || //linie intreaga
                ((linie==2 || linie==nrPatrateLatura-1) && coloana>=nrPatrateLatura/2 && coloana<=nrPatrateLatura/2+2) ||
                (linie>=nrPatrateLatura/2 && linie<=nrPatrateLatura/2+2 && coloana>=2 && coloana<=nrPatrateLatura-1) ||
                (linie>=nrPatrateLatura/2-1 && linie<=nrPatrateLatura/2+3 && coloana>=nrPatrateLatura/2-1 && coloana<=nrPatrateLatura/2+3))
            return 1;
    }


    if(tipTabla==4) ///triunghi
    {
        nrPatrateLatura=9;
        if(linie==nrPatrateLatura/2-1 && coloana==nrPatrateLatura/2+1)
            return 1;
        else if((linie==nrPatrateLatura/2 && coloana>=nrPatrateLatura/2 && coloana<=nrPatrateLatura/2+2) ||
                (linie==nrPatrateLatura/2+1 && coloana>=nrPatrateLatura/2-1 && coloana<=nrPatrateLatura-2) ||
                (linie==nrPatrateLatura/2+2 && coloana>=2 && coloana<=nrPatrateLatura-1) ||
                (linie==nrPatrateLatura-2 && coloana>=1 && coloana<=nrPatrateLatura))
            return 1;
    }


    if(tipTabla==5 && (TablaDeJoc[linie][coloana]==1 || TablaDeJoc[linie][coloana]==0))
        return 1;
    else
        return 0;

    return 0;
}

int mutareGresita(int linia1, int coloana1, int linia2, int coloana2)
{
    if (TablaDeJoc[linia1][coloana1]==0 && TablaDeJoc[linia2][coloana2]==0) return 11; // NU poti muta din spatii goale in spatii goale!!!
    if (TablaDeJoc[linia1][coloana1]==1 && TablaDeJoc[linia2][coloana2]==-1) return 10; //NU muta in afara tablei!!!!
    if (TablaDeJoc[linia1][coloana1]==-1 && (TablaDeJoc[linia2][coloana2]==0 || TablaDeJoc[linia2][coloana2]==1)) return 6; // Ai plecat din afara tablei.
    if (linia1==linia2 && coloana1==coloana2 && verifTabla(linia1,coloana1)==1 && verifTabla(linia2,coloana2)==1) return 1; // Locul de sosire trebuie sa difere de locul de plecare.
    if (TablaDeJoc[linia1][coloana1]==-1 && TablaDeJoc[linia2][coloana2]==-1) return 12;//Nu ai voie sa faci mutari in afara tablei.
    if (suprapunePiesaAlaturata(linia1,coloana1,linia2,coloana2)==true && TablaDeJoc[linia1][coloana1]==1 && TablaDeJoc[linia2][coloana2]==1) return 3;  //Ai mutat piesa peste o alta piesa.
    if (abs(coloana1 - coloana2) >= 1 && abs(linia1 - linia2) >= 1 && TablaDeJoc[linia1][coloana1]==1 && TablaDeJoc[linia2][coloana2]==0) return 9; //Mutarile NU se pot realiza pe diagonala!
    if (TablaDeJoc[linia1][coloana1]==1 && TablaDeJoc[linia2][coloana2]==1) return 3;
    if (TablaDeJoc[linia1][coloana1] == 1 && TablaDeJoc[linia2][coloana2] == 0 && verifTabla(linia2,coloana2) == 1 && (abs(linia1-linia2)==1 || abs(coloana1-coloana2)==1)) return 13; //Nu poti muta in spatii goale.
    if (abs(linia1-linia2)!=2 && coloana1==coloana2)  return 4; //Diferenta intre linii trebuie sa fie 2.
    if (abs(coloana1-coloana2)!=2 && linia1==linia2)  return 5; //Diferenta intre coloane trebuie sa fie 2.
    if (verifTabla(linia1,coloana1) == 1 && TablaDeJoc[linia1][coloana1]==0)  return 2; // Ai ales un loc de plecare unde nu este o piesa.
    if (existaPiesaIntre(linia1,coloana1,linia2,coloana2)==false) return 8; // Intre punctul de plecare si cel de sosire trebuie sa fie o piesa.

    return 0;
}


bool stabilestePiesaColorata(int linia1, int coloana1)
{
    int linia2,coloana2;
    if(mutareGresita(linia1,coloana1,linia2,coloana2)>=1 && mutareGresita(linia1,coloana1,linia2,coloana2)<=13)
        return false;
    else
        return true;
}

void patrat_simplu(int i,int j, int culoarePatratSimplu)
{
    setcolor(culoarePatratSimplu);
    rectangle(stanga+latura*(j-1),sus+latura*(i-1),stanga+latura*j,sus+latura*i);
}

void stabilestePatratColorat(int i, int j, int culoarep)
{
    if(TablaDeJoc[i][j]==1)
    {
        if(TablaDeJoc[i-1][j]==1 && verifTabla(i-2,j) && TablaDeJoc[i-2][j]==0 && i!=2)
            patrat_simplu(i-2,j,culoarep);
        if(TablaDeJoc[i][j+1]==1 && verifTabla(i,j+2) && TablaDeJoc[i][j+2]==0 && j!=nrPatrateLatura-1)
            patrat_simplu(i,j+2,culoarep);
        if(TablaDeJoc[i+1][j]==1 && verifTabla(i+2,j) && TablaDeJoc[i+2][j]==0 && i!=nrPatrateLatura-1)
            patrat_simplu(i+2,j,culoarep);
        if(TablaDeJoc[i][j-1]==1 && verifTabla(i,j-2) && TablaDeJoc[i][j-2]==0 && j!=2)
            patrat_simplu(i,j-2,culoarep);
    }
}

void refacere_mutare(int linia1,int coloana1, int linia2,int coloana2)
{
    if(k>0)
    {
        PlaySound(TEXT("undo.wav"), NULL, SND_FILENAME|SND_ASYNC);
        TablaDeJoc[linia2][coloana2]=0;
        TablaDeJoc[linia1][coloana1]=1;
        deseneazaPiesa(linia1,coloana1,culoarePiesa);
        deseneazaPiesa(linia2,coloana2,culoareFundal);
        if (linia1==linia2)
        {
            TablaDeJoc[linia1][(coloana1+coloana2)/2]=1;
            deseneazaPiesa(linia1,(coloana1+coloana2)/2,culoarePiesa);
        }
        if (coloana1==coloana2)
        {
            TablaDeJoc[(linia1+linia2)/2][coloana1]=1;
            deseneazaPiesa((linia1+linia2)/2,coloana1,culoarePiesa);
        }
        k--;
    }
}

int se_poate_muta()
{
    int ok=0;
    for(int i=1; i<=nrPatrateLatura; i++)
        for(int j=1; j<=nrPatrateLatura; j++)
        {
            if(TablaDeJoc[i][j]==1)
            {
                ///mutare in sus
                if(TablaDeJoc[i-1][j]==1 && verifTabla(i-2,j) && TablaDeJoc[i-2][j]==0 && i!=2)
                    ok=1;
                ///mutare la dreapta
                if(TablaDeJoc[i][j+1]==1 && verifTabla(i,j+2) && TablaDeJoc[i][j+2]==0 && j!=nrPatrateLatura-1)
                    ok=1;
                ///mutare in jos
                if(TablaDeJoc[i+1][j]==1 && verifTabla(i+2,j) && TablaDeJoc[i+2][j]==0 && i!=nrPatrateLatura-1)
                    ok=1;
                ///mutare la stanga
                if(TablaDeJoc[i][j-1]==1 && verifTabla(i,j-2) && TablaDeJoc[i][j-2]==0 && j!=2)
                    ok=1;
            }
        }
    return ok;
}

bool stabilesteMutarePiesa(int &linia1, int &coloana1,int &linia2, int &coloana2)
{
    int x,y,dreapta,jos;
    dreapta=stanga+latura*nrPatrateLatura;
    jos=sus+latura*nrPatrateLatura;
    int click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            cout<<"x="<<x<<" y="<<y<<endl;
            if (x>=21 && x<=140 && y>=552 && y<=573)
            {
                iesire_joc=1;
                return false;
            }
            if (x>=stanga && x<=dreapta && y>=sus && y<=jos)
            {
                click=true;
                linia1=(y-sus)/latura+1;
                coloana1=(x-stanga)/latura+1;
                cout<<"start: linia:"<<linia1<<", coloana: "<<coloana1<<endl;
                if(TablaDeJoc[linia1][coloana1]==1)
                {
                    deseneazaPiesa(linia1,coloana1,COLOR(210,105,30));
                    if(se_poate_muta())
                        stabilestePatratColorat(linia1, coloana1,COLOR(210,105,30));
                }

            }
        }
    while (!click);

    click=false;

    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>=13 && x<=200 && y>=552 && y<=560)
            {
                iesire_joc=1;
                return false;
            }
            if (x>=stanga && x<=dreapta && y>=sus && y<=jos)
            {
                click=true;
                linia2=(y-sus)/latura+1;
                coloana2=(x-stanga)/latura+1;
                undo=1;
                if(!mutareGresita(linia1,coloana1,linia2,coloana2))
                {
                    coada[++k].a=linia1;
                    coada[k].b=coloana1;
                    coada[k].c=linia2;
                    coada[k].d=coloana2;
                }
                cout<<"destinatie: linia:"<<linia2<<", coloana: "<<coloana2<<endl;

            }
            if(stabilestePiesaColorata(linia1,coloana1)==false && TablaDeJoc[linia1][coloana1]==1)
            {
                deseneazaPiesa(linia1,coloana1,culoarePiesa);
                stabilestePatratColorat(linia1, coloana1,culoareTabla);
            }

            if(TablaDeJoc[linia2][coloana2]==0)
                patrat_simplu(linia2,coloana2,culoareTabla);
        }
    while (!click);
    return true;
}

void scor()
{
    setcolor(getbkcolor());
    outtextxy(100,100,copie_contor1);
    outtextxy(680,100,copie_contor2);
    delay(50);
    setcolor(BLACK);
    sprintf(contor1, " %d ", nrPieseJucator1);
    settextstyle(10,4,4);
    outtextxy(100,100,contor1);
    sprintf(contor2, " %d ", nrPieseJucator2);
    outtextxy(680,100,contor2);
    strcpy(copie_contor1,contor1);
    strcpy(copie_contor2,contor2);
}


void executMutare(int linia1, int coloana1, int linia2, int coloana2)
{
    TablaDeJoc[linia1][coloana1]=0;
    TablaDeJoc[linia2][coloana2]=1;
    if (linia1==linia2)
    {
        TablaDeJoc[linia1][(coloana1+coloana2)/2]=0;
        deseneazaPiesa(linia1,(coloana1+coloana2)/2,culoareFundal);
        PlaySound(TEXT("pion.wav"), NULL, SND_FILENAME|SND_ASYNC); //sunet ptr mutare pion
    }
    if (coloana1==coloana2)
    {
        TablaDeJoc[(linia1+linia2)/2][coloana1]=0;
        deseneazaPiesa((linia1+linia2)/2,coloana1,culoareFundal);
        PlaySound(TEXT("pion.wav"), NULL, SND_FILENAME|SND_ASYNC);
    }
    deseneazaPiesa(linia1,coloana1,culoareFundal);
    PlaySound(TEXT("pion.wav"), NULL, SND_FILENAME|SND_ASYNC);
    deseneazaPiesa(linia2,coloana2,culoarePiesa); //aici piesa rosie pion
    PlaySound(TEXT("pion.wav"), NULL, SND_FILENAME|SND_ASYNC);
    TablaDeJoc[linia1][coloana1]=0;
}

void Patrat(int i,int j)
{
    setcolor(culoareTabla);
    rectangle(stanga+latura*(j-1),sus+latura*(i-1),stanga+latura*j,sus+latura*i);
    if(i!=(nrPatrateLatura+1)/2 || j!=(nrPatrateLatura+1)/2) //nu e piesa din centru
        deseneazaPiesa(i,j,culoarePiesa);
}

int citeste_tabla();
void Tabla()
{
    int i,j;
    if(tipTabla==3 || tipTabla==4)
        nrPatrateLatura=9;
    if(tipTabla==5)
        nrPatrateLatura=7;
    latime=inaltime=500;
    latura=latime/nrPatrateLatura;
    sus=(getmaxy()-latime)/2;
    stanga=(getmaxx()-inaltime)/2;
    setbkcolor(culoareFundal);
    clearviewport();
    setcolor(culoareTabla);
    stabilestePieseTabla();
    for (i=1; i<=nrPatrateLatura; i++)
        for (j=1; j<=nrPatrateLatura; j++)
            if(verifTabla(i,j))
            {
                if(tipTabla==5)
                {
                    citeste_tabla();
                    if(TablaDeJoc[i][j]==1)
                        Patrat(i,j);
                    if(TablaDeJoc[i][j]==0)
                    {
                        Patrat(i,j);
                        int x=culoarePiesa;
                        culoarePiesa=culoareFundal;
                        Patrat(i,j);
                        culoarePiesa=x;
                        /*deseneazaPiesa(i,j,culoareFundal);
                        TablaDeJoc[i][j]==0;*/
                    }
                }
                else
                    Patrat(i,j);
                    TablaDeJoc[i][j]=1;
            }

    TablaDeJoc[(nrPatrateLatura+1)/2][(nrPatrateLatura+1)/2]=0; //piesa din centru
}


void afiseazaMesajEroare(int mg)
{
    switch(mg)
    {
    case 1:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Locul de sosire trebuie sa difere de locul de plecare.");
        break;
    case 2:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Ai ales un loc de plecare unde nu este o piesa.");
        break;
    case 3:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Ai mutat piesa peste o alta piesa.");
        break;
    case 4:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Diferenta intre linii trebuie sa fie 2.");
        break;
    case 5:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Diferenta intre coloane trebuie sa fie 2.");
        break;
    case 6:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Ai plecat din afara tablei.");
        break;
    case 7:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Vrei sa muti in afara tablei.");
        break;
    case 8:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Intre punctul de plecare si cel de sosire trebuie sa fie o piesa.");
        break;
    case 9:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Mutarile NU se pot realiza pe diagonala!");
        break;
    case 10:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("NU muta in afara tablei!!!!");
        break;
    case 11:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("NU poti muta din spatii goale in spatii goale!!!");
        break;
    case 12:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Nu ai voie sa faci mutari in afara tablei.");
        break;
    case 13:
        PlaySound(TEXT("eroare_mutare.wav"), NULL, SND_FILENAME|SND_ASYNC);
        afiseazaMesaj("Nu poti muta in spatii goale.");
        break;
    }
}


int calculeaza_nr_pioni()
{
    int nr=0;
    for(int i=1; i<=nrPatrateLatura; i++)
        for(int j=1; j<=nrPatrateLatura; j++)
            if(TablaDeJoc[i][j]==1)
                nr++; //calculeaza nr pioni de pe tabla
    return nr;
}

void reset_cronometru()
{

    if(iesire_joc==1)
    {
        contor = 0;
        strcpy(secunde, ":00");
        strcpy(minute, "00");
        iesire_joc=0;
    }

}

void reset_timer60()
{
    if(iesire_joc==1)
    {
        contor = 0;
        strcpy(secunde6, ":00");
        strcpy(minute6, "01");
        iesire_joc=0;
    }
}

void reset_timer30()
{
    if(iesire_joc==1)
    {
        contor = 0;
        strcpy(secunde3, ":30");
        strcpy(minute, "00");
        iesire_joc=0;
    }
}

void cronometru_functie()
{
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(10);
        contor+=10;
        if(contor==1000)
        {
            secunde[2]++;
            if(secunde[2]=='9')
            {
                settextstyle(10,HORIZ_DIR,4);
                setcolor(RED);
                outtextxy(370,580,minute);
                outtextxy(420,580,secunde);
                delay(1200);
                secunde[2]='0';
                secunde[1]++;
            }
            if(secunde[1]=='6'&&secunde[2]=='0')
            {
                secunde[2]='0';
                secunde[1]='0';
                if(minute[1]=='9')
                {
                    settextstyle(10,HORIZ_DIR,4);
                    setcolor(RED);
                    outtextxy(370,580,minute);
                    outtextxy(420,580,secunde);
                    delay(1200);
                    minute[1]='0';
                    minute[0]+=1;
                }
                else
                    minute[1]++;
            }
            contor=0;
            settextstyle(10,HORIZ_DIR,4);
            setcolor(RED);
            outtextxy(370,580,minute);
            outtextxy(420,580,secunde);
        }
    }
}

void timer60()
{

    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        settextstyle(10,4,4);
        setcolor(RED);
        outtextxy(370,580,minute6);
        outtextxy(420,580,secunde6);

        delay(10);
        contor+=10;
        if(contor==1000)
        {
            secunde6[2]--;
            if(minute6[0]=='0' && minute6[1]=='0' && secunde6[1]=='0' && secunde6[2]=='0')
            {
                settextstyle(10,4,4);
                setcolor(RED);
                outtextxy(370,580,minute6);
                outtextxy(420,580,secunde6);
                delay(1000);
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                cleardevice();
                PlaySound(TEXT("game_over.wav"), NULL, SND_FILENAME|SND_ASYNC);
                outtextxy(390,280,"TIMPUL A EXPIRAT!");
                delay(4000);
                closegraph();
                exit(0);
                break;
            }
            if(minute6[1]=='1')
            {
                minute6[1]='0';
                secunde6[1]='5';
                secunde6[2]='9';
            }
            if(secunde6[2]=='0')
            {
                settextstyle(10,4,4);
                setcolor(RED);
                outtextxy(370,580,minute6);
                outtextxy(420,580,secunde6);
                delay(1200);
                secunde6[2]='9';
                secunde6[1]--;
            }
            contor=0;
        }
    }
}

void timer30()
{
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        settextstyle(10,4,4);
        setcolor(RED);
        outtextxy(370,580,minute);
        outtextxy(420,580,secunde3);
        delay(10);
        contor+=10;
        if(contor==1000)
        {
            secunde3[2]--;
            if(secunde3[1]=='0' && secunde3[2]=='0')
            {
                settextstyle(10,4,4);
                setcolor(RED);
                outtextxy(370,580,minute);
                outtextxy(420,580,secunde3);
                delay(1000);
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                cleardevice();
                outtextxy(390,280,"TIMPUL A EXPIRAT!");
                PlaySound(TEXT("game_over.wav"), NULL, SND_FILENAME|SND_ASYNC);
                delay(4000);
                closegraph();
                exit(0);
                break;
            }
            if(secunde3[1]=='3')
            {
                secunde3[1]='2';
                secunde3[2]='9';
            }
            if(secunde3[2]=='0')
            {
                settextstyle(10,4,4);
                setcolor(RED);
                outtextxy(370,580,minute);
                outtextxy(420,580,secunde3);
                delay(1400);
                secunde3[2]='9';
                secunde3[1]--;
            }
            contor=0;
        }
    }
}


int victorie_solo()
{
    if(se_poate_muta()==0)
    {
        if(calculeaza_nr_pioni()==1)
        {
            if(TablaDeJoc[4][4]!=1)
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

int victorie_duo()
{
    if(nrPieseJucator1>nrPieseJucator2)
        return 1;
    else if(nrPieseJucator1<nrPieseJucator2)
        return 2;
    return 0;
}

void meniu()
{
    int x=0,y=0;
    void *bitmap;
    setactivepage(0);

    setcolor(COLOR(255,0,0));
    setbkcolor(COLOR(255, 236, 55));
    putimage(x,y, bitmap, COPY_PUT);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10, HORIZ_DIR, 7);
    outtextxy(410,260, "SOLITARUL");
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(410, 310, "REGULI");
    outtextxy(410, 350, "SETARI");
    outtextxy(410, 390, "ALEGE O PROVOCARE");
    outtextxy(410, 430, "UN JUCATOR");
    outtextxy(410, 470, "DOI JUCATORI");

    ultim_apasat();
    setbkcolor(COLOR(250, 222, 0));
    outtextxy(100,50, "IESIRE");
    setvisualpage(0);
}

int provocare1_verif()
{
    int ok=1;
    if(TablaDeJoc[1][3]==0 || TablaDeJoc[1][4]==0 || TablaDeJoc[1][5]==0)
        ok=0;
    if(TablaDeJoc[2][2]==0 || TablaDeJoc[2][6]==0)
        ok=0;
    if(TablaDeJoc[3][1]==0 || TablaDeJoc[3][7]==0)
        ok=0;
    if(TablaDeJoc[4][1]==0 || TablaDeJoc[4][4]==0 || TablaDeJoc[4][7]==0)
        ok=0;
    if(TablaDeJoc[5][1]==0 || TablaDeJoc[5][7]==0)
        ok=0;
    if(TablaDeJoc[6][2]==0 || TablaDeJoc[6][6]==0)
        ok=0;
    if(TablaDeJoc[7][3]==0 || TablaDeJoc[7][4]==0 || TablaDeJoc[7][5]==0)
        ok=0;
    return ok;
}

int provocare2_verif()
{
    int ok=1;
    if(TablaDeJoc[3][3]==0 || TablaDeJoc[3][5]==0 )
        ok=0;
    if(TablaDeJoc[4][4]==0 )
        ok=0;
    if(TablaDeJoc[5][3]==0 || TablaDeJoc[5][5]==0)
        ok=0;
    return ok;
}


int citeste_tabla()
{
    srand(time(NULL));
    numar = rand() % 4 + 2;

    int pion;
    int nrPatrateTabla;
    ifstream fin;
    if(numar>=5)
    {
        string numeFisier = to_string(numar) + ".txt";
        fin.open(numeFisier);
        for(int i=1; i<=nrPatrateLatura; i++)
            for(int j=1; j<=nrPatrateLatura; j++)
            {
                fin>>TablaDeJoc[i][j];
            }
        fin.close();
    }
    cout<<numar<<endl;
    return numar;
}


void optiuni_meniu(int x, int y)
{
    int pagina=getvisualpage();
    if(x >= 60 && x <= 150 && y >= 36 && y<= 50 && pagina==0)
        gata=1,ok=1;
    if(x >= 365 && x <= 455 && y >= 295 && y<= 312 && pagina==0)
        reguli=1;
    if(x >= 60 && x <= 240 && y >= 500 && y<= 570 && pagina==1)
        reguliIesire=1;
    if(x >= 367 && x <= 453 && y >= 336 && y <= 351 && pagina==0)
        setari=1;
    if(x >= 30 && x <= 120 && y >= 547 && y<= 565 && pagina==2)
        setariIesire=1;

    if(x >= 5 && x <= 160 && y >= 545 && y <= 575 && pagina==3)
        iesireProvocare=1;
    if (x >=287 && x <= 530 && y >= 375 && y <= 393 && pagina==0)
        provocare=1;

    if(x>=336 && x<=485 && y>=415 && y<=430 && pagina==0)
        solo=1;
    if(x>=15 && x<=105 && y>=40 && y<=78 && undo==1)
        refacere_mutare(coada[k].a,coada[k].b,coada[k].c,coada[k].d);
    if(x>=320 && x<=500 && y>=457 && y<=473 && pagina==0)
        duo=1;

    if(x >= 154 && x <= 194 && y >= 134 && y<= 176 && pagina==3)
        cronometru=1; ///cronometru
    if(x >= 245 && x <= 356 && y >= 150 && y<= 178 && pagina==3)
        usor=1; ///timer 60
    if(x >= 450 && x <= 557 && y >= 152 && y<= 180 && pagina==3)
        greu=1; ///timer 30

    ///aranjare piese intr un anumit fel
    if(x>=100 && x<=360 && y>=280 && y<=490 && pagina==3)
        provocare1=1,provocare2=0;
    if(x>=435 && x<=720 && y>=280 && y<=480 && pagina==3)
        provocare2=1,provocare1=0;
    if(x>=215 && x<=550 && y>=80 && y<=91 && pagina==3)
        normal=1; //adica solo normal


    if(x >= 65 && x <= 230 && y >= 155 && y<= 170 && pagina==2)
        tipTabla=0; //englezeasca
    if(x >= 270 && x <= 450 && y >= 155 && y<= 170 && pagina==2)
        tipTabla=1; //continentala
    if(x >= 490 && x <= 750 && y >= 155 && y<= 170 && pagina==2)
        tipTabla=citeste_tabla(); //generare aleatorie

    if (x >= 175 && x <= 257 && y >= 295 && y <= 312 && pagina==2)
        culoareTabla = BLACK;

    if(x >= 355 && x <= 430 && y >= 290 && y <= 310 && pagina==2)
        culoareTabla = GREEN;

    if(x >= 510 && x <= 630 && y >= 290 && y <= 305 && pagina==2)
        culoareTabla = BLUE;

    if (x >= 200 && x <= 270 && y >= 375 && y <= 390 && pagina==2)
        culoarePiesa = RED;

    if(x >= 345 && x <= 435 && y >= 377 && y <= 390 && pagina==2)
        culoarePiesa = YELLOW;

    if(x >= 513 && x <= 564 && y >= 375 && y <= 390 && pagina==2)
        culoarePiesa = WHITE;


    if(x >= 175 && x <= 265 && y >= 456 && y <= 470 && pagina==2)
        culoareFundal = COLOR(252,207,2);

    if(x >= 335 && x <= 457 && y >= 455 && y <= 472 && pagina==2)
        culoareFundal = COLOR(0,139,139);

    if(x >= 515 && x <= 620 && y >= 453 && y <= 468 && pagina==2)
        culoareFundal = MAGENTA;


    if(x >= 330 && x <= 347 && y >= 546 && y <= 560 && pagina==2)
        nrPatrateLatura = 7;

    if(x >= 384 && x <= 413 && y >= 545 && y <= 555 && pagina==2)
        nrPatrateLatura = 9;

    if(x >= 443 && x <= 475 && y >= 545 && y <= 560 && pagina==2)
        nrPatrateLatura = 11;

}
void alege_provocare()
{
    provocare=0;
    iesireProvocare=0;
    setactivepage(3);

    readimagefile("reguli.jpg", 0, 0, getmaxx(), getmaxy());
    readimagefile("provocare1.jpg", 50, 280, 400, 500);
    readimagefile("provocare2.jpg", 400, 280, 750, 500);
    setcolor(WHITE);
    setbkcolor(COLOR(252,207,2));
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10, HORIZ_DIR, 6);
    outtextxy(430,50,"ALEGE O PROVOCARE:");
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(390, 120, "TERMINA JOCUL IN");
    readimagefile("cronometru.jpg", 150, 130, 200, 180);
    setcolor(GREEN);
    rectangle(245,180,355,150);
    outtextxy(300, 170, "60 sec");
    setcolor(COLOR(235, 5, 5));
    rectangle(445,180,555,150);
    outtextxy(500, 170, "30 sec");
    setcolor(WHITE);
    settextstyle(10,HORIZ_DIR,4);
    outtextxy(380, 230, "ARANJEAZA PIESELE IN ACEST FEL:");
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(380, 550, "REVIN-O LA TABLA NORMALA");
    rectangle(190,520,570,570);
    setvisualpage(3);


    settextstyle(COMPLEX_FONT,0,1);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    setcolor(WHITE);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(30,560,"IESIRE");

    do
    {
        ultim_apasat();
    }
    while(!iesireProvocare);

    setactivepage(0);
    setvisualpage(0);

}

void prov1(int linia1,int coloana1,int linia2,int coloana2)
{
    tipJoc=0;
    setactivepage(1);
    tipTabla=1;
    nrPatrateLatura=7;
    Tabla();
    bool mutare_facuta;
    settextstyle(10,HORIZ_DIR,4);
    setcolor(RED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(80,570,"IESIRE");
    outtextxy(60,70,"UNDO");
    rectangle(15,40,105,80);
    setvisualpage(1);
    settextstyle(10,HORIZ_DIR,1);
    outtextxy(100,100,"Atentie ai ales");
    outtextxy(100,120,"provocarea 1!");

    do
    {
        if(greu==1)
        {
            reset_timer30();
            timer30();
        }
        if(usor==1)
        {
            reset_timer60();
            timer60();
        }
        if(cronometru==1)
        {
            reset_cronometru();
            cronometru_functie();
        }
        mutare_facuta=stabilesteMutarePiesa(linia1,coloana1,linia2,coloana2);
        if (mutare_facuta)
        {
            setcolor(WHITE);
            rectangle(15,40,105,80);
            int mg=mutareGresita(linia1,coloana1,linia2,coloana2);
            if (!mg)
                executMutare(linia1,coloana1,linia2,coloana2);
            else
                afiseazaMesajEroare(mg);

        }
    }
    while(se_poate_muta() && mutare_facuta);
    usor=0; //resetez butoanele
    greu=0;

    if(se_poate_muta()==0)
    {
        setcolor(RED);
        settextstyle(10,4,5);
        cleardevice();
        outtextxy(380,280,"Joc terminat");
        if(provocare1_verif()==1)
        {
            settextstyle(10,4,5);
            outtextxy(385,320,"Ai castigat provocarea 1!");
            PlaySound(TEXT("win.wav"), NULL, SND_FILENAME|SND_ASYNC);
            delay(4000);
            provocare1=provocare2=0;
            setactivepage(0);
            setvisualpage(0);
        }
        else
        {
            settextstyle(10,4,5);
            outtextxy(385,320,"Ai pierdut provocarea 1!");
            PlaySound(TEXT("game_over.wav"), NULL, SND_FILENAME|SND_ASYNC);
            delay(4000);
            provocare1=provocare2=0;
            setactivepage(0);
            setvisualpage(0);
        }
        provocare1=provocare2=0;
    }
    tipTabla=0;
    provocare1=provocare2=0;

}

void prov2(int linia1,int coloana1,int linia2,int coloana2)
{
    tipJoc=0;
    setactivepage(1);
    tipTabla=1;
    nrPatrateLatura=7;
    Tabla();
    bool mutare_facuta;
    settextstyle(10,HORIZ_DIR,4);
    setcolor(RED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(80,570,"IESIRE");
    outtextxy(60,70,"UNDO");
    rectangle(15,40,105,80);
    setvisualpage(1);
    settextstyle(10,HORIZ_DIR,1);
    outtextxy(100,100,"Atentie ai ales");
    outtextxy(100,120,"provocarea 2!");

    do
    {
        if(greu==1)
        {
            reset_timer30();
            timer30();
        }
        if(usor==1)
        {
            reset_timer60();
            timer60();
        }
        if(cronometru==1)
        {
            reset_cronometru();
            cronometru_functie();
        }
        mutare_facuta=stabilesteMutarePiesa(linia1,coloana1,linia2,coloana2);
        if (mutare_facuta)
        {
            setcolor(WHITE);
            rectangle(15,40,105,80);
            int mg=mutareGresita(linia1,coloana1,linia2,coloana2);
            if (!mg)
                executMutare(linia1,coloana1,linia2,coloana2);
            else
                afiseazaMesajEroare(mg);

        }
    }
    while(se_poate_muta() && mutare_facuta);
    usor=0;
    greu=0;

    if(se_poate_muta()==0)
    {
        setcolor(RED);
        settextstyle(10,4,5);
        cleardevice();
        outtextxy(380,280,"Joc terminat");
        if(provocare2_verif()==1)
        {
            settextstyle(10,4,5);
            outtextxy(385,320,"Ai castigat provocarea 2!");
            PlaySound(TEXT("win.wav"), NULL, SND_FILENAME|SND_ASYNC);
            delay(4000);
            provocare1=provocare2=0;
            setactivepage(0);
            setvisualpage(0);
        }
        else
        {
            settextstyle(10,4,5);
            outtextxy(385,320,"Ai pierdut provocarea 2!");
            PlaySound(TEXT("game_over.wav"), NULL, SND_FILENAME|SND_ASYNC);
            delay(4000);
            provocare1=provocare2=0;
            setactivepage(0);
            setvisualpage(0);
        }
        provocare1=provocare2=0;
    }
    tipTabla=0;
    provocare1=provocare2=0;

}


void un_jucator(int linia1,int coloana1,int linia2,int coloana2)
{
    if(provocare1==1)
    {
        prov1(linia1,coloana1,linia2,coloana2);
        return;
    }
    else if(provocare2==1)
    {
        prov2(linia1,coloana1,linia2,coloana2);
        return;
    }
    else if(normal==1 || solo==1)
    {
        tipJoc=0;
        setactivepage(1);
        Tabla();
        bool mutare_facuta;
        settextstyle(10,HORIZ_DIR,4);
        setcolor(RED);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(80,570,"IESIRE");
        outtextxy(60,70,"UNDO");
        rectangle(15,40,105,80);
        setvisualpage(1);
        do
        {

            if(greu==1)
            {
                reset_timer30();
                timer30();
            }
            if(usor==1)
            {
                reset_timer60();
                timer60();
            }
            if(cronometru==1)
            {
                reset_cronometru();
                cronometru_functie();
            }
            mutare_facuta=stabilesteMutarePiesa(linia1,coloana1,linia2,coloana2);

            if (mutare_facuta)
            {
                setcolor(WHITE);
                rectangle(15,40,105,80);
                int mg=mutareGresita(linia1,coloana1,linia2,coloana2);
                if (!mg)
                    executMutare(linia1,coloana1,linia2,coloana2);
                else
                    afiseazaMesajEroare(mg);
            }
        }
        while(se_poate_muta() && mutare_facuta);
        usor=0;
        greu=0;
        if(se_poate_muta()==0)
        {
            setcolor(RED);
            settextstyle(10,4,5);
            cleardevice();
            outtextxy(380,280,"Joc terminat");
            if(victorie_solo())
            {
                settextstyle(10,4,5);
                outtextxy(385,320,"Ai castigat!");
                PlaySound(TEXT("win.wav"), NULL, SND_FILENAME|SND_ASYNC);
                delay(4000);
                setactivepage(0);
                setvisualpage(0);
            }
            else
            {
                settextstyle(10,4,5);
                outtextxy(385,320,"Ai pierdut!");
                PlaySound(TEXT("game_over.wav"), NULL, SND_FILENAME|SND_ASYNC);
                delay(4000);

                setactivepage(0);
                setvisualpage(0);
            }
        }
        provocare1=provocare2=0;
        return;
    }

}


void doi_jucatori(int linia1,int coloana1,int linia2,int coloana2)
{
    nrPieseJucator1=nrPieseJucator2=0;
    tipJoc=1;
    setactivepage(1);
    Tabla();
    bool mutare_facuta;
    settextstyle(10,HORIZ_DIR,3);
    setcolor(WHITE);
    outtextxy(120,60,"JUCATORUL 1:");
    setcolor(BLACK);
    outtextxy(680,60,"JUCATORUL 2:");
    scor();
    settextstyle(10,HORIZ_DIR,4);
    setcolor(RED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(80,570,"IESIRE");
    setvisualpage(1);

    do
    {
        if(greu==1)
        {
            reset_timer30();
            timer30();
        }
        if(usor==1)
        {
            reset_timer60();
            timer60();
        }
        if(cronometru==1)
        {
            reset_cronometru();
            cronometru_functie();
        }
        mutare_facuta=stabilesteMutarePiesa(linia1,coloana1,linia2,coloana2);
        if (mutare_facuta)
        {
            int mg=mutareGresita(linia1,coloana1,linia2,coloana2);
            if (!mg)
            {
                executMutare(linia1,coloana1,linia2,coloana2);
                if(randJucator==1)
                {
                    nrPieseJucator1++;
                    scor();
                }
                else if(randJucator==2)
                {
                    nrPieseJucator2++;
                    scor();
                }
                if(randJucator==1 && !mg)
                {
                    randJucator=2;
                    settextstyle(10,HORIZ_DIR,3);
                    setcolor(BLACK);
                    outtextxy(120,60,"JUCATORUL 1:");
                    setcolor(WHITE);
                    outtextxy(680,60,"JUCATORUL 2:");
                }
                else if(randJucator==2 && !mg)
                {
                    randJucator=1;
                    settextstyle(10,HORIZ_DIR,3);
                    setcolor(BLACK);
                    outtextxy(680,60,"JUCATORUL 2:");
                    setcolor(WHITE);
                    outtextxy(120,60,"JUCATORUL 1:");
                }
            }
            else
            {
                afiseazaMesajEroare(mg);
                if(randJucator==1 && nrPieseJucator1)
                {
                    nrPieseJucator1--;
                    scor();
                    randJucator=2;
                    settextstyle(10,HORIZ_DIR,3);
                    setcolor(BLACK);
                    outtextxy(120,60,"JUCATORUL 1:");
                    setcolor(WHITE);
                    outtextxy(680,60,"JUCATORUL 2:");
                }
                else if(randJucator==2 && nrPieseJucator2)
                {
                    nrPieseJucator2--;
                    scor();
                    randJucator=1;
                    settextstyle(10,HORIZ_DIR,3);
                    setcolor(BLACK);
                    outtextxy(680,60,"JUCATORUL 2:");
                    setcolor(WHITE);
                    outtextxy(120,60,"JUCATORUL 1:");
                }
            }
        }
    }
    while(se_poate_muta() && mutare_facuta);
    usor=0;
    greu=0;

    if(se_poate_muta()==0)
    {
        setcolor(RED);
        settextstyle(10,4,5);
        cleardevice();
        outtextxy(380,280,"Joc terminat");

        if(victorie_duo()==1)
        {
            settextstyle(10,4,5);
            outtextxy(400,320,"JUCATORUL 1 A CASTIGAT!!");
            PlaySound(TEXT("win.wav"), NULL, SND_FILENAME|SND_ASYNC);
            delay(4000);

            setactivepage(0);
            setvisualpage(0);
        }
        else
        {
            if(victorie_duo()==2)
            {
                settextstyle(10,4,5);
                outtextxy(400,320,"JUCATORUL 2 A CASTIGAT!!");
                PlaySound(TEXT("win.wav"), NULL, SND_FILENAME|SND_ASYNC);
                delay(4000);

                setactivepage(0);
                setvisualpage(0);
            }
            else
            {
                settextstyle(10,4,5);
                outtextxy(400,320,"Egalitate!");
                PlaySound(TEXT("egalitate.wav"), NULL, SND_FILENAME|SND_ASYNC);
                delay(4000);

                setactivepage(0);
                setvisualpage(0);
            }
        }
    }
}




void reguli_joc()
{
    reguliIesire=0;
    setactivepage(1);
    readimagefile("reguli.jpg", 0, 0, getmaxx(), getmaxy());
    setcolor(BLUE);

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10,HORIZ_DIR,5);
    setbkcolor(COLOR(252,207,2));
    outtextxy(400,50,"REGULILE JOCULUI");
    settextstyle(3,HORIZ_DIR,1);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(10,100,"1. TABLA DE JOC " );
    settextstyle(3,HORIZ_DIR,1);
    setcolor(LIGHTBLUE);
    outtextxy(10,130,"-> Se foloseste o tabla patrata cu gauri sau spatii goale in care sunt asezate initial piese.");
    outtextxy(10,160,"Dimensiunea tablei poate varia, dar in multe variante se foloseste o tabla 7 pe 7.");
    settextstyle(10,HORIZ_DIR,3);
    setcolor(BLUE);
    outtextxy(10,190,"2. SCOPUL JOCULUI:");
    settextstyle(3,HORIZ_DIR,1);
    setcolor(LIGHTBLUE);
    outtextxy(10,220,"-> Scopul jocului este sa elimini (sari peste) piesele de pe tabla, lasand doar o singura piesa in final." );
    settextstyle(10,HORIZ_DIR,3);
    setcolor(BLUE);
    outtextxy(10,250,"3. MISCARI POSIBILE:");
    settextstyle(3,0,1);
    setcolor(LIGHTBLUE);
    outtextxy(10,280,"-> Piesele se misca prin sarituri peste alte piese, similar cu miscarea unei dame in jocul de dame.");
    outtextxy(10,310,"-> O piesa poate sa sara peste o piesa adiacenta orizontal sau vertical (nu diagonal) pe o pozitie libera,");
    outtextxy(10,340,"astfel eliminand piesa pe care a sarit-o.");
    outtextxy(10,370,"-> Scopul este sa elimini cat mai multe piese posibil, avand grija sa nu lasi piese izolate,");
    outtextxy(10,400,"care nu pot fi eliminate.");
    settextstyle(10,HORIZ_DIR,3);
    setcolor(BLUE);
    outtextxy(10,430,"4. FINALUL JOCULUI:");
    settextstyle(3,HORIZ_DIR,1);
    setcolor(LIGHTBLUE);
    outtextxy(10,460,"-> Jocul se termina atunci cand nu mai poti face nicio miscare valida si ai eliminat toate piesele posibile,");
    outtextxy(10,490,"sau cand ramane doar o singura piesa pe tabla.");

    settextstyle(10,HORIZ_DIR,4);
    setcolor(BLUE);
    outtextxy(80,550,"IESIRE");
    setvisualpage(1);
    do
    {
        ultim_apasat();
    }
    while(!reguliIesire);

    setactivepage(0);
    setvisualpage(0);
}


void setari_meniu()
{
    setari=0;
    setariIesire=0;
    setactivepage(2);
    readimagefile("reguli.jpg", 0, 0, getmaxx(), getmaxy());
    setcolor(WHITE);
    setbkcolor(COLOR(252,207,2));
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10, HORIZ_DIR, 6);
    outtextxy(380,50,"SETARI");
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(390, 120, "ALEGE TIPUL TABLEI");
    setcolor(GREEN);
    outtextxy(150, 170, "ENGLEZEASCA");
    setcolor(COLOR(235, 5, 5));
    outtextxy(360, 170, "CONTINENTALA");
    setcolor(BLACK);
    outtextxy(620, 170, "GENERARE ALEATORIE");
    setcolor(WHITE);
    settextstyle(10,HORIZ_DIR,4);
    outtextxy(380, 230, "PERSONALIZEAZA-TI JOCUL");
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(380, 270, "Alege culoarea tablei");
    setcolor(COLOR(53, 57, 64));
    outtextxy(220, 310, "NEGRU");
    setcolor(COLOR(44, 87, 47));
    outtextxy(395, 310, "VERDE");
    setcolor(COLOR(39, 33, 130));
    outtextxy(570, 310, "ALBASTRU");
    setcolor(WHITE);
    outtextxy(400, 350, "Alege culoarea pieselor de joc");
    setcolor(LIGHTRED);
    outtextxy(240, 390, "ROSU");
    setcolor(YELLOW);
    outtextxy(390, 390, "GALBEN");
    setcolor(LIGHTGRAY);
    outtextxy(540, 390, "ALB");
    setcolor(WHITE);
    outtextxy(400, 430, "Alege culoarea fundalului");
    setcolor(YELLOW);
    outtextxy(220, 470, "GALBEN");
    setcolor(LIGHTBLUE);
    outtextxy(395, 470, "CYAN");
    setcolor(LIGHTMAGENTA);
    outtextxy(570, 470, "MAGENTA");
    setcolor(WHITE);
    outtextxy(400, 520, "Alege numarul de patrate de pe latura");
    setcolor(GREEN);
    outtextxy(340, 560, "7");
    setcolor(RED);
    outtextxy(400, 560, "9");
    setcolor(BLACK);
    outtextxy(460, 560, "11");


    setvisualpage(2);
    settextstyle(COMPLEX_FONT,0,1);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    setcolor(WHITE);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(30,560,"IESIRE");

    do
    {
        ultim_apasat();
    }
    while(!setariIesire);

    setactivepage(0);
    setvisualpage(0);
}

int main()
{
    initwindow(800,600,"SOLITARUL",350,50);
    readimagefile("bk2.jpg", 0, 0, getmaxx(), getmaxy());
    int linia1,coloana1,linia2,coloana2;

    do
    {
        meniu();
        gata=0;
        registermousehandler(WM_LBUTTONDOWN, optiuni_meniu);

        if(ok==1)
            gata=1;
        if(reguli==1)
        {
            reguli_joc();
            reguli=0;

        }
        if(setari==1)
        {
            setari_meniu();
            setari=0;
        }
        if(solo==1)
        {
            un_jucator(linia1,coloana1,linia2,coloana2);
            solo=0;
        }
        if(duo==1)
        {
            doi_jucatori(linia1,coloana1,linia2,coloana2);
            duo=0;
        }
        if(provocare==1)
        {
            alege_provocare();
            provocare=0;
        }
        ultim_apasat();
        delay(1);
    }
    while(!gata);

    //getch();
    closegraph();
    return 0;
}
