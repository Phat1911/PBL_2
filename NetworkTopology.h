#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

// Đại diện cho 1 liên kết giữa 2 router
struct LienKet {
    int denNode;
    int chiPhi;
    bool dangHoatDong;
};

class NetworkTopology {
private:
    map<int, string> tenNode;
    map<int, vector<LienKet>> danhSachKe;

public:
    NetworkTopology() = default;

    void themNode(int id, const string &ten);
    void themLienKet(int a, int b, int chiPhi);
    
    // Đánh dấu router bị lỗi: vô hiệu hóa toàn bộ liên kết đến và đi từ node đó
    void baoLoiNode(int id);
    // Khôi phục lại router hoạt động
    void khoiPhucNode(int id);
    string getTenNode(int id) const;
    const map<int, string>& getAllNodes() const;
    vector<LienKet> layHangXomHoatDong(int id) const;
    void inTopology() const;
};
