#pragma once

#include "NetworkTopology.h"
#include <vector>
#include <map>
using namespace std;

struct KetQuaDijkstra {
    map<int, int> khoangCach;            // Node ID -> Chi phí ngắn nhất
    map<int, int> nodeLienTruoc;         // Node ID -> ID node phía trước (để truy vết)
    
    // Hàm hỗ trợ in đường đi từ nguồn đến đích cụ thể
    vector<int> layLoTrinh(int nutDich) const;
};

class DijkstraRouter {
public:
    // Chạy Dijkstra trên đồ thị topology, tự động bỏ qua các link hỏng
    static KetQuaDijkstra timDuongNganNhat(const NetworkTopology &mang, int idNguon);
};
