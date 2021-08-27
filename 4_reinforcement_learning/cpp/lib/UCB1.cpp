#ifndef UCB_1
#define UCB_1
#include "template.hpp"
#include "utility.hpp"
#include <vector>

class UCB1 {
  public:
    std::vector<int> n, w, v;
    UCB1() {}

    void initialize(int sz) {
        n.assign(sz, 0);
        w.assign(sz, 0);
        v.assign(sz, 0);
    }

    int selectArm() {
        rep(i,n.size()){
            if(n[i] == 0){
                return i;
            }
        }
        int maxIdx = 0;
        int maxx = -1;
        rep(i, n.size()) {
            if(chmax(maxx, n[i])) {
                maxIdx = i;
            }
        }
        return maxIdx;
    }

    void update(int armIdx, int reward, int t) {
        n[armIdx]++;
        if(reward == 1){
            w[armIdx] += 1;
        }
        rep(i,n.size()){
            if(n[i] == 0){
                return;
            }
        }
        rep(i,n.size()){
            v[i] = w[i] / float(n[i]) + sqrt(2 * log(t) / float(n[i]));
        }
    }
};
#endif