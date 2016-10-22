#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* читаем n=200к (m=32) строк в сет (т.е. без дубликатов)
 * создаем dsu и запускаемся от каждой строки
 *  - находим всех соседей C_n^k = m^2
 *  - проверяем их нахождение в сете и если они там есть,
 *    то нужно соединить деревья dsu
 *  - ответ -- количество компонент в сете
 */

using Bit_string = std::vector<bool>;
using Bit_strings_set = std::unordered_set<Bit_string>;
using Parents = std::unordered_map<Bit_string, Bit_string>;
using Children = std::unordered_map<Bit_string, std::vector<Bit_string>>;
using Neighbours = std::unordered_set<Bit_string>;

class Dsu {
  public:
    Dsu(const Bit_strings_set& strings) :
        strings_(strings) {};
    void Solve();

    int count;

  private:
    void MakeSet(const Bit_string& s);
    Bit_string FindSet(const Bit_string& s);
    void UnionSets(Bit_string s1, Bit_string s2);
    void ChangeParent(Bit_string s1, Bit_string s2);
    Neighbours FindNeighbours(const Bit_string& s);

    Bit_strings_set strings_;
    Parents parents_;
    Children children_;
};

void Dsu::MakeSet(const Bit_string& s) {
    children_[s].push_back(s);
    parents_.insert({s, s});
}

Bit_string Dsu::FindSet(const Bit_string& s) {
    return parents_.find(s);
}

void Dsu::UnionSets(Bit_string s1, Bit_string s2) {
    s1 = FindSet(s1);
    s2 = FindSet(s2);
    if (s1 != s2) {
        ChangeParent(s1, s2);
    }
}

void Dsu::ChangeParent(Bit_string s1, Bit_string s2) {
    if (children_[s1].size() < children_[s2].size()) {
        auto s = children_[s1].back();
        children_[s1].pop_back();
        parents_[s] = s2;
        children_[s2].push_back(s);
    } else {
        auto s = children_[s2].back();
        children_[s2].pop_back();
        parents_[s] = s1;
        children_[s1].push_back(s);
    }
}

Neighbours Dsu::FindNeighbours(const Bit_string& s) {
    Neighbours neighbours;
    for (size_t i = 0; i != s.end()l ++i) {
        for (size_t j = i; j != s.end(); ++j) {
            size_t count = 0;
            std::string temp_string = "";
            while (count != s.size()) {
                if (count == i) {
                    if (s[i] == 0)
                        temp_string += 1;
                    else
                        temp_string += 0;
                } else if (count == j) {
                    if (s[j] == 0)
                        temp_string += 1;
                    else
                        temp_string += 0;
                } else {
                    temp_string += s[count];
                }
            }
            neighbours.insert()
        }
    }
    return neighbours;
}

void Dsu::Solve() {
    parents_.clear();
    children_.clear();
    for (auto iter = strings_.begin(); iter != strings_.end(); ++iter) {
        MakeSet(*iter);
    }
    for (auto iter = strings_.begin(); iter != strings_.end(); ++iter) {
        auto neighbours = FindNeighbours(*iter);
        for (auto neighbours_iter = neighbours.begin();
             neighbours_iter != neighbours.end();
             ++neighbours_iter) {
            if (FindSet(*neighbours_iter) != FindSet(*iter)) {
                UnionSets(*neighbours_iter, *iter);
            }
        }
    }
}

class Clusters {
  public:
    void Read();
    void Clusterize();

  private:
    Bit_strings_set strings_;
};

void Clusters::Read() {
    strings_.clear();
    int number_of_strings, number_of_bits;
    std::cin >> number_of_strings >> number_of_bits;
    for (int i = 0; i != number_of_strings; ++i) {
        std::string temp_string;
        std::cin >> temp_string;
        std::vector<bool> temp_vector;
        for (auto digit : temp_string) {
            temp_vector.push_back((digit == '1'));
        }
        strings_.insert(temp_vector);
    }
}

void Clusters::Clusterize() {
    Dsu dsu(strings_);
    dsu.Solve();
    std::cout << dsu.count;
}

int main() {
    Clusters clusters;
    clusters.Read();
    clusters.Clusterize();
}
