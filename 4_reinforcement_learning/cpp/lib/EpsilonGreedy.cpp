#ifndef EPSILON_GREEDY
#define EPSILON_GREEDY
#include "template.hpp"
#include "utility.hpp"
#include <vector>

class EpsilonGreedy {
  public:
    float epsilon;
    std::vector<int> n;
    std::vector<float> v;
    EpsilonGreedy(float _epsilon) : epsilon(_epsilon) {}

    void initialize(int sz) {
        n.assign(sz, 0);
        v.assign(sz, 0);
    }

    int selectArm() {
        if(epsilon > utility::rand()) {
            return utility::randint(n.size());
        } else {
            int maxIdx = 0;
            float maxx = -1;
            rep(i, n.size()) {
                if(chmax(maxx, v[i])) {
                    maxIdx = i;
                }
            }
            return maxIdx;
        }
    }

    void update(int armIdx, int reward, int t) {
        n[armIdx]++;
        v[armIdx] = ((n[armIdx] - 1) / float(n[armIdx])) * v[armIdx] +
                    (1 / float(n[armIdx])) * reward;
    }
};
#endif