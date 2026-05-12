#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

class Node {
    public:
        char symbol;
        int freq;
        Node* left;
        Node* right;
        Node(int freq, char symbol = ' ') {
            this->left = nullptr;
            this->right = nullptr;
            this->symbol = symbol;
            this->freq = freq;
        }
        void free(Node* node) {
            if (!node) return;
            free(node->left);
            free(node->right);
            delete node;
        }
};

struct Cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

class Huffman {
    public:
        string word;
        string encoded;
        map<char, int> freq;
        map<char, string> table;
        priority_queue<Node*, vector<Node*>, Cmp> queue;
        Node* root = new Node(0);

        void calc_freq(string s) {
            for (char c : s) freq[c]++;
        }
        void build_queue() {
            for (auto [c, f] : freq) {
                queue.push(new Node(f, c));
            }
        }
        void build_tree() {
            if (queue.size() == 1) {
                Node* only = queue.top(); queue.pop();
                Node* parent = new Node(only->freq);
                parent->left = only;
                queue.push(parent);
            }
            while (queue.size() > 1) {
                Node* left = queue.top(); queue.pop();
                Node* right = queue.top(); queue.pop();
                Node* parent = new Node(left->freq + right->freq);
                parent->left = left;
                parent->right = right;
                queue.push(parent);
            }
        }
        void build_table(Node* node, string prefix) {
            if (node == nullptr) return;
            if (!node->left && !node->right) {
                table[node->symbol] = prefix;
                return;
            }
            build_table(node->left, prefix + "1");
            build_table(node->right, prefix + "0");
        }

        Huffman(string word) {
            this->word = word;
            calc_freq(word);
            build_queue();
            build_tree();
            root = queue.top();
            build_table(root, "");
        }
        ~Huffman() {
            root->free(root);
        }
        string encode() {
            string output = "";
            for (char c : word) output += table[c];
            encoded = output;
            return output;
        }
        string decode() {
            string output = "";
            Node* current = root;
            for (char b : encoded) {
                if (b == '0') current = current->right;
                else current = current->left;
                if (!current->left && !current->right) {
                    output += current->symbol;
                    current = root;
                }
            }
            return output;
        }
};

int main() {
    string word = "banana";
    Huffman hf(word);
    cout << hf.encode() << endl;
    cout << hf.decode() << endl;
    return 0;
}