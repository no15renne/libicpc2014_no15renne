//H(C)=(c1b^(m-1)+c2b^(m-2)+...+cmb^0) mod h
//H(S[k+1..k+m])=(H(S[k..k+m-1])*b-skb^m+s(k+m)) mod h
const ull B = 100000007;
bool contain (string a, string b) {
    int al = a.length(), bl = b.length();
    if (al > bl) return false;
    ull t = 1;
    for (int i = 0; i < al; i++) t *= B;
    ull ah = 0, bh = 0;
    for (int i = 0; i < al; i++) ah = ah * B + a[i];
    for (int i = 0; i < al; i++) bh = bh * B + b[i];

    for (int i = 0; i + al <= bl; i++) {
        if (ah == bh) return true;
        if (i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
    }
    return false;
}
