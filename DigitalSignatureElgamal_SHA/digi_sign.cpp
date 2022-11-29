#include <bits/stdc++.h>
#include <gmp.h>

using namespace std;


string msg, hex_msg;
vector<string> w;

vector<string> k = {
    "428a2f98d728ae22", "7137449123ef65cd", "b5c0fbcfec4d3b2f", "e9b5dba58189dbbc",
    "3956c25bf348b538", "59f111f1b605d019", "923f82a4af194f9b", "ab1c5ed5da6d8118",
    "d807aa98a3030242", "12835b0145706fbe", "243185be4ee4b28c", "550c7dc3d5ffb4e2",
    "72be5d74f27b896f", "80deb1fe3b1696b1", "9bdc06a725c71235", "c19bf174cf692694",
    "e49b69c19ef14ad2", "efbe4786384f25e3", "0fc19dc68b8cd5b5", "240ca1cc77ac9c65",
    "2de92c6f592b0275", "4a7484aa6ea6e483", "5cb0a9dcbd41fbd4", "76f988da831153b5",
    "983e5152ee66dfab", "a831c66d2db43210", "b00327c898fb213f", "bf597fc7beef0ee4",
    "c6e00bf33da88fc2", "d5a79147930aa725", "06ca6351e003826f", "142929670a0e6e70",
    "27b70a8546d22ffc", "2e1b21385c26c926", "4d2c6dfc5ac42aed", "53380d139d95b3df",
    "650a73548baf63de", "766a0abb3c77b2a8", "81c2c92e47edaee6", "92722c851482353b",
    "a2bfe8a14cf10364", "a81a664bbc423001", "c24b8b70d0f89791", "c76c51a30654be30",
    "d192e819d6ef5218", "d69906245565a910", "f40e35855771202a", "106aa07032bbd1b8",
    "19a4c116b8d2d0c8", "1e376c085141ab53", "2748774cdf8eeb99", "34b0bcb5e19b48a8",
    "391c0cb3c5c95a63", "4ed8aa4ae3418acb", "5b9cca4f7763e373", "682e6ff3d6b2b8a3",
    "748f82ee5defb2fc", "78a5636f43172f60", "84c87814a1f0ab72", "8cc702081a6439ec",
    "90befffa23631e28", "a4506cebde82bde9", "bef9a3f7b2c67915", "c67178f2e372532b",
    "ca273eceea26619c", "d186b8c721c0c207", "eada7dd6cde0eb1e", "f57d4f7fee6ed178",
    "06f067aa72176fba", "0a637dc5a2c898a6", "113f9804bef90dae", "1b710b35131c471b",
    "28db77f523047d84", "32caab7b40c72493", "3c9ebe0a15c9bebc", "431d67c49c100d4c",
    "4cc5d4becb3e42b6", "597f299cfc657e2a", "5fcb6fab3ad6faec", "6c44198c4a475817"
    
};


vector<string> H = {
    "6a09e667f3bcc908", "bb67ae8584caa73b", "3c6ef372fe94f82b", "a54ff53a5f1d36f1", 
    "510e527fade682d1", "9b05688c2b3e6c1f", "1f83d9abfb41bd6b", "5be0cd19137e2179"
};


string get_str_to_hex(string str) {
    string ans = "";
    for (int i = 0; i < str.length(); i++) {
        stringstream ss;
        ss << hex << (int)(str[i]);
        string temp;
        ss >> temp;
        ans += temp;
    }
    return ans;
}


string hex_to_binary(string str) {
    string ans = "";
    for (int i = 0; i < str.length(); i++) {
        int num = ((str[i] >= '0' && str[i] <= '9') ? (str[i] - '0') : (str[i] - 'a' + 10));
        string temp = "";
        for (int j = 0; j < 4; j++) {
            if (num % 2)
                temp = "1" + temp;
            else
                temp = "0" + temp;
            num /= 2;
        }
        ans += temp;
    }
    return ans;
}

string binary_to_hex(string str) {
    string ans = "";
    for (int i = 0; i < str.length(); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            int temp = (str[i + j] == '1' ? 1 : 0);
            val = (val * 2) + temp;
        }
        char ch;
        if (val <= 9)
            ch = '0' + val;
        else
            ch = 'a' + (val - 10);
        ans += ch;
    }
    return ans;
}

string get_Message(string msg) {
    hex_msg = get_str_to_hex(msg);

    int bit_length = msg.length() * 8;

    int bit_length_mod = bit_length % 1024;
    bit_length_mod = 896 - bit_length_mod;
    bit_length_mod = (bit_length_mod + 1024) % 1024;

    string final_msg = hex_msg;
    final_msg += "8";
    bit_length_mod /= 4;
    for (int i = 0; i < bit_length_mod - 1; i++) {
        final_msg += "0";
    }

    stringstream ss;
    ss << hex << bit_length;
    string temp;
    ss >> temp;

    for (int i = 0; i < 32 - temp.length(); i++) 
        final_msg += "0";

    final_msg += temp;

    return final_msg;
}

string ROTR(string x, int k) {
    int size = x.length();
    for (int i = 0; i < k; i++) {
        char ch = x[x.length() - 1];
        x = ch + x;
        x = x.substr(0, size);
    }
    return x;
}

string SHR(string x, int k) {
    int size = x.length();
    for (int i = 0; i < k; i++) {
        x = "0" + x;
        x = x.substr(0, size);
    }
    return x;
}

string add_mod(string a, string b) {
    string c = "";
    int carry = 0;
    for (int i = a.length() - 1; i >= 0; i--) {
        char val1 = a[i] - '0', val2 = b[i] - '0';
        int sum = val1 + val2 + carry;
        if (sum % 2) {
            c = "1" + c;
        }
        else
            c = "0" + c;
        carry = sum / 2;
    }
    string ans = "";
    for (int i = c.length() - 64; i < c.length(); i++) {
        ans += c[i];
    }
    return ans;
}

string XOR(string a, string b) {
    string c = "";
    int i = 0, j = 0;
    while (i < a.length() || j < b.length()) {
        char ch1 = '0', ch2 = '0';
        if (i < a.length())
            ch1 = a[i];
        if (j < b.length())
            ch2 = b[j];
        i++;
        j++;
        if (ch1 == ch2)
            c += "0";
        else
            c += "1";
    }
    return c;
}

vector<string> get_msg_schedule(string final_msg) {
    vector<string> w(80);
    for (int i = 0; i <= 15; i++) {
        w[i] = final_msg.substr(i * 16, 16);
        w[i] = hex_to_binary(w[i]);
    }

    string temp = hex_to_binary(w[0]);

    for (int i = 16; i < 80; i++) {
        string s1, s2, s3, s4;
        string x = (w[i - 2]);
        string rotr19_x = ROTR(x, 19), rotr61_x = ROTR(x, 61), shr6_x = SHR(x, 6);
        s1 = XOR(rotr19_x, rotr61_x);
        s1 = XOR(s1, shr6_x);
        s2 = w[i - 7];
        x = (w[i - 15]);
        string rotr1_x = ROTR(x, 1), rotr8_x = ROTR(x, 8), shr7_x = SHR(x, 7);
        s3 = XOR(rotr1_x, rotr8_x);
        s3 = XOR(s3, shr7_x);
        s4 = w[i - 16];

        w[i] = add_mod(s1, s2);
        w[i] = add_mod(w[i], s3);
        w[i] = add_mod(w[i], s4);
    }

    return w;
}

string func_and(string a, string b) {
    string c = "";
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '1' && b[i] == '1')
            c += "1";
        else
            c += "0";
    }
    return c;
}

string func_not(string a) {
    string c = "";
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '0')
            c += "1";
        else
            c += "0";
    }
    return c;
}

string func_or(string a, string b) {
    string c = "";
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '1' || b[i] == '1')
            c += "1";
        else
            c += "0";
    }
    return c;
}

string func_ch(string e, string f, string g) {
    string t1 = func_and(e, f);
    string t2 = func_not(e);
    string t3 = func_and(t2, g);
    return XOR(t1, t3);
}

string func_maj(string a, string b, string c) {
    string t1 = func_and(a, b);
    string t2 = func_and(a, c);
    string t3 = func_and(b, c);

    string t4 = XOR(t1, t2);
    t4 = XOR(t4, t3);
    return t4;
}

string summasion0(string a) {
    string t1 = ROTR(a, 28), t2 = ROTR(a, 34), t3 = ROTR(a, 39);
    string ans = XOR(t1, t2);
    ans = XOR(ans, t3);
    return ans;
}
string summasion1(string e) {
    string t1 = ROTR(e, 14), t2 = ROTR(e, 18), t3 = ROTR(e, 41);
    string ans = XOR(t1, t2);
    ans = XOR(ans, t3);
    return ans;
}



string sha_algo(string final_msg) {


    for (int i = 0; i < 8; i++)
        H[i] = hex_to_binary(H[i]);
    for (int i = 0; i < 80; i++)
        k[i] = hex_to_binary(k[i]);

    for (int i = 0; i < final_msg.length(); i += 1024) {
        string str = final_msg.substr(i * 1024, 1024);
        vector<string> w = get_msg_schedule(str);
        string a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
        for (int j = 0; j < 80; j++) {
            string ch_efg = func_ch(e, f, g), maj_abc = func_maj(a, b, c), sum_0 = summasion0(a), sum_1 = summasion1(e);

            string t1 = add_mod(h, ch_efg);
            t1 = add_mod(t1, sum_1);
            t1 = add_mod(t1, w[j]);
            t1 = add_mod(t1, k[j]);

            string t2 = add_mod(sum_0, maj_abc);

            h = g;
            g = f;
            f = e;
            e = add_mod(d, t1);
            d = c;
            c = b;
            b = a;
            a = add_mod(t1, t2);
        }
        H[0] = add_mod(H[0], a);
        H[1] = add_mod(H[1], b);
        H[2] = add_mod(H[2], c);
        H[3] = add_mod(H[3], d);
        H[4] = add_mod(H[4], e);
        H[5] = add_mod(H[5], f);
        H[6] = add_mod(H[6], g);
        H[7] = add_mod(H[7], h);
    }

    string ans = "";
    for (int i = 0; i < 8; i++) {
        ans += binary_to_hex(H[i]);
    }
    return ans;
}


gmp_randstate_t state;
unsigned long seed;

void rand_init() {
    gmp_randinit_mt(state);
    seed = time(NULL);
    gmp_randseed_ui(state, seed);
}

void get_p_alpha(mpz_t p, mpz_t alpha, int bits) {
    mpz_t temp, q, r, t1, t2;
    int result = 0;
    mpz_inits(temp, q, r, t1, t2, NULL);
    while (!result) {
        int res1 = 0;
        while (!res1) {
            mpz_rrandomb(p, state, bits);
            res1 = mpz_probab_prime_p(p, 30);
        }
        mpz_sub_ui(temp, p, 1);
        mpz_fdiv_q_ui(temp, temp, 2);
        result = mpz_probab_prime_p(temp, 30);
        if (!result) {
            mpz_set_ui(q, 2);
            mpz_set(r, temp);
        }
    }


    int flag = 0;
    while (!flag) {
        mpz_urandomm(temp, state, p);
        while (mpz_cmp_ui(temp, 1) <= 0 || mpz_cmp(temp, p) >= 0) {
            mpz_urandomm(temp, state, p);
        }
        mpz_powm(t1, temp, q, p);
        mpz_powm(t2, temp, r, p);
        if (mpz_cmp_ui(t1, 1) != 0 && mpz_cmp_ui(t2, 1) != 0) {
            flag = 1;
        }
    }
    mpz_set(alpha, temp);
}

void get_public_private_key(mpz_t x, mpz_t y, mpz_t q, mpz_t alpha) {
    mpz_t temp, q_1;

    mpz_inits(temp, q_1, NULL);

    mpz_sub_ui(q_1, q, 1);
    mpz_urandomm(temp, state, q);
    while (mpz_cmp_ui(temp, 1) <= 0 || mpz_cmp(temp, q_1) >= 0) {
        mpz_urandomm(temp, state, q);
    }

    mpz_set(x, temp);
    mpz_powm(y, alpha, x, q);

}

void convert_hex_string_to_mpz_t(string m, mpz_t num) {
    mpz_set_ui(num, 0);
    for (int i = 0; i < m.length(); i++) {
        int val = ((m[i] >= '0' && m[i] <= '9') ? m[i] - '0' : m[i] - 'a' + 10);
        mpz_mul_ui(num, num, 16);
        mpz_add_ui(num, num, val);
    }
}

void GCD(mpz_t g, mpz_t A, mpz_t B) {
    if (mpz_cmp_ui(A, 0) == 0)
        mpz_set(g, B);
    else if (mpz_cmp_ui(B, 0) == 0)
        mpz_set(g, A);
    else {
        mpz_t a, b, t;
        mpz_inits(a, b, t, NULL);
        mpz_set(a, A);
        mpz_set(b, B);

        while (mpz_cmp_ui(b, 0)) {
            mpz_set(t, b);
            mpz_mod(b, a, b);
            mpz_set(a, t);
        }
        mpz_set(g, a);
    }
}


void get_sign_pair(mpz_t s1, mpz_t s2, mpz_t q, mpz_t m, mpz_t alpha, mpz_t xa) {
    mpz_t k, q_1, inv_k, temp, t1;
    mpz_inits(k, q_1, inv_k, temp, NULL);
    
    mpz_sub_ui(q_1, q, 1);
    
    mpz_set_ui(t1, 0);
    while (mpz_cmp_ui(t1, 1)) {
        mpz_urandomm(k, state, q);
        while (mpz_cmp_ui(k, 1) <= 0 && mpz_cmp(k, q_1) >= 0) {
            mpz_urandomm(k, state, q);
        }
        GCD(t1, k, q_1);
    }

    mpz_powm(s1, alpha, k, q);

    mpz_invert(inv_k, k, q_1);

    mpz_mul(temp, xa, s1);
    mpz_sub(temp, m, temp);
    mpz_mod(temp, temp, q_1);

    mpz_mul(temp, inv_k, temp);
    mpz_mod(temp, temp, q_1);
    mpz_set(s2, temp);


}

bool verifying_sign_pair(mpz_t s1, mpz_t s2, mpz_t ya, mpz_t alpha, mpz_t m, mpz_t q) {
    mpz_t v1, v2, temp;
    mpz_inits(v1, v2, NULL);


    mpz_powm(v1, alpha, m, q);

    mpz_powm(temp, s1, s2, q);
    mpz_powm(v2, ya, s1, q);

    mpz_mul(v2, v2, temp);
    mpz_mod(v2, v2, q);

    return mpz_cmp(v1, v2) == 0;
}


int main() {

    rand_init();

    cout << "Enter the string: ";
    getline(cin, msg);



    string final_msg = get_Message(msg);
    string h_m = sha_algo(final_msg);
    // printf("hash value: %s\n", h_m);
    cout << "Hash value : " << h_m << endl;


    mpz_t m, q, alpha, xa, ya, s1, s2;
    int bits = 1024;

    mpz_inits(m, q, alpha, xa, ya, s1, s2, NULL);

    convert_hex_string_to_mpz_t(h_m, m);


    // get_p_alpha(q, alpha, bits);
    get_p_alpha(q, alpha, bits);

    gmp_printf("\nq : %Zd\n\nalpha : %Zd\n\n", q, alpha);

    // USER A generates public key and private key
    get_public_private_key(xa, ya, q, alpha);


    // getting signature pair
    get_sign_pair(s1, s2, q, m, alpha, xa);

    gmp_printf("S1: %Zd\nS2: %Zd\n", s1, s2);

    if (verifying_sign_pair(s1, s2, ya, alpha, m, q)) {
        printf("Signature verified\n");
    }
    else {
        printf("Signature not verified\n");
    }

    return 0;
}