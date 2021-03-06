// CLRS3rd Section 16.3
// longwen6@gmail.com @ 2015-08-14

#include "IOUtil.hpp"
#include "AlgoUtil.hpp"
#include "Tree.hpp"
#include <queue>
using namespace std;

// letter and frequence
using Data = pair<char, int>;

using Node = BinaryTreeNode<Data>;

struct NodePtrFreqGreater {
  bool operator()(const Node* l, const Node* r) {
    return r->val.second < l->val.second;
  }
};
using PriorityQueue = priority_queue<Node*, vector<Node*>, NodePtrFreqGreater>;

Node* buildCodeTree(PriorityQueue& pq) {
  const int size = pq.size();
  for (int i = 1; i < size; ++i) {
    Node* l, *r;
    l = pq.top(), pq.pop();
    r = pq.top(), pq.pop();
    pq.push(new Node({'*', l->val.second + r->val.second}, l, r));
  }
  return pq.top();
}

void generateCode(const Node* root, string code,
                  vector<pair<char, string>>& res) {
  if (isLeaf(root)) {
    res.push_back(make_pair(root->val.first, move(code)));
    return;
  }
  if (root->left) generateCode(root->left, code + '0', res);
  if (root->right) generateCode(root->right, code + '1', res);
}

vector<pair<char, string>> generateHuffmanCode(const vector<Data>& vd) {
  PriorityQueue pq;
  for (auto const& e : vd) pq.push(new Node(e));
  auto tree = buildCodeTree(pq);
  vector<pair<char, string>> res;
  generateCode(tree, "", res);
  return res;
}

int main() {
  vector<Data> vd{
      {'a', 45}, {'b', 13}, {'c', 12}, {'d', 16}, {'e', 9}, {'f', 5}};
  auto encoding = generateHuffmanCode(vd);
  sort(encoding, [](auto l, auto r) { return l.first < r.first; });
  for (auto const& e : encoding) cout << e << endl;
}
