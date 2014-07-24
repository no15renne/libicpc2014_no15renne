    #include <algorithm>
    using namespace std;
    struct S{
      int n;
    //関数　構造体内
      bool operator< (const S &s) const {
      return s.n < n;
      }
    };
     
    // 関数 構造体外
    bool operator<(const S &s, const S &t){
      return s.n < t.n;
    }
     
    // 関数オブジェクト
    struct cmp1{
      bool operator()(const S &s, const S &t){
      return s.n < t.n;
      }
    };
     
    // 比較関数
    bool cmp2(const S &s, const S &t){
      return s.n < t.n;
    }
     
    int main(){
      S a[10];
      sort(a,a+10);
      sort(a,a+10,cmp1());
      sort(a,a+10,cmp2);
    }

