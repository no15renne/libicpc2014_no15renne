enum FACE { TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT };
template <class T>
class dice {
    public:
        dice() {
            id[TOP] = 0; id[FRONT] = 1; id[LEFT] = 2;
            id[RIGHT] = 3; id[BACK] = 4; id[BOTTOM] = 5;
        }
        T& operator[] (FACE f) { return var[id[f]]; }
        const T& operator[] (FACE f) const { return var[id[f]]; }
        bool operator==(const dice<T>& b) const {
            const dice<T> &a = *this;
            return a[TOP] == b[TOP] && a[BOTTOM] == b[BOTTOM] &&
                a[FRONT] == b[FRONT] && a[BACK] == b[BACK] &&
                a[LEFT] == b[LEFT] && a[RIGHT] == b[RIGHT];
        }
        void roll_x() { roll(TOP, BACK, BOTTOM, FRONT); }
        void roll_y() { roll(TOP, LEFT, BOTTOM, RIGHT); }
        void roll_z() { roll(FRONT, RIGHT, BACK, LEFT); }
        vector<dice> all_rolls() {
            vector<dice> ret;
            for (int k = 0; k < 6; (k&1?roll_y():roll_x()),++k)
                for (int i = 0; i < 4; roll_z(), ++i)
                    ret.push_back(*this);
            return ret;
        }
        bool equivalent_to(const dice& di) {
            for (int k = 0; k < 6; (k&1?roll_y():roll_x()),++k)
                for (int i = 0; i < 4; roll_z(), ++i)
                    if (*this == di) return true;
            return false;
        }
    private:
        void roll(FACE a, FACE b, FACE c, FACE d) {
            T tmp = id[a];
            id[a] = id[b]; id[b] = id[c];
            id[c] = id[d]; id[d] = tmp;
        }
        T var[6];
        int id[6];
};
