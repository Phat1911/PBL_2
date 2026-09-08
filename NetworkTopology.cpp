#include <iostream>
#include "NetworkTopology.h"
using namespace std;

void NetworkTopology::themNode(int id, const string &ten) {
    tenNode[id] = ten;
    if (danhSachKe.find(id) == danhSachKe.end()) {
        danhSachKe[id] = vector<LienKet>();
    }
}

void NetworkTopology::themLienKet(int a, int b, int chiPhi) {
    danhSachKe[a].push_back({b, chiPhi, true});
    danhSachKe[b].push_back({a, chiPhi, true});
}

void NetworkTopology::baoLoiNode(int id) {
    // 1. Vô hiệu hóa tất cả các liên kết XUẤT PHÁT TỪ id
    if (danhSachKe.find(id) != danhSachKe.end()) {
        for (auto &lk : danhSachKe[id]) {
            lk.dangHoatDong = false;
        }
    }
    // 2. Vô hiệu hóa tất cả các liên kết TRỎ ĐẾN id
    for (auto &cap : danhSachKe) {
        for (auto &lk : cap.second) {
            if (lk.denNode == id) {
                lk.dangHoatDong = false;
            }
        }
    }
}

void NetworkTopology::khoiPhucNode(int id) {
    if (danhSachKe.find(id) != danhSachKe.end()) {
        for (auto &lk : danhSachKe[id]) {
            lk.dangHoatDong = true;
        }
    }
    for (auto &cap : danhSachKe) {
        for (auto &lk : cap.second) {
            if (lk.denNode == id) {
                lk.dangHoatDong = true;
            }
        }
    }
}

string NetworkTopology::getTenNode(int id) const {
    auto it = tenNode.find(id);
    if (it != tenNode.end()) return it->second;
    return "Unknown Node";
}

const map<int, string>& NetworkTopology::getAllNodes() const {
    return tenNode;
}

vector<LienKet> NetworkTopology::layHangXomHoatDong(int id) const {
    vector<LienKet> ketQua;
    auto it = danhSachKe.find(id);
    if (it != danhSachKe.end()) {
        for (const auto &lk : it->second) {
            if (lk.dangHoatDong) {
                ketQua.push_back(lk);
            }
        }
    }
    return ketQua;
}

void NetworkTopology::inTopology() const {
    for (const auto &cap : danhSachKe) {
        cout << getTenNode(cap.first) << " (ID " << cap.first << ") noi voi:\n";
        for (const auto &lk : cap.second) {
            cout << "  -> " << getTenNode(lk.denNode) 
                      << " [Chi phi: " << lk.chiPhi << "] "
                      << (lk.dangHoatDong ? "[Online]" : "[OFFLINE/BROKEN]") << "\n";
        }
    }
}
