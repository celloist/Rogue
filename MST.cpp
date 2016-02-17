//
// Created by Mark Jan Kamminga on 06-02-16.
//

#include "Mst.h"

int Mst::find(Room* t) {
    if (typeLevels.find(t) != typeLevels.end()) {
        return typeLevels[t];
    }

    return -1;
}

void Mst::addEdge(Room *from, Room *to, int distance) {
    pq.push_back(make_pair(distance, make_pair(from, to)));
}

bool Mst::calc() {
    if (!calculated) {
        //Sort the rooms from smallest to biggest
        sort(pq.begin(), pq.end());

        int num = 1;
        while (!pq.empty()) {
            int distance = pq.begin()->first;

            Room *from = pq.begin()->second.first;
            Room *to = pq.begin()->second.second;

            int fromLevel = find(from);
            int toLevel = find(to);

            pq.erase(pq.begin());

            if (num < size && ((toLevel == -1 && fromLevel == -1) || fromLevel != toLevel)) {
                if (toLevel == -1 && fromLevel == -1) {
                    levels[++currentLevel] = vector<Room *>();
                    levels[currentLevel].push_back(to);
                    levels[currentLevel].push_back(from);
                    typeLevels[to] = currentLevel;
                    typeLevels[from] = currentLevel;
                } else if (toLevel == -1 && fromLevel >= 0) {
                    typeLevels[to] = fromLevel;
                    levels[fromLevel].push_back(to);
                } else if (fromLevel == -1 && toLevel >= 0) {
                    typeLevels[from] = toLevel;
                    levels[toLevel].push_back(from);
                } else if (fromLevel >= 0 && toLevel >= 0) {
                    int copyFrom;
                    int moveTo;
                    if (fromLevel > toLevel) {
                        copyFrom = fromLevel;
                        moveTo = toLevel;
                    } else {
                        copyFrom = toLevel;
                        moveTo = fromLevel;
                    }

                    for (auto it = levels[copyFrom].begin(); it != levels[copyFrom].end(); it++) {
                        typeLevels[it.operator*()] = moveTo;
                        //levels[moveTo].push_back(it.operator*());
                    }
                    levels[moveTo].insert(levels[moveTo].end(), levels[copyFrom].begin(), levels[copyFrom].end());
                    levels.erase(levels.find(copyFrom));
                } else {
                    return false;
                }

                minimalSpanningTreePaths[make_pair(to, from)] = distance;
                minimalSpanningTreePaths[make_pair(from, to)] = distance;
                num++;
            } else {
                excludedSanningTreePaths[make_pair(to, from)] = distance;
            }
        }

        calculated = true;
    }

    return true;
}

bool Mst::isInSpanningTree(Room *from, Room *to) {
    return minimalSpanningTreePaths.find(make_pair(from, to)) != minimalSpanningTreePaths.end();
}

bool Mst::collapse(int num) {
    if (num <= excludedSanningTreePaths.size()) {
        for (auto it = excludedSanningTreePaths.begin(); it != excludedSanningTreePaths.end() && num > 0; it++, num--) {
            Room *from = it.operator*().first.first;
            Room *to = it.operator*().first.second;

            from->removeEdge(to);
            to->removeEdge(from);
        }

        return true;
    }

    return false;
}
