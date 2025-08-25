#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <cctype>

std::string generate(int length) {
    const std::string lowers = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string symbols = "!@#$%^&*()-_=+[]{};:,<.>/?";
    const std::string all = lowers + uppers + digits + symbols;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, (int)all.size() - 1);

    std::string pw;
    pw.reserve(length);
    for (int i = 0; i < length; ++i) pw.push_back(all[dist(gen)]);
    return pw;
}

std::string strength(const std::string& pw) {
    bool hasL = false, hasU = false, hasD = false, hasS = false;
    for (char c : pw) {
        hasL = hasL || std::islower((unsigned char)c);
        hasU = hasU || std::isupper((unsigned char)c);
        hasD = hasD || std::isdigit((unsigned char)c);
        hasS = hasS || std::ispunct((unsigned char)c);
    }
    int score = (int)pw.size() >= 12;
    score += hasL + hasU + hasD + hasS; // 0..4
    if (score >= 4) return "Strong";
    if (score >= 3) return "Medium";
    return "Weak";
}

int main() {
    std::cout << "Length (e.g. 16): ";
    int len; std::cin >> len;
    std::string pw = generate(len);
    std::cout << "Password: " << pw << "\n";
    std::cout << "Strength: " << strength(pw) << "\n";

    std::cout << "Check your own password? (y/n): ";
    char ch; std::cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        std::cout << "Enter password: ";
        std::string user; std::cin >> user;
        std::cout << "Strength: " << strength(user) << "\n";
    }
    return 0;
}
