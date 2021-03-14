#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <chrono>
using namespace std;
bool OK;
long N, Max,T;
void generare_numere_random(long vector_size, long max_value, long V[]){
    srand(time(NULL));
    for(long i=0;i<vector_size;i++){
        V[i]=1+rand()%max_value;
    }
}
void generare_vector_constant(long vector_size, long max_value, long V[]){
    srand(time(NULL));
    long x=1+rand()%max_value;
    for(long i=0;i<vector_size;i++){
        V[i]=x;
    }
}
void citire_din_fisier(long vector_size, long max_value, long V[])
{
    char nume_fisier[50];
    cout<<"Introdu numele fisierului de intrare"<<'\n';
    cout<<"PS: In fisier trebuie scrise doar numerele pe care vrem sa le sortam, toate mai mici decat valoarea maxima introdusa!"<<'\n';
    cout<<"Daca in fisier sunt mai multe numere decat numarul de numere introdus se vor lua in considerare doar primele N numere!"<<'\n';
    cout<<"Daca in fisier sunt mai putine numere decat numarul de numere introduse restul de numere vor fi generate random!"<<'\n';
    cin>>nume_fisier;
    ifstream citeste_din_fisier;
    citeste_din_fisier.open(nume_fisier);
    cout<<"am primit "<<vector_size<<" numere si toate sunt sigur mai mici decat "<<max_value<<'\n';
    for(long i=0;i<vector_size;i++){
        citeste_din_fisier>>V[i];
    }
}
void duplicare_vector(long vector_size, long max_value, long V[], long V2[]){
    for(long i=0;i<vector_size;i++){
        V2[i]=V[i];
    }
}
void afisare_vector(long vector_size, long V[]){
    for(long i=0;i<vector_size;i++){
        cout<<V[i]<<" ";
    }
    cout<<'\n';
}
void bubble_sort(long vector_size, long V[]){
    for(long i=0;i<vector_size-1;i++){
        for(long j=i+1;j<vector_size;j++){
            if(V[i]>V[j]){
                swap(V[i],V[j]);
            }
        }
    }

}
void counting_sort(long vector_size, long max_value, long V[]){
    long *Frecv = new long[max_value+1];
    for(long i=0;i<=max_value;i++){
        Frecv[i]=0;
    }
    long Max=0;
    for(long i=0;i<vector_size;i++){
        Frecv[V[i]]++;
        if(V[i]>Max){
            Max=V[i];
        }
    }
    long I=0;
    for(long i=0;i<=Max;i++){
        while(Frecv[i]>0){
            V[I]=i;
            I++;
            Frecv[i]--;
        }
    }
    delete[] Frecv;
}
void quick_sort(long st, long dr, long V[])
{
    if(st<dr){
        long pivot=(st+dr)/2;
        swap(V[pivot], V[st]);
        long i=st, j=dr;
        bool D_sau_S=0;
        while(i<j){
            if(V[i]>V[j]){
                swap(V[i], V[j]);
                D_sau_S = !D_sau_S;
            }
            if(D_sau_S == 0){
                j--;
            }
            else
            i++;
        }
        quick_sort(st, i-1, V);
        quick_sort(i+1, dr, V);
    }
}
void merge_sort(long st, long dr, long V[], long vector_temporar[])
{
    if(st<dr){
        long m=(st+dr)/2;
        merge_sort(st, m, V, vector_temporar);
        merge_sort(m+1, dr, V, vector_temporar);
        long i=st, j=m+1, k=0;
        while(i<=m && j<=dr){
            if(V[i]<V[j]){
                vector_temporar[k]=V[i];
                i++;
                k++;
            }
            else{
                vector_temporar[k]=V[j];
                j++;
                k++;
            }
        }
        while(i<=m){
            vector_temporar[k]=V[i];
            i++;
            k++;
        }
        while(j<=dr){
            vector_temporar[k]=V[j];
            j++;
            k++;
        }
        long I=st;
        long K=0;
        while(I<=dr){
            V[I]=vector_temporar[K];
            I++;
            K++;
        }
    }
}
void counting_sort_pt_radix(long vector_size, long V[], long putere10)
{
    long ap_cif[10];
    long *vector_temporar = new long[N];
    for(long i=0;i<10;i++){
        ap_cif[i]=0;
    }
    for(long i=0;i<vector_size;i++){
        ap_cif[(V[i]/putere10)%10]++;
    }
    for(long i=1;i<10;i++){
        ap_cif[i] = ap_cif[i]+ap_cif[i-1];
    }
    for(long i=vector_size-1;i>=0;i--){
        vector_temporar[ap_cif[V[i]/putere10%10]-1] = V[i];
        ap_cif[V[i]/putere10%10]--;
    }
    for(long i=0;i<vector_size;i++){
        V[i]=vector_temporar[i];
    }
    delete[] vector_temporar;
}
void radix_sort(long vector_size, long V[])
{
    long Max=V[0];
    for(long i=1;i<vector_size;i++){
        if(V[i]>Max){
            Max=V[i];
        }
    }
    for(long putere10=1;putere10<=Max;putere10=putere10*10){
        counting_sort_pt_radix(vector_size,V,putere10);
    }
}
bool comparare_vectori(long vector_size, long V1[], long V2[]){
    for(long i=0;i<vector_size;i++){
        if(V1[i]!=V2[i]){
            return 0;
        }
    }
    return 1;
}
int main ()
{
    cout<<"Introdu cate secvente de numere vrei sa sortezi"<<'\n';
    cin>>T;
    for(int indice=0; indice<T; indice++){
        cout<<"Vrei numere random??"<<'\n'<<"Apasa 1"<<'\n';
        cout<<"Vrei sa introduci numere din fisier??"<<'\n'<<"Apasa 2"<<'\n';
        cout<<"Vrei vector constant?"<<'\n'<<"Apasa 3"<<'\n';
        cout<<"Vrei vector crescator?"<<'\n'<<"Apasa 4"<<'\n';
        cout<<"Vrei vector descrescator?"<<'\n'<<"Apasa 5"<<'\n';
        cout<<"Vrei vector aproape crescator?"<<'\n'<<"Apasa 6"<<'\n';
        int OPTIUNE;
        cin>>OPTIUNE;
        cout<<"Cate numere vrei?"<<'\n';
        cin>>N;
        cout<<"Care e valoarea maxima pe care o pot da?"<<'\n';
        cin>>Max;
        long *Vector = new long[N];
        long *VectorSortatCorect = new long[N];
        if(OPTIUNE == 1){
            generare_numere_random(N, Max, Vector);
        }
        else
        if(OPTIUNE == 2){
            citire_din_fisier(N, Max, Vector);
        }
        else
        if(OPTIUNE == 3){
            generare_vector_constant(N, Max, Vector);
        }
        else
        if(OPTIUNE == 4){
            generare_numere_random(N, Max, Vector);
            sort(Vector, Vector+N);
        }
        else
        if(OPTIUNE == 5){
            generare_numere_random(N, Max, Vector);
            sort(Vector, Vector+N, greater<long>());
        }
        else
        if(OPTIUNE == 6){
            generare_numere_random(N, Max, Vector);
            sort(Vector, Vector+N/2);
        }
        else{
            cout<<"Nu am optiunea asta"<<'\n';
            continue;
        }
        long *Vector_de_Sortat = new long[N];
        cout<<"SORTARE NATIVA"<<'\n';
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);

        auto  start1 = std::chrono::steady_clock::now();
        sort(Vector_de_Sortat, Vector_de_Sortat+N);
        auto stop1= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff1 = stop1 - start1;
        cout<<diff1.count()<<" secunde"<<'\n';
        duplicare_vector(N, Max, Vector_de_Sortat, VectorSortatCorect);
        cout<<'\n';

        cout<<"BUBBLE SORT"<<'\n';
        if(N>10000){
            cout<<"Dureaza prea mult sa sorteze"<<'\n'<<'\n';
        }
        else{
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);

        auto  start2 = std::chrono::steady_clock::now();
        bubble_sort(N, Vector_de_Sortat);
        auto stop2= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff2 = stop2 - start2;
        cout<<diff2.count()<<" secunde"<<'\n';
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1){
            cout<<"CORECT!!!!!"<<'\n';
        }
        else
        cout<<"GRESIT!!!!!"<<'\n';
        cout<<'\n';
        }

        cout<<"COUNTING SORT"<<'\n';
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);

        auto  start3 = std::chrono::steady_clock::now();
        counting_sort(N, Max, Vector_de_Sortat);
        auto stop3= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff3 = stop3 - start3;
        cout<<diff3.count()<<" secunde"<<'\n';
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1){
            cout<<"CORECT!!!!!"<<'\n';
        }
        else
        cout<<"GRESIT!!!!!"<<'\n';
        cout<<'\n';

        cout<<"QUICK SORT"<<'\n';
        if((N >= 1000000 && (OPTIUNE == 3)) || N>1000000){
            cout<<"Dureaza prea mult sa sorteze"<<'\n'<<'\n';
        }
        else{
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);

        auto  start4 = std::chrono::steady_clock::now();
        quick_sort(0,N-1,Vector_de_Sortat);
        auto stop4= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff4 = stop4 - start4;
        cout<<diff4.count()<<" secunde"<<'\n';
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1){
            cout<<"CORECT!!!!!"<<'\n';
        }
        else
        cout<<"GRESIT!!!!!"<<'\n';
        cout<<'\n';
        }

        cout<<"MERGE SORT"<<'\n';
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);
        long *VectorTemporar = new long[N];

        auto  start5 = std::chrono::steady_clock::now();
        merge_sort(0,N-1,Vector_de_Sortat,VectorTemporar);
        auto stop5= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff5 = stop5 - start5;
        cout<<diff5.count()<<" secunde"<<'\n';
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1){
            cout<<"CORECT!!!!!"<<'\n';
        }
        else
        cout<<"GRESIT!!!!!"<<'\n';
        cout<<'\n';

        delete[] VectorTemporar;
        cout<<"RADIX SORT"<<'\n';
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);

        auto  start6 = std::chrono::steady_clock::now();
        radix_sort(N,Vector_de_Sortat);
        auto stop6= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff6 = stop6 - start6;
        cout<<diff6.count()<<" secunde"<<'\n';
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1){
            cout<<"CORECT!!!!!"<<'\n';
        }
        else
        cout<<"GRESIT!!!!!"<<'\n';
        cout<<'\n';

        if(indice==T-1){
            cout<<"GATA TOT!!"<<'\n';
            cout<<"BYE BYE!! :)";
        }
        else
        cout<<"URMATORUL!!"<<'\n';

        delete[] Vector;
        delete[] Vector_de_Sortat;
    }
    return 0;
}
