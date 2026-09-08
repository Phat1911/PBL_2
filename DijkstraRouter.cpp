#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
#include "DijkstraRouter.h"
using namespace std;

vector<int> KetQuaDijkstra::layLoTrinh(int nutDich) const {
    vector<int> loTrinh;
    int curr = nutDich;
    while (curr != -1) {
        loTrinh.push_back(curr);
        auto it = nodeLienTruoc.find(curr);
        if (it != nodeLienTruoc.end()) {
            curr = it->second;
        } else {
            break;
        }
    }
    reverse(loTrinh.begin(), loTrinh.end());
    return loTrinh;
}

KetQuaDijkstra DijkstraRouter::timDuongNganNhat(const NetworkTopology &mang, int idNguon) {
    KetQuaDijkstra kq;
    const auto &allNodes = mang.getAllNodes();

    // Khởi tạo khoảng cách vô cùng và node liền trước là -1
    for (const auto &node : allNodes) {
        kq.khoangCach[node.first] = INT_MAX;
        kq.nodeLienTruoc[node.first] = -1;
    }

    if (kq.khoangCach.find(idNguon) == kq.khoangCach.end()) {
        return kq; // Node nguồn không tồn tại trong mạng
    }

    kq.khoangCach[idNguon] = 0;

    // Min-Priority Queue: lưu trữ pair<chiPhi, nodeId>
    using Element = pair<int, int>;
    priority_queue<Element, vector<Element>, greater<Element>> hangDoi;
    hangDoi.push({0, idNguon});

    while (!hangDoi.empty()) {
        int chiPhiHienTai = hangDoi.top().first;
        int u = hangDoi.top().second;
        hangDoi.pop();

        if (chiPhiHienTai > kq.khoangCach[u]) {
            continue;
        }

        // Chỉ duyệt qua các neighbor còn HOẠT ĐỘNG
        for (const auto &canh : mang.layHangXomHoatDong(u)) {
            int v = canh.denNode;
            int chiPhiMoi = chiPhiHienTai + canh.chiPhi;

            if (chiPhiMoi < kq.khoangCach[v]) {
                kq.khoangCach[v] = chiPhiMoi;
                kq.nodeLienTruoc[v] = u;
                hangDoi.push({chiPhiMoi, v});
            }
        }
    }

    return kq;
}
