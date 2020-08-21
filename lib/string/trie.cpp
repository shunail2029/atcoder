#include <string>
#include <vector>

class Trie {
    private:
        int val;
        Trie *parent;
        std::vector<Trie *> children;
    public:
        Trie(Trie *parent = nullptr) : parent(parent), children(26, nullptr) {}
        ~Trie() {
            for (Trie *ptr : children) delete ptr;
        }
        Trie *find(const std::string &str) {
            Trie *ptr = this;
            for (char c : str) {
                int idx = c - 'a';
                if (ptr->children[idx] == nullptr) ptr->children[idx] = new Trie(ptr);
                ptr = ptr->children[idx];
            }
            return ptr;
        }
        void insert(const std::string &str, int val) {
            Trie *ptr = this->find(str);
            ptr->val = val;
        }
        int getVal() const { return val; }
};
