#include <iostream>
#include <string>
#include <vector>
#include <cctype>

static int valeurHex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return c - 'A' + 10;
}

static std::vector<int> decoder(const std::string &s) {
    std::vector<int> octets;
    if (s == "-") return octets;
    for (size_t i = 0; i + 1 < s.size(); i += 2)
        octets.push_back(valeurHex(s[i]) * 16 + valeurHex(s[i + 1]));
    return octets;
}

// vrai si l'octet i existe et vaut v (un octet absent fait echouer la regle)
static bool est(const std::vector<int> &b, size_t i, int v) {
    return b.size() > i && b[i] == v;
}

static bool commence(const std::vector<int> &b, size_t debut, const std::vector<int> &motif) {
    for (size_t k = 0; k < motif.size(); k++)
        if (!est(b, debut + k, motif[k])) return false;
    return true;
}

static std::string reconnaitre(long long taille, const std::vector<int> &b) {
    if (taille < 4) return "";
    if (taille >= 8 && commence(b, 0, {0x89, 0x50, 0x4E, 0x47})) return "PNG";
    if (commence(b, 0, {0xFF, 0xD8, 0xFF})) return "JPEG";
    if (commence(b, 0, {0x42, 0x4D})) return "BMP";
    if (commence(b, 0, {0x71, 0x6F, 0x69, 0x66})) return "QOI";
    if (commence(b, 0, {0x47, 0x49, 0x46, 0x38})) return "GIF";
    if (est(b, 0, 0) && est(b, 1, 0) && (est(b, 2, 1) || est(b, 2, 2)) && est(b, 3, 0)) return "ICO";
    if (taille >= 10 && commence(b, 0, {0x23, 0x3F})) return "HDR";
    if (commence(b, 0, {0x76, 0x2F, 0x31, 0x01})) return "EXR";
    if (est(b, 0, 0x50) && b.size() > 1 && b[1] >= 0x31 && b[1] <= 0x36) {
        int chiffre = b[1];
        if (chiffre == 0x31 || chiffre == 0x34) return "PBM";
        if (chiffre == 0x32 || chiffre == 0x35) return "PGM";
        return "PPM";
    }
    if (taille >= 18 && b.size() > 2) {
        int t = b[2];
        if (t == 0 || t == 1 || t == 2 || t == 3 || t == 9 || t == 10 || t == 11) return "TGA";
    }
    // SVG : on saute le BOM puis les blancs
    size_t i = 0;
    if (commence(b, 0, {0xEF, 0xBB, 0xBF})) i = 3;
    while (i < b.size() && (b[i] == 0x20 || b[i] == 0x09 || b[i] == 0x0A || b[i] == 0x0D)) i++;
    if (commence(b, i, {0x3C, 0x3F, 0x78, 0x6D, 0x6C}) || commence(b, i, {0x3C, 0x73, 0x76, 0x67}))
        return "SVG";
    return "";
}

static bool extensionJuste(const std::string &format, const std::string &ext) {
    if (format == "PNG")  return ext == "png";
    if (format == "JPEG") return ext == "jpg" || ext == "jpeg";
    if (format == "BMP")  return ext == "bmp";
    if (format == "QOI")  return ext == "qoi";
    if (format == "GIF")  return ext == "gif";
    if (format == "ICO")  return ext == "ico" || ext == "cur";
    if (format == "HDR")  return ext == "hdr";
    if (format == "EXR")  return ext == "exr";
    if (format == "PBM")  return ext == "pbm";
    if (format == "PGM")  return ext == "pgm";
    if (format == "PPM")  return ext == "ppm";
    if (format == "TGA")  return ext == "tga";
    if (format == "SVG")  return ext == "svg";
    return false;
}

int main() {
    int n = 0;
    std::cin >> n;
    int lus = 0, mensonges = 0, refuses = 0;

    for (int i = 0; i < n; i++) {
        std::string nom, hex;
        long long taille;
        std::cin >> nom >> taille >> hex;

        std::string ext;
        size_t point = nom.rfind('.');
        if (point != std::string::npos) {
            ext = nom.substr(point + 1);
            for (char &c : ext) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }

        std::string format = reconnaitre(taille, decoder(hex));
        if (format.empty()) {
            std::cout << nom << " REFUSE\n";
            refuses++;
        } else if (extensionJuste(format, ext)) {
            std::cout << nom << " " << format << " OK\n";
            lus++;
        } else {
            std::cout << nom << " " << format << " MENT\n";
            lus++;
            mensonges++;
        }
    }

    std::cout << "LUS " << lus << "\n";
    std::cout << "MENSONGES " << mensonges << "\n";
    std::cout << "REFUSES " << refuses << "\n";
    return 0;
}
