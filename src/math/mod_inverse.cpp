int mod_inverse (int a, int m) {
    int x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}