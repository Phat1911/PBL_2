#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
 
struct LienKet {
    int denNode;
    int chiPhi;
    bool dangHoatDong;
};
 
class NetworkTopology{
private:
    map<int, string> tenNode;
    map<int, vector<LienKet>> danhSachKe;
 
public:
    void themNode(int id, string ten) {
        tenNode[id] = ten;
        danhSachKe[id] = vector<LienKet>();
    }
 
    void themLienKet(int a, int b, int chiPhi) {
        danhSachKe[a].push_back({b, chiPhi, true});
        danhSachKe[b].push_back({a, chiPhi, true});
    }
 
    void baoLoi(int id) {
        for (auto &cap : danhSachKe) {
            for (auto &lk : cap.second) {
                if (lk.denNode == id) {
                    lk.dangHoatDong = false;
                }
            }
        }
    }
 
    vector<LienKet> layHangXom(int id) {
        vector<LienKet> ketQua;
        for (auto &lk : danhSachKe[id]) {
            if (lk.dangHoatDong) {
                ketQua.push_back(lk);
            }
        }
        return ketQua;
    }
 
    void inTopology() {
        for (auto &cap : danhSachKe) {
            cout << tenNode[cap.first] << " noi voi: ";
            for (auto &lk : cap.second) {
                if (lk.dangHoatDong) {
                    cout << tenNode[lk.denNode] << "(chi phi " << lk.chiPhi << ") ";
                }
            }
            cout << endl;
        }
    }
};
 
int main() {
    NetworkTopology mang;
    mang.themNode(1, "RouterA");
    mang.themNode(2, "RouterB");
    mang.themNode(3, "RouterC");
    mang.themNode(4, "ClientD");
    mang.themLienKet(1, 2, 2);
    mang.themLienKet(1, 3, 5);
    mang.themLienKet(2, 3, 1);
    mang.themLienKet(3, 4, 4);
    cout << "Topology ban dau:" << endl;
    mang.inTopology();
    cout << endl << "RouterB gap su co, danh dau mat ket noi..." << endl;
    mang.baoLoi(2);
    cout << endl << "Topology sau khi RouterB loi:" << endl;
    mang.inTopology();
    return 0;
}
