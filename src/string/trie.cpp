struct Trie {
    Trie *next[26];
    Trie () { fill(next, next + 26, (Trie *)0); }
};
