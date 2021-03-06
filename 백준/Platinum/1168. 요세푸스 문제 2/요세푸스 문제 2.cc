#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
#define debug(x)  std::cout << "[Debug] " << #x << " is " << x << '\n'
#define endl '\n'
typedef long long ll;

struct SegTree{
    int N, size;
    vector<int> node;
    SegTree(int n){
        N = n;
        size = 1;
        while(size < n) size *= 2;
        size *= 2;
        node.resize(size + 1);
    }
    void construct(){
        for(int i = size/2; i < N + size/2; i++)
            node[i] = 1;
        for(int i = size/2 - 1; i > 0; i--)
            node[i] = node[i*2] + node[i*2+1];
    }
    void insert(int idx, int val = 1){
        idx += size/2;
        node[idx] += val;
        idx /= 2;
        while(idx > 0){
            node[idx] = node[idx*2] + node[idx*2 + 1];
            idx /= 2;
        }
    }
    int Kth(int k){
        int curr = 1;
        while(curr < size/2){
            if(node[curr*2] < k){
                // go right child
                k -= node[curr*2];
                curr *= 2;
                curr++;
            }else{
                curr *= 2;
            }
        }
        return curr - size/2;
    }
    int sum(int s, int e){
        int l = s + size/2;
        int r = e + size/2;
        int ret = 0;
        while(l <= r){
            if(l % 2) ret += node[l++];
            if(!(r % 2)) ret += node[r--];
        }
        return ret;
    }
    void debugLeafs(){
        cout << "[Debug] ";
        for(int i = size/2; i < N + size/2; i ++)
            cout << node[i] << " ";
        cout << endl;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, K; cin >> N >> K;
    SegTree tree(N);

    tree.construct();
    int ret = 0;
    int index = 1;
    cout << "<";
    for(int i = 0; i < N; i++){
        int survivals = N - i; // 남은 사람 수
        index += K - 1; // 이전 사람을 제거했으므로, K-1번 째 사람을 찾아야 
        // "이전에 제거한 사람을 포함해서 K번 째" 사람을 찾을 수 있음
        
        // 원순열 배열을 풀어헤쳐서, 길이가 N인 여러 개의 배열이 연속적으로 이어져있다고 생각해보자.
        // index는 그냥 다음 배열로 계속 늘려나가되, 도착한 위치에 남아있는 사람 수에 맞춰 보정을 해줌.
        // (이미 죽은 사람은 건너뛰어야 하므로)
        index = (index % survivals == 0)? survivals : index % survivals; 

        ret = tree.Kth(index);
        tree.insert(ret, -1);
        
        cout << (ret + 1);
        if(i == N-1) cout << ">";
        else cout << ", ";
    }

    return 0;
}
