#include <iostream>
#include <climits>
#include "NetworkTopology.h"
#include "DijkstraRouter.h"
using namespace std;

void inKetQuaDinhTuyen(const NetworkTopology &mang, int idNguon, const KetQuaDijkstra &kq) {
    cout <<"\n=== KET QUA DINH TUYEN TU ";
    cout <<mang.getTenNode(idNguon);
    cout <<" ===\n";
    for (const auto &node : mang.getAllNodes()) {
        int dich = node.first;
        if (dich == idNguon) continue;

        cout <<"Toi ";
        cout <<mang.getTenNode(dich);
        cout <<":";
        if (kq.khoangCach.at(dich) == INT_MAX) {
            cout <<"[KHONG THE KET NOI]\n";
        } else {
            cout <<"Chi phi =";
            cout <<kq.khoangCach.at(dich);
            cout <<" | Lo trinh: ";
            vector<int> path = kq.layLoTrinh(dich);
            for(size_t i=0;i<path.size();i++){
                cout <<mang.getTenNode(path[i]);
                if (i + 1 < path.size()) cout <<" -> ";
            }
            cout <<"\n";
        }
    }
}

int main() {
    NetworkTopology mang;
    
    // 1. Khoi tao cac Router / Thiet bi
    mang.themNode(1,"RouterA");
    mang.themNode(2,"RouterB");
    mang.themNode(3,"RouterC");
    mang.themNode(4,"ClientD");

    // 2. Thiet lap lien ket & trong so
    mang.themLienKet(1,2,2);
    mang.themLienKet(1,3,5);
    mang.themLienKet(2,3,1);
    mang.themLienKet(3,4,4);

    cout << "-------------------------------------------\n";
    cout << "TRANG THAI MANG BAN DAU:\n";
    mang.inTopology();

    // Chay thuat toan tu RouterA (ID = 1)
    KetQuaDijkstra kqBanDau = DijkstraRouter::timDuongNganNhat(mang, 1);
    inKetQuaDinhTuyen(mang,1,kqBanDau);

    // 3. Mo phong su co: RouterB gap truc trac bi ngat ket noi
    cout << "\n-------------------------------------------\n";
    cout << ">>> CANH BAO: RouterB gap su co mang! Bat dau bao loi...\n";
    mang.baoLoiNode(2);
    
    cout << "\nTRANG THAI MANG SAU SU CO:\n";
    mang.inTopology();

    // Tinh toan lai tuyen duong moi khi khong con RouterB
    KetQuaDijkstra kqSauSuCo=DijkstraRouter::timDuongNganNhat(mang, 1);
    inKetQuaDinhTuyen(mang,1,kqSauSuCo);

    return 0;
}
