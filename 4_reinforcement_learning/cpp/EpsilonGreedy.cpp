
#include "lib/template.hpp"

#include "lib/EpsilonGreedy.cpp"
#include "lib/SlotArm.cpp"
#include "lib/UCB1.cpp"

pair<vector<int>, vector<float>> play(EpsilonGreedy &epsilonGreedy,
                                      vector<SlotArm> &arms, int numSims,
                                      int numTime) {
    vector<int> times(numSims * numTime, 0);
    vector<float> rewards(numSims * numTime, 0);

    for(int sim = 0; sim < numSims; sim++) {
        epsilonGreedy.initialize(arms.size());
        for(int time = 0; time < numTime; time++) {
            int idx = sim * numTime + time;

            times[idx] = time + 1;
            int chosenArm = epsilonGreedy.selectArm();
            float reward = arms[chosenArm].draw();
            rewards[idx] = reward;

            epsilonGreedy.update(chosenArm, reward, time + 1);
        }
    }
    return {times, rewards};
}

int main() {
    vector<SlotArm> arms = {SlotArm(0.1), SlotArm(0.2), SlotArm(0.3),
                            SlotArm(0.5), SlotArm(0.9)};
    EpsilonGreedy epsilonGreedy(0.1);
    auto [times, rewards] = play(epsilonGreedy, arms, 1000, 250);
    rep(j, 250) {
        float mean = 0;
        rep(i, 1000) { mean += rewards[i * 250 + j]; }
        mean /= 1000;
        cout << j + 1 << "," << mean << endl;
    }
}
