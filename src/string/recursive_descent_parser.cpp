string expr;
int pos;
int expression();
int term();
int factor();
int expression(){
    int ret = term();
    while(1){
        if(expr[pos] == '+'){
            pos++;
            ret += term();
        }else if(expr[pos] == '-'){
            pos++;
            ret -= term();
        }else break;
    }
    return ret;
}

int term(){
    int ret = factor();
    while(1){
        if(expr[pos] == '*'){
            pos++;
            ret *= factor();
        }else if(expr[pos] == '/'){
            pos++;
            ret /= factor();
        }else break;
    }
    return ret;
}

int factor(){
    int ret = 0;
    if(expr[pos] == '('){
        pos++;
        ret = expression();
        pos++;
        return ret;
    }
    while(isdigit(expr[pos])){
        ret *= 10;
        ret += expr[pos]-'0';
        pos++;
    }
    return ret;
}

int main(){
    while(cin >> expr){
        pos = 0;
        cout << expression() << endl;
    }
    return 0;
}
