#ifndef STATE
#define STATE

#include <assert.h>
#include <iostream>
#include <vector>
#include "utility.hpp"
using std::swap;

#define rep(i, N) for(int i = 0; i < int(N); ++i)
const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

// state of game
class State {
  private:
    const static int H = 3;
    const static int W = 3;
    int pieceCount(const std::vector<int> &pieces) const {
        int count = 0;
        for(auto &p : pieces) {
            if(p == 1) {
                count += p;
            }
        }
        return count;
    }

  public:
    std::vector<int> pieces, enemy_pieces;
    State(std::vector<int> &_pieces, std::vector<int> &_enemy_pecies)
        : pieces(_pieces), enemy_pieces(_enemy_pecies) {}
    State() {
        pieces.assign(9, 0);
        enemy_pieces.assign(9, 0);
    }

    bool isLose() {
        rep(i, H) rep(j, W) {
            int idx = i * W + j;
            rep(k, 8) {
                int ni = ((i + dx[k]) + H) % H;
                int nj = ((j + dy[k]) + W) % W;
                if(not isIn(ni, nj))
                    continue;
                int nidx = ni * W + nj;
                int mi = ((i - dx[k]) + H) % H;
                int mj = ((j - dy[k]) + W) % W;
                if(not isIn(mi, mj))
                    continue;
                int midx = mi * W + mj;
                if(enemy_pieces[idx] && enemy_pieces[nidx] &&
                   enemy_pieces[midx]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isDraw() {
        return pieceCount(pieces) + pieceCount(enemy_pieces) == H * W;
    }

    bool isDone() { return isLose() || isDraw(); }

    bool isIn(int x, int y) { return 0 <= x && x < H && 0 <= y && y < W; }

    State next(int action) {
        std::vector<int> next_pieces = pieces;
        assert(pieces[action] == 0);
        pieces[action] = 1;
        return State(enemy_pieces, pieces);
    }

    std::vector<int> legalActions() const{
        std::vector<int> actions;
        rep(i, H * W) {
            if(pieces[i] == 0 && enemy_pieces[i] == 0) {
                actions.push_back(i);
            }
        }
        return actions;
    }

    bool isFirstPlayer() const {
        return pieceCount(pieces) == pieceCount(enemy_pieces);
    }

    friend std::ostream &operator<<(std::ostream &os, const State &a) {
        std::string ox = "ox";
        if(!a.isFirstPlayer()) {
            std::swap(ox[0], ox[1]);
        }
        std::string str;
        rep(i, H * W) {
            if(a.pieces[i] == 1) {
                str.push_back(ox[0]);
            } else if(a.enemy_pieces[i] == 1) {
                str.push_back(ox[1]);
            } else {
                str.push_back('-');
            }
            if(i % 3 == 2) {
                str.push_back('\n');
            }
        }
        os << str;
        return os;
    }
};

int randomAction(const State &state) {
    std::vector<int> legalActions = state.legalActions();
    return legalActions[utility::randint(legalActions.size())];
}

#endif