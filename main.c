#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct korisnik
{
    char ime[30], prez[30], mejl[60];
    int lbo;
}Korpod;

typedef struct elem
{
    char ia[30];
    int cena, rb;
    struct elem *pret, *sled;
}Elem;

void ispisi(Elem *prvi, Elem *posl, Elem *tek)
{
    Elem *stari;
    while(prvi)
    {
        stari=prvi;
        printf("%s - %d din\n", prvi->ia, prvi->cena);
        prvi=prvi->sled;
        free(stari);
    }
    posl=tek=NULL;
}

int main()
{
    Korpod a;
    Elem *prvi, *posl, *tek;
    prvi=posl=tek=NULL;
    int b, i, p=0, e=0, k, n=0, j, h, dan, mesec, god, da, m, g;
    float c=0;
    /*k-redni broj analize
    n-ukupni broj analiza iz datoteke
    c-ukupna cena
    i,h,e-brojaci
    b-lbo
    j-koliko analiza hocemo
    p-logicka promenljiva*/
    char s[3], r[30], q[30];
    /*s-da ili ne
    r-ime
    q-prezime*/
    FILE *dato, *dato1;
    printf("Dobar dan i dobrodosli u medicinsku laboratoriju Anora!\n");
   while(1)
   {
       printf("\nUnesite danasnji datum (dan.mesec.godina.): ");
       scanf("%d.%d.%d.",&dan,&mesec,&god);
       if(god>0 && mesec>0 && mesec<13)
       {
           if(mesec==1 || mesec==5 || mesec==3 || mesec==7 || mesec==8 || mesec==10 || mesec==12)
            {
                if(dan>0 && dan<32) break;
            }
            else if(mesec==2)
            {
                if((god%4==0 && god%100!=0) ||god%400==0)
                    if(dan>0 && dan<30) break;
                if(dan>0 && dan<29) break;
            }
            else if(dan>0 && dan<31) break;
       }
       printf("POGRESAN DATUM!\n");
   }
    da=dan;
    m=mesec;
    g=god;
    printf("\n\nUkoliko imate nalog u nasoj bazi korisnika ukucajte 'DA', u suprotnom 'NE': ");
    scanf("%s", &s);
    for(i=0;s[i];i++) s[i]=toupper(s[i]);
    dato=fopen("korisnici.txt", "r");
    if(dato==NULL)
    {
        printf("Greska pri otvaranju datoteke!");
        exit(1);
    }
    while(!strcmp(s, "DA"))
    {
        printf("\nUnesite LBO: ");
        scanf("%d", &b);
        while(!feof(dato))
        {
            fscanf(dato, "%d%s%s%s", &a.lbo, &a.ime, &a.prez, &a.mejl);
            e++;
            if(b==a.lbo)
            {
                printf("\nVasi podaci:\n");
                printf("-Ime i prezime: %s %s\n", a.ime, a.prez);
                printf("-E-mail: %s\n", a.mejl);
                p=1;
                rewind(dato);
                break;
            }
        }
        if(!p)
        {
            printf("Niste pronadjeni u bazi korisnika. Ukoliko zelite da pokusate ponovo ukucajte 'DA', u suprotnom 'NE': ");
            scanf("%s", &s);
            for(i=0;s[i];i++) s[i]=toupper(s[i]);
            rewind(dato);
        }
        else strcpy(s,"NE");
    }
    fclose(dato);
    if(p)
    {
        dato=fopen("korisnici.txt", "r+w");
        if(dato==NULL)
        {
            printf("Greska pri otvaranju datoteke!");
            exit(1);
        }
        printf("\nDa li zelite da unesete izmene u Vasim korisnickim podacima (ukucajte 'da' ili 'ne')? ");
        scanf("%s", &s);
        for(i=0;s[i];i++) s[i]=toupper(s[i]);
        if(!strcmp(s, "DA"))
        {
            for(i=0;i<e-1;i++)
            {
                fscanf(dato, "%d%s%s%s", &a.lbo, &a.ime, &a.prez, &a.mejl);
            }
            fscanf(dato, "%d", &a.lbo);
            printf("Unesite ime i prezime: ");
            scanf("%s %s", &a.ime, &a.prez);
            printf("Unesite e-mail adresu: ");
            scanf("%s", &a.mejl);
        }
        fseek(dato, 0, SEEK_CUR);
        fprintf(dato, "\t%s\t%s\t%s", a.ime, a.prez, a.mejl);
        fclose(dato);
    }
    else
    {
        dato=fopen("korisnici.txt", "a");
        if(dato==NULL)
        {
            printf("Greska pri otvaranju datoteke!");
            exit(1);
        }
        printf("\nUnesite Vase podatke da bismo Vam napravili nalog:\n");
        printf("Ime i prezime: ");
        scanf("%s%s", &a.ime, &a.prez);
        printf("E-mail adresa: ");
        scanf("%s", &a.mejl);
        printf("LBO: ");
        scanf("%d", &a.lbo);
        fprintf(dato, "\n%d\t%s %s\t%s", a.lbo, a.ime, a.prez, a.mejl);
        fclose(dato);
    }
    strcpy(q,a.ime);
    strcpy(r,a.prez);
    printf("\nSpisak analiza koje su dostupne i njihove cene:\n");
    dato1=fopen("cenovnik.txt", "r");
    if(dato1==NULL)
    {
        printf("Greska pri otvaranju datoteke!");
        exit(1);
    }
    while(fgets(s, 30, dato1)!=NULL)
    {
        printf("%s", s);
        n++;
    }
    rewind(dato1);
    int d[n], t=0;
    /* d-niz rednih brojeva analiza koje se rade
    t-indeks*/
    while(1)
    {
        printf("\n\nKoliko analiza zelite da uradite: ");
        scanf("%d", &j);
        if(j>0 && j<=n) break;
        else printf("Pogresan unos!");
    }
    printf("\nUnesite redne brojeve analiza:\n");
    for(i=1;i<=j;i++)
    {
        while(1)
        {
            printf("- ");
            scanf("%d", &k);
            while(k<1 || k>n)
            {
                printf("Pogresan unos! Morate ponovo izvrsiti unos: ");
                scanf("%d", &k);
            }
            if(!t)
            {
                d[t]=k;
                t++;
                break;
            }
            else
            {
                while(1)
                {
                    for(t=0;t<i-1;t++) if(d[t]==k) break;
                    if(t<i-1)
                    {
                        printf("Ovaj unos vec postoji. Morate ponovo izvrsiti unos: ");
                        scanf("%d", &k);
                        if(k!=d[t]) break;
                    }
                    else break;
                }
                d[t]=k;
                break;
            }
        }
        Elem *novi=malloc(sizeof(Elem));
        if(novi==NULL)
        {
            printf("Nije moguce izvrsiti unos.");
            exit(2);
        }
        for(h=0;h<n;h++)
        {
            fscanf(dato1, "%d%s%d", &novi->rb, &novi->ia, &novi->cena);
            if(novi->rb==k)
            {
                rewind(dato1);
                break;
            }
        }
        novi->sled=novi->pret=NULL;
        c=c+novi->cena;
        if(!prvi) prvi=posl=tek=novi;
        else
        {
            novi->pret=tek;
            tek->sled=novi;
            tek=posl=novi;
        }
    }
    if(t+1>=10)
    {
        printf("Za izabranih 10 i vise analiza ostvarili ste 10 posto popusta!");
        c=c-c*0.1;
    }
    printf("\nVas radni list:\n");
    printf("---------------------------------------------------------------\n");
    printf("Datum: %d.%d.%d.\n", da, m, g);
    printf("Ime i prezime: %s %s\n", q, r);
    printf("\nSpisak analiza koje korisnik zeli da uradi:\n");
    ispisi(prvi, posl, tek);
    printf("\nUkupno za placanje: %.2f\n", c);
    printf("---------------------------------------------------------------\n");
    fclose(dato1);
    printf("Ukoliko zelite da Vam rezultate posaljemo na mejl ukucajte 'DA', u suprotnom 'NE': ");
    scanf("%s", &s);
    for(i=0;s[i];i++) s[i]=toupper(s[i]);
    if(!strcmp(s,"DA"))
    {
        printf("Rezultati ce biti poslati na mejl, a naplata mora biti sada obavljena.\nDa li je naplata obavljena (ako jeste ukucajte 'DA', u suprotnom 'NE')? ");
        scanf("%s", &s);
        for(i=0;s[i];i++) s[i]=toupper(s[i]);
        if(!strcmp(s,"DA")) printf("\nU redu! Mozete preci u susednu prostoriju za uzimanje uzorka.\n");
        else printf("Kako naplata nije obavljena, ne mozete preci u prostoriju za uzimanje uzorka!\n");
    }
    else printf("\nU redu! Mozete preci u susednu prostoriju za uzimanje uzorka.\n");
    return 0;
}
