// Return the longest palindrome substring length in a string //
int manacher(string s) {
    string newS = "#";
    for (auto ch : s) {
        newS += ch;
        newS += "#";
    }

    int n = newS.length();
    int LPS[n] = {};
    int C = 0, R = 0;

    for (int i = 0; i < n; i++) {
        int imir = 2 * C - i;

        if (R > i) {
            LPS[i] = min(R - i, LPS[imir]);
        } else {
            LPS[i] = 0;
        }

        while (((i + 1 + LPS[i]) < n) && ((i - 1 - LPS[i]) >= 0) && newS[i + 1 + LPS[i]] == newS[i - 1 - LPS[i]]) {
            LPS[i] += 1;
        }

        if (i + LPS[i] > R) {
            C = i;
            R = i + LPS[i];
        }
    }

    int maxL = 0;
    for (int i = 0; i < n; i++) {
        maxL = max(maxL, LPS[i]);
    }

    return maxL;
}