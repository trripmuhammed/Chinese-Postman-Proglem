#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>

using namespace std;
#define dugum_sayisi 6

class Graph {
public:
    bool is_euler = true;
    vector<vector<int>> ciftlesmis_tek_derece_matrisi;
    vector<int> tek_dereceli_ciftleri;
    int dugum_dereceleri[dugum_sayisi] = {2,3,3,3,3,2};
    int kenar_agirlik_matrisi[dugum_sayisi][dugum_sayisi] = {{0, 1, 2, 0, 0, 0},
                                                             {1, 0, 5, 3, 0, 0},
                                                             {2, 5, 0, 0, 4, 0},
                                                             {0, 3, 0, 0, 6, 1},
                                                             {0, 0, 4, 6, 0, 1},
                                                             {0, 0, 0, 1, 1, 0}};


    int kenar_matrisisi[dugum_sayisi][dugum_sayisi] = {{0, 1, 1, 0, 0, 0},
                                                       {1, 0, 1, 1, 0, 0},
                                                       {1, 1, 0, 0, 1, 0},
                                                       {0, 1, 0, 0, 1, 1},
                                                       {0, 0, 1, 1, 0, 1},
                                                       {0, 0, 0, 1, 1, 0}};


    void derece_doldur(){
        for(int i = 0; i <dugum_sayisi;i++){
            for(int j=0;j < dugum_sayisi;j++){
                if(kenar_agirlik_matrisi[i][j] != 0) dugum_dereceleri[i] += 1;
            }
        }
    }

    Graph();
    void kenar_agirlik_matrisini_olustur();
    void tek_derecelileri_bul();
    //void tek_derecelileri_ciftlestir();
    //void iki_boyutlu_vector_ata(const std::vector<std::vector<int>> &vector, int array[][dugum_sayisi]);

    void print_vector(vector<int> &vector){
        for (int i : vector) {
            cout << i << " ";
        }
    }

    //void tumCiftlesemeler(vector<int>&,vector<vector<int>>&,int, int);
};

Graph::Graph() {
    /*for (int i = 0; i < dugum_sayisi; i++) {
        for (int j = 0; j < dugum_sayisi; j++) {
            kenar_agirlik_matrisi[i][j] = 0;
        }
    }*/
}

void Graph::kenar_agirlik_matrisini_olustur() {
    std::cout << "Lutfen kenar sayisini giriniz" << std::endl;
    std::cout << "Lutfen sirasiyla kenarlarin agirliklarini giriniz" << std::endl;
    for (int i = 0; i < dugum_sayisi; i++) {
        for (int j = 0; j < dugum_sayisi; j++) {
            if (kenar_agirlik_matrisi[i][j] != 0) {
                dugum_dereceleri[i] += 1;
            }
        }
    }
}



void Graph ::tek_derecelileri_bul() {
    int counter = 0;
    for(int i =0; i <dugum_sayisi; i++){
        if(dugum_dereceleri[i]%2 == 1){
            tek_dereceli_ciftleri.push_back(i);
            counter++;
        }
    }
    tek_dereceli_ciftleri.resize(counter);
    if(tek_dereceli_ciftleri.size() > 2) {is_euler = false;}
}

void tumCiftlesemeler(vector<int>& dizi, vector<vector<int>>& tumCiftlesemelerVec ,int index = 0) {
    if (index == dizi.size() - 1) {
        if (dizi[0] == 1) {
            for (int eleman : dizi) {
                cout << eleman << " ";
            }
            cout << endl;

            tumCiftlesemelerVec.push_back(dizi);
        }
        return;
    }

    // Dizideki her bir eleman için tekrar et
    for (int i = index; i < dizi.size(); ++i) {
        // Swap işlemi yapmadan önce, aynı elemanın dizide başka bir yere gelmediğinden emin ol
        if (find(dizi.begin() + index, dizi.begin() + i, dizi[i]) == dizi.begin() + i) {
            swap(dizi[index], dizi[i]);
            tumCiftlesemeler(dizi, tumCiftlesemelerVec, index + 1);
            swap(dizi[index], dizi[i]);
        }
    }
}


int minDistance(const vector<int>& dist, const vector<bool>& es_control) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < dugum_sayisi; v++)
        if (es_control[v] == false && dist[v] <= min)
            min = dist[v],min_index = v;

    return min_index;
}

void path_add(const vector<int>& path, int j, vector<int>& temp_path) {
    if (path[j] == -1)
        return;

    path_add(path, path[j], temp_path);

    temp_path.push_back(j);
}

int dijkstra(int graph[dugum_sayisi][dugum_sayisi], int src, int dest,vector<int>& temp_path) {
    vector<int> dist(dugum_sayisi, INT_MAX);
    vector<bool> es_control(dugum_sayisi, false);
    vector<int> path(dugum_sayisi, -1);

    dist[src] = 0;

    for (int count = 0; count < dugum_sayisi - 1; count++) {
        int u = minDistance(dist, es_control);

        es_control[u] = true;

        for (int v = 0; v < dugum_sayisi; v++)
            if (!es_control[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
    }

    temp_path.push_back(src);
    path_add(path, dest, temp_path);
    return dist[dest];
}

int main() {

    Graph graph;
    vector<int> dizi;
    graph.tek_derecelileri_bul();

    for(int i =0; i < graph.tek_dereceli_ciftleri.size(); i++){
        dizi.push_back(graph.tek_dereceli_ciftleri[i]);
        cout << dizi[i] << endl;
    }

    dizi.resize(graph.tek_dereceli_ciftleri.size());

    vector<int> temp_path;
    tumCiftlesemeler(dizi, graph.ciftlesmis_tek_derece_matrisi);



    int size = graph.ciftlesmis_tek_derece_matrisi.size();
    int sutun_sayisi = graph.tek_dereceli_ciftleri.size();
    int min_result[size];

    for (int i = 0; i < size; i++) {
        int sonuc_toplam=0;
        for (int j = 0; j < sutun_sayisi; j= j+2) {
            sonuc_toplam += dijkstra(graph.kenar_agirlik_matrisi,graph.ciftlesmis_tek_derece_matrisi[i][j],graph.ciftlesmis_tek_derece_matrisi[i][j+1],temp_path);
        }
        min_result[i] = sonuc_toplam;
    }

    int min_yol = min_result[0];
    int min_index = 0;
    for (int i = 0; i < size; i++) {
        if (min_result[i] < min_yol) {
            min_yol = min_result[i];
            min_index = i;
        }
    }


    temp_path.clear();
    for(int i=0; i<graph.tek_dereceli_ciftleri.size(); i = i+2) {
        dijkstra(graph.kenar_agirlik_matrisi,graph.ciftlesmis_tek_derece_matrisi[min_index][i],graph.ciftlesmis_tek_derece_matrisi[min_index][i+1],temp_path);
        temp_path.push_back(-2);
    }
    cout << endl;

    for(int i=0; i<temp_path.size();i++){
        cout << temp_path[i] << " ";
    }
    cout << endl;

    for(int i=0; i<temp_path.size()-1;i++){
        if(temp_path[i] == -2){i++;}
        graph.kenar_matrisisi[temp_path[i]][temp_path[i+1]] +=1;
        graph.kenar_matrisisi[temp_path[i+1]][temp_path[i]] +=1;
    }
    cout << endl;
    cout << "Yeni Kenar Matrixi" << endl;
    for(int i=0;i<dugum_sayisi;i++){
        for(int j=0;j<dugum_sayisi;j++){
            cout << graph.kenar_matrisisi[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Kenar Agirlik Matrixi" << endl;
    for(int i=0;i<dugum_sayisi;i++){
        for(int j=0;j<dugum_sayisi;j++){
            cout << graph.kenar_agirlik_matrisi[i][j] << " ";
        }
        cout << endl;
    }


    cout << "eklenmesi gereken siranin indexi: " << min_index << endl;
    cout << "min eklenmesi gereken kenar agirliklari toplami: " << min_yol << endl;

    return 0;
}
