#include <iostream>
#include <vector>

#define dugum_sayisi 6
#define INF INT_MAX

class Graph {
public:
    int ciftlesmis_tek_derece_matrisi[dugum_sayisi][2];
    int dugum_dereceleri[dugum_sayisi];
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
    std::vector<int> path;

    Graph();
    void kenar_agirlik_matrisini_olustur();
    std::vector<int> tek_derecelileri_bul();
    void tek_derecelileri_ciftlestir();
    int kabaKuvvetToplamYol(Graph &graf, int baslangic, int hedef);
    void iki_boyutlu_vector_ata(const std::vector<std::vector<int>> &vector, int array[][dugum_sayisi]);
    int ciftlesme_icin_en_kisa_yolu_bul(int src, int target);
};

Graph::Graph() {
    // 'path' vektörünü boyutlandır
    path.resize(dugum_sayisi, 0);
}

void Graph::kenar_agirlik_matrisini_olustur() {
    std::cout << "Lutfen kenar sayisini giriniz" << std::endl;
    std::cout << "Lutfen sirasiyla kenarlarin agirliklarini giriniz" << std::endl;
    for (int i = 0; i < dugum_sayisi; i++) {
        for (int j = 0; j < dugum_sayisi; j++) {
            // std::cin >> kenar_agirlik_matrisi[i][j];
            if (kenar_agirlik_matrisi[i][j] != 0) {
                dugum_dereceleri[i] += 1;
            }
        }
    }
}

std::vector<int> Graph ::tek_derecelileri_bul() {
    std::vector<int> tek_dereceli_ciftleri;
    for(int i =0; i <dugum_sayisi; i++){
        if(dugum_dereceleri[i]%2 == 1){
            tek_dereceli_ciftleri[i] = i;
        }
    }
    return tek_dereceli_ciftleri;
}
/*
void Graph::tek_derecelileri_ciftlestir() {
    std::vector<int> tek_dereceli_ciftleri = tek_derecelileri_bul();
    for (int i = 0; i < tek_dereceli_ciftleri.size(); i++) {
        bool eslesti_mi[tek_dereceli_ciftleri.size()];
        int k = i, j = 0;  //   0,1,2,3,4,5,6,7
        for (int z = 0; z < tek_dereceli_ciftleri.size() / 2; z += 2) {
            while (!(eslesti_mi[j] && eslesti_mi[k + 1])) {
                eslesti_mi[j] ? : k++ , j++; j == k + 1 ? : k++ , k = k;
            }
            ciftlesmis_tek_derece_matrisi[i][0] = tek_dereceli_ciftleri[j];
            ciftlesmis_tek_derece_matrisi[i][1] = tek_dereceli_ciftleri[k + 1];
            eslesti_mi[j] = true;
            eslesti_mi[k + 1] = true;
            k += 2;
            j += 2;
        }
    }
}

int Graph::kabaKuvvetToplamYol(Graph &graf, int baslangic, int hedef) {
    if (baslangic == hedef) {
        return 1;
    }

    int result = 0;
    for (int i = 0; i < dugum_sayisi; ++i) {
        if (graf.kenar_agirlik_matrisi[baslangic][i] != 0) {
            result += kabaKuvvetToplamYol(graf, i, hedef);
        }
    }
    return result;
}

void Graph::iki_boyutlu_vector_ata(const std::vector<std::vector<int>> &vector, int array[][dugum_sayisi]) {
    for (int i = 0; i < dugum_sayisi; i++) {
        for (int j = 0; j < dugum_sayisi; j++) {
            array[i][j] = vector[i][j];
        }
    }
}

int Graph::ciftlesme_icin_en_kisa_yolu_bul(int src, int target) {
    if (target == src) {
        return 1;
    }

    int result = 0;
    for (int i = 0; i < dugum_sayisi; i++) {
        if (kenar_agirlik_matrisi[src][i] != 0) {
            result += ciftlesme_icin_en_kisa_yolu_bul(i, target);
            path.push_back(i);
        }
    }
    return result;
}

int main() {
    Graph obj;
    obj.kenar_agirlik_matrisini_olustur();
    obj.tek_derecelileri_ciftlestir();

    // Vektörleri dizilere dönüştür
    int ciftlesmis_tek_derece_matrisi[dugum_sayisi][2];
    int dugum_dereceleri[dugum_sayisi];
    int path[dugum_sayisi];

    // 'ciftlesmis_tek_derece_matrisi' vektörünü diziye dönüştür
    for (int i = 0; i < dugum_sayisi; i++) {
        ciftlesmis_tek_derece_matrisi[i][0] = obj.ciftlesmis_tek_derece_matrisi[i][0];
        ciftlesmis_tek_derece_matrisi[i][1] = obj.ciftlesmis_tek_derece_matrisi[i][1];
    }

    // 'dugum_dereceleri' vektörünü diziye dönüştür
    for (int i = 0; i < dugum_sayisi; i++) {
        dugum_dereceleri[i] = obj.dugum_dereceleri[i];
    }

    // 'path' vektörünü diziye dönüştür
    for (int i = 0; i < dugum_sayisi; i++) {
        path[i] = obj.path[i];
    }

    return 0;
}

/*
 #include <iostream>
#include <vector>

#define dugum_sayisi 6
#define INF INT_MAX

class Graph{

public:
    std::vector<std::vector<int>> ciftlesmis_tek_derece_matrisi;
    int *dugum_dereceleri;
    int kenar_agirlik_matrisi[dugum_sayisi][dugum_sayisi]={{0,1,2,0,0,0},{1,0,5,3,0,0},{2,5,0,0,4,0},{0,3,0,0,6,1},{0,0,4,6,0,1},{0,0,0,1,1,0}};
    std::vector<std::vector<int>> kenar_matrisisi={{0,1,1,0,0,0},{1,0,1,1,0,0},{1,1,0,0,1,0},{0,1,0,0,1,1},{0,0,1,1,0,1},{0,0,0,1,1,0}};
    std::vector<int> path;
    Graph();
    void kenar_agirlik_matrisini_olustur();
    std::vector<int> tek_derecelileri_bul();
    void tek_derecelileri_ciftlestir();
    void ciftlesme_icin_en_kisa_yolu_bul();
    void graf_icin_en_kisa_yolu_bul();
    int faktoriyeli_bul(int);

    int kabaKuvvetToplamYol(Graph &graf, int baslangic, int hedef);

    std::vector<int> kimlerle_komsu(int index);

    void iki_boyutlu_vector_ata(std::vector<std::vector<int>> vector, std::vector<std::vector<int>> temp);

    int ciftlesme_icin_en_kisa_yolu_bul(int src, int target);
};

Graph::Graph(){;
    dugum_dereceleri = new int[dugum_sayisi];
    for(int i = 0; i <dugum_sayisi; i++){
        //dugum_dereceleri[i] = 0;
        path[i] = 0;
        for(int j = 0; j <dugum_sayisi; j++){
            kenar_agirlik_matrisi[i][j] = 0;
        }
    }
}

void Graph::kenar_agirlik_matrisini_olustur() {
    std::cout << "Lutfen kenar sayisini giriniz" << std::endl;
    std::cout << "Lutfen sirasiyla kenarlarin agirliklarini giriniz" << std::endl;
    for(int i = 0; i <dugum_sayisi; i++){
        for(int j = 0; j <dugum_sayisi; j++) {
            //std::cin >> kenar_agirlik_matrisi[i][j];
            if (kenar_agirlik_matrisi[i][j] != 0) {
                dugum_dereceleri[i] += 1;
            }
        }
    }
}

std::vector<int> Graph ::tek_derecelileri_bul() {
    std::vector<int> tek_dereceli_ciftleri;
    for(int i =0; i <dugum_sayisi; i++){
        if(dugum_dereceleri[i]%2 == 1){
            tek_dereceli_ciftleri[i] = i;
        }
    }
    return tek_dereceli_ciftleri;
}

int Graph ::faktoriyeli_bul(int x) {
    int faktoriyel=1;
    for(int i=1; i<=x; i++) {
        faktoriyel *= i;
    }
    return faktoriyel;
}

int min(int x, int y) {
    return (x < y) ? x : y;
}
/*
int kaba_kuvvet(Graph& graph,int source,int target){
    if (source == target) {
        return 1;
    }

    int result = 0;
    for (int i = 0; i < dugum_sayisi; ++i) {
        if (graph.kenar_agirlik_matrisi[source][i] != 0) {
            result += kaba_kuvvet(graph, i, target);
        }
    }
    return result;

}*/



/*
int kabaKuvvetToplamYol(Graph& graf, int baslangic, int hedef) {
    // Hedefe ulaşıldığında ve bu bir geçerli yol olduğunda 1'i döndür
    if (baslangic == hedef) {
        return 1;
    }

    int toplamYol = 0;

    // Tüm olası yolları gez
    for (int i = 0; i < dugum_sayisi; ++i) {
        // Geçerli kenar var mı ve döngüyü önlemek için zaten geçilen bir dugum değil mi?
        if (graf.kenar_agirlik_matrisi[baslangic][i] != 0 && i != baslangic) {
            // Geçerli yolu takip et ve toplam yolu arttır
                toplamYol += kabaKuvvetToplamYol(graf, i, hedef);
                graf.path[i] = i;
        }
    }

    return toplamYol;
}//

std::vector<int> Graph :: kimlerle_komsu(int index) {
    std::vector<int> index_list;
    for(int i = 0; i <dugum_sayisi; i++){
        if(kenar_agirlik_matrisi[index][i] != 0){
            index_list.push_back(i);
        }
    }
    return index_list;
}

void Graph :: iki_boyutlu_vector_ata(std::vector<std::vector<int>> vector,std::vector<std::vector<int>> temp){
    for(int i =0; i <vector.size(); i++){
        for(int j =0; j <vector[i].size(); j++){
            temp[i][j] = vector[i][j];
        }
    }
}

int Graph ::ciftlesme_icin_en_kisa_yolu_bul(int src,int target) {
    if(target == src){
        return 1;
    }

    int result = 0;

    for(int i =0; i <dugum_sayisi; i++){
        if(kenar_agirlik_matrisi[src][i] != 0){
            result += ciftlesme_icin_en_kisa_yolu_bul(i, target);
            path.push_back(i);
        }
    }
    return result;
}


void Graph ::tek_derecelileri_ciftlestir() {
    std::vector<int> tek_dereceli_ciftleri = tek_derecelileri_bul();
    for(int i =0; i <tek_dereceli_ciftleri.size(); i++){
        bool eslesti_mi[tek_dereceli_ciftleri.size()];
        int k =i,j=0;  //   0,1,2,3,4,5,6,7
        for(int z =0; z <tek_dereceli_ciftleri.size()/2; z+=2){
            while(!(eslesti_mi[j] && eslesti_mi[k + 1])){ eslesti_mi[j] ? : k++ , j++; j==k+1 ? : k++ , k=k; }
            ciftlesmis_tek_derece_matrisi[i][0] = tek_dereceli_ciftleri[j];
            ciftlesmis_tek_derece_matrisi[i][1] = tek_dereceli_ciftleri[k + 1];
            eslesti_mi[j] = true;
            eslesti_mi[k+1] = true;
            k+=2;
            j+=2;
        }

    }
}







int main(){

    Graph obj;
    obj.kenar_agirlik_matrisini_olustur();
    obj.tek_derecelileri_ciftlestir();
    for(int i=0; i<obj.ciftlesmis_tek_derece_matrisi.size(); i++) {
        std::cout << obj.ciftlesmis_tek_derece_matrisi[i][0] << " " << obj.ciftlesmis_tek_derece_matrisi[i][1] << std::endl;
    }

}
 */